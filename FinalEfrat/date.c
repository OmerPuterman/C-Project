#include "Date.h"

#include "generalStrings.h"
#include <stdlib.h>


int checkDate(int day, int month, int year)
{
	if (day > 0 && month > 0 && month < 13 && year >= 1900)
	{
		if (month < 8)
		{
			if (month == 2 && day < 29)
			{
				return 1;
			}
			else if ((month % 2 == 1 && day < 32) || (month % 2 == 0 && day < 31))
			{
				return 1;
			}
		}
		else if ((month % 2 == 1 && day < 31) || (month % 2 == 0 && day < 32))
		{
			return 1;
		}
	}
	return 0;
}
void initDate(Date* d)
{
	int valid;
	int day, month, year;
	char waste;
	do
	{
		valid = 0;
		char* DateStringed = getStrExactLength("type Date: dd##mm##yyy");
		if (DateStringed[2] == '#' && DateStringed[3] == '#' && DateStringed[6] == '#' && DateStringed[7] == '#')
		{
			valid = 1;
			sscanf(DateStringed, " %d %c%c %d %c%c %d", &day, &waste, &waste, &month, &waste, &waste, &year);
		}


	} while (valid == 0 || checkDate(day, month, year) == 0);

	d->day = day;
	d->month = month;
	d->year = year;
}
void printDate(Date* d)
{
	printf("Date: %d//%d//%d      ", d->day, d->month, d->year);
}
int compareDates(Date date1, Date date2) {
	// Compare years
	if (date1.year != date2.year) {
		return date1.year - date2.year;
	}

	// Compare months
	if (date1.month != date2.month) {
		return date1.month - date2.month;
	}

	// Compare days
	return date1.day - date2.day;
}

int		saveDateToFile(const Date* pDate, FILE* fp)
{
	if (fwrite(pDate, sizeof(Date), 1, fp) != 1)
	{
		printf("Error write date\n");
		return 0;
	}

	return 1;

}

int		loadDateFromFile(Date* pDate, FILE* fp)
{
	if (fread(pDate, sizeof(Date), 1, fp) != 1)
	{
		printf("Error write date\n");
		return 0;
	}

	return 1;

}
int		compareDate(const void* d1, const void* d2)
{
	const Date* pDate1 = (const Date*)d1;
	const Date* pDate2 = (const Date*)d2;
	if (pDate1->year > pDate2->year)
		return 1;
	if (pDate1->year < pDate2->year)
		return -1;

	if (pDate1->month > pDate2->month)
		return 1;

	if (pDate1->month < pDate2->month)
		return -1;

	if (pDate1->day > pDate2->day)
		return 1;

	if (pDate1->day < pDate2->day)
		return -1;

	return 0;
}