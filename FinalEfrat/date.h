#pragma once

#include <stdio.h>

typedef struct
{
    int day;
    int month;
    int year;
}Date;

int checkDate(int day, int month, int year);
void initDate(Date* d);
void printDate(Date* d);
int compareDates(Date date1, Date date2);
int		saveDateToFile(const Date* pDate, FILE* fp);
int		loadDateFromFile(Date* pDate, FILE* fp);
