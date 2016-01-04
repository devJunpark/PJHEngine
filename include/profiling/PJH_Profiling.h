#ifndef __PJH_INCLUDE_PJH_PROFILING_H__
#define __PJH_INCLUDE_PJH_PROFILING_H__

#include "log/PJH_Log.h"
#include "assert/PJH_Assert.h"
#include <cinttypes>

/* 
@@ TODO : 
It needs to keep of critical section for multi threading.
So, If I implement thread manager, I adapt it here.
*/

namespace PJH {
namespace PJH_Profiling{
namespace {
	typedef struct {
		size_t startTime;
		size_t endTime;
		bool isProfiling;
		const char* lastCallFuncName;
	} __PJH_Profiling_type;
}

static __PJH_Profiling_type _pjh_gProfileData;

typedef void(*CALLBACK_PROFILING_START)();
typedef void(*CALLBACK_PROFILING_END)();

static const char* getLastCalledFunctionName()
{
	return _pjh_gProfileData.lastCallFuncName;
}

static void __pjh_simple_profiling_start_func(CALLBACK_PROFILING_START callback = NULL)
{
	if (_pjh_gProfileData.isProfiling)
		return;

	_pjh_gProfileData.isProfiling = true;
	_pjh_gProfileData.lastCallFuncName = __PJH_CALLED_FUNCTION__;

	if (callback)
		callback();
}
static void __pjh_simple_profiling_end_func(CALLBACK_PROFILING_END callback = NULL)
{
	if (!_pjh_gProfileData.isProfiling)
		return;



	if (callback)
		callback();

	_pjh_gProfileData.isProfiling = false;
}
} // PJH_Profiling
} // PJH

#define PJH_SIMPLE_TIMESTAMP_START_WITH_CALLBACK(callback) PJH::PJH_Profiling::__pjh_simple_profiling_start_func(callback)
#define PJH_SIMPLE_TIMESTAMP_END_WITH_CALLBACK(callback) PJH::PJH_Profiling::__pjh_simple_profiling_end_func(callback)

#define PJH_SIMPLE_TIMESTAMP_START PJH_SIMPLE_TIMESTAMP_START_WITH_CALLBACK(NULL)
#define PJH_SIMPLE_TIMESTAMP_END PJH_SIMPLE_TIMESTAMP_END_WITH_CALLBACK(NULL)

#endif  __PJH_INCLUDE_PJH_PROFILING_H__