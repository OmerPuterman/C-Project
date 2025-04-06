#include "tyreman.h"
#include <stdio.h>
#include <stdlib.h>



void initTyreMan(TyreMan* t,Person* p)
{
	t->carsToFix = (LIST*)malloc(sizeof(LIST));
	if (t->carsToFix == NULL)
	{
		return NULL;
	}
	L_init(t->carsToFix);
	t->tyreWoman = p;
	t->carCount = 0;
}


void printTyreMan(const TyreMan* t)
{
	printf("The tyre man is: \n");
	printPerson(t->tyreWoman);

	if (!t->carsToFix) return;
	printf("And the cars that he is working on: \n");
	NODE* p = t->carsToFix->head.next;
	while (p != NULL)
	{
		printCar(p->key);
		p = p->next;
	}


}
void freeTyreMan(TyreMan* t)
{
	freePerson(t->tyreWoman);
	
}
void addCar(Car* c, TyreMan* t)
{
	L_insert(t->carsToFix, c);
}



int		saveTyremanToFile(const TyreMan* pT, FILE* fp)
{
	
		if (!writeStringToFile(pT->tyreWoman->name, fp, "Error writing name \n"))
		{
			fclose(fp);
			return 0;
		}
	fclose(fp);
	return 1;
}

