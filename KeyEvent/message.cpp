#include "message.h"
#include "delayed_function.h"
#include "entity.h"


Message::Message( Entity* pSrc,
	const std::vector<Entity*>& pDests,
	MessageType type )
	:
	m_pSender( pSrc ),
	m_type( type )
{
	for( Entity* dest : pDests )
	{
		m_pReceivers.emplace_back( dest );
	}
}
	
Message::~Message() noexcept
{
	//m_pReceivers.clear();
}

Message::Message( Message&& rhs ) noexcept
	:
	m_pSender{rhs.m_pSender},
	m_type{rhs.m_type},
	m_bHandled{rhs.m_bHandled}
{
	for( Entity* dest : rhs.m_pReceivers )
	{
		m_pReceivers.emplace_back( dest );
	}
	rhs.m_pReceivers.clear();
}

Message& Message::operator=( Message&& rhs ) noexcept
{
	if ( this != &rhs )
	{
		m_pSender = rhs.m_pSender;
		
		for( Entity* dest : rhs.m_pReceivers )
		{
			m_pReceivers.emplace_back( dest );
		}
		rhs.m_pReceivers.clear();

		m_type = rhs.m_type;
		m_bHandled = rhs.m_bHandled;
	}
	return *this;
}

MessageType Message::getType() const noexcept
{
	return m_type;
}

Entity* Message::getSender() noexcept
{
	return m_pSender;
}

std::vector<Entity*>& Message::getReceivers() noexcept
{
	return m_pReceivers;
}

bool Message::isHandled() const noexcept
{
	return m_bHandled;
}

void Message::setHandled( bool b ) noexcept
{
	m_bHandled = b;
}


MessageCall::MessageCall( Entity* psrc,
	const std::vector<Entity*>& pDests,
	MessageType type,
	std::unique_ptr<DelayedFunc> df )
	:
	Message( psrc, pDests, type ),
	m_pDelFunc{ std::move( df )}
{}

MessageCall::MessageCall( MessageCall&& rhs ) noexcept
	:
	Message( std::move( rhs ) ),
	m_pDelFunc{ std::move( rhs.m_pDelFunc )}
{}

MessageCall& MessageCall::operator=( MessageCall&& rhs ) noexcept
{
	if ( this != &rhs )
	{
		Message::operator=( std::move( rhs ) );
		std::swap( m_pDelFunc, rhs.m_pDelFunc );
	}
	return *this;
}

DelayedFunc* MessageCall::getCallable() const noexcept
{
	return m_pDelFunc.get();
}
