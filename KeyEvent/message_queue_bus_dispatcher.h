#pragma once

#include <vector>
#include <mutex>
#include <condition_variable>
#include <memory>


class Message;

//============================================================
//	\class	MessageBus
//
//	\author	KeyC0de
//	\date	2019/12/09 4:51
//
//	\brief	thread safe event queue built from a Vector
//			enqueue or dequeue whenever, wherever, we'll be together
//			it pa-owns its contents (Messages)
//			move only
//			accessible only from the MessageDispatcher friend class
//=============================================================
class MessageBus final
{
	friend class MessageDispatcher;

	std::vector<std::unique_ptr<class Message>> m_vec;
	std::size_t m_size = 0;
	mutable std::mutex m_mu;
	std::condition_variable m_cond;

private:
	MessageBus();
	MessageBus( int initialCapacity );

private:
	void removeFrontByBackSwap();

public:
	MessageBus( const MessageBus& rhs ) = delete;
	MessageBus& operator=( const MessageBus& rhs ) = delete;
	MessageBus( MessageBus&& rhs ) noexcept;
	MessageBus& operator=( MessageBus&& rhs ) noexcept;

	//===================================================
	//	\function	enqueue
	//	\brief  push_back() : enqueue at the back
	//	\date	2019/12/09 4:50
	void enqueue( class Message* msg );
	//===================================================
	//	\function	dequeue
	//	\brief  pop_front() : dequeue messages from the front
	//	\date	2019/12/09 4:51
	std::unique_ptr<class Message> dequeue();
	class Message* peekFront() const noexcept;
	class Message* peekBack() const noexcept;

	explicit operator bool();
	class Message* operator[]( std::size_t index );
	const class Message* operator[]( std::size_t index ) const;

	std::size_t getSize() const noexcept;
	std::size_t getCapacity() const noexcept;

	inline bool isEmpty() const noexcept;
	void clear();
};


//============================================================
//	\class	MessageDispatcher
//
//	\author	KeyC0de
//	\date	2019/12/09 17:15
//
//	\brief	Meyer's singleton
//			contains the message queue
//=============================================================
class MessageDispatcher final
{
	MessageBus m_mb;

	MessageDispatcher( int initialCapacity );
public:
	~MessageDispatcher() noexcept = default;
	MessageDispatcher( const MessageDispatcher& fs ) = delete;
	MessageDispatcher& operator=( const MessageDispatcher& fs ) = delete;

	MessageDispatcher( MessageDispatcher&& rhs ) noexcept;
	MessageDispatcher& operator=( MessageDispatcher&& rhs ) noexcept;

	static MessageDispatcher& getInstance( int initialCapacity = 100 );
	//===================================================
	//	\function	addMessage
	//	\brief  add new message to the MessageBus
	//	\date	2020/12/10 4:47
	void addMessage( class Message* msg );
	//===================================================
	//	\function	dispatchAll
	//	\brief  dispatch all pending messages
	//	\date	2019/12/10 4:47
	void dispatchAll();
	//TODO: dispatchByEventType
	//TODO: dispatchEventsTargetedTo( specific actor )
	void clear();

	std::size_t getSize() const noexcept;
	std::size_t getCapacity() const noexcept;
};
