#pragma once

#include <memory>
#include <vector>


class Entity;
class DelayedFunc;

//============================================================
//	\class	Message
//
//	\author	KeyC0de
//	\date	2019/12/09 13:23
//
//	\brief	The Message - Enveloppe
//=============================================================
class Message
{
public:
	enum class Type
	{
		Idle = 0,
		Damage,
		Heal,
		Greet,
		PhysicsCollision
	};
private:
	bool m_bHandled = false;
	class Entity* m_pSender;
	std::vector<class Entity*> m_pReceivers;
	Message::Type m_type;

public:
	Message( class Entity* srcId, const std::vector<class Entity*>& destId,
		Message::Type type );
	virtual ~Message() noexcept;
	Message( const Message& rhs ) = delete;
	Message& operator=( const Message& rhs ) = delete;
	Message( Message&& rhs ) noexcept;
	Message& operator=( Message&& rhs ) noexcept;

	Message::Type getType() const noexcept;
	class Entity* getSender() noexcept;
	std::vector<class Entity*>& getReceivers() noexcept;
	bool isHandled() const noexcept;
	void setHandled( bool b) noexcept;
};


//============================================================
//	\class	MessageCall
//
//	\author	KeyC0de
//	\date	2019/12/10 3:01
//
//	\brief	a Message with arbitrary callable object
//			virtual contructed, move only
//=============================================================
class MessageCall
	:
	public Message
{
	std::unique_ptr<class DelayedFunc> m_pDelFunc;
public:
	MessageCall( class Entity* psrc, const std::vector<class Entity*>& pDests,
		Message::Type type, std::unique_ptr<DelayedFunc> df );
	virtual ~MessageCall() noexcept = default;
	MessageCall( MessageCall&& rhs ) noexcept;
	MessageCall& operator=( MessageCall&& rhs ) noexcept;

	class DelayedFunc* getCallable() const noexcept;
};


//============================================================
//	\class	DataMessage<T>
//
//	\author	KeyC0de
//	\date	2019/12/10 3:01
//
//	\brief	a Message with arbitrary data payload T
//			virtual contructed, move only
//=============================================================
template<class T>
class DataMessage
	:
	public Message
{
	std::unique_ptr<T> m_pPayload;
public:
	template<typename ... TParams>
	DataMessage( class Entity* src,
		const std::vector<class Entity*>& pDests,
		Message::Type type,
		TParams&&... args )
		:
		Message( src, pDests, type ),
		m_pPayload( std::make_unique<T>( std::forward<TParams>( args )... ) )
	{}

	virtual ~DataMessage() noexcept = default;
	
	DataMessage( DataMessage&& rhs ) noexcept
		:
		Message( std::move( rhs ) ),
		m_pPayload{std::move( rhs.m_pPayload )}
	{}
	
	DataMessage& operator=( DataMessage&& rhs ) noexcept
	{
		if ( this != &rhs )
		{
			Message::operator=( std::move( rhs ) );
			std::swap( m_pPayload, rhs.m_pPayload );
		}
		return *this;
	}
	
	T* getPayload() const noexcept
	{
		return m_pPayload.get();
	}
};
