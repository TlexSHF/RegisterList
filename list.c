#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "list.h"

/* DOUBLE LINKED NODE */

/* CREATE A PERSON NODE */
PERSON *createNode(char *szName, int iAge, char *szMunicipality) {
    PERSON *pNode = malloc(sizeof(*pNode));

    if(pNode != NULL) {
        memset(pNode, 0, sizeof(*pNode));

        pNode->szName = copyString(szName);
        pNode->iAge = iAge;
        pNode->szMunicipality = copyString(szMunicipality);

        pNode->pNext = NULL;
        pNode->pPrevious = NULL;
    }
    return pNode;
}
/* ADD ELEMENT IN FRONT, BETWEEN OR AT END */
/* if index = -1 will add at last position */
void addElement(PERSON *pNode, int index, LIST *pList) {
    PERSON *pTmpNode;
    //Validates -1 <= index <= iSize
    if(index >= -1 && index <= pList->iSize) {
        if(index == 0) {
            //Place at HEAD
            if(pList->pHead == NULL) {
                //If head is null, tail is also null
                pList->pHead = pNode;
                pList->pTail = pNode;
            } else {
                pNode->pNext = pList->pHead;
                pList->pHead->pPrevious = pNode;
                pList->pHead = pNode;
            }

        } else if(index == -1 || index == pList->iSize) {
            //Place at TAIL
            if(pList->pTail == NULL) {
                //If tail is null, head is also null
                pList->pHead = pNode;
                pList->pTail = pNode;
            } else {
                pNode->pPrevious = pList->pTail;
                pList->pTail->pNext = pNode;
                pList->pTail = pNode;
            }
        } else {
            //Place in MIDDLE
            pTmpNode = getElementByIndex(index - 1, pList);
            pNode->pNext = pTmpNode->pNext;
            pNode->pPrevious = pTmpNode;
            pNode->pNext->pPrevious = pNode;
            pNode->pPrevious->pNext = pNode;
        }
        pList->iSize++;
    } else {
        printf("Invalid index. Please insert between 0 and %i", pList->iSize);
    }
}
/* GET ELEMENT BY INDEX */
/* if index = -1 will get last element */
PERSON *getElementByIndex(int index, LIST *pList) {
    int i;
    PERSON *pThis;

    //Validates -1 <= index < iSize
    if(index >= -1 && index < pList->iSize) {
        if(index == 0) {
            //Returns HEAD
            pThis = pList->pHead;
        } else if(index == -1 || index == pList->iSize - 1) {
            //Returns TAIL
            pThis = pList->pTail;
        } else if(index > pList->iSize / 2) {
            //Searches from HEAD
            pThis = pList->pHead;
            for(i = 0; i < index; i++) {
                //Ends when pThis->pNext == index
                pThis = pThis->pNext;
            }
        } else {
            //Searches from TAIL
            pThis = pList->pTail;
            for(i = pList->iSize - 1; i > index; i--) {
                //Ends when pThis->pPrevious == index
                pThis = pThis->pPrevious;
            }
        }
    } else {
        printf("Invalid index. Please insert between 0 and %i", pList->iSize);
        pThis = NULL;
    }

    return pThis;
}
/* GET FIRST INDEX MATCHING NAME */
int getIndexByName(char *szName, LIST *pList) {
    int i = 0;
    PERSON *pTmp;

    if(szName == NULL || pList == NULL) {
        printf("name or list empty\r\n");
    } else {
        pTmp = pList->pHead;
        //Increments i until the node has the same name
        //TODO Segfault sometimes
        while(strcmp( toLowerCase(pTmp->szName), toLowerCase(szName) ) != 0) {
            pTmp = pTmp->pNext;
            i++;
            if(i >= pList->iSize) {
                //Could not find
                i = -1;
                break;
            }
        }
    }
    return i;
}
/* DELETES ALL ELEMENTS WITH NAME */
void deleteByName(char *szName, LIST *pList) {
    int i;
    int iOriginListSize = pList->iSize;
    PERSON *pTmp = pList->pHead;
    //Increments i until the node has the same name
    for(i = 0; i < iOriginListSize; i++) {
        if(strcmp(toLowerCase(pTmp->szName), toLowerCase(szName)) == 0) {
            deleteElement(pTmp, pList);
        }
        pTmp = pTmp->pNext;
    }
}
/* DELETES ALL ELEMENTS BETWEEN CERTAIN AGE */
void deleteByAge(int iLowBound, int iHighBound, LIST *pList) {
    int i;
    int iOriginListSize = pList->iSize;
    PERSON *pTmp = pList->pHead;
    //Increments until node has age in between ages
    for(i = 0; i < iOriginListSize; i++) {
        if(pTmp->iAge >= iLowBound && pTmp->iAge <= iHighBound) {
            deleteElement(pTmp, pList);
        }
        pTmp = pTmp->pNext;
    }
}
void deleteElement(PERSON *pNode, LIST *pList) {

    if(pList->pHead == pNode && pList->pTail == pNode) {
        //Removing connections to only element int list
        pList->pHead = NULL;
        pList->pTail = NULL;

    } else if(pList->pHead == pNode) {
        //Removing connections to head
        pList->pHead = pList->pHead->pNext;

    } else if(pList->pTail == pNode) {
        //Removing connections to tail
        pList->pTail = pList->pTail->pPrevious;

    } else {
        //Removing connections in middle
        pNode->pNext->pPrevious = pNode->pPrevious;
        pNode->pPrevious->pNext = pNode->pNext;
    }
    free(pNode);
    pList->iSize--;
}
void printList(LIST *pList) {
    int i;
    PERSON *pNode = pList->pHead;

    if(pList->iSize == 0) {
        printf("... is empty. Please insert some elements\r\n");
    } else {
        for(i = 0; i < pList->iSize; i++) {
            printf("%i: %s %i %s\r\n", i, pNode->szName, pNode->iAge, pNode->szMunicipality);
            pNode = pNode->pNext;
        }
    }
}
void freeListContents(LIST *pList) {
    PERSON *pTmp = pList->pHead;
    PERSON *pTmpNext;
    while(pTmp != NULL) {
        pTmpNext = pTmp->pNext;
        free(pTmp->szName);
        free(pTmp->szMunicipality);
        free(pTmp);
        pTmp = pTmpNext;
    }
}
char *copyString(char *szString) {
    int i;
    int iSize = strlen(szString) + 1; //strlen +1 counts also the \0 character
    char *szStringCpy = malloc(sizeof(char) * iSize);
    if(szStringCpy == NULL) {
        printf("error on malloc\r\n");
    } else {
        for(i = 0; i < iSize; i++) {
            szStringCpy[i] = szString[i];
        }
    }
    return szStringCpy;
}
//TODO This function only works on database strings, but not on the others
char *toLowerCase(char *szText) {
    int i;
    char newChar;

    for(i = 0; i < strlen(szText); i++) {
        newChar = szText[0] | 0x20;
        szText[0] = newChar;
    }
    return szText;
}