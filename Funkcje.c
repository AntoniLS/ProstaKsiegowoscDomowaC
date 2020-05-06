#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

#include "Funkcje.h"

void printingMenu() {
    char decission[10];
    printf("[1] Show whole bill from all forwarded transactions\n");
    printf("[2] Show daily spending\n");
    printf("[3] Show weekly spending\n");
    printf("[4] Show yearly spending\n");
    printf("[5] Show all spending by specific family member\n");
    printf("Choose one of above [first digit is valid] >");
    scanf("%s", decission);
    printf("%s %c", decission, decission[0]);
    printf("\n");
    int ifCorrect = check(decission);
    printf("in main %d", ifCorrect);
    switch (ifCorrect) {
        case 1:
            //TODO
            break;
        case 2:
            //TODO
            break;
        case 3:
            //TODO
            break;
        case 4:
            //TODO
            break;
        case 5:
            //TODO
            break;
        default:
            printf("Incorrect decission\n");
            sleep(3);
            //printf("\033c"); // wipe terminal //doesnt work at all
            system("clear");
            printingMenu();
            break;
    }
};

int check(const char *decission) {
    if (isdigit(decission[0])) {
        int r = atoi(decission);
        printf("in funct %d\n", r);
        return r;
    } else return 0;
}

void loadingFromFile(const char *nameOfEntryFile, PayNode **pHead) {
    FILE *entryFile = fopen(nameOfEntryFile, "r");
    if (entryFile) {
        char temporaryLine[100]; // jak zmienic na char*
        while (fgets(temporaryLine, 100, entryFile)) {
            /// wczytywanie do tymczasowej struktury //
            InfoToPayNode temp; // tymczasowy node
            char *piece = strtok(temporaryLine, " ");
            printf("%s|", piece);
            temp.HowMuchMoney.value = piece;
            piece = strtok(NULL, " ");
            printf("%s|", piece);
            temp.HowMuchMoney.currency = piece;
            piece = strtok(NULL, " ");
            printf("%s|", piece);
            temp.CategoryOfProduct.category = piece;
            piece = strtok(NULL,":");
            printf("%s|", piece);
            temp.accountNumber = piece;
            //printf("%s %s %s\n", temp.accountNumber, temp.HowMuchMoney.value,temp.HowMuchMoney.currency);
            printf("\n");
            addingPaymentToNode(pHead, temp);

        }
        fclose(entryFile);
    }
}

void addingPaymentToNode(PayNode **pHead, InfoToPayNode temp) {
    PayNode *newNode = malloc(sizeof(PayNode));
    if (newNode == NULL) {
        printf("no memory for allocation\n");
        exit(1);
    }
    printf("%s %s %s\n", temp.accountNumber, temp.HowMuchMoney.value,temp.HowMuchMoney.currency);
    (*newNode).InfoAboutPayment = temp;
    printf("%s %s %s\n", (*newNode).InfoAboutPayment.accountNumber, (*newNode).InfoAboutPayment.HowMuchMoney.value,(*newNode).InfoAboutPayment.HowMuchMoney.currency);
    newNode->pNext = NULL;

    if (*pHead == NULL) { //lista pusta
        printf("pHead\n");
        *pHead = newNode;
        return;
    }
    // lista zapelniona
    PayNode *d = *pHead;
    while (d->pNext != NULL) {
        d = d->pNext;
        printf("loop\n");
    }
    printf("nowyNode\n");
    d->pNext = newNode;
}

void readingNodes(PayNode *pHead) {
    while (pHead->pNext != NULL) {
        //czytanie
        printf("LoP\n");
        printf("%s %s %s\n", pHead->InfoAboutPayment.accountNumber, pHead->InfoAboutPayment.HowMuchMoney.value,pHead->InfoAboutPayment.HowMuchMoney.currency);
        pHead = pHead->pNext;
    }
}

