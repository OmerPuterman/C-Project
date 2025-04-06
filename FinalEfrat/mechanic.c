#include "mechanic.h"
#include "car.h"
#include <stdio.h>
#include <stdlib.h>




void initMechanic(Mechanic* m, Person* p)
{

	m->mechanicMan = p;
	m->carCount = 0;
	m->carsToFix = NULL;
}

void printMechanic(const Mechanic* m)
{
	printf("The mechanic is: \n");
	printPerson(m->mechanicMan);
	printf("\n");
	printf("And the cars that he is working on: \n");
	for (int i = 0; i < m->carCount; i++)
		printCar(m->carsToFix[i]);
}

void freeMechanic(Mechanic* m)
{
	
	free(m);
}

int addCar1(Mechanic* m, Car* c)
{
	if (c->problemType == 2)
	{
		m->carsToFix = (Car*)realloc(m->carsToFix, sizeof(Car) * (m->carCount + 1));
		if (m->carsToFix == NULL)
		{
			return 0;
		}
		m->carsToFix[m->carCount] = c;
		m->carCount++;
		return 1;
	}
	return 0;
}



int		saveMechanicToFile(const Mechanic* pM, FILE* fp)
{
	
		if (!writeStringToFile(pM->mechanicMan->name, fp, "Error writing name \n"))
		{
			fclose(fp);
			return 0;
		}
	fclose(fp);
	return 1;
}

