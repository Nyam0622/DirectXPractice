#define WIN32_LEAN_AND_MEAN 
//Windows.h�� �ִ� API�� ���ֻ������ �ʴ� �͵��� ���� Complie�ӵ��� ������Ų��.
//LEAN(�������)MEAN(��������� ������� �ʴ�)
#include<Windows.h>
#include<sstream>
#include<wrl/client.h>
#include<d3d11.h>

#pragma comment(lib, "d3d11.lib")

const wchar_t gClassName[]{ L"MyWindowClass" };
const wchar_t gTitle[]{ L"Direct3D" };
const int WINDOW_WIDTH{ 800 };
const int WINDOW_HEIGHT{ 600 };

HWND gHwnd{ };
HINSTANCE gInstance{ };

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd)
{
	
	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpszClassName = gClassName;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpfnWndProc = WindowProc;
	wc.cbSize = sizeof(WNDCLASSEX);

	if (!RegisterClassEx(&wc))
	{
		MessageBox(nullptr, L"Failed to register window class!", L"Error", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	RECT wr{ 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT }; 
	//Ŭ���̾�Ʈ ������ ũ�⸦ ������� �簢�� ũ���� RECT(�»��, ���ϴ�)
	AdjustWindowRect( &wr, WS_OVERLAPPEDWINDOW, FALSE ); 
	//������ ũ��(rect), ������ ��Ÿ��(���� ���� WS_OVERAPPEDWINDOW), �޴�(false)

	gHwnd = CreateWindowEx(
		NULL,
		gClassName,
		L"Hellow Window",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		wr.right - wr.left,
		wr.bottom - wr.top,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (gHwnd == nullptr)
	{
		MessageBox(nullptr, L"Failed to Create Window Class!", L"Error", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ShowWindow(gHwnd, nShowCmd);

	SetForegroundWindow(gHwnd);
	/*
	* ������ â�� �������� �������� â�� Ȱ��ȭ ��Ų��. �ٸ� �����忡 ���� ���� �켱������ �Ҵ��Ѵ�.
	* �۾�ǥ���ٿ� ������ ���� �� Ŭ���ϸ� �ö���� ȿ���̴�.
	*/
	SetFocus(gHwnd);
	//������ â�� Ű���� ��Ŀ���� �����Ѵ�.

	UpdateWindow(gHwnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return static_cast<int>(msg.wParam);
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_CLOSE:
			DestroyWindow(hWnd);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		case WM_LBUTTONDOWN:
		{
			std::wostringstream oss;
			oss << "X : " << LOWORD(lParam) << ", Y : " << HIWORD(lParam);

			MessageBox(hWnd, oss.str().c_str(), L"���콺 ���� Ŭ��!", MB_OK);
			break;
		}

		case WM_KEYDOWN:
		{
			std::wostringstream oss;

			oss << "Virtual Key = " << wParam << ", Extra = " << std::hex << lParam << std::endl;
			OutputDebugString(oss.str().c_str());
			break;
		}
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}