#ifndef __PLATFORM_H
#define __PLATFORM_H

#if defined(WINDOWS) || defined(WIN32) || defined(WIN64) || defined(_WINDLL)
// stl classes in dll interface
#pragma warning(disable:4251)

#define DLL_EXPORT __declspec(dllexport)
#define DLL_IMPORT __declspec(dllimport)
#else
#define DLL_EXPORT
#define DLL_IMPORT
#endif

#if defined(IN_DLL_PROJECT) || defined(_WINDLL)
#define DLL_SPEC DLL_EXPORT
#else
#define DLL_SPEC DLL_IMPORT
#endif

#endif
