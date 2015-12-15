#include <fstream>
#include <string>

#include "PJH_Filesystem.h"
#include "PJH_Log.h"
#include "PJH_Assert.h"

#ifdef _WIN32
	#include <direct.h>
	#define getcwd _getcwd

	#include <Shlwapi.h>
	#pragma  comment(lib, "shlwapi.lib")
	#define PathFileExistsDefine PathFileExistsA
#elif
	#include <unistd.h>
	#define PathFileExistsDefine(dummy_path) -1
#endif

namespace PJH{
namespace Filesystem{
PJH_FilesystemManager* PJH_FilesystemManager::_instance = NULL;

PJH_FilesystemManager::PJH_FilesystemManager() 
{

}
PJH_FilesystemManager::~PJH_FilesystemManager()
{

}

PJH_FilesystemManager* PJH_FilesystemManager::getInstance()
{
	if (!_instance)
	{
		PJH_TAG_LOG("PJH_Filesystem::getInstance", "Instance will be created by getInstance");
		_instance = new PJH_FilesystemManager();
	}
	return _instance;
}
void PJH_FilesystemManager::release()
{
	if (_instance) {
		PJH_TAG_LOG("PJH_Filesystem::release", "Instance will be deleted by release");
		std::vector<SubFileSystem_Ptr>::iterator iter = _instance->_child.begin();
		while (iter != _instance->_child.end())
		{
			if (*iter != NULL)
				_instance->_child.erase(iter);
			iter = _instance->_child.begin();
		}
		_instance->_child.clear();
		delete _instance;
	}
	_instance = NULL;
}

bool PJH_FilesystemManager::isExistPath(const char* path)
{
	if (!path) {
		PJH_TAG_LOG("PJH_FilesystemManager::isExistPath",
					"Argument is invalid.");
		return false;
	}
	int retval = PathFileExistsDefine(path);

	return retval == 1;
}

bool PJH_FilesystemManager::isExistFile(const char* filename, const char* dirpath)
{
	PJH_ASSERT_STR(filename != NULL, "Filename is null. you have not to pass null.");

	bool isExist = true;
	std::string fullpath;

	if (dirpath) {
		fullpath.append(dirpath);
	}
	else {
		char path[1024];
		isExist = getWorkingDirectory(path, sizeof(path));
		if (!isExist)
			return false;
		fullpath.append(path);
	}

	char lastchar = *(fullpath.rbegin());
	if (lastchar != '\\' && lastchar != '/')
		fullpath.append("/");

	fullpath.append(filename);

	isExist = std::ifstream(fullpath.c_str()).is_open();

	return isExist;
}

bool PJH_FilesystemManager::getWorkingDirectory(char* path, int size)
{
	bool isSuccessed = getcwd(path, size) != NULL;
	if (!isSuccessed) {
		PJH_TAG_LOG("PJH_Filesystem::getWorkingDirectory",
					"getcwd function is not provided by this platform");
	}
	return isSuccessed;
}

SubFileSystem_Ptr PJH_FilesystemManager::openSubFilesystem(const char* rootpath)
{
	char cwdpath[1024];
	if (!rootpath) {
		getWorkingDirectory(cwdpath, sizeof(cwdpath));
	}
	SubFileSystem_Ptr newsfs = PJH_SubFilesystem::sharedptr_create();
	if (newsfs) {
		bool isSuccessed = newsfs->setRootPath(rootpath == NULL ? cwdpath : rootpath);
		if (isSuccessed) {
			_child.push_back(newsfs);
		}
	}
	return newsfs;
}

bool PJH_FilesystemManager::closeSubFilesystem(SubFileSystem_Ptr subfilesystem)
{
	if (subfilesystem == NULL) {
		PJH_TAG_LOG("PJH_FilesystemManager::closeSubFilesystem", 
					"You passed invalid pointer. You must check argument");
		return false;
	}
	std::vector<SubFileSystem_Ptr>::iterator iter;
	for (iter = _child.begin(); iter != _child.end(); ++iter)
	{
		if (*iter != NULL && (*iter == subfilesystem)) {
			PJH_TAG_LOG("PJH_FilesystemManager::closeSubFilesystem",
						"successed to search for removing subfilesystem.");
			_child.erase(iter);
			return true;
		}
	}
	return false;
}
} // End of namespace of Filesystem
} // End of namespace of PJH