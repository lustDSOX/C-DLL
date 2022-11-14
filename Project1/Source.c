#include"Header.h"
BOOL WINAPI DllMain(
	HINSTANCE hinstDLL,  // handle to DLL module
	DWORD fdwReason,     // reason for calling function
	LPVOID lpvReserved)  // reserved
{
	// Perform actions based on the reason for calling.
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		// Initialize once for each new process.
		// Return FALSE to fail DLL load.
		break;

	case DLL_THREAD_ATTACH:
		// Do thread-specific initialization.
		break;

	case DLL_THREAD_DETACH:
		// Do thread-specific cleanup.
		break;

	case DLL_PROCESS_DETACH:

		if (lpvReserved != NULL)
		{
			break; // do not do cleanup if process termination scenario
		}

		// Perform any necessary cleanup.
		break;
	}
	return TRUE;  // Successful DLL_PROCESS_ATTACH.
}

extern __declspec(dllimport) void GetData(Array * array);

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
	int index = 0;
	for (size_t i = 0; i < bytes; i++)
	{
		if ((text[i] == '\n') || (i == bytes - 1)) {
			size++;
		}
	}
	char** lines = calloc(size, sizeof(char*));
	for (size_t i = 0; i < bytes; i++)
	{
		if ((text[i+1] == '\r') || (i == bytes - 1)) {
			if (index == 0) {
				lines[index] = malloc(i);
			}
			else {
				int last_size = 0;
				for (size_t j = 0; j < index; j++)
				{
					int s = 0;
					while (lines[j][s] == -51)
					{
						last_size++;
						s++;
					}
				}
				int count = i - last_size -(2*index);
				lines[index] = malloc(count);
			}
			i += 2;
			index++;
		}
	}

	anketa* peoples = calloc(size, sizeof(anketa));
	int line = 0;
	int charindex = 0;
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
		buf = strtok(NULL, ";ý");
		peoples[i].Age = buf;
		
	}
	array->size = size;
	array->Peoples = peoples;
}

void Search(Array* array,char* needed) {
	int newSize = 1;
	anketa* peoples ={0};
	for (size_t i = 0; i <= array->size; i++)
	{
		if (strstr(array->Peoples[i].Surname, needed) != NULL) {
			if (newSize == 1) {
				peoples = calloc(newSize, sizeof(anketa));
			}
			else
			{
				peoples = (anketa*)realloc(peoples, newSize);
			}
			newSize++;
			peoples[newSize-2] = array->Peoples[i];
			break;
		}
	}
	array->size = newSize-1;
	array->Peoples = peoples;
}
void WriteData(Array* array, char* filename) {
	HANDLE file = CreateFile(filename, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	for (size_t i = 0; i < array->size; i++)
	{
		char text[50] = "";
		strncat(text,array->Peoples[i].Surname, strlen(array->Peoples[i].Surname));
		strncat(text, ";",1);
		strncat(text, array->Peoples[i].Name, strlen(array->Peoples[i].Name));
		strncat(text, ";",1);
		strncat(text, array->Peoples[i].SecondName, strlen(array->Peoples[i].SecondName));
		strncat(text, ";",1);
		strncat(text, array->Peoples[i].Age, strlen(array->Peoples[i].Age));
		strncat(text, "\n",1);
		int size = strlen(text);
		WriteFile(file,text,size, NULL, NULL);
	}
}

double AVGAge(Array* array) {
	int all_age = 0;
	for (size_t i = 0; i < array->size; i++)
	{
		all_age += atoi(array->Peoples[i].Age);
	}
	double avg = all_age / array->size;
	return avg;
}