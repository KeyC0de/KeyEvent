#pragma once

#include <sdkddkver.h>	// applies default values to windows defines, 
						//	unless some are already defined (eg _WIN32_WINNT)
#undef _WIN32_WINNT
#undef NTDDI_VERSION
#define _WIN32_WINNT _WIN32_WINNT_WINBLUE
#define NTDDI_VERSION NTDDI_WINBLUE

#ifndef _MSC_VER
static_assert( false, "Non Windows Platform - Nah huh\n" );
#endif // !_MSC_VER

#ifndef USE_GDIPLUS
// defines to get rid of superfluous Windows functionality
// However GDI+ requires all the functionality that is disabled by these switches
#	define WIN32_LEAN_AND_MEAN		// Cryptography, DDE, RPC, Shell, and Windows Sockets
#	define NOGDICAPMASKS			// CC_*, LC_*, PC_*, CP_*, TC_*, RC_
#	define NOVIRTUALKEYCODES		// VK_*
//#	define NOWINMESSAGES			// WM_*, EM_*, LB_*, CB_*
//#	define NOWINSTYLES				// WS_*, CS_*, ES_*, LBS_*, SBS_*, CBS_*
//#	define NOSYSMETRICS				// SM_*
//#	define NOGDI					// All GDI defines and routines
//#	define NOUSER					// All USER defines and routines
//#	define NOICONS					// IDI_*
//#	define NOKEYSTATES				// MK_*
//#	define NOSHOWWINDOW				// SW_*
#	define NOMENUS					// MF_*
#	define NOSYSCOMMANDS			// SC_*
#	define NORASTEROPS				// Binary and Tertiary raster ops
#	define OEMRESOURCE				// OEM Resource values
#	define NOATOM					// Atom manager routines
#	define NOCLIPBOARD				// Clipboard routines
#	define NOCOLOR					// Screen colors
#	define NOCTLMGR					// Control and Dialog routines
#	define NODRAWTEXT				// DrawText() and DT_*
#	define NOKERNEL					// KERNEL macros and routines
//#	define NONLS					// NLS (Native Language Support) macros and routines
//#	define NOMB						// MB_* and MessageBox()
#	define NOMEMMGR					// GMEM_*, LMEM_*, GHND, LHND, associated routines
#	define NOMETAFILE				// typedef METAFILEPICT
#	define NOOPENFILE				// OpenFile(), OemToAnsi, AnsiToOem, and OF_*
#	define NOSCROLL					// SB_* and scrolling routines
#	define NOSERVICE				// All SERVICE_ Controller routines
//#	define NOSOUND					// Sound driver routines
#	define NOIMAGE					// 
#	define NOTEXTMETRIC				// typedef TEXTMETRIC and associated routines
#	define NOWH						// SetWindowsHook and WH_*
#	define NOWINOFFSETS				// GWL_*, GCL_*, associated routines
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
//#	define ANSI_ONLY				// no unicode support
#	ifndef _DEBUG
#		define NOPROFILER			// Profiler interface
#	endif // _DEBUG
#endif

#if defined( _MFC_VER ) || defined( _AFX )
#	define _AFX_ALL_WARNINGS	// turns off MFC's hiding of some common and often safely ignored warning message
#	define VC_EXTRALEAN			// more trimming of windows headers for MFC only projects
#endif

#define NOMINMAX		// no windows min-max functions, we want the std:: mins & maxes
#define STRICT			// enables Strict type checking for windows types

#define _CRT_SECURE_NO_DEPRECATE	// non-secure c/winapi functions are not deprecated
#define _SCL_SECURE_NO_WARNINGS		// don't emit warnings for non-secure winapi functions
//#define _ITERATOR_DEBUG_LEVEL	0	// disable checked iterators === #define _SECURE_SCL 0
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#define _CRT_SECURE_NO_WARNINGS 1
#define _WINSOCK_DEPRECATED_NO_WARNINGS 1

#ifdef _ALLOW_KEYWORD_MACROS
// prevent replacing c/c++ keywords with macros
#	undef _ALLOW_KEYWORD_MACROS
#endif // _ALLOW_KEYWORD_MACROS

#include <Windows.h>

#define IDD_MFPLAYBACK_DIALOG		102
#define IDD_ABOUTBOX				103
#define IDM_ABOUT					104
#define IDM_EXIT					105
#define IDI_SMALL					108
#define IDC_MFPLAYBACK				109
#define IDD_OPENURL					129
#define IDC_EDIT_URL				1000
#define ID_FILE_OPENFILE			32771
#define ID_FILE_OPENURL				32772
#define IDR_MAINFRAME				128
#define IDC_MYICON					2
#define IDC_STATIC					-1


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

// provides relocatable base address at RVA = 0
extern "C" IMAGE_DOS_HEADER __ImageBase;
#define THIS_INSTANCE ( (HINSTANCE)&__ImageBase )