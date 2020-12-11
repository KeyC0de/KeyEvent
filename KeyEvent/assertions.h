#pragma once

#ifndef TRUE
#define TRUE 1
#endif // !TRUE

// unicode preprocess
#if defined(_UNICODE) || defined(UNICODE)
#	define unicode
#	if defined(_MSC_VER) || defined (_WIN32) || defined(_WIN64)
#		define __function__ __FUNCTIONW__
#	elif defined(GNUC) || defined(__linux__) || defined (__unix__) || defined (GNUG)
#		define __function__ __PRETTY_FUNCTION__
#	endif
#else
#	define ascii
#	if defined(_MSC_VER) || defined (_WIN32) || defined(_WIN64)
#		define __function__ __FUNCTION__
#	elif defined(GNUC) || defined(__linux__) || defined(__unix__) || defined(GNUG)
#		define __function__ __func__
#	endif
#endif


#if defined _DEBUG && !defined _NDEBUG

#	ifdef __cplusplus
extern "C" {
#	endif

#	ifdef UNICODE
#		define LSTR( expr ) L ## expr
#		define STRINGIFY( expr ) LSTR( #expr )
extern bool assertPrint( const wchar_t* expr,
	const wchar_t* file,
	int line,
	const wchar_t* function,
	const wchar_t* msg );

// assert that arg is true, if not print error
#		define ASSERT( arg, msg ) (!( arg ) \
			&& assertPrint( STRINGIFY( arg ),\
				__FILEW__,\
				__LINE__,\
				__function__,\
				msg ) )
#	else
#		define STRINGIFY( expr ) #expr
extern bool assertPrint( const char* expr,
	const char* file,
	int line,
	const char* function,
	const char* msg );

// assert that arg is true, if not print error
#		define ASSERT( arg, msg ) (!(arg) \
			&& assertPrint( STRINGIFY( arg ),\
				__FILE__,\
				__LINE__,\
				__function__,\
				msg ) )
#	endif // UNICODE

#	ifdef __cplusplus
}
#	endif

#else
// Release
#	define ASSERT(arg, msg) void(0);
#endif // _DEBUG
