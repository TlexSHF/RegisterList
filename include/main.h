#ifndef OPPGAVE_3_MAIN_H
#define OPPGAVE_3_MAIN_H
#include "list.h"

#define OK 0
#define QUIT 1
#define ERROR 1

void printMenu();
int selectOption();
int getInput(char *szBuffer, int iSize);
void case1AddElement(LIST *pList, char *szBuffer0, char *szBuffer1, int iSize);
void case2GetElement(LIST *pList, char *szBuffer, int iSize);
void case3GetIndex(LIST *pList, char *szBuffer, int iSize);
void case4DeleteByName(LIST *pList, char *szBuffer, int iSize);
void case5DeleteByAge(LIST *pList, char *szBuffer, int iSize);
int validateAge(char *szBuffer, int iSize);
int checkIfNumber(char *szText);

#endif //OPPGAVE_3_MAIN_H
