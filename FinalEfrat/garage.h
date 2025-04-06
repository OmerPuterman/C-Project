#pragma once
#include "car.h"
#include "painter.h"
#include "mechanic.h"
#include "tyreman.h"
#include "accident.h"
typedef enum { eSorteLicense_Plate = 0, eSortedDriverName = 1, eSortedDate = 2, eNotSorted = 3, ENofTypes }SortType;
static const char* sType[ENofTypes] = { "SortedLicense_Plate", "SortedDriverName", "SortedDate", "NotSorted" };
typedef struct
{
	int carCount;
	Car* cars;
	Painter* p;
	Mechanic* m;
	TyreMan* t;
	SortType sType;
}Garage;


void initGarage(Garage* g);
void printGarage(const Garage* g);
void freeGarage(Garage* g);
int addCarsToGarage(Garage* g, Accident* a);
int addCarToGarage(Garage* g, Car* c);
void SortArray(const Garage* g);
void setSType(Garage* g);
void addPainter(Garage* g,Painter*p);
void addMechanic(Garage* g,Mechanic*m);
void addTyreMan(Garage* g,TyreMan*t);
void firePainter(Garage* g);
void fireMechanic(Garage* g);
void fireTyreMan(Garage* g);
Car* searchArray(const Garage* g);
void generalArrayFunction(void* arr, int size, int typeSize, void(*func)(void* element));
void printCarBrands(const Garage* g);
int carExists(const Garage* g, char plate[10]);

int saveGarageToTxt(const Garage* g, const char* fileName);
int loadGarageFromTxt(const Garage* g, const char* fileName);
