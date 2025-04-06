#pragma once
#include <stdio.h>
#include "garage.h"

typedef unsigned char BYTE;

int		saveGarageToFile(const Garage* g, const char* fileName, const char* cFileName);


int		initGarageFromFile(Garage* g, Car* c, const char* fileName, const char* cFileName);


int		createCarArr(Garage* g);






