#ifndef __PJH_INCLUDE_PJH_SUB_FILESYSTEM_H__
#define __PJH_INCLUDE_PJH_SUB_FILESYSTEM_H__

#include "PJH_DllDef.h"

#include <string>
#include <map>
#include <set>

#include "filesystem/PJH_File.h"
// This class must be created by PJH_Filesystemmanager.

namespace PJH {
namespace Filesystem {
class PJH_SubFilesystem;
typedef std::shared_ptr<PJH_SubFilesystem> SubFileSystem_Ptr;

class PJH_DLL_API PJH_SubFilesystem 
{
friend class PJH_FilesystemManager;
public :
	typedef std::map<std::string, SubFileSystem_Ptr> MAP_NAME_DIR_TYPE;
	typedef std::map<std::string, PJHFile_Ptr>		 MAP_NAME_FILE_TYPE;

	typedef std::pair<MAP_NAME_DIR_TYPE::const_iterator, MAP_NAME_DIR_TYPE::const_iterator>   DirIteratorPair;
	typedef std::pair<MAP_NAME_FILE_TYPE::const_iterator, MAP_NAME_FILE_TYPE::const_iterator> FileIteratorPair;

private : 
	struct PJH_SubFilesystemDeleter {
		void operator() (PJH_SubFilesystem* sfs) {
			if (sfs)
				delete sfs;
		}
	};

	std::string _rootpath;
	MAP_NAME_DIR_TYPE  _dirchilds;	// Key:Dir's full name
	MAP_NAME_FILE_TYPE _filechilds; // Key:File's full name, Value:File pointer instance.

	explicit PJH_SubFilesystem();
	virtual ~PJH_SubFilesystem();

	static SubFileSystem_Ptr sharedptr_create() 
	{
		return SubFileSystem_Ptr(new PJH_SubFilesystem(), PJH_SubFilesystemDeleter()); 
	}

public :
	// If RootPath were not set, This class assume rootpath is current working directory.
	bool		setRootPath(const char* rootpath);
	const char* getRootPath() const;

	bool isExist(const char* targetname, bool isSearchSub = false) const;

	PJHFile_Ptr		  getFile(const char* targetname, bool isSearchSub = false);
	SubFileSystem_Ptr getDir(const char* targetname, bool isSearchSub = false);

	FileIteratorPair getFileList() const;
	DirIteratorPair  getDirList()  const;

	FileIteratorPair getFileList();
	DirIteratorPair  getDirList();

	bool addFile(const char* filename, const void* buffer = NULL, int buffersize = 0);
	bool deleteFile(const char* filename);

	bool addFolder(const char* foldername);
	bool deleteFolder(const char* foldername);

	void cachingFileList();
	void cachingDirList();
};
} // namespace Filesystem.
} // namespace PJH.

#endif  __PJH_INCLUDE_PJH_SUB_FILESYSTEM_H__