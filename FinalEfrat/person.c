#include "person.h"

#include "generalStrings.h"
#include "General.h"
#include "fileHelper.h"


void initPerson(Person* p)
{
	p->name = getStrExactLength("please enter the Name of person: ");
}
void printPerson(const Person* p)
{
	printf("his name is: %s\n", p->name);
}
void freePerson(Person* p)
{
	free(p->name);
	free(p);
}


	int		savePersonToFile(const Person* pP, FILE* fp)
	{
		if (!writeStringToFile(pP->name, fp, "Error write name\n"))
		{
			fclose(fp);
			return 0;
		}
		return 1;
	}

