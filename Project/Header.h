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
	int size;
	anketa* Peoples;
}Array;
typedef void(_cdecl* GetData)(Array*);