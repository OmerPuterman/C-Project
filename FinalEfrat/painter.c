#include "painter.h"
#include <stdio.h>
#include <stdlib.h>
#include "fileHelper.h"


#define printP(p) printPerson(p)


void initPainter(Painter* p, Person* person)
{
	
	p->carCount = 0;
	p->carsToFix = NULL;

	p->painterMan = person;
}
void printPainter(const Painter* p)
{
	printf("The painter is: \n");
	//printPerson(p->painterMan);
	printP(p->painterMan);
	printf("Cars that the painter is working on: \n");
	for (int i = 0; i < p->carCount; i++)
	{
		printCar(&p->carsToFix[i]);
	}
	
}
void freePainter(Painter* p)
{
	
	freePerson(p->painterMan);
	free(p);
}
int addCar2(Painter* p, Car* c)
{
	if (c->problemType == 0)
	{
		p->carsToFix = (Car*)realloc(p->carsToFix, sizeof(Car) * (p->carCount + 1));
		if (p->carsToFix == NULL)
		{
			return 0;
		}
		p->carsToFix[p->carCount] = *c;
		p->carCount++;
		return 1;
	}
	return 0;
}






int		savePainterToFile(const Painter* pF, FILE* fp)
{
	if(!writeStringToFile(pF->painterMan->name, fp, "Error writing name \n"))
	{
		fclose(fp);
		return 0;
	}
	fclose(fp);
	return 1;
}


