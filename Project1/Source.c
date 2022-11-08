#include"Header.h"
INT WINAPI WinMain(HINSTANCE histance, HINSTANCE hPrevInstance, LPSTR lpCMDline, int nCmdShow) 
{
	Array array;
	GetData(&array);
	Search(&array, "Десятков");
	int s = array.size;
	return s;
}

void GetData(Array* array) {
	FILE* pFile = fopen("Users.csv", "r");
	fseek(pFile, 0, SEEK_END);
	int size = ftell(pFile);
	fseek(pFile, 0, SEEK_SET);
	fclose(pFile);
	HANDLE file = CreateFile(L"Users.csv", GENERIC_READ, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
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
	char** lines = calloc(size, sizeof(char*));
	int line = 0;
	int charindex = 0;
	for (size_t i = 0; i < size; i++)
	{
		lines[i] = malloc(200);
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
	array->size = size;
	array->Peoples = peoples;
}

void Search(Array* array,char* needed) {
	int newSize = 1;
	char* ans;
	anketa* peoples = calloc(newSize, sizeof(anketa));
	for (size_t i = 0; i <= array->size; i++)
	{
		ans = strstr(array->Peoples[i].Surname, needed);
		if (strstr(array->Peoples[i].Surname, needed) != NULL) {
			newSize++;
			peoples = (anketa*)realloc(peoples, newSize);
			peoples[newSize-2] = array->Peoples[i];
		}
	}
	array->size = newSize-1;
	array->Peoples = peoples;
}
void WriteData(Array* array, char* filename) {
	HANDLE file = CreateFile(filename, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	for (size_t i = 0; i < array->size; i++)
	{
		WriteFile(file,)
	}
}