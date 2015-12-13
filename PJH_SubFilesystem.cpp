#include "PJH_Filesystem.h"
#include "PJH_SubFilesystem.h"
#include "PJH_Log.h"
#include "PJH_File.h"

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

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
	MAP_NAME_DIR_TYPE::iterator diriter = _dirchilds.begin();
	while (diriter != _dirchilds.end())
	{
		if (diriter->second != NULL){
			PJH_FilesystemManager::getInstance()->closeSubFilesystem(diriter->second);
			_dirchilds.erase(diriter);
		}
		diriter = _dirchilds.begin();
	}
	MAP_NAME_FILE_TYPE::iterator fileiter = _filechilds.begin();
	while (fileiter != _filechilds.end())
	{
		if (fileiter->second != NULL) {
			if (fileiter->second->isOpen())
				fileiter->second->close();
			_filechilds.erase(fileiter);
		}
		fileiter = _filechilds.begin();
	}
	_dirchilds.clear();
	_filechilds.clear();
}

bool PJH_SubFilesystem::setRootPath(const char* rootpath)
{
	if (rootpath == NULL)
		return false;
	if (!PJH_FilesystemManager::isExistPath(rootpath)) {
		PJH_TAG_LOG("PJH_SubFilesystem::setRootPath",
			"rootpath that was passed doesn't exist path. You must check path of argument");
		return false;
	}

	if (!_rootpath.empty()) 
		_rootpath.clear();
	_rootpath.append(rootpath);
	if (!_rootpath.empty()) {
		char lastchar = *(_rootpath.rbegin());
		if (lastchar != '\\' && lastchar != '/')
			_rootpath.append("/");
	}
	return true;
}
const char* PJH_SubFilesystem::getRootPath() const
{
	return _rootpath.empty() ? NULL : _rootpath.c_str();
}

bool PJH_SubFilesystem::isExist(const char* targetname, bool isSearchSub) const
{
	namespace fs = boost::filesystem;

	if (!targetname) {
		PJH_TAG_LOG("PJH_SubFilesystem::isExist", "you passed invalid pointer as targetname.");
		return false;
	}
	std::string relatedpath{ getRootPath() };
	relatedpath.append(targetname);
	if (isSearchSub) {
		/// @@ TODO::

	}
	else {
		fs::path targetdir{ relatedpath.c_str() };
		return fs::exists(targetdir);
	}

	return false;
}

bool PJH_SubFilesystem::addFile(const char* filename, const void* buffer, int buffersize)
{
	if (!filename) {
		PJH_TAG_LOG("PJH_SubFilesystem::addFile", "you passed invalid pointer as targetname.");
		return false;
	}
	std::string strFilename{ filename };
	MAP_NAME_FILE_TYPE::const_iterator iter = _filechilds.begin();
	PJHFile_Ptr rtvfile = NULL;
	for (iter; iter != _filechilds.end(); ++iter)
	{
		if (iter->first == strFilename) {
			rtvfile = iter->second;
			break;
		}
	}
	std::string fullpath{ getRootPath() };
	fullpath.append(filename);
	int option = PJH_FileOp::FOPEN_READWRITE;
	if (!rtvfile) {
		rtvfile = PJHFile_Ptr(new PJH_File());
		rtvfile->open(fullpath.c_str(), 
					  isExist(filename) ? option : option | PJH_FileOp::FOPEN_CREATE);
		_filechilds.insert(std::pair<std::string, PJHFile_Ptr>(strFilename, rtvfile));
	}
	else if (!rtvfile->isOpen()) {
		rtvfile->open(fullpath.c_str(), option);
	}

	if (buffer != NULL && buffersize != 0)
		rtvfile->save(buffer, buffersize);
	rtvfile->close();
	
	return true;
}

bool PJH_SubFilesystem::deleteFile(const char* filename)
{
	namespace fs = boost::filesystem;

	if (!filename){
		PJH_TAG_LOG("PJH_SubFilesystem::deleteFile", "you passed invalid pointer as targetname.");
		return false;
	}
	else {
		if (!isExist(filename)) {
			PJH_TAG_LOG("PJH_SubFilesystem::deleteFile", "This file doesn't exist on this subfilesystem");
			return false;
		}
	}
	std::string strFilename{ filename };
	MAP_NAME_FILE_TYPE::iterator iter = _filechilds.begin();
	for (iter; iter != _filechilds.end(); ++iter)
	{
		if (iter->first == strFilename) 
			break;
	}
	if (iter != _filechilds.end()) { // successed searching file instance.
		PJHFile_Ptr file = iter->second;
		if (file != NULL && file->isOpen())
			file->close();
		_filechilds.erase(iter);
	}
	std::string fullpath{ getRootPath() };
	fs::path targetfile{ fullpath.append(filename).c_str() };
	return fs::remove(targetfile);;
}

bool PJH_SubFilesystem::addFolder(const char* foldername)
{
	namespace fs = boost::filesystem;

	if (!foldername) {
		PJH_TAG_LOG("PJH_SubFilesystem::addFolder", "you passed invalid pointer as targetname.");
		return NULL;
	}
	std::string strDirName{ foldername };
	MAP_NAME_DIR_TYPE::const_iterator citer = _dirchilds.begin();
	SubFileSystem_Ptr sfs = NULL;
	for (citer; citer != _dirchilds.end(); ++citer)
	{
		if (citer->first == strDirName) {
			sfs = citer->second;
			break;
		}
	}
	if (!sfs) { // Target was already cached on memory;
		if (!isExist(foldername)) { // Target didn't exist yet.
			std::string fullpath{ getRootPath() };
			fullpath.append(foldername);
			fs::path dirpath{ fullpath.c_str() };
			bool isSuccessed = fs::create_directories(dirpath);
			if (isSuccessed) {
				sfs = PJH_FilesystemManager::getInstance()->openSubFilesystem(fullpath.c_str());
				_dirchilds.insert(std::pair<std::string, SubFileSystem_Ptr>(strDirName, sfs));
			}
			return isSuccessed;
		}
	}
	return false;
}
bool PJH_SubFilesystem::deleteFolder(const char* foldername)
{
	namespace fs = boost::filesystem;

	if (!foldername) {
		PJH_TAG_LOG("PJH_SubFilesystem::addFolder", "you passed invalid pointer as targetname.");
		return NULL;
	}
	std::string strDirName{ foldername };
	MAP_NAME_DIR_TYPE::const_iterator iter = _dirchilds.begin();
	SubFileSystem_Ptr sfs = NULL;
	for (iter; iter != _dirchilds.end(); ++iter)
	{
		if (iter->first == strDirName) {
			sfs = iter->second;
			break;
		}
	}
	std::string fullpath{ getRootPath() };
	fullpath.append(foldername);
	fs::path dirpath{ fullpath.c_str() };
	bool isRemoveSuccessed = false;
	if (isExist(foldername))
		isRemoveSuccessed = fs::remove(dirpath);
	if (sfs){
		if (isRemoveSuccessed) {
			PJH_FilesystemManager::getInstance()->closeSubFilesystem(sfs);
			_dirchilds.erase(iter);
		}
	}
	return isRemoveSuccessed;
}

SubFileSystem_Ptr PJH_SubFilesystem::getDir(const char* targetname, bool isSearchSub)
{
	namespace fs = boost::filesystem;

	if (!targetname) {
		PJH_TAG_LOG("PJH_SubFilesystem::getDir", "you passed invalid pointer as targetname.");
		return NULL;
	}
	std::string strFoldername{ targetname };
	MAP_NAME_DIR_TYPE::const_iterator citer = _dirchilds.begin();
	SubFileSystem_Ptr sfs = NULL;
	for (citer; citer != _dirchilds.end(); ++citer)
	{
		if (citer->first == strFoldername) {
			sfs = citer->second;
			break;
		}
	}
	if (!sfs) {
		if (isExist(targetname)) {
			std::string fullpath{ getRootPath() };
			fullpath.append(targetname);
			sfs = PJH_FilesystemManager::getInstance()->openSubFilesystem(fullpath.c_str());
			if (!sfs) {
				PJH_TAG_LOG("PJH_SubFilesystem::getDir", 
							"Unknown Error during trying to get directory path[%s]!", fullpath.c_str());
			}
			else {
				_dirchilds.insert(std::pair<std::string, SubFileSystem_Ptr>(strFoldername, sfs));
			}
		}
	}

	return sfs;
}

PJHFile_Ptr PJH_SubFilesystem::getFile(const char* targetname, bool isSearchSub)
{
	namespace fs = boost::filesystem;

	if (!targetname) {
		PJH_TAG_LOG("PJH_SubFilesystem::getFile", "you passed invalid pointer as targetname.");
		return NULL;
	}

	std::string strFilename{ targetname };
	MAP_NAME_FILE_TYPE::const_iterator citer = _filechilds.begin();
	PJHFile_Ptr fp = NULL;
	for (citer; citer != _filechilds.end(); ++citer)
	{
		if (citer->first == strFilename) {
			fp = citer->second;
			break;
		}
	}
	if (!fp) {
		if (isExist(targetname)) {
			std::string fullpath{ getRootPath() };
			fullpath.append(targetname);
			fp = PJHFile_Ptr(new PJH_File());
			if (fp){
				_filechilds.insert(std::pair<std::string, PJHFile_Ptr>(strFilename, fp));
			}
		}
	}
	return fp;
}

} // namespace Filesystem
} // namespace PJH