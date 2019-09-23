#include "Util.h"
#include <stdarg.h>
#include <string>
#include <windows.h>

static char debugBuffer[1000];

void Util::DebugOutput(char *format, ...)
{
	//#ifdef _DEBUG
	va_list argList;
	va_start(argList, format);
	char *currentDebugBuffer = debugBuffer;
	vsprintf_s(currentDebugBuffer, ARRAYSIZE(debugBuffer), format, argList);
	va_end(argList);
	OutputDebugStringA(currentDebugBuffer);
	//#endif
}