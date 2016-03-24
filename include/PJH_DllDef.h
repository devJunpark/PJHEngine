#ifndef __PJH_INCLUDE_PJH_DLLDEF_H__
#define __PJH_INCLUDE_PJH_DLLDEF_H__

#ifndef BOOST_ALL_NO_LIB
	#define BOOST_ALL_NO_LIB
#endif

#if defined(_MSC_VER) && defined(__PJH_USE_DLL)
#pragma warning(disable:4251)
#endif

#if defined(__PJH_DLL_API) && defined(__PJH_USE_DLL)
#define PJH_DLL_API __declspec(dllexport)
#elif defined(__PJH_USE_DLL)
#define PJH_DLL_API __declspec(dllimport)
#else
#define PJH_DLL_API
#endif

#endif  __PJH_INCLUDE_PJH_DLLDEF_H__