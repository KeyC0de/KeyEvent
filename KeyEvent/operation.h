#pragma once

#include <functional>
#include <memory>


//===================================================
//	\function	Operation
//	\brief  returns a ready-made callable with its arguments,
//				packaged in a std::unique_ptr
//				able to be inserted in any container or used for whatever purpose
//			utilizes std::function for type erasure and std::bind for argument packing
//	\date	2020/11/05 3:17
class Operation
{
	using TF = std::function<void()>;
	TF m_f;
private:
	Operation( TF&& f );

public:
	template <typename TFunction,
		typename... TArgs>
	static std::unique_ptr<Operation> setup( TFunction&& f,
		TArgs&&... args )
	{// function pointers
		return std::unique_ptr<Operation>( new Operation(
			std::bind( std::forward<TFunction>( f ),
				std::forward<TArgs>( args )... ) ) );
	}
	// TRet( *f )( std::forward<TArgs>( args )... );

	template <typename TMethod,
		typename T,
		typename ...TArgs>
	static std::unique_ptr<Operation> setup( TMethod&& mf,
		T&& obj,
		TArgs&& ...args )
	{// member function pointers
		return std::unique_ptr<Operation>( new Operation(
			std::bind( std::forward<TMethod>( mf ),
				std::forward<T>( obj ),
				std::forward<TArgs>( args )... ) ) );
	}
	//( std::forward<T>( obj ).*mf )( std::forward<TArgs>( args )... ); -> TRet

	~Operation() noexcept;
	Operation( const Operation& rhs ) = delete;
	Operation& operator=( const Operation& rhs ) = delete;
	Operation( Operation&& rhs ) noexcept;
	Operation& operator=( Operation&& rhs ) noexcept;

	void operator()() const;
	void swap( Operation& rhs ) noexcept;
	void reset() noexcept;

	inline operator bool() const noexcept;
	inline constexpr bool operator==( const Operation& rhs ) const noexcept;
	inline constexpr bool operator!=( const Operation& rhs ) const noexcept;
	inline constexpr bool operator==( const Operation* rhs ) const noexcept;
	inline constexpr bool operator!=( const Operation* rhs ) const noexcept;
};