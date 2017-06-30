#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#include <windows.h>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <string>
#include <iostream>

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[] = _T("newApplication");

HWND textWindow, submitButton, open, clearWindow, nameOfFile, nameOfFile2, createFile;
HINSTANCE hInstance;

int WINAPI WinMain(HINSTANCE hThisInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpszArgument,
	int nCmdShow)
{
	HWND hwnd;               /* This is the handle for our window */
	MSG messages;            /* Here messages to the application are saved */
	WNDCLASSEX wincl;        /* Data structure for the windowclass */

							 /* The Window structure */
	wincl.hInstance = hThisInstance;
	wincl.lpszClassName = szClassName;
	wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
	wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
	wincl.cbSize = sizeof(WNDCLASSEX);

	/* Use default icon and mouse-pointer */
	wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
	wincl.lpszMenuName = NULL;                 /* No menu */
	wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
	wincl.cbWndExtra = 0;                      /* structure or the window instance */
											   /* Use Windows's default colour as the background of the window */
	wincl.hbrBackground = (HBRUSH)COLOR_BACKGROUND;

	/* Register the window class, and if it fails quit the program */
	if (!RegisterClassEx(&wincl))
		return 0;

	/* The class is registered, let's create the program*/
	hwnd = CreateWindowEx(
		0,                   /* Extended possibilites for variation */
		szClassName,         /* Classname */
		_T("New Application 2017-06-28"),       /* Title Text */
		WS_OVERLAPPED | WS_SYSMENU, /* default window */
		CW_USEDEFAULT,       /* Windows decides the position */
		CW_USEDEFAULT,       /* where the window ends up on the screen */
		544,                 /* The programs width */
		375,                 /* and height in pixels */
		HWND_DESKTOP,        /* The window is a child-window to desktop */
		NULL,                /* No menu */
		hThisInstance,       /* Program Instance handler */
		NULL                 /* No Window Creation data */
	);

	/* Make the window visible on the screen */
	ShowWindow(hwnd, nCmdShow);

	/* Run the message loop. It will run until GetMessage() returns 0 */
	while (GetMessage(&messages, NULL, 0, 0))
	{
		/* Translate virtual-key messages into character messages */
		TranslateMessage(&messages);
		/* Send message to WindowProcedure */
		DispatchMessage(&messages);
	}

	/* The program return-value is 0 - The value that PostQuitMessage() gave */
	return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	char text[10000];
	char fileName[100];
	char fileName2[100];

	switch (message)                  /* handle the messages */
	{
	case WM_CREATE:
		
		submitButton = CreateWindowExA(WS_EX_WINDOWEDGE, "Button", "SUBMIT", WS_CHILD | WS_VISIBLE | WS_BORDER, 300, 10, 100, 20, hwnd, NULL, hInstance, (LPVOID)lParam);
		createFile   = CreateWindowExA(WS_EX_WINDOWEDGE, "Button", "CREATE", WS_CHILD | WS_VISIBLE | WS_BORDER, 300, 175, 100, 20, hwnd, NULL, hInstance, (LPVOID)lParam);
		open         = CreateWindowExA(WS_EX_WINDOWEDGE, "Button", "OPEN", WS_CHILD | WS_VISIBLE | WS_BORDER, 300, 95, 100, 20, hwnd, NULL, hInstance, (LPVOID)lParam);
		clearWindow  = CreateWindowExA(WS_EX_WINDOWEDGE, "Button", "CLEAR WINDOW", WS_CHILD| WS_VISIBLE | WS_BORDER, 300, 300, 150, 20, hwnd, NULL, hInstance, (LPVOID)lParam);

		textWindow   = CreateWindowExA(WS_EX_WINDOWEDGE, "Edit", "test", WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | ES_MULTILINE, 10, 10, 250, 300, hwnd, NULL, hInstance, (LPVOID)lParam);
		nameOfFile   = CreateWindowExA(WS_EX_WINDOWEDGE, "Edit", "the file to open.txt", WS_CHILD | WS_VISIBLE | WS_BORDER, 300, 70, 150, 20, hwnd, NULL, hInstance, (LPVOID)lParam);
		nameOfFile2  = CreateWindowExA(WS_EX_WINDOWEDGE, "Edit", "name to create file.txt", WS_CHILD | WS_VISIBLE | WS_BORDER, 300, 150, 150, 20, hwnd, NULL, hInstance, (LPVOID)lParam);
		
		
		break;
	case WM_COMMAND:
		if (message == WM_COMMAND && (HWND)lParam == submitButton)
		{
			MessageBoxA(NULL, "Your file has successfully been submitted!", "Information", MB_OK | MB_ICONINFORMATION);
		}
		
		if (message == WM_COMMAND && (HWND)lParam == createFile)
		{
			GetWindowTextA(nameOfFile2, (LPSTR)fileName2, _countof(fileName2));
			GetWindowTextA(textWindow, (LPSTR)text, _countof(text));
			
			std::fstream file(fileName2, std::fstream::app);
			
			if (!file.is_open())/* if the file can't be accessed or doesn't exist */
			{
				MessageBoxA(NULL, "Couldn't open the specified file.", "Error", MB_ICONERROR);
			}
			else
			{
				for (int i = 0; i < strlen(text); i++)
				{
					file << text[i];
				}

				file.close();
			}

		}
		
		if (message == WM_COMMAND && (HWND)lParam == open)
		{
			GetWindowTextA(nameOfFile, (LPSTR)fileName, _countof(fileName));
			GetWindowTextA(textWindow, (LPSTR)text, _countof(text));

			std::ifstream file(fileName);
			std::string line;
			
			if (!file.is_open())
			{
				MessageBoxA(NULL, "Couldn't open the specified file.", "Error", MB_ICONERROR);
			}
			else
			{
				for (int i = 0; i < 10000; i++)
				{
					text[i] = 0;
				}

				while (std::getline(file, line))
				{
					strcpy(text, line.c_str()); /* Doesn't work with \n. This needs fixing. */
				}

				SetWindowTextA(textWindow, (LPSTR)text);
				file.close();
			}
		}
		
		if (message == WM_COMMAND && (HWND)lParam == clearWindow)
		{
			const int result = MessageBoxA(NULL, "Are you sure you want to empty the text field?", "Warning", MB_YESNO | MB_ICONWARNING);
			
			switch (result)
			{
				case IDYES:
					GetWindowTextA(textWindow, (LPSTR)text, _countof(text));

					for (int i = 0; i < strlen(text); i++)
						text[i] = 0;

					SetWindowTextA(textWindow, (LPCSTR)text);
					break;
				case IDNO:
					break;
			}
		}

		break;
	case WM_DESTROY:
		PostQuitMessage(0);       /* send a WM_QUIT to the message queue */
		break;
	default:                      /* for messages that we don't deal with */
		return DefWindowProc(hwnd, message, wParam, lParam);
	}

	return 0;
}
