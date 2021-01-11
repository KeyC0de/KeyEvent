#include <iostream>
#include <thread>
#include <random>
#include <string>
#include "delayed_function.h"
#include "message.h"
#include "message_queue_bus_dispatcher.h"
#include "entity.h"
#include "global_manager.h"


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
	std::cout << std::boolalpha << '\n';

	std::thread{ []() { doSomeWork(); } }.join();
	std::thread{ []() { doSomeWork(); } }.join();

	// Example where the communication involves 2 entities
	using namespace std::string_literals;
	Entity e1{ "Nikos"s };
	Entity e2{ "Mary"s, 125 };

	e1.printInfo();
	e2.printInfo();

	/// frame begins
	// Entities want to communicate with each other so they send messages

	// suppose we want e1 to send a "Damage" message to e2
	// you can create whatever type of Message::Type you want
	//	as well as call whichever function of e2 you want
	auto e1CallLater( DelayedFunc::setup( &Entity::damage,
		&e2,
		50 ) );
	// e1 creates the message to dispatch it
	std::vector<Entity*> recipients;
	recipients.push_back( &e2 );

	MessageCall* msg = new MessageCall{ &e1,
		recipients,
		Message::Type::Damage,
		std::move( e1CallLater )};

	// send the message - it gets posted to the dispatcher
	e1.sendMessage( msg );

	// check how many messages are tin the queue
	std::cout << "Size="s << getGM.md.getSize() << '\n';
	std::cout << "Capacity="s << getGM.md.getCapacity() << '\n';

	// dispatch messages
	getGM.md.dispatchAll();

	std::cout << "Size="s << getGM.md.getSize() << '\n';
	std::cout << "Capacity="s << getGM.md.getCapacity() << '\n';

	e1.printInfo();
	e2.printInfo();
	
	/// frame ends - clear the message queue
	getGM.md.clear();
	

	std::system( "pause" );
	return 0;
}