#ifndef __PJH_INCLUDE_PJH_SUB_FILESYSTEM_H__
#define __PJH_INCLUDE_PJH_SUB_FILESYSTEM_H__

#include <string>
#include <map>
#include <set>

// This class must be created by PJH_Filesystemmanager.

namespace PJH {
namespace Filesystem {
class PJH_File;
class PJH_SubFilesystem 
{
friend class PJH_FilesystemManager;
public :
	typedef std::map<std::string, PJH_SubFilesystem*> MAP_NAME_DIR_TYPE;
	typedef std::map<std::string, PJH_File*>		  MAP_NAME_FILE_TYPE;
private : 

	std::string _rootpath;
	MAP_NAME_DIR_TYPE  _dirchilds;	// Key:Dir's full name
	MAP_NAME_FILE_TYPE _filechilds; // Key:File's full name, Value:File pointer instance.

	explicit PJH_SubFilesystem();
	virtual ~PJH_SubFilesystem();
public :
	// If RootPath were not set, This class assume rootpath is current working directory.
	bool		setRootPath(const char* rootpath);
	const char* getRootPath() const;

	bool isExist(const char* targetname, bool isSearchSub = false) const;

	PJH_File*		   getFile(const char* targetname, bool isSearchSub = false);
	PJH_SubFilesystem* getDir( const char* targetname, bool isSearchSub = false);

	MAP_NAME_FILE_TYPE::const_iterator getFileList() const;
	MAP_NAME_DIR_TYPE::const_iterator  getDirList()  const;

	bool addFile(const char* filename, const void* buffer = NULL, int buffersize = 0);
	bool deleteFile(const char* filename);

	bool addFolder(const char* foldername);
	bool deleteFolder(const char* foldername);

	void refresh();
};
} // namespace Filesystem.
} // namespace PJH.

#endif  __PJH_INCLUDE_PJH_SUB_FILESYSTEM_H__