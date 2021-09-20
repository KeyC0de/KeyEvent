#pragma once

// AMD64 only
static_assert( sizeof( void* ) == 8 );
static_assert( sizeof( size_t ) == 8 );

#ifndef _MSC_VER
static_assert( false, "Non Windows Platform - Nah huh\n" );
#endif // !_MSC_VER

static_assert( _MSC_VER >= 1900,
	"Microsoft Visual Studio 2015 or later compiler required." );
static_assert( __cplusplus >= 201703L,
	"C++17 language conformance or later required. Use /Zc:__cplusplus compile option." );
static_assert( _MSVC_LANG >= 201703L,
	"C++17 language conformance or later required." );

#undef _WIN32_WINNT
#undef NTDDI_VERSION
#define _WIN32_WINNT _WIN32_WINNT_WINBLUE
#define NTDDI_VERSION NTDDI_WINBLUE
#include <sdkddkver.h>

#ifndef USE_GDIPLUS
// defines to get rid of superfluous Windows functionality
// However GDI+ requires all the functionality that is disabled by these switches
#	define WIN32_LEAN_AND_MEAN		// Cryptography, DDE, RPC, Shell, MCI, Windows Sockets
#	define NOGDICAPMASKS			// CC_*, LC_*, PC_*, CP_*, TC_*, RC_
#	define NOMENUS					// MF_*
#	define NOSYSCOMMANDS			// SC_*
#	define NORASTEROPS				// Binary and Tertiary raster ops
#	define OEMRESOURCE				// OEM Resource values
#	define NOATOM					// Atom manager routines
#	define NOCLIPBOARD				// Clipboard routines
#	define NOCOLOR					// Screen colors
#ifdef NO_DUMPS
#	define NOCTLMGR					// Control and Dialog routines, generating dumps
#endif // !TAKING_DUMPS
#	define NODRAWTEXT				// DrawText() and DT_*
#	define NOKERNEL					// KERNEL macros and routines
#	define NOMEMMGR					// GMEM_*, LMEM_*, GHND, LHND, associated routines
#	define NOMETAFILE				// typedef METAFILEPICT
#	define NOOPENFILE				// OpenFile(), OemToAnsi, AnsiToOem, and OF_*
#	define NOSCROLL					// SB_* and scrolling routines
#	define NOSERVICE				// All SERVICE_ Controller routines
#	define NOIMAGE					// 
#	define NOWH						// SetWindowsHook and WH_*
#	define NOCOMM					// No serial communication API & driver routines
#	define NOKANJI					// Kanji support
#	define NOHELP					// Help engine interface
#	define NODEFERWINDOWPOS			// DeferWindowPos routines
#	define NOMCX					// Modem Configuration Extensions
#	define NORPC					// no Remote Procedure Call Routines
#	define NOPROXYSTUB				// not use Proxies, nor Stubs (for DLLs)
#	define NOIMM					// no Input Method Manager
#	define NOMCX					// no Media Center Extender (for xBox)
#	define NOTAPE					// no Tape
#	if defined NDEBUG || !defined _DEBUG 
#		define NOPROFILER			// Profiler interface
#	endif // NDEBUG
#endif

//#	define NOVIRTUALKEYCODES		// VK_*
//#	define NOWINMESSAGES			// WM_*, EM_*, LB_*, CB_*
//#	define NOWINSTYLES				// WS_*, CS_*, ES_*, LBS_*, SBS_*, CBS_*
//#	define NOSYSMETRICS				// SM_*
//#	define NOGDI					// All GDI defines and routines
//#	define NOUSER					// All USER defines and routines
//#	define NOICONS					// IDI_*
//#	define NOKEYSTATES				// MK_*
//#	define NOSHOWWINDOW				// SW_*
//#	define NONLS					// NLS (Native Language Support) macros and routines
//#	define NOMB						// MB_* and MessageBox()
//#	define NOSOUND					// Sound driver routines
//#	define NOTEXTMETRIC				// typedef TEXTMETRIC and associated routines
									// 	required by atlbase.h
//#	define NOWINOFFSETS				// GWL_*, GCL_*, associated routines
//#	define ANSI_ONLY				// no unicode support

#if defined( _MFC_VER ) || defined( _AFX )
#	define _AFX_ALL_WARNINGS	// turns off MFC's hiding of some common and often safely ignored warning message
#	define VC_EXTRALEAN			// more trimming of windows headers for MFC only projects
#endif

#ifndef NOMINMAX
#	define NOMINMAX		// no windows min-max functions, we want the std:: mins & maxes
#endif // !NOMINMAX
#ifndef STRICT
#	define STRICT		// enables Strict pointer checking for windows types
#endif // !STRICT

#if defined NDEBUG || !defined _DEBUG 
//#	define _ITERATOR_DEBUG_LEVEL		0	// disables checked iterators - no checking on container bounds for overwrites 
											// equivalent to #define _SECURE_SCL 0
#endif // NDEBUG

#define _CRT_SECURE_NO_DEPRECATE		1	// non-secure c/winapi functions are not deprecated
#define _CRT_SECURE_NO_WARNINGS			1	// don't emit warnings for non-secure winapi functions
#define _WINSOCK_DEPRECATED_NO_WARNINGS 1

#ifdef _ALLOW_KEYWORD_MACROS
// prevent replacing c/c++ keywords with macros
#	undef _ALLOW_KEYWORD_MACROS
#endif // _ALLOW_KEYWORD_MACROS

#include <Windows.h>


// provides relocatable process base address at RVA = 0
extern "C" IMAGE_DOS_HEADER __ImageBase;
#define THIS_INSTANCE ( (HINSTANCE)&__ImageBase )