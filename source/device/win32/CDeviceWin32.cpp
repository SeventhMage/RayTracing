#include "CDeviceWin32.h"
#include "../CKeyEvent.h"
#include "../CEventManager.h"
#include "base/Log.h"

namespace se
{
	namespace device
	{
		LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
		{
			switch (message)
			{
			case WM_PAINT:
			{
							 PAINTSTRUCT ps;
							 BeginPaint(hWnd, &ps);
							 EndPaint(hWnd, &ps);
			}
				return 0;
			case WM_ERASEBKGND:
				return 0;

			case WM_SYSKEYDOWN:
			case WM_SYSKEYUP:
				return 0;
			case WM_KEYDOWN:
			{
							   IKeyEvent *event = CEventManager::Instance()->GetKeyEvent();
							   if (event)
							   {
								   switch (wParam)
								   {
								   case VK_SPACE:
									   event->OnPress(EKP_KEYBOARD_SPACE);
									   break;
								   case VK_ESCAPE:
									   event->OnPress(EKP_KEYBOARD_ESC);
								   case 'N':
								   case 'n':
									   event->OnPress(EKP_KEYBOARD_N);
									   break;
								   case 'A':
								   case 'a':
									   event->OnPress(EKP_KEYBOARD_A);
									   break;
								   case 'D':
								   case 'd':
									   event->OnPress(EKP_KEYBOARD_D);
									   break;
								   case 'W':
								   case 'w':
									   event->OnPress(EKP_KEYBOARD_W);
									   break;
								   case 'S':
								   case 's':
									   event->OnPress(EKP_KEYBOARD_S);
									   break;
								   }

							   }
			}
				return 0;
			case WM_KEYUP:
			{
							 IKeyEvent *event = CEventManager::Instance()->GetKeyEvent();
							 if (event)
							 {
								 switch (wParam)
								 {
								 case VK_SPACE:
									 event->OnUp(EKP_KEYBOARD_SPACE);
									 break;
								 case 'N':
								 case 'n':
									 event->OnUp(EKP_KEYBOARD_N);
									 break;
								 case 'A':
								 case 'a':
									 event->OnUp(EKP_KEYBOARD_A);
									 break;
								 case 'D':
								 case 'd':
									 event->OnUp(EKP_KEYBOARD_D);
									 break;
								 case 'W':
								 case 'w':
									 event->OnUp(EKP_KEYBOARD_W);
									 break;
								 case 'S':
								 case 's':
									 event->OnUp(EKP_KEYBOARD_S);
									 break;
								 }

							 }

			}
				return 0;
			case WM_MOUSEWHEEL:
			{
								  IKeyEvent *event = CEventManager::Instance()->GetKeyEvent();
								  if (event)
								  {
									  short zDelta = HIWORD(wParam);
									  event->OnWheel(zDelta);
								  }								   				
			}
				return 0;
			case WM_SIZE:
			{
							CEventManager::Instance()->OnSize(0, 0, LOWORD(lParam), HIWORD(lParam));
			}
				return 0;

			case WM_DESTROY:
				PostQuitMessage(0);
				return 0;

			case WM_SYSCOMMAND:
				// prevent screensaver or monitor powersave mode from starting
				if ((wParam & 0xFFF0) == SC_SCREENSAVE ||
					(wParam & 0xFFF0) == SC_MONITORPOWER ||
					(wParam & 0xFFF0) == SC_KEYMENU
					)
					return 0;

				break;

			case WM_ACTIVATE:
				// we need to take care for screen changes, e.g. Alt-Tab

				break;

			case WM_USER:

				return 0;

			case WM_SETCURSOR:
				// because Windows forgot about that in the meantime


			case WM_INPUTLANGCHANGE:
				// get the new codepage used for keyboard input

				return 0;
			case WM_LBUTTONDOWN:
			{
								   IKeyEvent *event = CEventManager::Instance()->GetKeyEvent();
								   if (event)
								   {
									   event->OnPress(EKP_MOUSE_LBUTTON);
								   }
			}

				return 0;
			case WM_LBUTTONUP:
			{
								 IKeyEvent *event = CEventManager::Instance()->GetKeyEvent();
								 if (event)
								 {
									 event->OnUp(EKP_MOUSE_LBUTTON);
								 }
			}
				return 0;
			case WM_LBUTTONDBLCLK:
				return 0;
			case WM_RBUTTONDOWN:
			{
								   IKeyEvent *event = CEventManager::Instance()->GetKeyEvent();
								   if (event)
								   {
									   event->OnPress(EKP_MOUSE_RBUTTON);
								   }
			}
				return 0;
			case WM_RBUTTONUP:
			{
								 IKeyEvent *event = CEventManager::Instance()->GetKeyEvent();
								 if (event)
								 {
									 event->OnUp(EKP_MOUSE_RBUTTON);
								 }
			}
				return 0;
			case WM_MOUSEMOVE:
			{
								 IKeyEvent *event = CEventManager::Instance()->GetKeyEvent();
								 if (event)
								 {
									 int x = LOWORD(lParam);
									 int y = HIWORD(lParam);
									 event->SetMousePosition(x, y);
								 }
			}
				return 0;
			}

			return DefWindowProc(hWnd, message, wParam, lParam);
		}

		CDeviceWin32::CDeviceWin32(int x, int y, int width, int height, bool fullScreen /* = false */)			
			: m_hWnd(0)
			, m_iWidth(width)
			, m_iHeight(height)
			, m_bFullScreen(fullScreen)
		{
			CEventManager::Instance()->SetDevice(this);

			HINSTANCE hInstance = GetModuleHandle(0);

			const wchar_t* ClassName = L"CWin32Device";

			// Register Class
			WNDCLASSEX wcex;
			wcex.cbSize = sizeof(WNDCLASSEX);
			wcex.style = CS_HREDRAW | CS_VREDRAW;
			wcex.lpfnWndProc = WndProc;
			wcex.cbClsExtra = 0;
			wcex.cbWndExtra = 0;
			wcex.hInstance = hInstance;
			wcex.hIcon = LoadCursor(NULL, IDC_ARROW);
			wcex.hCursor = LoadCursor(NULL, IDI_APPLICATION);
			wcex.hbrBackground = NULL;// (HBRUSH)(COLOR_WINDOW + 1);
			wcex.lpszMenuName = 0;
			wcex.lpszClassName = ClassName;
			wcex.hIconSm = 0;

			// if there is an icon, load it
			wcex.hIcon = (HICON)LoadImage(hInstance, L"", IMAGE_ICON, 0, 0, LR_LOADFROMFILE);

			RegisterClassEx(&wcex);

			// calculate client size

			RECT clientSize;
			clientSize.top = x;
			clientSize.left = x;
			clientSize.right = width;
			clientSize.bottom = height;

			DWORD style = WS_POPUP;

			if (!fullScreen)
				style = WS_OVERLAPPEDWINDOW;//WS_SYSMENU | WS_BORDER | WS_CAPTION | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;

			AdjustWindowRect(&clientSize, style, FALSE);

			int realWidth = clientSize.right - clientSize.left;
			int realHeight = clientSize.bottom - clientSize.top;

			int windowLeft = (GetSystemMetrics(SM_CXSCREEN) - realWidth) / 2;
			int windowTop = (GetSystemMetrics(SM_CYSCREEN) - realHeight) / 2;

			if (windowLeft < 0)
				windowLeft = 0;
			if (windowTop < 0)
				windowTop = 0;	// make sure window menus are in screen on creation

			if (fullScreen)
			{
				windowLeft = 0;
				windowTop = 0;
				HWND hDesk = GetDesktopWindow();
				RECT rc;
				GetWindowRect(hDesk, &rc);
				realWidth = rc.right;
				realHeight = rc.bottom;;
			}
			m_iWidth = realWidth;
			m_iHeight = realHeight;
			// create window
			m_hWnd = CreateWindow(ClassName, L"", style, windowLeft, windowTop,
				realWidth, realHeight, NULL, NULL, hInstance, NULL);
			
			//初始化渲染器驱动
			HDC hDC = GetDC(m_hWnd);

			ReleaseDC(m_hWnd, hDC);

			ShowWindow(m_hWnd, SW_SHOWNORMAL);
			UpdateWindow(m_hWnd);			

			// fix ugly ATI driver bugs.
			MoveWindow(m_hWnd, windowLeft, windowTop, realWidth, realHeight, TRUE);

			ShowCursor(TRUE);		

			memset(&m_bmpInfo, 0, sizeof(BITMAPINFO));
			m_bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
			m_bmpInfo.bmiHeader.biWidth = m_iWidth;//宽度
			m_bmpInfo.bmiHeader.biHeight = m_iHeight;//高度
			m_bmpInfo.bmiHeader.biPlanes = 1;
			m_bmpInfo.bmiHeader.biBitCount = 32;
			m_bmpInfo.bmiHeader.biCompression = BI_RGB;
		}

		CDeviceWin32::~CDeviceWin32()
		{
			
		}

		void CDeviceWin32::SwapBuffers()
		{
			HDC hDC = GetDC(m_hWnd);
			::SwapBuffers(hDC);
			ReleaseDC(m_hWnd, hDC);
		}

		int CDeviceWin32::GetWindowWidth()
		{
			return m_iWidth;
		}

		int CDeviceWin32::GetWindowHeight()
		{
			return m_iHeight;
		}

		unsigned long long CDeviceWin32::GetSystemRunTime()
		{
			return GetTickCount64();
		}

		void CDeviceWin32::Sleep(unsigned long ms)
		{
			::Sleep(ms);
		}

		void CDeviceWin32::OnSize(int iPosX, int iPosY, int iWidth, int iHeight)
		{
			m_iWidth = iWidth;
			m_iHeight = iHeight;
			m_bmpInfo.bmiHeader.biWidth = m_iWidth;
			m_bmpInfo.bmiHeader.biHeight = m_iHeight;
		}

		bool CDeviceWin32::Run()
		{
			bool bQuit = false;
			MSG msg;
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);

				if (msg.message == WM_QUIT)
					bQuit = true;
			}
			return !bQuit;

		}

		void CDeviceWin32::DrawBuffer(void *buffer)
		{
			HDC hdc = GetDC(m_hWnd);			
			
			SetStretchBltMode(hdc, STRETCH_HALFTONE);
			StretchDIBits(hdc, 0, 0, m_iWidth, m_iHeight, 0, m_iHeight, m_iWidth, -m_iHeight, buffer, &m_bmpInfo, DIB_RGB_COLORS, SRCCOPY);
			
			//::SwapBuffers(hdc);
		
			ReleaseDC(m_hWnd, hdc);			
		}

		void CDeviceWin32::DrawString(int iPosX, int iPoxY, const char *str, int length)
		{
			HDC hdc = GetDC(m_hWnd);
			RECT rect = { iPosX, iPoxY, m_iWidth, m_iHeight };
			::DrawTextA(hdc, str, length, &rect, 0);
			//::TextOutA(hdc, iPosX, iPoxY, str, length);
			ReleaseDC(m_hWnd, hdc);
		}


	}
}