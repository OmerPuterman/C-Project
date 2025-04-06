#pragma once
#include "car.h"
#include "date.h"
typedef struct
{
	char* accidentLocation;
	Car c1, c2;
	Date d;
}Accident;
void initAccident(Accident* a);
void printAccident(const Accident* a);
void freeAccident(Accident* a);

int writeAccToFile(const Accident* a,const char* fileName);