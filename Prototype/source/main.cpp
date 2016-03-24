#include <iostream>

#include "filesystem/PJH_File.h"
#include "filesystem/PJH_Filesystem.h"
#include "assert/PJH_Assert.h"
#include "filesystem/PJH_SubFilesystem.h"
#include "profiling/PJH_Profiling.h"

#include <thread>

int main()
{
	//PJH_TIMESTAMP_START_WITH_ID("MAIN");

	PJH_LOWLEVEL_PROFILE_START;

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

	std::this_thread::sleep_for(std::chrono::milliseconds(1234));

	/*if (!PJH::Filesystem::PJH_FilesystemManager::isExistFile("test1.txt"))
		PJH_ABORT_STR("this file doesn't exist");
	else
		std::cout << "test.txt exist" << std::endl;

	file.close();

	PJH::Filesystem::PJH_FilesystemManager* sfminstance = PJH::Filesystem::PJH_FilesystemManager::getInstance();
	{
		PJH::Filesystem::SubFileSystem_Ptr sfs = NULL;
		sfs = sfminstance->openSubFilesystem();
		if (sfs && sfs->getRootPath() != NULL) {
			if (sfs->addFolder("testfolder")) {
				std::cout << "successed to add folder" << std::endl;
			}
			sfs->addFile("hihi.text");
			pjhfs::SubFileSystem_Ptr sfs2 = sfs->getDir("scripts");
			if (sfs2 && sfs->isExist("git")){
				std::cout << "git folder exist" << std::endl;
			}
		}
		else {
			PJH_LOG("Doesn't exist path");
		}
		sfminstance->closeSubFilesystem(sfs);
	}
	sfminstance->release();*/

	//time_t t = PJH_TIMESTAMP_END_WITH_ID("MAIN");
	time_t t = PJH_LOWLEVEL_PROFILE_END;

	std::cout << "PROFILE TIME : " << t << "ms" << std::endl;

	getchar();

	return 0;
}