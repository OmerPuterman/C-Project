#pragma once
#include "list.h"
#include "person.h"
#include "car.h"

typedef struct {

	int carCount;
	LIST* carsToFix;
	Person* tyreWoman;

}TyreMan;

void initTyreMan(TyreMan* t,Person* p);
void printTyreMan(const TyreMan* t);
void freeTyreMan(TyreMan* t);
void addCar(Car* c, TyreMan* t);

int		saveTyremanToFile(const TyreMan* pT, FILE* fp);