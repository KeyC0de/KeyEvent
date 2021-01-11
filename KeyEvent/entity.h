#pragma once

#include <string>
#include <memory>


// An Entity class for message testing

// example message Payload1
// for `DataMessage`s - not used here
//struct Payload1
//{
//	int m_damage;
//	int m_heal;
//	std::string m_greeting;
//};

class Message;

class Entity
{
	std::string m_name;
	std::size_t m_id;
	int m_hp;
public:
	Entity( const std::string& name, int hp = 100 );

	int damage( int amount );
	int heal( int amount );
	void greet( const std::string& str ) const noexcept;
	std::string getName() const noexcept;
	std::size_t getId() const noexcept;
	void printInfo() const noexcept;

	void onMessageReceived( std::unique_ptr<class Message> msg );
	void sendMessage( class Message* msg ) const noexcept;
};