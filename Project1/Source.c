#include"Header.h"
INT WINAPI WinMain(HINSTANCE histance, HINSTANCE hPrevInstance, LPSTR lpCMDline, int nCmdShow) {
	FILE* pFile = fopen("1.txt", "r");
	fseek(pFile, 0, SEEK_END);
	int size = ftell(pFile);
	fclose(pFile);
	HANDLE file = CreateFile(L"1.txt", GENERIC_READ, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD bytes;
	char* text = calloc(size, 1);
	ReadFile(file, text, size, &bytes, NULL);
	CloseHandle(file);
	int indeX = 0;
	size = 0;
	for (size_t i = 0; i < bytes; i++)
	{
		if (text[i] == '\n') {
			break;
		}
		size = i;
		indeX = i;
	}
	char* line = calloc(size, 1);
	for (size_t i = indeX-size; i < size; i++)
	{
		line[i] = text[i];
	}
}