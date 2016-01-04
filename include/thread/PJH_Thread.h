#pragma  once
#include <thread>
#include <string>
#include <mutex>
#include <assert.h>

namespace PJH {
class Thread
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
