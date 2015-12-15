#ifndef __PJH_INCLUDE_PJH_FILE_H__
#define __PJH_INCLUDE_PJH_FILE_H__

#include <string>
#include <cstdint>
#include <memory>
#include "PJH_FileDef.h"

namespace PJH {
namespace Filesystem {
class PJH_File;
typedef std::shared_ptr<PJH_File> PJHFile_Ptr;
namespace Impl {
	class PJH_FileImpl;
} // Impl
class PJH_File
{
private : 
	std::shared_ptr < Impl::PJH_FileImpl > _impl;

public :
	explicit PJH_File();
	virtual ~PJH_File();

	bool open(const char* filename,
		int option = PJH_FileOp::FOPEN_READWRITE | PJH_FileOp::FOPEN_CREATE);
	bool load(void* buffer);
	bool save(const void* buffer, uint32_t buffersize);
	bool close();

	uint64_t getFileSize() const;
	std::string getFileName() const;
	std::string getFilePath() const;
	std::string getFileExtension() const;
	bool isOpen() const;
};
} // Filesystem
} // PJH

#endif  __PJH_INCLUDE_PJH_FILE_H__