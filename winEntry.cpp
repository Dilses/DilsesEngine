#include <iostream>
#include <Windows.h>
#include <vector>

#include "resource.h"
#include "constants.hpp"
#include "winEntry.hpp"

std::vector<HWND> hWnds;

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
{
	WNDCLASSEX wcex{};

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = Wndproc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ENGINEICON));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = mainMenuClassName;
	wcex.hIconSm = NULL;

	if (!RegisterClassEx(&wcex))
	{
		MessageBoxEx(NULL, L"Registration window class failed", L"Error", MB_ICONERROR, 0);
	}

	hWnds.emplace_back(CreateWindowEx(0, mainMenuClassName, mainMenuName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL));
	if (hWnds[0] == NULL)
	{
		MessageBoxEx(NULL, L"Creaate window failed", L"Error", MB_ICONERROR, 0);
	}
	ShowWindow(hWnds[0], nShowCmd);

	MSG msg{};
	while (GetMessage(&msg, NULL, 0, 0) != NULL)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return EXIT_SUCCESS;
}

LRESULT Wndproc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_DESTROY:
			PostQuitMessage(EXIT_SUCCESS);
			return EXIT_SUCCESS;
			break;
		default:
			break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}