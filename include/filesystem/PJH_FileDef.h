#ifndef __PJH_INCLUDE_PJH_FILEDEF_H__
#define __PJH_INCLUDE_PJH_FILEDEF_H__

namespace PJH {
namespace Filesystem{
enum PJH_FileOp {
	FOPEN_CREATE	  = 0x1,		// If the file doesn't exist, It will be created.
	FOPEN_READONLY    = 0x1 << 1,	// Read only mode.  If the file doesn't exist, It will be not created.
	FOPEN_WRITEONLY   = 0x1 << 2,	// Write only mode. If the file doesn't exist, It will be not created.
	FOPEN_READWRITE   = 0x1 << 3, // you can read and write.

	FOPEN_OVERWRITE	  = 0x1 << 4, // If the file already exist, It will be deleted then It will be created newly.
	FOPEN_APPENDWRITE = 0x1 << 5, // This flag include FOPEN_CREATE flag. just append if you were write.

	FOPEN_BINARYMODE  = 0x1 << 6, // It will try to open as binary mode.
};

enum PJH_FileAttr {
	FATTR_NAME = 0,
	FATTR_LASTACCESS_TIME,
	FAATR_CREATED_TIME,
	FATTR_EXTENSION,
	FATTR_SIZE,
};
}
}

#endif  __PJH_INCLUDE_PJH_FILEDEF_H__
