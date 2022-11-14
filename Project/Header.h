#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
typedef struct ANKETA {
	char* Name;
	char* SecondName;
	char* Surname;
	char* Age;
} anketa;
typedef struct Array {
	double size;
	anketa* Peoples;
}Array;
typedef void(_cdecl* GetData)(Array*);
typedef double(_cdecl* AVGAge)(Array*);
typedef void(_cdecl* Search)(Array*,char*);
typedef void(_cdecl* WriteData)(Array*, char*);