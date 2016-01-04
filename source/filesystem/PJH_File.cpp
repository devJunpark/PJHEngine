#include "filesystem/PJH_File.h"
#include "filesystem/PJH_FileImpl.h"
#include <memory>

using namespace PJH::Filesystem;

PJH_File::PJH_File()
{
	_impl = std::make_shared<Impl::PJH_FileImpl>();
}
PJH_File::~PJH_File()
{

}

bool PJH_File::open(const char* filename, int option)
{
	return _impl->open(filename, option);
}
bool PJH_File::load(void* buffer)
{
	return _impl->load(buffer);
}
bool PJH_File::save(const void* buffer, uint32_t buffersize)
{
	return _impl->save(buffer, buffersize);
}
bool PJH_File::close()
{
	return _impl->close();
}

uint64_t PJH_File::getFileSize() const { return _impl->getFileSize(); }
std::string PJH_File::getFileName() const { return _impl->getFileName(); }
std::string PJH_File::getFilePath() const { return _impl->getFilePath(); }
std::string PJH_File::getFileExtension() const { return _impl->getFileExtension(); }
bool PJH_File::isOpen() const { return _impl->isOpen(); }