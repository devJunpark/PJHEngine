#ifndef __PJH_INCLUDE_PJH_FILE_IMPL_H__
#define __PJH_INCLUDE_PJH_FILE_IMPL_H__

#include <string>
#include <cstdint>
#include <fstream>
#include "filesystem/PJH_FileDef.h"

namespace PJH {
namespace Filesystem{
namespace Impl {
class PJH_FileImpl 
{
public : 
	

private : 
	int			_option;

	std::string _filename;
	std::string _path;
	std::string _extension;

	std::fstream* _fs;

public :
	explicit PJH_FileImpl();
	virtual ~PJH_FileImpl();

	bool open(const char* filename, 
			  int option = PJH_FileOp::FOPEN_READWRITE | PJH_FileOp::FOPEN_CREATE);
	bool load(void* buffer);
	bool save(const void* buffer, uint32_t buffersize);
	bool close();

	uint64_t getFileSize() const;
	int getFileOption() const;
	std::string getFileName() const;
	std::string getFilePath() const;
	std::string getFileExtension() const;
	bool isOpen() const;
};
} // Impl
} // Filesystem
} // PJH

#endif  __PJH_INCLUDE_PJH_FILE_IMPL_H__