#pragma once

#if defined _DEBUG && !defined _NDEBUG

#	ifdef __cplusplus
extern "C" {
#	endif

//#		define LSTR( expr ) L ## expr
//#		define STRINGIFY( expr ) LSTR( #expr )
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
				__FUNCTION__,\
				msg ) )
#	ifdef __cplusplus
}
#	endif

#else
// Release
#	define ASSERT( arg, msg ) void(0);
#endif // _DEBUG
