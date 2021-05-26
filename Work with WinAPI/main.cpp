#include <windows.h> 
#include <ctime>

// Дескриптор окна
HWND hWindow;
// Кисть
HBRUSH hBrush; 

// Функция для запуска блокнота
void LaunchNotepad()
{
	// Структура для определения свойств окна
	STARTUPINFO startInfo;
	// Структура содержит информацию о новом процессе и его потоке
	PROCESS_INFORMATION procInfo;
	// Заполняет блок памяти нулями с началом на stratInfo размером структуры STARTUPINFO
	ZeroMemory(&startInfo, sizeof(STARTUPINFO));
	// Создает новый процесс и его главный поток; данный процесс запускает блокнот 
	CreateProcess("C:\\Windows\\Notepad.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &startInfo, &procInfo);
}

// Обработка нажатия клавиш
BOOL KeystrokeProcessing(WPARAM wParam)
{
	// Определяет источник сообщения
	switch (wParam)
	{
		// Обработка нажатия клавиши Enter
		case VK_RETURN:
		{
			// Создаем кисть для заполнения окна случайным цветом
			HBRUSH hCurrBrush = CreateSolidBrush(RGB((rand() % 255), (rand() % 255), (rand() % 255)));
			// Заменяем дескриптор кисти фона новым цветом кисти
			SetClassLong(hWindow, GCL_HBRBACKGROUND, (long)hCurrBrush);
			// Перерисовываем всю область окна, стирая фон
			InvalidateRect(hWindow, NULL, TRUE);
			return TRUE;
		}
		
		// Обработка нажатия клавиши Esc
		case VK_ESCAPE:
		{	
			// Делаем запрос на закрытие окна
			PostQuitMessage(0);
			return TRUE;
		}

		// Обработка нажатия сочетания клавиши Ctrl+Q
		case VK_CONTROL:
		{
			// Если нажата клавиша 'Q'
			if (GetKeyState(0x51) == 1)
			{
				// Делаем запрос на закрытие окна
				PostQuitMessage(0);
				return TRUE;
			}
		}

		// Обработка нажатия клавиши Shift+C
		case VK_SHIFT:
		{
			// Если нажата клавиша 'C'
			if (GetKeyState(0x43) == 1)
			{
				// Запускаем блокнот
				LaunchNotepad();
				return TRUE;
			}
		}
	}
	return FALSE;
}

// Данная функция будет получать сообщения, которые Windows отсылает окну
// WindProc принимает дескриптор окна, номер сообщения и дополнительную информацию о нем
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		// Обработка нажатия несистемной клавиши 
		case WM_KEYUP:
		{
			// Если нажата клавиша/сочетание клавиш клавиатуры 
			if (KeystrokeProcessing(wParam))
				return 0;
			break;
		}

		// Обработка нажатия левой кнопки мыши 
		case WM_LBUTTONUP:
		{
			// Структура, определяющая координаты верхнего левого и правого нижнего углов прямоугольника
			// Создадим свою систему координат XоY
			RECT XoY;
			// Отыскиваем размеры рамки, ограничивающей окно
			GetWindowRect(hWnd, &XoY);
			// Находим координаты центра окна по х
			long centreX = (XoY.right -XoY.left) / 2;
			// Находим координаты центра по y
			long centreY = (XoY.bottom - XoY.top) / 2;
			// Ширина рабочей области
			long currentX = LOWORD(lParam);
			// Высота рабочей области
			long currentY = HIWORD(lParam);

			// Если нажали в левый верхний угол (цвет должен смениться на красный)
			if (currentX <= centreX && currentY <= centreY)
			{
				// Создаем кисть для заполнения окна красным цветом
				HBRUSH hRed = CreateSolidBrush(RGB(255, 0, 0));
				// Заменяем дескриптор кисти фона новым цветом кисти
				SetClassLong(hWindow, GCL_HBRBACKGROUND, (long)hRed);
				// Перерисовываем всю область окна, стирая фон
				InvalidateRect(hWindow, NULL, TRUE);
			}

			// Если нажали в правый верхний угол (цвет должен смениться на желтый)
			if (currentX >= centreX && currentY <= centreY)
			{
				// Создаем кисть для заполнения окна желтым цветом
				HBRUSH hYellow = CreateSolidBrush(RGB(255, 255, 0));
				// Заменяем дескриптор кисти фона новым цветом кисти
				SetClassLong(hWindow, GCL_HBRBACKGROUND, (long)hYellow);
				// Перерисовываем всю область окна, стирая фон
				InvalidateRect(hWindow, NULL, TRUE);
			}

			// Если нажали в левый нижний угол (цвет должен смениться на зеленый)
			if (currentX <= centreX && currentY >= centreY)
			{
				// Создаем кисть для заполнения окна зеленым цветом
				HBRUSH hGreen = CreateSolidBrush(RGB(0, 255, 0));
				// Заменяем дескриптор кисти фона новым цветом кисти
				SetClassLong(hWindow, GCL_HBRBACKGROUND, (long)hGreen);
				// Перерисовываем всю область окна, стирая фон
				InvalidateRect(hWindow, NULL, TRUE);
			}

			// Если нажали в правый нижний угол (цвет должен смениться на синий)
			if (currentX >= centreX && currentY >= centreY)
			{
				// Создаем кисть для заполнения окна синим цветом
				HBRUSH hBlue = CreateSolidBrush(RGB(0, 0, 255));
				// Заменяем дескриптор кисти фона новым цветом кисти
				SetClassLong(hWindow, GCL_HBRBACKGROUND, (long)hBlue);
				// Перерисовываем всю область окна, стирая фон
				InvalidateRect(hWindow, NULL, TRUE);
			}
			return 0;
		}

		// Условие закрытия окна
		case WM_DESTROY:
		{
			// Делаем запрос на закрытие окна
			PostQuitMessage(0);
			return 0;
		}
	}

	// Если не обработали сообщения, то вызываем функцию по умолчанию
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

// Основная функция 
int WINAPI WinMain(HINSTANCE hInstance,		// Указатель на текущий экземпляр
				   HINSTANCE hPrevInstance, // Указатель на предыдущий запущенный экземпляр
				   LPSTR lpCmdLine,			// Указатель н аначало командной строки
				   int nCmdShow)			// Тип отображения окна программы
{
	// Для того, чтобы рандомные значения при каждом запуске были отличны
	srand(time(NULL));

	// Кисть для заполнения окна синим цветом
	hBrush = CreateSolidBrush(RGB(0, 0, 225));
	// Создаем класс окна
	WNDCLASS Window; // Создаем класс окна
	// При изменении ширины или высоты окна оно будет перерисовано
	Window.style = CS_HREDRAW | CS_VREDRAW;
	// Передаем функцию обработки сообщений
	Window.lpfnWndProc = WndProc;
	// Число дополнительных байт за структурой
	Window.cbClsExtra = 0;
	// Число дополнительных байтов за экземпляром окна
	Window.cbWndExtra = 0;
	// Дескриптор, содержит оконную процедуру для класса
	Window.hInstance = hInstance;
	// Дескриптор значка класса (задаем по умолчанию)
	Window.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	// Дескриптор курсора (задаем по умолчанию)
	Window.hCursor = LoadCursor(NULL, IDC_ARROW);
	// Дескриптор кисти для закраски фона
	Window.hbrBackground = hBrush;
	// Указатель на имя меню
	Window.lpszMenuName = NULL;
	// Указатель на имя класса окна
	Window.lpszClassName = "WinAPI";
								  
	// Обработка ошибки (в случае, когда класс окна не зарегстрирован)
	if (!RegisterClass(&Window))
	{
		MessageBox(NULL, "Класс окна не зарегстрирован", "ERROR", MB_OK);
		return 0;
	}

	// Дескриптор окна
	hWindow = CreateWindow(
		"WinAPI",					// Указатель на имя класса окна
		"Лабораторная работа 2",	// Указатель на имя окна
		WS_OVERLAPPEDWINDOW,		// Стиль окна
		CW_USEDEFAULT,				// Горизонтальная позиция окна (ро усолчанию)
		CW_USEDEFAULT,				// Вертикальная позиция окна (по умолчанию)
		320,						// Ширина окна
		240,						// Высота окна
		HWND_DESKTOP,				// Дескриптор родительского окна
		NULL,						// Дескриптор меню
		hInstance,					// Дескриптор экземпляра приложения
		NULL);						// Указатель на данные создания окна (ничего не передаем)

	// Обработка ошибки (в случае, если окно не создано)
	if (!hWindow)
	{
		MessageBox(NULL, "Окно не было создано", "ERROR", MB_OK);
		return 0;
	}

	// Устанавливает состояние показа определяемого окна
	ShowWindow(hWindow, nCmdShow);
	// Обновляет рабочую область заданного окна
	UpdateWindow(hWindow);

	// Структура сообщения
	MSG message;
	// Переменная состояния
	byte flag;

	// Цикл обработки событий (пока есть извлекаемые из очереди сообщения)
	while ((flag = GetMessage(&message, NULL, 0, 0)) != 0)
	{
		if (flag == -1)
		{
			break;
		}

		// Переводим виртуальное сообщение в текстовое
		TranslateMessage(&message);
		// Передаем сообщения оконной процедуре
		DispatchMessage(&message);
	}

	// Деструктор
	DestroyWindow(hWindow);
	UnregisterClass("WinAPI", hInstance);

	return 0;
}