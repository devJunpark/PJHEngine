#pragma once
#include <string>
#include <memory>

namespace PJH {
class Filesystem
{
	typedef enum {


	} FS_OPTION;

private : 
	static std::string _rootpath;
	static std::unique_ptr<Filesystem> _uinstance;

	explicit Filesystem();
	~Filesystem();

public : 
	static std::unique_ptr<Filesystem> getInstance();

	const char* getRootPath() const;

	bool isExistFile(const char* filename) const;
	bool isExistDir(const char* dirname) const;

    bool readFile(const void* buff, const char* filename, const char* dirpath=NULL) const;
	bool wirteFile(const void* buff, const char* filename, const char* dirpath=NULL) const;

	unsigned int getFileSize(const char* filename, const char* dirpath = NULL) const;
	unsigned int getDirSize(const char* dirpath=NULL) const;
};
}
