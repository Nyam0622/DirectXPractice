#define WIN32_LEAN_AND_MEAN 
//Windows.h에 있는 API중 자주사용하지 않는 것들을 없애 Complie속도를 증가시킨다.
//LEAN(군살없는)MEAN(평균적으로 사용하지 않는)
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
	//클라이언트 영역의 크기를 만들어줄 사각형 크기의 RECT(좌상단, 우하단)
	AdjustWindowRect( &wr, WS_OVERLAPPEDWINDOW, FALSE ); 
	//윈도우 크기(rect), 윈도우 스타일(가장 흔한 WS_OVERAPPEDWINDOW), 메뉴(false)

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
	* 지정된 창을 전경으로 가져오고 창을 활성화 시킨다. 다른 스레드에 비해 높은 우선순위를 할당한다.
	* 작업표시줄에 내려가 있을 때 클릭하면 올라오는 효과이다.
	*/
	SetFocus(gHwnd);
	//지정된 창에 키보드 포커스를 설정한다.

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

			MessageBox(hWnd, oss.str().c_str(), L"마우스 왼쪽 클릭!", MB_OK);
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