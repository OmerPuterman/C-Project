#include <stdio.h>
#include <stdlib.h>
#include "garageFile.h"
#include "General.h"
#include "fileHelper.h"
#include <string.h>



int		createCarArr(Garage* g)
{
	g->cars = (Car*)malloc(g->carCount * sizeof(Car));
	if (!g->cars)
	{
		printf("Alocation error\n");
		return 0;
	}
	return 1;
}

int		initGarageFromFile(Garage* g, Car* c, const char* fileName, const char* cFileName)
{
	FILE* fp;
	fp = fopen(fileName, "rb");
	if (!fp)
	{
		printf("Error open garage file\n");
		return 0;
	}
	g->cars = NULL;
	if (!readIntFromFile(&g->sType, fp, "Error\n"))
	{
		fclose(fp);
		return 0;
	}
	if (!readIntFromFile(&g->carCount, fp, "Error reading car count\n"))
	{
		fclose(fp);
		return 0;
	}

	if (!createCarArr(g))
	{
		printf("Alocation error\n");
		fclose(fp);
		return 0;
	}

	for (int i = 0;i < g->carCount;i++)
	{
		g->cars[i].brand = readStringFromFile(fp, "Error reading name\n");
		if (!g->cars[i].brand)
		{
			fclose(fp);
			return 0;
		}
		g->cars[i].driver = (Person*)malloc(sizeof(Person));
		g->cars[i].driver->name = readStringFromFile(fp, "Error reading name\n");
		if (!g->cars[i].driver->name)
		{
			fclose(fp);
			return 0;
		}

		
		if (!readFixSizeStrFromFile(g->cars[i].license_plate, fp, "Error reading\n"))
		{
			fclose(fp);
			return 0;
		}
		if (!readIntFromFile(&g->cars[i].problemType, fp, "Error  \n"))
		{
			fclose(fp);
			return 0;
		}
		if (!readIntFromFile(&g->cars[i].purchaseDate.day, fp, "Error  \n"))
		{
			fclose(fp);
			return 0;
		}
		if (!readIntFromFile(&g->cars[i].purchaseDate.month, fp, "Error  \n"))
		{
			fclose(fp);
			return 0;
		}
		if (!readIntFromFile(&g->cars[i].purchaseDate.year, fp, "Error  \n"))
		{
			fclose(fp);
			return 0;
		}
	}

	g->m->mechanicMan = (Person*)malloc(sizeof(Person));
	if (!g->m->mechanicMan->name)
	{
		fclose(fp);
		return 0;
	}
	g->m->mechanicMan->name = readStringFromFile(fp,"Error reading name\n" );
	
	g->t->tyreWoman = (Person*)malloc(sizeof(Person));
	if (!g->t->tyreWoman->name)
	{
		fclose(fp);
		return 0;
	}
	g->t->tyreWoman->name = readStringFromFile(fp, "Error reading name\n");
	
	
	FILE* fc;
	fc = fopen(cFileName, "rb");
	if (!fc)
	{
		printf("Error open garage file\n");
		return 0;
	}
	BYTE data[1];
	if (fread(&data, sizeof(BYTE), 1, fc) != 1)
		return 0;
	int len = (data[0] >> 3) & 0x1F;
	g->p->painterMan->name = (char*)calloc(len + 1, sizeof(char));
	if (!g->p->painterMan->name)
		return 0;
	if (fread(g->p->painterMan->name, sizeof(char), len, fc) != len)
	{
		free(g->p->painterMan->name);
		return 0;
	}
	
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

	fclose(fc);
	fclose(fp);
	return 1;
	//needs free

}


int		saveGarageToFile(const Garage* g, const char* fileName, const char* cFileName)
{
	FILE* fp;
	fp = fopen(fileName, "wb");
	if (!fp) {
		printf("Error open garage file to write\n");
		return 0;
	}

	if (!writeIntToFile(g->sType, fp, "Error write type\n"))
	{
		fclose(fp);
		return 0;
	}
	if (!writeIntToFile(g->carCount, fp, "Error write  count\n"))
	{
		fclose(fp);
		return 0;
	}


	for (int i = 0;i < g->carCount;i++)
	{
		writeStringToFile(g->cars[i].brand, fp, "Error  \n");
		writeStringToFile(g->cars[i].driver->name, fp, "Error  \n");
		writeStringToFile(g->cars[i].license_plate, fp, "Error  \n");
		writeIntToFile(g->cars[i].problemType, fp, "Error \n");
		writeIntToFile(g->cars[i].purchaseDate.day, fp, "Error  \n");
		writeIntToFile(g->cars[i].purchaseDate.month, fp, "Error  \n");
		writeIntToFile(g->cars[i].purchaseDate.year, fp, "Error \n");
	}

	if (!writeStringToFile(g->m->mechanicMan->name, fp, "Error \n"))
	{
		fclose(fp);
		return 0;
	}
	if (!writeStringToFile(g->t->tyreWoman->name, fp, "Error \n"))
	{
		fclose(fp);
		return 0;
	}
	
	

	FILE* fc;
	fc = fopen(cFileName, "wb");
	if (!fc) {
		printf("Error \n");
		return 0;
	}

	BYTE data[1] = { 0 };
	int len = (int)strlen(g->p->painterMan->name);
	data[0] = len << 3;
	
	if (fwrite(&data, sizeof(BYTE), 1, fc) != 1)
		return 0;

	if (fwrite(g->p->painterMan->name, sizeof(char), len, fc) != len)
		return 0;


	fclose(fc);
	fclose(fp);
	return 1;
}

