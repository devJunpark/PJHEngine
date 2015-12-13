#include <iostream>

#include "PJH_File.h"
#include "PJH_Filesystem.h"
#include "PJH_Assert.h"
#include "PJH_SubFilesystem.h"

int main()
{
	namespace pjhfs = PJH::Filesystem;
	PJH::Filesystem::PJH_File file;

	file.open("test1.txt", 
		/*PJH::Filesystem::PJH_FileOp::FOPEN_CREATE |*/ 
		PJH::Filesystem::PJH_FileOp::FOPEN_WRITEONLY);

	if (file.isOpen()) {
		std::cout << "successe" << std::endl;
	}
	else {
		std::cout << "Failed" << std::endl;
	}

	char path[1024];
	if (!PJH::Filesystem::PJH_FilesystemManager::getWorkingDirectory(path, sizeof(path)))
		PJH_ABORT;
		
	std::cout << path << std::endl;

	if (!PJH::Filesystem::PJH_FilesystemManager::isExistFile("test1.txt"))
		PJH_ABORT_STR("this file doesn't exist");
	else
		std::cout << "test.txt exist" << std::endl;

	file.close();

	PJH::Filesystem::PJH_FilesystemManager* sfminstance = PJH::Filesystem::PJH_FilesystemManager::getInstance();
	PJH::Filesystem::PJH_SubFilesystem* sfs = NULL;
	sfs = sfminstance->openSubFilesystem("D://engine//PJHEngine//PJHEngine");
	if (sfs && sfs->getRootPath() != NULL) {
		std::cout << sfs->getRootPath() << std::endl;

		bool isExistFolder = sfs->isExist("scripts");
		if ( isExistFolder)
			std::cout << "Folder Exist" << std::endl;
		else
			std::cout << "Folder doesn't Exist" << std::endl;

		std::cout << "isExist test.txt : " << sfs->isExist("test1.txt") << std::endl;
		sfs->deleteFile("test1.txt");
		std::cout << "isExist test.txt : " << sfs->isExist("test1.txt") << std::endl;

		sfs->addFile("test12.txt");
		std::cout << "isExist test.txt : " << sfs->isExist("test12.txt") << std::endl;

		std::cout << "Ready to get dir" << std::endl;
		pjhfs::PJH_SubFilesystem* subfs = sfs->getDir("scripts");
		if (subfs) {
			std::cout << "getdir successed" << std::endl;
		}

		std::cout << "Ready to get file" << std::endl;
		pjhfs::PJH_File* fp = sfs->getFile("abcd.txt");
		if (fp) {
			std::cout << "getfile successed" << std::endl;
		}
		fp = sfs->getFile("test12.txt");
		if (fp) {
			std::cout << "getfile successed" << std::endl;
		}
	}
	else {
		PJH_LOG("Doesn't exist path");
	}

	sfminstance->closeSubFilesystem(sfs);
	sfminstance->release();
	getchar();

	return 0;
}