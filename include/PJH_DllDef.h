#ifndef __PJH_INCLUDE_PJH_DLLDEF_H__
#define __PJH_INCLUDE_PJH_DLLDEF_H__

#ifdef __PJH_DLL_API
#define PJH_DLL_API __declspec(dllexport)
#else
#define PJH_DLL_API __declspec(dllimport)
#endif

#endif  __PJH_INCLUDE_PJH_DLLDEF_H__