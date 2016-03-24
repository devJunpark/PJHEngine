#ifndef __PJH_INCLUDE_PJH_PROFILING_H__
#define __PJH_INCLUDE_PJH_PROFILING_H__

#include "PJH_DllDef.h"

#include <cinttypes>
#include <map>
#include <string>

#include "log/PJH_Log.h"
#include "assert/PJH_Assert.h"
#include "boost/date_time/posix_time/posix_time.hpp"

/* 
@@ TODO : 
It needs to keep of critical section for multi threading.
So, If I implement thread manager, I adapt it here.
*/

namespace PJH {
namespace PJH_Profiling{

static const char* _pjh_id = "__PJH_TIME_STAMP";

namespace {
typedef struct __PJH_Profiling_type_t{
	boost::posix_time::ptime startTime;
	bool isProfiling;
	__PJH_Profiling_type_t::__PJH_Profiling_type_t() : isProfiling(false){}
} __PJH_Profiling_type;

typedef void(*CALLBACK_PROFILING_START)();
typedef void(*CALLBACK_PROFILING_END)();

static __PJH_Profiling_type _pjh_gLowProfile;
static std::map<std::string, __PJH_Profiling_type> _pjh_gProfileMap;

void _pjh_insert_profile(const std::string& _requestId)
{
	using namespace boost::posix_time;

	__PJH_Profiling_type& insertedProf = _pjh_gProfileMap[_requestId];

	PJH_DEBUG_ASSERT(!insertedProf.isProfiling);
	
	insertedProf.isProfiling = true;
	insertedProf.startTime = microsec_clock::local_time();
}
time_t _pjh_erase_profile(const std::string& _requestId)
{
	using namespace boost::posix_time;

	std::map<std::string, __PJH_Profiling_type>::iterator isFind = _pjh_gProfileMap.find(_requestId);
	PJH_DEBUG_ASSERT(isFind != _pjh_gProfileMap.end());

	ptime starttime = isFind->second.startTime;
	_pjh_gProfileMap.erase(isFind);

	time_duration diff = microsec_clock::local_time() - starttime;
	return diff.total_milliseconds();
}
}

const char* getLastCalledFunctionName()
{
	return NULL;
}

static void __pjh_simple_profiling_start_func(const std::string& _requestId, CALLBACK_PROFILING_START callback = NULL)
{
	if (callback)
		callback();

	_pjh_insert_profile(_requestId);
}
static time_t __pjh_simple_profiling_end_func(const std::string& _requestId, CALLBACK_PROFILING_END callback = NULL)
{
	time_t diffTime = _pjh_erase_profile(_requestId);

	if (callback)
		callback();

	return diffTime;
}

static void __pjh_lowlevel_profile_start()
{
	using namespace boost::posix_time;

	PJH_DEBUG_ASSERT(!_pjh_gLowProfile.isProfiling);

	_pjh_gLowProfile.isProfiling = true;
	_pjh_gLowProfile.startTime = microsec_clock::local_time();
}

static time_t __pjh_lowlevel_profile_end()
{
	using namespace boost::posix_time;

	PJH_DEBUG_ASSERT(_pjh_gLowProfile.isProfiling);

	_pjh_gLowProfile.isProfiling = false;
	return (microsec_clock::local_time() - _pjh_gLowProfile.startTime).total_milliseconds();
}

} // PJH_Profiling
} // PJH

#define PJH_SIMPLE_TIMESTAMP_START_WITH_CALLBACK(requestid, callback) PJH::PJH_Profiling::__pjh_simple_profiling_start_func(requestid, callback)
#define PJH_SIMPLE_TIMESTAMP_END_WITH_CALLBACK(requestid, callback)	  PJH::PJH_Profiling::__pjh_simple_profiling_end_func(requestid, callback)

#define PJH_SIMPLE_TIMESTAMP_START	PJH_SIMPLE_TIMESTAMP_START_WITH_CALLBACK(PJH::PJH_Profiling::_pjh_id, NULL)
#define PJH_SIMPLE_TIMESTAMP_END	PJH_SIMPLE_TIMESTAMP_END_WITH_CALLBACK(PJH::PJH_Profiling::_pjh_id, NULL)

#define PJH_TIMESTAMP_START_WITH_ID(requestId)	PJH_SIMPLE_TIMESTAMP_START_WITH_CALLBACK(requestId, NULL)
#define PJH_TIMESTAMP_END_WITH_ID(requestId)	PJH_SIMPLE_TIMESTAMP_END_WITH_CALLBACK(requestId, NULL)

#define PJH_LOWLEVEL_PROFILE_START PJH::PJH_Profiling::__pjh_lowlevel_profile_start()
#define PJH_LOWLEVEL_PROFILE_END   PJH::PJH_Profiling::__pjh_lowlevel_profile_end()

#endif  __PJH_INCLUDE_PJH_PROFILING_H__