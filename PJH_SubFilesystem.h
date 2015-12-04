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
private : 
	std::string _rootpath;
	std::set<std::string> _dirchilds;			  // Key:Dir's full name
	std::map<std::string, PJH_File*> _filechilds; // Key:File's full name, Value:File pointer instance.

	explicit PJH_SubFilesystem();
	virtual ~PJH_SubFilesystem();

public :
	// If RootPath were not set, This class assume rootpath is current working directory.
	bool		setRootPath(const char* rootpath);
	const char* getRootPath();

	bool isExist(const char* targetname, bool isSearchSub = false) const;

	PJH_File*		   searchFile(const char* targetname, bool isSearchSub = false) const;
	PJH_SubFilesystem* searchDir(const char* targetname, bool isSearchSub = false) const;

	PJH_File* addFile(const char* filename, const void* buffer=NULL);
	bool	  deleteFile(const char* filename);

	PJH_SubFilesystem* addFolder(const char* foldername);
	bool			   deleteFolder(const char* foldername);

	const std::set<std::string>&			getDirs() const;
	const std::map<std::string, PJH_File*>& getFils() const;

	void refresh();
};
} // namespace Filesystem.
} // namespace PJH.

#endif  __PJH_INCLUDE_PJH_SUB_FILESYSTEM_H__