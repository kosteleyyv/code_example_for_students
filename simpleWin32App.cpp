#include <Windows.h>

//описание приложения 6. СТРУКТУРА WINDOWS ПРИЛОЖЕНИЙ стр 60 
//Боровской, И. Г. Технология разработки программных систем: Учебное пособие [Электронный ресурс] / И. Г. Боровской. — Томск: ТУСУР, 2012. — 260 с.

LRESULT CALLBACK WindowProc(
  HWND hwnd,      
  UINT uMsg,      
  WPARAM wParam,  
  LPARAM lParam   
);


int WINAPI WinMain(
  HINSTANCE hInstance,      
  HINSTANCE hPrevInstance,  
  LPSTR lpCmdLine,         
  int nCmdShow              
)
{

	WNDCLASS ws = {0};
	ws.lpszClassName = "sl;jhfkjsabvjdsbvk";
	ws.hInstance = hInstance;
	ws.lpfnWndProc = WindowProc;

	if (NULL == RegisterClass(&ws))
		return 0;

	HWND hwnd = CreateWindow(
		ws.lpszClassName,  
		"Test", 
		WS_OVERLAPPEDWINDOW,     
		10,               
		10,              
		200,           
		300,         
		NULL,      
		NULL,         
		hInstance,  
		NULL);        

	if (hwnd == NULL)
		return 0;


	ShowWindow(hwnd, nCmdShow);


	MSG msg;
	while (GetMessage(&msg, 0,0,0))
		DispatchMessage(&msg);

	return 0;
}


LRESULT CALLBACK WindowProc(
  HWND hwnd,      
  UINT uMsg,      
  WPARAM wParam,  
  LPARAM lParam   
)
{

	switch (uMsg) {
	case WM_DESTROY :
		PostQuitMessage(0);

	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);

}
