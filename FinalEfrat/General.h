#ifndef __GENERAL__
#define __GENERAL__

#define MAX_STR_LEN 255


char* getStrExactName(const char* msg);
char* myGets1(char* buffer, int size, FILE* source);
char* getDynStr(char* str);
char** splitCharsToWords(char* str, int* pCount, int* pTotalLength);

void generalArrayFunction1(void* arr, int size, int typeSize, void(*func)(void* element));

#endif
