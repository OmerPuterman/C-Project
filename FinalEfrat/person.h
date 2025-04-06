#pragma once

#include <stdio.h>

typedef struct
{
	char* name;
}Person;

void initPerson(Person*p);
void printPerson(const Person* p);
void freePerson(Person* p);
int		savePersonToFile(const Person* pP, FILE* fp);