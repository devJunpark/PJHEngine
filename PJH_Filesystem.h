#pragma once
#include <vector>
#include <memory>

#include "PJH_SubFilesystem.h"

#if _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4521) // It is Multiple copy ctors warning. I ignore it.
#endif

namespace PJH {
namespace Filesystem {
class PJH_FilesystemManager
{
private:
	static PJH_FilesystemManager* _instance;

	std::vector<SubFileSystem_Ptr> _child;

	explicit PJH_FilesystemManager();
	explicit PJH_FilesystemManager(const PJH_FilesystemManager&);
	explicit PJH_FilesystemManager(PJH_FilesystemManager&);
	virtual ~PJH_FilesystemManager();

public:
	static PJH_FilesystemManager* getInstance();
	static void release();

	static bool isExistPath(const char* path);
	static bool isExistFile(const char* filename, const char* dirpath = NULL);
	static bool getWorkingDirectory(char* path, int size);

	SubFileSystem_Ptr openSubFilesystem(const char* rootpath = NULL);
	bool closeSubFilesystem(SubFileSystem_Ptr subfilesystem);

};
} // namespace Filesystem
} // namespace PJH

#if _MSC_VER
#pragma  warning(pop)
#endif
