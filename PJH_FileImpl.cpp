#include "PJH_FileImpl.h"
#include "PJH_Log.h"

using namespace PJH::Filesystem::Impl;

PJH_FileImpl::PJH_FileImpl()
	:_option(FOPEN_READONLY), _fs(NULL)
{

}

PJH_FileImpl::~PJH_FileImpl()
{
	if (_fs) {
		_fs->close();
		delete _fs;
	}
	_fs = NULL;
}

uint64_t PJH_FileImpl::getFileSize() const { return 0; } // Not implemented
int PJH_FileImpl::getFileOption() const { return _option; }
std::string PJH_FileImpl::getFileName() const { return _filename; }
std::string PJH_FileImpl::getFilePath() const { return _path; }
std::string PJH_FileImpl::getFileExtension() const { return _extension; }
bool PJH_FileImpl::isOpen() const { return _fs != NULL && _fs->is_open(); }

bool PJH_FileImpl::open(const char* filename, int option)
{
	if (filename == NULL)
		return false;
	
	_option = option;
	std::fstream::open_mode mode;

	if (option & PJH_FileOp::FOPEN_READWRITE)
		mode = std::ios::in | std::ios::out;
	else if (option & PJH_FileOp::FOPEN_READONLY) 
		mode = std::ios::in;
	else if (option & PJH_FileOp::FOPEN_WRITEONLY) 
		mode = std::ios::out;

	if (option & PJH_FileOp::FOPEN_APPENDWRITE)
		mode |= std::ios::app;
	else if (option & PJH_FileOp::FOPEN_OVERWRITE)
		mode |= std::ios::trunc;
	else if (option & PJH_FileOp::FOPEN_CREATE)
		mode |= std::ios::trunc;

	if (option & PJH_FileOp::FOPEN_BINARYMODE)  mode |= std::ios::binary;

	_fs = new std::fstream();
	_fs->open(filename, mode);

	bool result = isOpen();

	if (result) {
		_filename.append(filename);
		PJH_TAG_LOG("PJH_FileImpl", "FileName[%s], option[%d]", filename, option);
	}
	else {
		PJH_TAG_LOG("PJH_FileImpl", "Failed to open file.")
	}
	
	return result;
}

bool PJH_FileImpl::load(void* buffer)
{
	return false;
}
bool PJH_FileImpl::save(const void* buffer, uint32_t buffersize)
{
	return false;
}
bool PJH_FileImpl::close()
{
	if (!isOpen()) return false;

	_fs->close();
	return true;
}