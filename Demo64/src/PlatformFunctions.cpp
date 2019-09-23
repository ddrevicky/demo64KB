#include <Windows.h>
#include "PlatformFunctions.h"

FILEREAD(Win32FileRead)
{
	HANDLE fileHandle = 0;
	fileHandle = CreateFileW(fileName, GENERIC_READ, NULL, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	File result = { 0 };
	if (fileHandle != INVALID_HANDLE_VALUE)
	{
		WIN32_FILE_ATTRIBUTE_DATA fileAttributes;
		if (GetFileAttributesExW(fileName, GetFileExInfoStandard, &fileAttributes))
		{
			uint32 fileSize = fileAttributes.nFileSizeLow;
			HANDLE heap = GetProcessHeap();
			result.data = HeapAlloc(heap, HEAP_ZERO_MEMORY, fileSize);
			if (result.data)
			{
				DWORD bytesReadFromFile = 0;
				if (ReadFile(fileHandle, result.data, fileSize, &bytesReadFromFile, NULL) &&
					bytesReadFromFile == fileSize)
				{
					result.size = bytesReadFromFile;
				}
				else
				{
					HeapFree(heap, NULL, result.data);
					OutputDebugStringA("Error reading file\n");
				}
			}
			else
			{
				OutputDebugStringA("Allocation error\n");
			}
		}
		else
		{
			OutputDebugStringA("Error getting file attributes\n");
		}
		CloseHandle(fileHandle);
	}
	else
	{
		DWORD errorMessageID = ::GetLastError();
		LPSTR messageBuffer = nullptr;
		size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

		OutputDebugStringA("Error opening file, SYSTEM MSG: ");
		OutputDebugStringA(messageBuffer);
		LocalFree(messageBuffer);
	}
	return result;
}

FILERELEASE(Win32FileRelease)
{
	HANDLE heap = GetProcessHeap();
	HeapFree(heap, NULL, file.data);
}