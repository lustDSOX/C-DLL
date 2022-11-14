#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

extern __declspec(dllimport) void GetData(Array* array);
extern __declspec(dllimport) void Search(Array* array, char*);
extern __declspec(dllimport) void WriteData(Array* array, char*);
extern __declspec(dllimport) double AVGAge(Array* array);