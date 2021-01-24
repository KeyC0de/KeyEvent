#include <iostream>
#include "entity.h"
#include "message.h"
#include "delayed_function.h"
#include "message_queue_bus_dispatcher.h"


Entity::Entity( const std::string& name,
	int hp )
	:
	m_name{name},
	m_hp(hp)
{
	static std::size_t instanceId = 0;
	m_id = instanceId;
	++instanceId;
}

// Message Handling
int Entity::damage( int amount )
{
	m_hp -= std::abs( amount );
	return m_hp;
}

int Entity::heal( int amount )
{
	m_hp += std::abs( amount );
	return m_hp;
}

void Entity::greet( const std::string& str ) const noexcept
{
	std::cout << str;
}

std::string Entity::getName() const noexcept
{
	return m_name;
}

std::size_t Entity::getId() const noexcept
{
	return m_id;
}

void Entity::printInfo() const noexcept
{
	std::cout << "My name is "
		<< m_name
		<< " with health "
		<< m_hp
		<< '\n';
}

void Entity::onMessageReceived( std::unique_ptr<class Message> msg )
{
	auto pDataMsg = dynamic_cast<MessageCall*>( msg.get() );

	auto callback = pDataMsg->getCallable();
	callback->call();
	
	switch ( pDataMsg->getType() )
	{
	case Message::Type::Damage:
	{
		//m_hp -= payload->m_damage;
		std::cout << "Damage message received" << '\n';
		break;
	}
	case Message::Type::Heal:
	{
		//m_hp += payload->m_heal;
		std::cout << "Heal message received" << '\n';
		break;
	}
	case Message::Type::Greet:
	{
		//greet( payload->m_greeting );
		std::cout << "Greet message received" << '\n';
		break;
	}
	case Message::Type::PhysicsCollision:
	{
		std::cout << "Physics collision received" << '\n';
		break;
	}
	default:
		break;
	}
	pDataMsg->setHandled( true );
}

void Entity::sendMessage( class Message* msg ) const noexcept
{
	auto& md = MessageDispatcher::getInstance();
	md.addMessage( msg );
}
