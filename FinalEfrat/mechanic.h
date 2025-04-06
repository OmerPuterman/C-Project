#pragma once

#include "car.h"
#include "person.h"


typedef struct {

	int carCount;
	Car** carsToFix;
	Person* mechanicMan;

}Mechanic;

void initMechanic(Mechanic* m, Person* p);
void printMechanic(const Mechanic* m);
void freeMechanic(Mechanic* m);
int addCar1(Mechanic* m, Car* c);
int	saveMechanicToFile(const Mechanic* pM, FILE* fp);
