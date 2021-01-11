#pragma once

#include <functional>
#include <memory>


//===================================================
//	\function	DelayedFunc
//	\brief  returns a ready-made callable with its arguments,
//			packaged in a std::unique_ptr
//			able to be inserted in any container or used for whatever purpose
//			utilizes std::function for type erasure and std::bind for argument packing
//	\date	2020/11/05 3:17
class DelayedFunc
{
	using TF = std::function<void()>;
	TF m_f;
private:
	DelayedFunc( TF&& f );

public:

	template <typename TFunction,
		typename... TArgs>
	static std::unique_ptr<DelayedFunc> setup( TFunction&& f,
		TArgs&&... args )
	{// function pointers
		return std::unique_ptr<DelayedFunc>( new DelayedFunc(
			std::bind( std::forward<TFunction>( f ),
				std::forward<TArgs>( args )... ) ) );
	}
	// TRet( *f )( std::forward<TArgs>( args )... );

	template <typename TMethod,
		typename T,
		typename ...TArgs>
	static std::unique_ptr<DelayedFunc> setup( TMethod&& mf,
		T&& obj,
		TArgs&& ...args )
	{// member function pointers
		return std::unique_ptr<DelayedFunc>( new DelayedFunc(
			std::bind( std::forward<TMethod>( mf ),
				std::forward<T>( obj ),
				std::forward<TArgs>( args )... ) ) );
	}
	//( std::forward<T>( obj ).*mf )( std::forward<TArgs>( args )... ); -> TRet

	~DelayedFunc() noexcept;
	DelayedFunc( const DelayedFunc& rhs ) = delete;
	DelayedFunc& operator=( const DelayedFunc& rhs ) = delete;
	DelayedFunc( DelayedFunc&& rhs ) noexcept;
	DelayedFunc& operator=( DelayedFunc&& rhs ) noexcept;

	void swap( DelayedFunc& rhs ) noexcept;
	void call() const;
	void reset() noexcept;

	inline operator bool() const noexcept;
	inline constexpr bool operator==( const DelayedFunc& rhs ) const noexcept;
	inline constexpr bool operator!=( const DelayedFunc& rhs ) const noexcept;
	inline constexpr bool operator==( const DelayedFunc* rhs ) const noexcept;
	inline constexpr bool operator!=( const DelayedFunc* rhs ) const noexcept;
};