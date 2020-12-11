#include "delayed_function.h"

DelayedFunc::DelayedFunc( TF&& f )
	:
	m_f( std::forward<TF>( f ) )
{}

DelayedFunc::~DelayedFunc() noexcept
{
	reset();
}

DelayedFunc::DelayedFunc( DelayedFunc&& rhs ) noexcept
	:
	m_f{std::move( rhs.m_f )}
{}

DelayedFunc& DelayedFunc::operator=( DelayedFunc&& rhs ) noexcept
{
	if ( this != &rhs )
	{
		this->swap( rhs );
	}
	return *this;
}

void DelayedFunc::swap( DelayedFunc& rhs ) noexcept
{
	std::swap( m_f, rhs.m_f );
}

void DelayedFunc::call() const
{
	m_f();
}

void DelayedFunc::reset() noexcept
{
	m_f = nullptr;
}

inline DelayedFunc::operator bool() const noexcept
{
	return m_f != nullptr;
}

inline constexpr bool DelayedFunc::operator==( const DelayedFunc& rhs ) const noexcept
{
	return &this->m_f == &rhs.m_f;
}

inline constexpr bool DelayedFunc::operator!=( const DelayedFunc& rhs ) const noexcept
{
	return &this->m_f != &rhs.m_f;
}

inline constexpr bool DelayedFunc::operator==( const DelayedFunc* rhs ) const noexcept
{
	return &this->m_f == &rhs->m_f;
}

inline constexpr bool DelayedFunc::operator!=( const DelayedFunc* rhs ) const noexcept
{
	return &this->m_f != &rhs->m_f;
}
