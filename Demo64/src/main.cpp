#include <windows.h>
#include "glFunctions.h"
#include "App.h"
#include "main.h"
#include <cassert>

/* Definitions */
PFGLFINISH glFinish;
PFGLCLEARCOLOR glClearColor;
PFGLCLEAR glClear;
PFNGLCREATESHADERPROC glCreateShader;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
PFNGLBINDVERTEXARRAY glBindVertexArray;
PFNGLGENBUFFERS glGenBuffers;
PFNGLBINDBUFFERPROC glBindBuffer;
PFNGLBUFFERDATAPROC glBufferData;
PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
PFNGLCOMPILESHADERPROC glCompileShader;
PFNGLCREATEPROGRAMPROC glCreateProgram;
PFNGLATTACHSHADERPROC glAttachShader;
PFNGLLINKPROGRAMPROC glLinkProgram;
PFNGLDETACHSHADERPROC glDetachShader;
PFNGLUSEPROGRAMPROC glUseProgram;
PFNGLGETUNIFORMLOCATIONARBPROC glGetUniformLocation;
PFNGLUNIFORM1FARBPROC glUniform1f;
PFNGLUNIFORM2FARBPROC glUniform2f;
PFNGLUNIFORM3FARBPROC glUniform3f;
PFNGLSHADERSOURCEPROC glShaderSource;
PFNGLDRAWELEMENTS glDrawElements;
PFNGLGETSHADERIVPROC glGetShaderiv;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;

bool isRunning = true;
const char g_szClassName[] = "myWindowClass";
static WINDOWPLACEMENT GlobalWindowPosition = {sizeof(GlobalWindowPosition)};

// Function source: Raymond Chen - https://blogs.msdn.microsoft.com/oldnewthing/20100412-00/?p=14353/
void ToggleFullScreen(HWND hwnd)
{
	DWORD dwStyle = GetWindowLong(hwnd, GWL_STYLE);
	if (dwStyle & WS_OVERLAPPEDWINDOW) 
	{
		MONITORINFO mi = { sizeof(mi) };
		if (GetWindowPlacement(hwnd, &GlobalWindowPosition) &&
			GetMonitorInfo(MonitorFromWindow(hwnd,
				MONITOR_DEFAULTTOPRIMARY), &mi)) 
		{
			SetWindowLong(hwnd, GWL_STYLE,
				dwStyle & ~WS_OVERLAPPEDWINDOW);
			SetWindowPos(hwnd, HWND_TOP,
				mi.rcMonitor.left, mi.rcMonitor.top,
				mi.rcMonitor.right - mi.rcMonitor.left,
				mi.rcMonitor.bottom - mi.rcMonitor.top,
				SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
		}
	}
	else 
	{
		SetWindowLong(hwnd, GWL_STYLE,
			dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(hwnd, &GlobalWindowPosition);
		SetWindowPos(hwnd, NULL, 0, 0, 0, 0,
			SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER |
			SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
	}
}

void *GetAnyGLFuncAddress(const char *name)
{
	void *p = (void *)wglGetProcAddress(name);
	if (p == 0 || (p == (void*)0x1) || (p == (void*)0x2) || (p == (void*)0x3) || (p == (void*)-1))
	{
		HMODULE module = LoadLibraryA("opengl32.dll");
		p = (void *)GetProcAddress(module, name);
	}

	assert(p);
	return p;
}

void InitOpenGLFunctions()
{
	glFinish = (PFGLFINISH)GetAnyGLFuncAddress("glFinish");
	glClearColor = (PFGLCLEARCOLOR)GetAnyGLFuncAddress("glClearColor");
	glClear = (PFGLCLEAR)GetAnyGLFuncAddress("glClear");
	glCreateShader = (PFNGLCREATESHADERPROC)GetAnyGLFuncAddress("glCreateShader");
	glShaderSource = (PFNGLSHADERSOURCEPROC)GetAnyGLFuncAddress("glShaderSource");
	glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)GetAnyGLFuncAddress("glVertexAttribPointer");
	glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)GetAnyGLFuncAddress("glEnableVertexAttribArray");
	glBindVertexArray = (PFNGLBINDVERTEXARRAY)GetAnyGLFuncAddress("glBindVertexArray");
	glGenBuffers = (PFNGLGENBUFFERS)GetAnyGLFuncAddress("glGenBuffers");
	glBindBuffer = (PFNGLBINDBUFFERPROC)GetAnyGLFuncAddress("glBindBuffer");
	glBufferData = (PFNGLBUFFERDATAPROC)GetAnyGLFuncAddress("glBufferData");
	glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)GetAnyGLFuncAddress("glGenVertexArrays");
	glCompileShader = (PFNGLCOMPILESHADERPROC)GetAnyGLFuncAddress("glCompileShader");
	glCreateProgram = (PFNGLCREATEPROGRAMPROC)GetAnyGLFuncAddress("glCreateProgram");
	glAttachShader = (PFNGLATTACHSHADERPROC)GetAnyGLFuncAddress("glAttachShader");
	glLinkProgram = (PFNGLLINKPROGRAMPROC)GetAnyGLFuncAddress("glLinkProgram");
	glDetachShader = (PFNGLDETACHSHADERPROC)GetAnyGLFuncAddress("glDetachShader");
	glUseProgram = (PFNGLUSEPROGRAMPROC)GetAnyGLFuncAddress("glUseProgram");
	glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONARBPROC)GetAnyGLFuncAddress("glGetUniformLocation");
	glUniform1f = (PFNGLUNIFORM1FARBPROC)GetAnyGLFuncAddress("glUniform1f");
	glUniform2f = (PFNGLUNIFORM2FARBPROC)GetAnyGLFuncAddress("glUniform2f");
	glUniform3f = (PFNGLUNIFORM3FARBPROC)GetAnyGLFuncAddress("glUniform3f");
	glGetShaderiv = (PFNGLGETSHADERIVPROC)GetAnyGLFuncAddress("glGetShaderiv");
	glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)GetAnyGLFuncAddress("glGetShaderInfoLog");

	glDrawElements = (PFNGLDRAWELEMENTS)GetAnyGLFuncAddress("glDrawElements");
}

// Source: https://www.opengl.org/wiki/Creating_an_OpenGL_Context_%28WGL%29
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	{
		PIXELFORMATDESCRIPTOR pfd =
		{
			sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,  //Flags
			PFD_TYPE_RGBA,            //The kind of Framebuffer. RGBA or palette.
			32,                        //Colordepth of the Framebuffer.
			0, 0, 0, 0, 0, 0,
			0,
			0,
			0,
			0, 0, 0, 0,
			24,                        //Number of bits for the depthbuffer
			8,                        //Number of bits for the stencilbuffer
			0,                        //Number of Aux buffers in the Framebuffer.
			PFD_MAIN_PLANE,
			0,
			0, 0, 0
		};

		HDC ourWindowHandleToDeviceContext = GetDC(hWnd);

		int letWindowsChooseThisPixelFormat = ChoosePixelFormat(ourWindowHandleToDeviceContext, &pfd);
		SetPixelFormat(ourWindowHandleToDeviceContext, letWindowsChooseThisPixelFormat, &pfd);

		HGLRC ourOpenGLRenderingContext = wglCreateContext(ourWindowHandleToDeviceContext);
		wglMakeCurrent(ourWindowHandleToDeviceContext, ourOpenGLRenderingContext);

	} break;

	case WM_CLOSE:
	{
		isRunning = false;
	} break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

static void ProcessMessages(HWND window, Context *context)
{
	MSG message;
	while (PeekMessageA(&message, window, 0, 0, PM_REMOVE))
	{
		switch (message.message)
		{
		case WM_SYSKEYDOWN:
		case WM_KEYDOWN:
		{
			switch (message.wParam)
			{
			case VK_ESCAPE:
				isRunning = false;
				break;
			case 'W':
				context->wPressed = true;
				break;
			case 'A':
				context->aPressed = true;
				break;
			case 'S':
				context->sPressed = true;
				break;
			case 'D':
				context->dPressed = true;
				break;
			case 'R':
				context->rPressed = true;
				break;
			case 'F':
				ToggleFullScreen(window);
				context->fPressed = true;
				break;
			case 'Q':
				context->qPressed = true;
				break;
			case VK_UP:
				context->upPressed = true;
				break;
			}
		} break;

		case WM_KEYUP:
		{
			switch (message.wParam)
			{
			case VK_ESCAPE:
				isRunning = false;
				break;
			case 'W':
				context->wPressed = false;
				break;
			case 'A':
				context->aPressed = false;
				break;
			case 'S':
				context->sPressed = false;
				break;
			case 'D':
				context->dPressed = false;
				break;
			case 'R':
				context->rPressed = false;
				break;
			case 'F':
				context->fPressed = false;
				break;
			case 'Q':
				context->qPressed = false;
				break;
			case VK_UP:
				context->upPressed = false;
				break;
			}
		} break;

		case WM_LBUTTONDOWN:
		{
			if (!context->leftButtonDown)
			{
				context->leftButtonPressed = true;
			}
			context->leftButtonDown = true;
		} break;

		case WM_MOUSEMOVE:
		{
			{
				context->mousePosition.x = (float)uint16((message.lParam));
				context->mousePosition.y = (float)uint16((message.lParam >> 16));
				if (context->leftButtonDown == false)
				{
					context->previousMousePosition.x = context->mousePosition.x;
					context->previousMousePosition.y = context->mousePosition.y;
				}
			}
		} break;

		case WM_LBUTTONUP:
		{
			context->leftButtonDown = false;
		} break;

		default:
		{
			TranslateMessage(&message);
			DispatchMessageA(&message);
		} break;
		}
	}
}

#define MAXSAMPLES 50
int tickindex = 0;
float ticksum = 0;
float ticklist[MAXSAMPLES] = {};

float CalcAverageTick(float newtick)
{
	ticksum -= ticklist[tickindex];  
	ticksum += newtick;              
	ticklist[tickindex] = newtick;   
	if (++tickindex == MAXSAMPLES)
		tickindex = 0;

	return(ticksum / MAXSAMPLES);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	WNDCLASSEXA windowClass = {};
	windowClass.cbSize = sizeof(WNDCLASSEXA);
	windowClass.style = CS_VREDRAW | CS_HREDRAW;
	windowClass.lpfnWndProc = WndProc;
	windowClass.hInstance = hInstance;
	windowClass.lpszClassName = "64kBDemo";
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);

	LARGE_INTEGER clockFreq;
	QueryPerformanceFrequency(&clockFreq);
	LARGE_INTEGER startTime, endTime, elapsedTicks;
	QueryPerformanceCounter(&startTime);
	
	if (RegisterClassExA(&windowClass))
	{
		DWORD style = WS_VISIBLE | WS_OVERLAPPEDWINDOW;
		DWORD dwExStyle = WS_EX_TOPMOST;

		RECT wr = { 0, 0, SCREEN_X, SCREEN_Y };
		AdjustWindowRectEx(&wr, style, FALSE, dwExStyle);  

		HWND window = CreateWindowExA(dwExStyle, windowClass.lpszClassName, "64kBDemo", style,
			CW_USEDEFAULT, CW_USEDEFAULT, wr.right - wr.left, wr.bottom - wr.top,
			NULL, NULL, hInstance, NULL);

		InitOpenGLFunctions();

		Context context = {};
		App::Init(&context);
		glClearColor(1, 0, 0, 1);

		HDC windowHandle = GetDC(window);

		wchar_t buffer[256] = {};
		if (window)
		{
			// Disabling VSync for benchmarking
#if 0
			typedef BOOL(WINAPI *PFNWGLSWAPINTERVALEXTPROC)(int interval);
			PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT = NULL;
			wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
			if (wglSwapIntervalEXT)
			{
				 wglSwapIntervalEXT(0);		// Turn VSYNC off
			}
#endif
			
			while (isRunning)
			{
				QueryPerformanceCounter(&endTime);
				elapsedTicks.QuadPart = endTime.QuadPart - startTime.QuadPart;
				startTime.QuadPart = endTime.QuadPart;
				float dt = (float)elapsedTicks.QuadPart / clockFreq.QuadPart;

#ifdef _DEBUG
				float avgSecondsPerFrame = CalcAverageTick(dt);
				float avgMSPerFrame = 1000 * avgSecondsPerFrame;
				float avgFPS = 1.0f / avgSecondsPerFrame;
				_snwprintf_s(buffer, 200, L"AvgMS %.5f   AvgFPS %.1f\n", avgMSPerFrame, avgFPS);
				OutputDebugStringW(buffer);
#endif
		
				ProcessMessages(window, &context);
				App::Update(&context, dt);
				SwapBuffers(windowHandle);
			}
		}
	}
}