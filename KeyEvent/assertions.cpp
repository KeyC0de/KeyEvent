#include "assertions.h"
#include <iostream>

#if defined _DEBUG && !defined _NDEBUG

#ifdef __cplusplus
extern "C" {
#endif

#ifdef UNICODE
// just builds the error string
bool assertPrint( const wchar_t* expr,
	const wchar_t* file,
	int line,
	const wchar_t* function,
	const wchar_t* msg )
{
	std::wcerr << L">> Assertion failed @ file: "
		<< file
		<< L"\n>> function: "
		<< function
		<< L"\n>> line: "
		<< line
		<< L"\n>> !( "
		<< expr
		<< L" )\n";
	if ( msg != nullptr )
	{
		std::wcerr << L">> Diagnostic message: "
			<< msg
			<< L'\n';
		return true;
	}
	std::wcout.flush();
	return false;
}

#else

// just builds the error string
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
#endif // UNICODE


#ifdef __cplusplus
}
#endif

#endif // _DEBUG