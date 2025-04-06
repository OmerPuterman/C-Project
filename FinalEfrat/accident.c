#include "accident.h"
#include "date.h"
#include "generalStrings.h"

#define printCarToFile(car,fp)  fprintf(fp, "brand - %s\n", car.brand);\
								fprintf(fp, "name - %s\n", car.driver->name);\
								fprintf(fp, "license plate - %s\n", car.license_plate);\
								fprintf(fp, "problem type - %d\n", car.problemType);\
								fprintf(fp, "date - %d/%d/%d\n", car.purchaseDate.day, car.purchaseDate.month, car.purchaseDate.year);\

void initAccident(Accident* a)
{
	a->accidentLocation = getStrExactLength("please enter the place of the accident: ");
	initDate(&a->d);
	initCar(&a->c1);
	initCar(&a->c2);
}
void printAccident(const Accident* a)
{
	printf("the accident happened in: %s at the date", a->accidentLocation);
	printDate(&a->d);
	printf("\nwith the cars:\n");
	printCar(&a->c1);
	printCar(&a->c2);

}
void freeAccident(Accident* a)
{
	freeCar(&a->c1);
	freeCar(&a->c2);
	free(a->accidentLocation);
	free(a);
}

int writeAccToFile(const Accident* a, const char* fileName)
{
	if (!a)
		return 0;

	FILE* fp;

	fp = fopen(fileName, "a");
	if (!fp) {
		printf("Error open Garage file to write\n");
		return 0;
	}

	fprintf(fp, "accident location - %s\n", a->accidentLocation);
	fprintf(fp, "Date of accident - %d/%d/%d\n", a->d.day, a->d.month, a->d.year);
	printCarToFile(a->c1,fp);
	printCarToFile(a->c2,fp);

		fclose(fp);
		return 1;
}