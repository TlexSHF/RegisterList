#ifndef DOUBLELINKEDLIST_LIST_H
#define DOUBLELINKEDLIST_LIST_H

typedef struct _PERSON {

    char *szName;
    int iAge;
    char *szMunicipality;

    struct _PERSON *pNext;
    struct _PERSON *pPrevious;

} PERSON;

typedef struct _LIST {
    int iSize;
    PERSON *pHead;
    PERSON *pTail;
} LIST;


PERSON *createNode(char *szName, int iAge, char *szMunicipality);
void addElement(PERSON *pNode, int index, LIST *pList);
PERSON *getElementByIndex(int index, LIST *pList);
int getIndexByName(char *szName, LIST *pList);
void deleteByName(char *szName, LIST *pList);
void deleteByAge(int iLowBound, int iHighBound, LIST *pList);
void deleteElement(PERSON *pNode, LIST *pList);
void printList(LIST *pList);
void freeListContents(LIST *pList);
char *copyString(char *szString);
char *toLowerCase(char *szText);


#endif //DOUBLELINKEDLIST_LIST_H
