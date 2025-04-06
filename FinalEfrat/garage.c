#include "garage.h"
#include "General.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define is_eq(str1,str2) strcmp(str1, str2) == 0 ? 1 : 0; 

void initGarage(Garage* g)
{
	g->p = (Painter*)malloc(sizeof(Painter));
	if (g->p == NULL)
	{
		freePainter(g->p);
		return NULL;
	}
	g->m = (Mechanic*)malloc(sizeof(Mechanic));
	if (g->m == NULL)
	{
		freeMechanic(g->m);
		return NULL;
	}
	g->t = (TyreMan*)malloc(sizeof(TyreMan));
	if (g->t == NULL)
	{
		freeTyreMan(g->t);
		return NULL;
	}
	g->p->painterMan = (Person*)malloc(sizeof(Person));
	if (g->p->painterMan == NULL)
	{
		freePerson(g->p->painterMan);
		return NULL;
	}
	g->m->mechanicMan = (Person*)malloc(sizeof(Person));
	if (g->m->mechanicMan == NULL)
	{
		freePerson(g->m->mechanicMan);
		return NULL;
	}
	g->t->tyreWoman = (Person*)malloc(sizeof(Person));
	if (g->t->tyreWoman == NULL)
	{
		freePerson(g->t->tyreWoman);
		return NULL;
	}

	g->p->carCount = 0;
	g->p->carsToFix = NULL;
	g->p->painterMan->name = "";
	g->m->carCount =0;
	g->m->carsToFix = NULL;
	g->m->mechanicMan = "";
	g->t->carCount = 0;
	g->t->carsToFix = NULL;
	g->t->tyreWoman = "";
	g->carCount = 0;
	
	g->cars = NULL;
	g->sType = 3;


}
void printGarage(const Garage* g)
{
	generalArrayFunction(g->cars, g->carCount, sizeof(Car), printCar);
	printPainter(g->p);
	printMechanic(g->m);
	printTyreMan(g->t);
}
void freeGarage(Garage* g)
{
	freeCar(g->cars);
	freePainter(g->p);
	freeMechanic(g->m);
	freeTyreMan(g->t);
	free(g);
}
int addCarsToGarage(Garage* g, Accident* a)
{
	g->cars = (Car*)realloc(g->cars, (g->carCount + 2) * sizeof(Car));
	if (g->cars == NULL)
	{
		return 0;
	}
	switch (a->c1.problemType)
	{
	case 0:
	{
		addCar2(g->p, &a->c1);
		break;
	}
	case 1:
	{
		addCar(&a->c1, g->t);
		break;
	}
	case 2:
	{
		addCar1(g->m, &a->c1);
		break;
	}
	default:
	{
		printf("Error No Problem For Garage to Fix");
		return 0;
		break;
	}
	}
	switch (a->c2.problemType)
	{
	case 0:
	{
		addCar2(g->p, &a->c2);
		break;
	}
	case 1:
	{
		addCar(&a->c2, g->t);
		break;
	}
	case 2:
	{
		addCar1(g->m, &a->c2);
		break;
	}
	default:
	{
		printf("Error No Problem For Garage to Fix");
		return 0;
		break;
	}
	}
	g->cars[g->carCount] = a->c1;
	g->cars[g->carCount + 1] = a->c2;
	g->carCount += 2;
	return 1;
}
int addCarToGarage(Garage* g, Car* c)
{
	if (carExists(g, c->license_plate) == 1)
	{
		printf("Car already added (lisence plate)");
		return 0;
	}
	g->cars = (Car*)realloc(g->cars, (g->carCount + 1) * sizeof(Car));
	if (g->cars == NULL)
	{
		return 0;
	}
	switch (c->problemType)
	{
	case 0:
	{
		addCar2(g->p, c);
		break;
	}
	case 1:
	{
		addCar(c, g->t);
		break;
	}
	case 2:
	{
		addCar1(g->m, c);
		break;
	}
	default:
	{
		printf("Error No Problem For Garage to Fix");
		return 0;
		break;
	}
	}

	g->cars[g->carCount] = *c;
	g->carCount++;
	return 1;
}

void SortArray(const Garage *g)
{
	switch (g->sType)
	{
	case 0:
	{
		qsort(g->cars, g->carCount, sizeof(Car), CompareLicense_Plate);
		break;
	}
	case 1:
	{
		qsort(g->cars, g->carCount, sizeof(Car), CompareDriverName);
		break;
	}
	case 2:
	{
		qsort(g->cars, g->carCount, sizeof(Car), CompareDate);
		break;
	}
	default:
	{
		break;
	}
	}
}
void setSType(Garage* g)
{
	int temp;
	do
	{
		printf("please enter type of sorted array -\n #0 SortedLicense_Plate\n #1 SortedDriversName\n #2 SortedDateOfPurchase\n ");// #3 NotSorted\n
		scanf("%d", &temp);


	} while ((temp < 0) || (temp > eNofTypes - 1));
	g->sType = temp;
}
void addPainter(Garage* g, Painter* p)
{
	g->p = (Painter*)malloc(sizeof(Painter));
	if (g->p == NULL)
	{
		freePainter(g->p);
		return;
	}
	g->p = p;
	for (int i = 0; i < g->carCount; i++)
	{
		if (g->cars[i].problemType == 0) {
			addCar2(g->p, &g->cars[i]);
		}
	}
}
void addMechanic(Garage* g, Mechanic* m)
{
	g->m = (Mechanic*)malloc(sizeof(Mechanic));
	if (g->m == NULL)
	{
		freeMechanic(g->p);
		return;
	}
	g->m = m;
	for (int i = 0; i < g->carCount; i++)
	{
		if (g->cars[i].problemType == 2) {
			addCar1(g->m, &g->cars[i]);
		}
	}
}
void addTyreMan(Garage* g, TyreMan* t)
{
	g->t = (TyreMan*)malloc(sizeof(TyreMan));
	if (g->t == NULL)
	{
		freeTyreMan(g->p);
		return;
	}
	g->t = t;
	for (int i = 0; i < g->carCount; i++)
	{
		if (g->cars[i].problemType == 1) {
			addCar(&g->cars[i], g->t);
		}
	}
}
void firePainter(Garage* g)
{
	
	freePainter(g->p);
	g->p = NULL;
}
void fireMechanic(Garage* g)
{
	freeMechanic(g->m);
	g->m = NULL;
}
void fireTyreMan(Garage* g)
{
	freeTyreMan(g->t);
	g->t = NULL;
}
Car* searchArray(const Garage* g)
{
	Car c;
	switch (g->sType)
	{
	case 0:
	{
		int found;
		char plate[10];
		do
		{
			found = 0;

			printf("enter cars license plate : \n");
			scanf("%s", plate);
			for (int i = 0; i < strlen(plate); i++)
				if (!isdigit(plate[i]))
					found = 1;

		} while (strlen(plate) != 9 || found == 1);
		plate[9] = '\0';
		strcpy(c.license_plate, plate);

		return bsearch(&c, g->cars, g->carCount, sizeof(Car), CompareLicense_Plate);
		break;
	}
	case 1:
	{
		c.driver = (Person*)malloc(sizeof(Person));
		if (c.driver == NULL)
		{
			return;
		}
		initPerson(c.driver);
		return bsearch(&c, g->cars, g->carCount, sizeof(Car), CompareDriverName);
		break;
	}
	case 2:
	{
		initDate(&c.purchaseDate);
		return bsearch(&c, g->cars, g->carCount, sizeof(Car), CompareDate);
		break;
	}
	default:
	{
		printf("Error Flight Array not sorted ");
		return NULL;
		break;
	}
	}
}



void generalArrayFunction(void* arr, int size, int typeSize, void(*func)(void* element))
{
	for (int i = 0; i < size; i++)
		func((char*)(arr)+i * typeSize);

}
void printCarBrands(const Garage* g)
{
	generalArrayFunction(g->cars, g->carCount, sizeof(Car), printBrand);
}
int carExists(const Garage* g, char plate[10])
{
	for (int i = 0; i < g->carCount; i++)
	{
		if (sameCar(&g->cars[i], plate) == 1) {
			return 1;
		}
	}
	return 0;
}
void chooseBrand(Garage* g)
{
	char* str[255] ;
	printf("please enter the Name of the brand : ");
	scanf("%s", str);

	int found = 0, count = 0;

	for (int i = 0; i < g->carCount; i++)
	{
		found = is_eq(g->cars[i].brand, str);
		if (found)
		{
			printCar(&(g->cars[i]));
			count++;
		}
			
		found = 0;
	}
	if (count == 0)
		printf("car brand was not found.");


	
}

int saveGarageToTxt(const Garage* g, const char* fileName)
{
	if (!g)
		return 0;
	FILE* fp;

	fp = fopen(fileName, "w");
	if (!fp) {
		printf("Error open Garage file to write\n");
		return 0;
	}
	fprintf(fp, "%d\n", g->sType);
	fprintf(fp, "%d\n", g->carCount);
	if (g->carCount > 0)
	{
		for (int i = 0; i < g->carCount;i++)
		{
			fprintf(fp, "%s\n", g->cars[i].brand);
			fprintf(fp, "%s\n", g->cars[i].driver->name);
			fprintf(fp, "%s\n", g->cars[i].license_plate);
			fprintf(fp, "%d\n", g->cars[i].problemType);
			fprintf(fp, "%d %d %d\n", g->cars[i].purchaseDate.day, g->cars[i].purchaseDate.month, g->cars[i].purchaseDate.year);
		}

	}

	fprintf(fp, "%s\n", g->t->tyreWoman->name);
	fprintf(fp, "%s\n", g->p->painterMan->name);
	fprintf(fp, "%s\n", g->m->mechanicMan->name);

	

	fclose(fp);
	return 1;
}

int loadGarageFromTxt(Garage* g, const char* fileName)
{
	FILE* fp;

	fp = fopen(fileName, "r");
	if (!fp)
	{
		printf("Error open airport manager file\n");
		return 0;
	}

	char temp[255];

	fscanf(fp, "%d", &g->sType);
	fscanf(fp, "%d", &g->carCount);
	


	for (int i = 0; i < g->carCount; i++)
	{
		g->cars = (Car*)realloc(g->cars, (g->carCount + 1) * sizeof(Car));
		if (g->cars == NULL)
		{
			return 0;
		}
		
		myGets1(temp, 255, fp);
		g->cars[i].brand = getDynStr(temp);

		g->cars[i].driver = (Person*)malloc(sizeof(Person));
		if (!g->cars[i].driver)
		{
			break;
		}

		myGets1(temp, 255, fp);
		g->cars[i].driver->name = getDynStr(temp);
		
		myGets1(&g->cars[i].license_plate, 255, fp);
		
		fscanf(fp, "%d", &g->cars[i].problemType);
		fscanf(fp, "%d %d %d", &g->cars[i].purchaseDate.day, &g->cars[i].purchaseDate.month, &g->cars[i].purchaseDate.year);

	}

	g->t->tyreWoman = (Person*)malloc(sizeof(Person));
	if (!g->t->tyreWoman)
	{
		fclose(fp);
		return 0;
	}
	myGets1(temp, 255, fp);
	g->t->tyreWoman->name = getDynStr(temp);

	g->p->painterMan = (Person*)malloc(sizeof(Person));
	if (!g->p->painterMan)
	{
		fclose(fp);
		return 0;
	}
	myGets1(temp, 255, fp);
	g->p->painterMan->name = getDynStr(temp);

	g->m->mechanicMan = (Person*)malloc(sizeof(Person));
	if (!g->m->mechanicMan)
	{
		fclose(fp);
		return 0;
	}
	myGets1(temp, 255, fp);
	g->m->mechanicMan->name = getDynStr(temp);


	fgetc(fp);
	g->t->carsToFix = (LIST*)malloc(sizeof(LIST));
	if (g->t->carsToFix == NULL)
	{
		return NULL;
	}
	L_init(g->t->carsToFix);
	for (int i = 0;i < g->carCount;i++)
	{
		int type = g->cars[i].problemType;

		if (type == 0)
			addCar2(g->p, &g->cars[i]);
		else if (type == 1)
			addCar(&g->cars[i], g->t);
		else
			addCar1(g->m, &g->cars[i]);
	}

	fclose(fp);
	return 1;
}

