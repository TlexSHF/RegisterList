#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "main.h"
#include "list.h"
int main(int argc, char **argv ){
    //Creates the list
    LIST *pList = malloc(sizeof(LIST));

    if(pList != NULL) {
        memset(pList, 0, sizeof(LIST));
        do {
            printMenu();
        } while( selectOption(pList) == OK );
        //If QUIT -> Program stops

        /* Freeing the list */
        freeListContents(pList);
        free(pList);
    }
    return 0;
}
void printMenu() {

    printf("\r\n"
           "Type the number of your action [1-6]: \r\n"
           "1. Add element\r\n"
           "2. Get element by index\r\n"
           "3. Get index of element\r\n"
           "4. Delete elements by name\r\n"
           "5. Delete elements by age\r\n"
           "6. Print entire database\r\n"
           "7. QUIT\r\n"
    );

}
int selectOption(LIST *pList) {
    int iInstructionCode = OK;
    int iChar;
    int iSize = 256;
    int iBuffer0;
    int iBuffer1;
    PERSON *pNode;
    char *szBuffer0 = malloc(sizeof(char) * iSize);
    char *szBuffer1 = malloc(sizeof(char) * iSize);
    if(szBuffer0 == NULL || szBuffer1 == NULL) {
        printf("malloc failed: szBuffer0 or szBuffer1\r\n");
    } else {
        memset(szBuffer0, 0, sizeof(char) * iSize);
        memset(szBuffer1, 0, sizeof(char) * iSize);

        do {
            iChar = getchar();
        } while( iChar == '\n' );

        printf("Input selected (%i)\r\n", iChar);

        switch (iChar) {
            case '1':
                case1AddElement(pList, szBuffer0, szBuffer1, iSize);
                iInstructionCode = OK;
                break;
            case '2':
                case2GetElement(pList, szBuffer0, iSize);
                iInstructionCode = OK;
                break;
            case '3':
                case3GetIndex(pList, szBuffer0, iSize);
                iInstructionCode = OK;
                break;
            case '4':
                case4DeleteByName(pList, szBuffer0, iSize);
                iInstructionCode = OK;
                break;
            case '5':
                case5DeleteByAge(pList, szBuffer0, iSize);
                iInstructionCode = OK;
                break;
            case '6':
                /* PRINT LIST */
                printf("This is the database so far:\r\n\n");
                printList(pList);
                iInstructionCode = OK;
                break;
            case '7':
                /* QUIT PROGRAM */
                printf("Quitting... \r\n");
                iInstructionCode = QUIT;
                break;
            default:
                printf("invalid number\r\n");
                break;
        }

        free(szBuffer0);
        free(szBuffer1);
    }
    return iInstructionCode;
}
int getInput(char *szBuffer, int iSize) {
    int iInstructionCode = OK;

    if(szBuffer == NULL) {
        printf("Fail: szBuffer not pointing to allocated memory\r\n");
        iInstructionCode = ERROR;
    } else {
        //Resetting buffer if previously used
        memset(szBuffer, 0, sizeof(char) * iSize);

        if( scanf("%s", szBuffer) != 0) {
            iInstructionCode = OK;
        } else {
            printf("something went wrong with input...\r\n");
            iInstructionCode = ERROR;
        }

    }

    return iInstructionCode;
}
/* ADD ELEMENT */
void case1AddElement(LIST *pList, char *szBuffer0, char *szBuffer1, int iSize) {
    int iInstructionCode = ERROR; //Only if gotten to the innermost step, everything is okay
    int iBuffer = 0;
    PERSON *pNode;
    int iInputCode = 0;
    if(szBuffer0 == NULL || szBuffer1 == NULL) {
        printf("Fail: strings not pointing to allocated memory\r\n");
    } else {
        printf("[Add element] selected\r\n");

        printf("Enter the [NAME]:\r\n");
        if (getInput(szBuffer0, iSize) == OK) {
            printf("[NAME]: '%s' gathered\r\n", szBuffer0);

            do {
                printf("Enter the [AGE]:\r\n");
                iInputCode = getInput(szBuffer1, iSize);

            } while(checkIfNumber(szBuffer1) == 0);

            if (iInputCode == OK) {

                iBuffer = atoi(szBuffer1);
                printf("[AGE]: '%i' gathered\r\n", iBuffer);

                printf("Enter the [MUNICIPALITY]:\r\n");
                if (getInput(szBuffer1, iSize) == OK) {
                    printf("[MUNICIPALITY]: '%s' gathered\r\n", szBuffer1);

                    pNode = createNode(szBuffer0, iBuffer, szBuffer1);
                    addElement(pNode, -1, pList); //Element will be placed in last place

                    printf("Element added to database");
                    iInstructionCode = OK;
                }
            }
        }
    }
    if(iInstructionCode == ERROR) {
        printf("Something went wrong. Try again...");
    }
}
/* GET ELEMENT BY INDEX */
void case2GetElement(LIST *pList, char *szBuffer, int iSize) {
    int iBuffer = 0;
    PERSON *pNode;
    int iInputCode;
    if(pList->iSize == 0) {
        printf("There are no elements in the database yet. Try adding some before you get them\r\n");
    } else if(szBuffer == NULL) {
        printf("Fail: string not pointing to allocated memory\r\n");
    } else {

        printf("[Get element] selected\r\n");

        //Many checks to validate that input: doesnt fail, is a number, is in the list
        while(1) {
            printf("Enter [INDEX] of element:\r\n");
            iInputCode = getInput(szBuffer, iSize);
            if(iInputCode == OK) {

                if(checkIfNumber(szBuffer)) {
                    iBuffer = atoi(szBuffer);
                    if(iBuffer < pList->iSize) {
                        printf("Finding element '%i'...\r\n", iBuffer);
                        break;
                    } else {
                        printf("The index needs to be in between: 0 and %i\r\n", pList->iSize - 1);
                    }
                } else {
                    printf("The index needs to be a number\r\n");
                }
            } else {
                break;
            }
        }

        if(iInputCode == OK) {
            printf("Finding element '%i'...\r\n", iBuffer);

            pNode = getElementByIndex(iBuffer, pList);
            printf("%s, %i years, lives in %s\r\n", pNode->szName, pNode->iAge, pNode->szMunicipality);
        } else {
            printf("Something went wrong. Try again...");
        }
    }
}
/* GET INDEX OF ELEMENT */
void case3GetIndex(LIST *pList, char *szBuffer, int iSize) {
    int iBuffer = 0;
    if(pList->iSize == 0) {
        printf("There are no elements in the database yet. Try adding some before you get them\r\n");
    } else if(szBuffer == NULL) {
        printf("Fail: string not pointing to allocated memory\r\n");
    } else {
        printf("[Get index] selected\r\n");
        printf("Enter [NAME] of element:\r\n");
        if (getInput(szBuffer, iSize) == OK) {
            printf("Finding index of '%s'...\r\n", szBuffer);

            //TODO should return all indexes for that name?
            iBuffer = getIndexByName(szBuffer, pList);
            if(iBuffer == -1) {
                printf("couldnt find element in database\r\n");
            } else {
                printf("The Index for the first %s found is: '%i'", szBuffer, iBuffer);
            }

        } else {
            printf("Something went wrong. Try again...");
        }
    }
}
/* DELETE BY NAME */
void case4DeleteByName(LIST *pList, char *szBuffer, int iSize) {
    if(pList->iSize == 0) {
        printf("There are no elements in the database yet. Try adding some before you delete them\r\n");
    } else if(szBuffer == NULL) {
        printf("Fail: string not pointing to allocated memory\r\n");
    } else {

        /* DELETE BY NAME */
        printf("[Delete by NAME] selected\r\n");

        printf("Enter [NAME] of elements:\r\n"
               "(All elements of this [NAME] will be DELETED!)\r\n");
        if (getInput(szBuffer, iSize) == OK) {

            printf("Deleting all elements named '%s'...\r\n", szBuffer);
            deleteByName(szBuffer, pList);

        } else {
            printf("Something went wrong. Try again...");
        }
    }
}
/* DELETE BY AGE */
void case5DeleteByAge(LIST *pList, char *szBuffer, int iSize) {
    int iBuffer0 = 0;
    int iBuffer1 = 0;
    int iInputCode = 0;
    int iInstructionCode = ERROR; //Only if gotten to the innermost step, everything is okay

    if(pList->iSize == 0) {
        printf("There are no elements in the database yet. Try adding some before you delete them\r\n");
    } else if(szBuffer == NULL ) {
        printf("Fail: strings not pointing to allocated memory\r\n");
    } else {

        printf("[Delete by AGE] select\r\n");

        printf("All elements between the two [AGES] will be deleted!\r\n"
               "Enter [LOWEST BOUND AGE] to be deleted\r\n");

        iBuffer0 = validateAge(szBuffer, iSize);
        if(iBuffer0 != -1) {
            printf("[LOWEST BOUND AGE] '%i' gathered\r\n", iBuffer0);
            printf("Enter [HIGHEST BOUND AGE] to be deleted\r\n");
            iBuffer1 = validateAge(szBuffer, iSize);
            if(iBuffer1 != -1) {
                printf("[HIGHEST BOUND AGE] '%i' gathered\r\n", iBuffer1);

                if(iBuffer0 <= iBuffer1) {
                    printf("Deleting all elements between '%i' and '%i' years\r\n", iBuffer0, iBuffer1);
                    deleteByAge(iBuffer0, iBuffer1, pList);
                    iInstructionCode = OK;
                } else {
                    printf("The ages are in the wrong order. Try again with the smaller number first \r\n"
                           "(Or two similar numbers if there is only one age wished to be deleted)\r\n");
                }
            }
        }
        if (iInstructionCode == ERROR) {
            printf("Something went wrong. Try again...");
        }
    }
}
int validateAge(char *szBuffer, int iSize) {
    int iBuffer = -1;
    int iInputCode = 0;

    while(1) {
        iInputCode = getInput(szBuffer, iSize);
        if(iInputCode == OK) {

            if(checkIfNumber(szBuffer)) {
                iBuffer = atoi(szBuffer);
                break;
            } else {
                printf("The age needs to be a positive number. Try again: \r\n");
            }
        } else {
            break;
        }
    }

    return iBuffer;
}
int checkIfNumber(char *szText) {
    int i = 0;
    int isNumber = 1;

    if(szText == NULL) {
        isNumber == 0;
    } else {
        while(szText[i] != '\0') {
            if(!(isdigit(szText[i]))) {
                isNumber = 0;
            }
            i++;
        }
    }

    return isNumber;
}