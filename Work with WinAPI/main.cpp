#include <windows.h> 
#include <ctime>

// ���������� ����
HWND hWindow;
// �����
HBRUSH hBrush; 

// ������� ��� ������� ��������
void LaunchNotepad()
{
	// ��������� ��� ����������� ������� ����
	STARTUPINFO startInfo;
	// ��������� �������� ���������� � ����� �������� � ��� ������
	PROCESS_INFORMATION procInfo;
	// ��������� ���� ������ ������ � ������� �� stratInfo �������� ��������� STARTUPINFO
	ZeroMemory(&startInfo, sizeof(STARTUPINFO));
	// ������� ����� ������� � ��� ������� �����; ������ ������� ��������� ������� 
	CreateProcess("C:\\Windows\\Notepad.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &startInfo, &procInfo);
}

// ��������� ������� ������
BOOL KeystrokeProcessing(WPARAM wParam)
{
	// ���������� �������� ���������
	switch (wParam)
	{
		// ��������� ������� ������� Enter
		case VK_RETURN:
		{
			// ������� ����� ��� ���������� ���� ��������� ������
			HBRUSH hCurrBrush = CreateSolidBrush(RGB((rand() % 255), (rand() % 255), (rand() % 255)));
			// �������� ���������� ����� ���� ����� ������ �����
			SetClassLong(hWindow, GCL_HBRBACKGROUND, (long)hCurrBrush);
			// �������������� ��� ������� ����, ������ ���
			InvalidateRect(hWindow, NULL, TRUE);
			return TRUE;
		}
		
		// ��������� ������� ������� Esc
		case VK_ESCAPE:
		{	
			// ������ ������ �� �������� ����
			PostQuitMessage(0);
			return TRUE;
		}

		// ��������� ������� ��������� ������� Ctrl+Q
		case VK_CONTROL:
		{
			// ���� ������ ������� 'Q'
			if (GetKeyState(0x51) == 1)
			{
				// ������ ������ �� �������� ����
				PostQuitMessage(0);
				return TRUE;
			}
		}

		// ��������� ������� ������� Shift+C
		case VK_SHIFT:
		{
			// ���� ������ ������� 'C'
			if (GetKeyState(0x43) == 1)
			{
				// ��������� �������
				LaunchNotepad();
				return TRUE;
			}
		}
	}
	return FALSE;
}

// ������ ������� ����� �������� ���������, ������� Windows �������� ����
// WindProc ��������� ���������� ����, ����� ��������� � �������������� ���������� � ���
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		// ��������� ������� ����������� ������� 
		case WM_KEYUP:
		{
			// ���� ������ �������/��������� ������ ���������� 
			if (KeystrokeProcessing(wParam))
				return 0;
			break;
		}

		// ��������� ������� ����� ������ ���� 
		case WM_LBUTTONUP:
		{
			// ���������, ������������ ���������� �������� ������ � ������� ������� ����� ��������������
			// �������� ���� ������� ��������� X�Y
			RECT XoY;
			// ���������� ������� �����, �������������� ����
			GetWindowRect(hWnd, &XoY);
			// ������� ���������� ������ ���� �� �
			long centreX = (XoY.right -XoY.left) / 2;
			// ������� ���������� ������ �� y
			long centreY = (XoY.bottom - XoY.top) / 2;
			// ������ ������� �������
			long currentX = LOWORD(lParam);
			// ������ ������� �������
			long currentY = HIWORD(lParam);

			// ���� ������ � ����� ������� ���� (���� ������ ��������� �� �������)
			if (currentX <= centreX && currentY <= centreY)
			{
				// ������� ����� ��� ���������� ���� ������� ������
				HBRUSH hRed = CreateSolidBrush(RGB(255, 0, 0));
				// �������� ���������� ����� ���� ����� ������ �����
				SetClassLong(hWindow, GCL_HBRBACKGROUND, (long)hRed);
				// �������������� ��� ������� ����, ������ ���
				InvalidateRect(hWindow, NULL, TRUE);
			}

			// ���� ������ � ������ ������� ���� (���� ������ ��������� �� ������)
			if (currentX >= centreX && currentY <= centreY)
			{
				// ������� ����� ��� ���������� ���� ������ ������
				HBRUSH hYellow = CreateSolidBrush(RGB(255, 255, 0));
				// �������� ���������� ����� ���� ����� ������ �����
				SetClassLong(hWindow, GCL_HBRBACKGROUND, (long)hYellow);
				// �������������� ��� ������� ����, ������ ���
				InvalidateRect(hWindow, NULL, TRUE);
			}

			// ���� ������ � ����� ������ ���� (���� ������ ��������� �� �������)
			if (currentX <= centreX && currentY >= centreY)
			{
				// ������� ����� ��� ���������� ���� ������� ������
				HBRUSH hGreen = CreateSolidBrush(RGB(0, 255, 0));
				// �������� ���������� ����� ���� ����� ������ �����
				SetClassLong(hWindow, GCL_HBRBACKGROUND, (long)hGreen);
				// �������������� ��� ������� ����, ������ ���
				InvalidateRect(hWindow, NULL, TRUE);
			}

			// ���� ������ � ������ ������ ���� (���� ������ ��������� �� �����)
			if (currentX >= centreX && currentY >= centreY)
			{
				// ������� ����� ��� ���������� ���� ����� ������
				HBRUSH hBlue = CreateSolidBrush(RGB(0, 0, 255));
				// �������� ���������� ����� ���� ����� ������ �����
				SetClassLong(hWindow, GCL_HBRBACKGROUND, (long)hBlue);
				// �������������� ��� ������� ����, ������ ���
				InvalidateRect(hWindow, NULL, TRUE);
			}
			return 0;
		}

		// ������� �������� ����
		case WM_DESTROY:
		{
			// ������ ������ �� �������� ����
			PostQuitMessage(0);
			return 0;
		}
	}

	// ���� �� ���������� ���������, �� �������� ������� �� ���������
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

// �������� ������� 
int WINAPI WinMain(HINSTANCE hInstance,		// ��������� �� ������� ���������
				   HINSTANCE hPrevInstance, // ��������� �� ���������� ���������� ���������
				   LPSTR lpCmdLine,			// ��������� � ������� ��������� ������
				   int nCmdShow)			// ��� ����������� ���� ���������
{
	// ��� ����, ����� ��������� �������� ��� ������ ������� ���� �������
	srand(time(NULL));

	// ����� ��� ���������� ���� ����� ������
	hBrush = CreateSolidBrush(RGB(0, 0, 225));
	// ������� ����� ����
	WNDCLASS Window; // ������� ����� ����
	// ��� ��������� ������ ��� ������ ���� ��� ����� ������������
	Window.style = CS_HREDRAW | CS_VREDRAW;
	// �������� ������� ��������� ���������
	Window.lpfnWndProc = WndProc;
	// ����� �������������� ���� �� ����������
	Window.cbClsExtra = 0;
	// ����� �������������� ������ �� ����������� ����
	Window.cbWndExtra = 0;
	// ����������, �������� ������� ��������� ��� ������
	Window.hInstance = hInstance;
	// ���������� ������ ������ (������ �� ���������)
	Window.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	// ���������� ������� (������ �� ���������)
	Window.hCursor = LoadCursor(NULL, IDC_ARROW);
	// ���������� ����� ��� �������� ����
	Window.hbrBackground = hBrush;
	// ��������� �� ��� ����
	Window.lpszMenuName = NULL;
	// ��������� �� ��� ������ ����
	Window.lpszClassName = "WinAPI";
								  
	// ��������� ������ (� ������, ����� ����� ���� �� ��������������)
	if (!RegisterClass(&Window))
	{
		MessageBox(NULL, "����� ���� �� ��������������", "ERROR", MB_OK);
		return 0;
	}

	// ���������� ����
	hWindow = CreateWindow(
		"WinAPI",					// ��������� �� ��� ������ ����
		"������������ ������ 2",	// ��������� �� ��� ����
		WS_OVERLAPPEDWINDOW,		// ����� ����
		CW_USEDEFAULT,				// �������������� ������� ���� (�� ���������)
		CW_USEDEFAULT,				// ������������ ������� ���� (�� ���������)
		320,						// ������ ����
		240,						// ������ ����
		HWND_DESKTOP,				// ���������� ������������� ����
		NULL,						// ���������� ����
		hInstance,					// ���������� ���������� ����������
		NULL);						// ��������� �� ������ �������� ���� (������ �� ��������)

	// ��������� ������ (� ������, ���� ���� �� �������)
	if (!hWindow)
	{
		MessageBox(NULL, "���� �� ���� �������", "ERROR", MB_OK);
		return 0;
	}

	// ������������� ��������� ������ ������������� ����
	ShowWindow(hWindow, nCmdShow);
	// ��������� ������� ������� ��������� ����
	UpdateWindow(hWindow);

	// ��������� ���������
	MSG message;
	// ���������� ���������
	byte flag;

	// ���� ��������� ������� (���� ���� ����������� �� ������� ���������)
	while ((flag = GetMessage(&message, NULL, 0, 0)) != 0)
	{
		if (flag == -1)
		{
			break;
		}

		// ��������� ����������� ��������� � ���������
		TranslateMessage(&message);
		// �������� ��������� ������� ���������
		DispatchMessage(&message);
	}

	// ����������
	DestroyWindow(hWindow);
	UnregisterClass("WinAPI", hInstance);

	return 0;
}