#pragma once
#include "Def.h"

struct File
{
	uint32 size;
	void *data;
};

#define FILEREAD(name) File name(const wchar_t *fileName)
typedef FILEREAD(FileRead);

#define FILERELEASE(name) void name(File file)
typedef FILERELEASE(FileRelease);
