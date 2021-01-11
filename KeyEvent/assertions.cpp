#include "assertions.h"
#include <iostream>


#if defined _DEBUG && !defined _NDEBUG

#ifdef __cplusplus
extern "C" {
#endif

// builds the error string
bool assertPrint( const char* expr,
	const char* file,
	int line,
	const char* function,
	const char* msg )
{
	std::cerr << ">> Assertion failed @ "
		<< file
		<< ", function: "
		<< function
		<< ", line: "
		<< line
		<< " - ! "
		<< expr
		<< '\n';
	if ( msg != nullptr )
	{
		std::cerr << ">> Diagnostic message: "
			<< msg
			<< '\n';
		return true;
	}
	std::cout.flush();
	return false;
}

#ifdef __cplusplus
}
#endif

#endif // _DEBUG