#include "PJH_Filesystem.h"
#include "PJH_SubFilesystem.h"
#include "PJH_Log.h"
#include "PJH_File.h"

#if defined(_MSC_VER) || !defined(_MSC_VER)

#endif

#ifdef _MSC_VER

#else
// If _MSC_VER weren't defined by platform, I will use boost library for cross platform.


#endif

namespace PJH {
namespace Filesystem{
PJH_SubFilesystem::PJH_SubFilesystem()
{
}
PJH_SubFilesystem::~PJH_SubFilesystem()
{

}

bool PJH_SubFilesystem::setRootPath(const char* rootpath)
{
	if (rootpath == NULL)
		return false;
	if (!_rootpath.empty()) {
		if (!PJH_FilesystemManager::isExistPath(rootpath)) {
			PJH_TAG_LOG("PJH_SubFilesystem::setRootPath",
						"rootpath that was passed doesn't exist path. You must check path of argument");
			return false;
		}
		_rootpath.clear();
	}
	_rootpath.append(rootpath);
	return true;
}
const char* PJH_SubFilesystem::getRootPath()
{
	return _rootpath.c_str();
}

bool PJH_SubFilesystem::isExist(const char* targetname, bool isSearchSub) const
{
	
}

PJH_File* PJH_SubFilesystem::addFile(const char* filename, const void* buffer)
{

}

bool PJH_SubFilesystem::deleteFile(const char* filename)
{

}


} // namespace Filesystem
} // namespace PJH