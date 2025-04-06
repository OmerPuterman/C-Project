#pragma once
#define LENGTH 9

#include "person.h"
#include "date.h"
#include <stdio.h>

typedef enum { ePaint = 0, eTyres = 1, eMalfunction = 2, eNofTypes }Problem;
static const char* pType[eNofTypes] = { "Paint", "Tyres", "Malfunction" };

typedef struct {

	Person* driver;
	char* brand;
	char license_plate[LENGTH+1];
	Problem problemType;
	Date purchaseDate;

}Car;

void	printCar(const Car* c);
void	freeCar(Car* c);
void	initCar(Car* c);
int		CompareLicense_Plate(const void* a, const void* b);
int		CompareDriverName(const void* a, const void* b);
int		CompareDate(const void* a, const void* b);

int		saveCarToFile(const Car* pC, FILE* fp);

void printBrand(const Car* c);
int sameCar(const Car* c, char plate[10]);