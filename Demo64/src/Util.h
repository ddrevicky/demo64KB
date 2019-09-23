#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#pragma once

namespace Util
{
	void DebugOutput(char *format, ...);
}