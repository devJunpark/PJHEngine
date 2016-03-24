#ifndef __PJH_INCLUDE_PJH_ASSERT_H__
#define __PJH_INCLUDE_PJH_ASSERT_H__

#include "log/PJH_Log.h"

/*
why do This preprocessor need to redefine?
__func__			was added to C++ in C++11.
__FUNCTION__		is a pre-standard extension that some C compilers support (including gcc and Visual C++);
in general, you should use __func__ where it is supported and only use __FUNCTION__ if you are using a compiler that does not support it
(for example, Visual C++, which does not support C99 and does not yet support all of C++0x, does not provide __func__).
__PRETTY_FUNCTION__ is a gcc extension that is mostly the same as __FUNCTION__,
except that for C++ functions it contains the "pretty" name of the function including the signature of the function. Visual C++ has a similar
(but not quite identical) extension, __FUNCSIG__.
*/
#ifndef __FUNCTION__
#define __PJH_CALLED_FUNCTION__ __func__
#else
#define __PJH_CALLED_FUNCTION__ __FUNCTION__
#endif

#define PJH_ASSERT_STR(express, log)\
	do {\
		if(!(express)) {\
			PJH_TAG_LOG("Assert", \
						"%s::%s line[%d] - log:["log"]",\
						__FILE__, __PJH_CALLED_FUNCTION__, __LINE__);\
			abort();\
				}\
		}while (0)
#define PJH_ASSERT(express) PJH_ASSERT_STR(express, "")
#define PJH_ABORT			PJH_ASSERT(false)
#define PJH_ABORT_STR(log)	PJH_ASSERT_STR(false, log)

#if defined(_DEBUG)
#define PJH_DEBUG_ASSERT(express) PJH_ASSERT(express)
#else
#define PJH_DEBUG_ASSERT(express)
#endif

#endif  __PJH_INCLUDE_PJH_ASSERT_H__