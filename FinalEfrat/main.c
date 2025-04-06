#include "person.h"
#include "garage.h"
#include "garageFile.h"

#include "car.h"
#include "date.h"
#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>

#define GARAGE_FILE_NAME "garage.bin"
#define CGARAGE_FILE_NAME "cGarage.bin"
#define GARAGE_FILE_NAME_TXT "garage.txt"
#define ACC_FILE_NAME "accident.txt"

int main()
{
	FILE* fp;
	int work = 1;
	Garage g;
	initGarage(&g);
	
	int x = 0;
	do {

		printf("Enter 1 - initiate garage from txt file\n");
		printf("Enter 2 - initiate garage from bin file\n");
		printf("Enter 3 - initiate garage yourself\n");
		scanf("%d", &x);

	} while ((x != 1) && (x != 2) && (x != 3));
	if (x == 1)
	{
		fp = fopen(GARAGE_FILE_NAME_TXT, "r");
		if (fp)
		{
			loadGarageFromTxt(&g, GARAGE_FILE_NAME_TXT);
		}
		else
		{
			work = 0;
		}
		
	}
	else if (x == 2)
	{
		fp = fopen(GARAGE_FILE_NAME, "rb");
		if (fp)
		{
			initGarageFromFile(&g, g.cars, GARAGE_FILE_NAME, CGARAGE_FILE_NAME);
		}
		else
		{
			work = 0;
		}
	}
	if (x==3||work==0)
	{
		Person p1;
		Person p2;
		Person p3;
		printf("Painter ");
		initPerson(&p1);
		printf("Mechanic ");
		initPerson(&p2);
		printf("Tyrewoman ");
		initPerson(&p3);
		Painter p;
		Mechanic m;
		TyreMan t;
		initPainter(&p, &p1);
		initMechanic(&m, &p2);
		initTyreMan(&t, &p3);
		addTyreMan(&g, &t);
		addPainter(&g, &p);
		addMechanic(&g, &m);
	}
	
	int option;
	do
	{
		printf("Please choose one of the following options\n");
		printf("0 - Choose binary or text file\n");
		printf("1 - Print Garage\n");
		printf("2 - Print Painter\n");
		printf("3 - Print Mechanic\n");
		printf("4 - Print TyreMan\n");
		printf("5 - Add Car To Garage\n");
		printf("6 - Report An Accident (Add both cars to garage)\n");
		printf("7 - Fire And Hire New Painter\n");
		printf("8 - Fire And Hire New Mechanic\n");
		printf("9 - Fire And Hire New TyreMan\n");
		printf("10 - Sort Cars In Garage\n");
		printf("11 - Find a Car in Garage\n");
		printf("12 - Print all brand types in Garage\n");
		printf("13 - Print cars in the garage with chosen brand\n");
		printf("-1 - Quit\n");
		scanf("%d", &option);
		switch (option)
		{
		case 0:
		{
			
			do {
			
				printf("Enter 1 - initiate garage from txt file\n");
				printf("Enter 2 - initiate garage from bin file\n");
				scanf("%d", &x);

			} while ((x != 1) && (x != 2));
			if(x == 1)
				loadGarageFromTxt(&g, GARAGE_FILE_NAME_TXT);
			else 
				initGarageFromFile(&g, g.cars, GARAGE_FILE_NAME, CGARAGE_FILE_NAME);
			break;
		}
		case 1:
		{
			printGarage(&g);
			break;
		}
		case 2:
		{
			printPainter(g.p);
			break;
		}
		case 3:
		{
			printMechanic(g.m);
			break;
		}
		case 4:
		{
			printTyreMan(g.t);
			break;
		}
		case 5:
		{
			Car c;
			initCar(&c);
			addCarToGarage(&g, &c);
			break;
		}
		case 6:
		{
			Accident a;
			initAccident(&a);
			addCarsToGarage(&g, &a);
			writeAccToFile(&a, ACC_FILE_NAME);
			break;
		}
		case 7:
		{
			firePainter(&g);
			Person person;
			initPerson(&person);
			Painter p;
			initPainter(&p, &person);
			addPainter(&g, &p);
			break;
		}
		case 8:
		{
			fireMechanic(&g);
			Person person;
			initPerson(&person);
			Mechanic m;
			initMechanic(&m, &person);
			addMechanic(&g, &m);
			break;
		}
		case 9:
		{
			fireTyreMan(&g);
			Person person;
			initPerson(&person);
			TyreMan t;
			initTyreMan(&t, &person);
			addTyreMan(&g, &t);
			break;
		}
		case 10:
		{
			setSType(&g);
			SortArray(&g);
			break;
		}
		case 11:
		{
			Car* search;
			search = searchArray(&g);
			if (search == NULL)
			{
				printf("Error no such car exists in garage");
				return;
			}
			printCar(search);
			break;
		}
		case 12:
		{
			printCarBrands(&g);
			break;
		}
		case 13:
		{
			chooseBrand(&g);
			break;
		}
		default:
			break;
		}
	} while (option != -1);

	//saveGarageToTxt(&g, GARAGE_FILE_NAME_TXT);
	saveGarageToFile( &g, GARAGE_FILE_NAME, CGARAGE_FILE_NAME);
	
}