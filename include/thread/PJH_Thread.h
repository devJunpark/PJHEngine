#pragma  once

#include "PJH_DllDef.h"

#include <thread>
#include <string>
#include <mutex>
#include <assert.h>

namespace PJH {
class PJH_DLL_API Thread
{
private:
	std::mutex _mutex;

public:
	explicit Thread()
	{
	}
	virtual ~Thread() {}

	void operator()() const;
};
}
