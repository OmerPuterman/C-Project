#include "car.h"
#include "person.h"
#include "General.h"
#include "fileHelper.h"
#include <stdlib.h>
#include <stdio.h>
#include "generalStrings.h"


void printCar(const Car* c)
{
	printf("car's brand - %s \ncar's license plate - %s \ncar's type - %s\n", c->brand, c->license_plate, *(pType + c->problemType));
	printPerson(c->driver);
	printf("Cars  ");
	printDate(&c->purchaseDate);
	printf("\n\n");

}
void freeCar(Car* c)
{
	freePerson(c->driver);
	free(c->brand);
	free(c);
}
void initCar(Car* c)
{
	int temp = 0;
	char name[255];
	char brand[255];
	char plate[255];

	c->driver = (Person*)malloc(sizeof(Person));
	initPerson(c->driver);
	

	c->brand = getStrExactLength("enter cars brand: ");
	printf("enter date of purchase");
	initDate(&c->purchaseDate);
	int found;
	do
	{
		found = 0;
		printf("enter cars license plate : \n");
		myGets(plate, sizeof(plate));
		for (int i = 0; i < strlen(plate); i++)
			if (!isdigit(plate[i]))
				found = 1;

	} while (strlen(plate) != 9 || found == 1);
	strcpy(c->license_plate, plate);

	do
	{
		printf("enter car type of accident - \n #0 Paint\n #1 Tyres\n #2 Malfunction\n ");
		scanf("%d", &temp);

	} while ((temp < 0) || (temp >= eNofTypes));

	c->problemType = temp;

}
int CompareLicense_Plate(const void* a, const void* b)
{
	Car* c1 = (Car*)a;
	Car* c2 = (Car*)b;
	int num1;
	int num2;
	sscanf(c1->license_plate, "%d", &num1);
	sscanf(c2->license_plate, "%d", &num2);
	if (num1 == num2) {
		return 0;
	}
	else if (num1 < num2) {
		return -1;
	}
	else {
		return 1;
	}
}
int CompareDriverName(const void* a, const void* b)
{
	Car* c1 = (Car*)a;
	Car* c2 = (Car*)b;
	return strcmp(c1->driver->name,c2->driver->name);
}
int CompareDate(const void* a, const void* b)
{
	Car* c1 = (Car*)a;
	Car* c2 = (Car*)b;
	return compareDates(c1->purchaseDate,c2->purchaseDate);
}




int		saveCarToFile(const Car* pC, FILE* fp)
{
	if (!writeCharsToFile(pC->license_plate,LENGTH, fp, "Error write license plate code\n"))
		return 0;

	if (!writeStringToFile(pC->brand, fp, "Error write brand name\n"))
	{
		fclose(fp);
		return 0;
	}

	if (!saveDateToFile(&pC->purchaseDate, fp))
		return 0;

	if (!writeIntToFile(pC->problemType, fp, "Error write problem type\n"))
		return 0;
}

void printBrand(const Car* c)
{
	printf("%s \n", c->brand);
}
int sameCar(const Car* c, char plate[10])
{
	if (c->license_plate == plate)
	{
		return 1;
	}
	return 0;
}