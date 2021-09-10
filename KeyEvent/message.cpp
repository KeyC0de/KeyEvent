#include "message.h"
#include "delayed_function.h"
#include "entity.h"


Message::Message( Entity* pSrc,
	const std::vector<Entity*>& pDests,
	Message::Type type )
	:
	m_pSender(pSrc),
	m_type(type)
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
	m_bHandled{rhs.m_bHandled},
	m_pSender{rhs.m_pSender},
	m_type{rhs.m_type}
{
	for( Entity* dest : rhs.m_pReceivers )
	{
		m_pReceivers.emplace_back( dest );
	}
	rhs.m_pReceivers.clear();
}

Message& Message::operator=( Message&& rhs ) noexcept
{
	m_bHandled = rhs.m_bHandled;
	m_pSender = rhs.m_pSender;
	m_type = rhs.m_type;

	for( Entity* dest : rhs.m_pReceivers )
	{
		m_pReceivers.emplace_back( dest );
	}
	rhs.m_pReceivers.clear();
	return *this;
}

Message::Type Message::getType() const noexcept
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
	Message::Type type,
	std::unique_ptr<DelayedFunc> df )
	:
	Message{psrc, pDests, type},
	m_pFunc{std::move( df )}
{

}

MessageCall::MessageCall( MessageCall&& rhs ) noexcept
	:
	Message{std::move( rhs )},
	m_pFunc{std::move( rhs.m_pFunc )}
{

}

MessageCall& MessageCall::operator=( MessageCall&& rhs ) noexcept
{
	Message::operator=( std::move( rhs ) );
	std::swap( m_pFunc, rhs.m_pFunc );
	return *this;
}

DelayedFunc* MessageCall::getCallable() const noexcept
{
	return m_pFunc.get();
}
