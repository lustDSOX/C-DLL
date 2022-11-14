#include "Header.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR LpCmdLIne, int nCmdShow) {
	HINSTANCE dll = LoadLibrary(L"DLL.dll");
	GetData getData = (GetData)GetProcAddress(dll, "GetData");
	Array array;
	getData(&array);
	int s = array.size;
	FreeLibrary(dll);
	return 0;
}