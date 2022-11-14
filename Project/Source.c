#include "Header.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR LpCmdLIne, int nCmdShow) {
	HINSTANCE dll = LoadLibrary(L"DLL.dll");
	GetData Get = (GetData)GetProcAddress(dll, "GetData");
	AVGAge AVG = (AVGAge)GetProcAddress(dll, "AVGAge");
	WriteData Write = (WriteData)GetProcAddress(dll, "WriteData");
	Search search = (Search)GetProcAddress(dll, "Search");
	Array array;
	Get(&array);
	double s = AVG(&array);
	search(&array, "ôûâ");
	Write(&array, L"newdata.csv");
	FreeLibrary(dll);
	return 0;
}