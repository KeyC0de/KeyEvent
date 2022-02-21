#include <iostream>
#include <thread>
#include <random>
#include <string>
#include "operation.h"
#include "message.h"
#include "message_queue_bus_dispatcher.h"
#include "entity.h"


int getRandomInt()
{
	std::random_device device;
	std::default_random_engine eng{ device() };
	std::uniform_int_distribution<int> distrInt( INT_MIN, INT_MAX );
	return distrInt( eng );
}

void doSomeWork()
{

}


int main()
{
	std::cout << std::boolalpha;

	std::thread{
		[]() { doSomeWork(); }
	}.join();
	std::thread{
		[]() { doSomeWork(); }
	}.join();

	// Example where the communication involves 2 entities
	using namespace std::string_literals;
	Entity e1{"Nikos"s};
	Entity e2{"Mary"s, 125};

	e1.printInfo();
	e2.printInfo();

	/// frame begins
	// Entities want to communicate with each other so they send messages

	// suppose we want e1 to send a "Damage" message to e2
	// you can create whatever type of Message::Type you want
	//	as well as call whichever function of e2 you want
	auto e1CallLater( Operation::setup( &Entity::damage,
		&e2,
		50 ) );
	// e1 creates the message to dispatch it
	std::vector<Entity*> recipients;
	recipients.push_back( &e2 );

	MessageCall* msg = new MessageCall{&e1,
		recipients,
		Message::Type::Damage,
		std::move( e1CallLater )};

	// send the message - it gets posted to the dispatcher which adds it to the MessageBus/EventQueue
	e1.sendMessage( msg );

	// check how many messages are in the queue
	auto& md = MessageDispatcher::getInstance();
	std::cout << "Size="s
		<< md.getSize()
		<< '\n';
	std::cout << "Capacity="s
		<< md.getCapacity()
		<< '\n';

	// dispatch messages
	md.dispatchAll();

	std::cout << "Size="s
		<< md.getSize()
		<< '\n';
	std::cout << "Capacity="s
		<< md.getCapacity()
		<< '\n';

	e1.printInfo();
	e2.printInfo();
	
	/// frame ends - clear the message queue
	md.clear();
	

#if defined _DEBUG && !defined NDEBUG
	while ( !getchar() );
#endif
	return EXIT_SUCCESS;
}