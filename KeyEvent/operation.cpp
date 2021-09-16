#include "operation.h"


Operation::Operation( TF&& f )
	:
	m_f{std::forward<TF>( f )}
{

}

Operation::~Operation() noexcept
{
	reset();
}

Operation::Operation( Operation&& rhs ) noexcept
	:
	m_f{std::move( rhs.m_f )}
{

}

Operation& Operation::operator=( Operation&& rhs ) noexcept
{
	this->swap( rhs );
	return *this;
}

void Operation::operator()() const
{
	m_f();
}

void Operation::swap( Operation& rhs ) noexcept
{
	std::swap( m_f,
		rhs.m_f );
}

void Operation::reset() noexcept
{
	m_f = nullptr;
}

inline Operation::operator bool() const noexcept
{
	return m_f != nullptr;
}

inline constexpr bool Operation::operator==( const Operation& rhs ) const noexcept
{
	return &this->m_f == &rhs.m_f;
}

inline constexpr bool Operation::operator!=( const Operation& rhs ) const noexcept
{
	return &this->m_f != &rhs.m_f;
}

inline constexpr bool Operation::operator==( const Operation* rhs ) const noexcept
{
	return &this->m_f == &rhs->m_f;
}

inline constexpr bool Operation::operator!=( const Operation* rhs ) const noexcept
{
	return &this->m_f != &rhs->m_f;
}
