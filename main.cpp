#include <iostream>

#include "PJH_File.h"
#include "PJH_Filesystem.h"
#include "PJH_Assert.h"
#include "PJH_SubFilesystem.h"

int main()
{
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
	sfs = sfminstance->openSubFilesystem("E:\\pr\\FMP\\FMP\\Dev\\Client\\Main");
	if (sfs && sfs->getRootPath() != NULL) {
		std::cout << sfs->getRootPath() << std::endl;
		sfs->setRootPath("C:/");
		std::cout << sfs->getRootPath() << std::endl;
		sfs->setRootPath(NULL);
		std::cout << sfs->getRootPath() << std::endl;
	}
	else {
		PJH_LOG("Doesn't exist path");
	}

	sfminstance->closeSubFilesystem(sfs);
	sfminstance->release();
	getchar();

	return 0;
}