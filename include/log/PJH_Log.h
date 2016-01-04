#ifndef __PJH_INCLUDE_PJH_LOG_H__
#define __PJH_INCLUDE_PJH_LOG_H__

#include <cstdarg>
#include <cstdint>
#include <iostream>
#include <string>

#define PJH_FORMATTING_LOG_WITHOUT_TAG(str, ...) \
	PJH::Logsystem::PJH_Log::formattingLogWithTag("", str, __VA_ARGS__);
#define PJH_FORMATTING_LOG_WITH_TAG(tag, str, ...) \
	PJH::Logsystem::PJH_Log::formattingLogWithTag("<TAG:"tag"> ", str, __VA_ARGS__);

#if defined(DEBUG)
	#define PJH_LOG(str, ...)			PJH_FORMATTING_LOG_WITHOUT_TAG(str, __VA_ARGS__)
	#define PJH_TAG_LOG(tag, str, ...)  PJH_FORMATTING_LOG_WITH_TAG(tag, str, __VA_ARGS__)
#else
	#define PJH_LOG(str, ...)
	#define PJH_TAG_LOG(tag, str, ...)
#endif

namespace PJH {
namespace Logsystem {
class PJH_Log 
{
private : 

public : 
	static void formattingLogWithTag(const char* tag, const char* str, ...)
	{
		va_list argptr;
		va_start(argptr, str);

		std::string log(tag);
		log.append(str);
		log.append("\n");
		vprintf(log.c_str(), argptr);

		va_end(argptr);
	}
};
}
}

#endif  __PJH_INCLUDE_PJH_LOG_H__