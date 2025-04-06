#pragma once
#include "car.h"
#include "person.h"
typedef struct
{
	int carCount;
	Car* carsToFix;
	Person* painterMan;
}Painter;


void initPainter(Painter* p, Person* person);
void printPainter(const Painter* p);
void freePainter(Painter* p);
int addCar2(Painter*p,Car* c);
int		savePainterToFile(const Painter* pF, FILE* fp);
