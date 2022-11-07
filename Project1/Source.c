#include"Header.h"
Array GetData() {
	FILE* pFile = fopen("data.csv", "r");
	fseek(pFile, 0, SEEK_END);
	int size = ftell(pFile);
	fseek(pFile, 0, SEEK_SET);
	fclose(pFile);
	HANDLE file = CreateFile(L"data.csv", GENERIC_READ, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD bytes;
	char* text = calloc(size, 1);
	ReadFile(file, text, size, &bytes, NULL);
	CloseHandle(file);
	size = 0;
	for (size_t i = 0; i < bytes; i++)
	{
		if ((text[i] == '\n') || (i == bytes - 1)) {
			size++;
		}
	}
	
	anketa* peoples = calloc(size, sizeof(anketa));
	char** lines = calloc(size, 1);
	int line = 0;
	int charindex = 0;
	for (size_t i = 0; i < size; i++)
	{
		lines[i] = calloc(100, 1);
	}
	for (size_t i = 0; i < bytes; i++)
	{
		lines[line][charindex] = text[i];
		charindex++;
		if ((text[i + 1] == '\r') && (text[i + 2] == '\n')) {
			line++;
			i += 2;
			charindex = 0;
		}
	}
	for (size_t i = 0; i < size; i++)
	{
		char* buf=strtok(lines[i], ";");
		peoples[i].Surname = buf;
		buf= strtok(NULL, ";");
		peoples[i].Name = buf;
		buf = strtok(NULL, ";");
		peoples[i].SecondName = buf;
		buf = strtok(NULL, ";");
		peoples[i].Age = buf;
		
	}
	Array array = { size,peoples };
	return array;
}
