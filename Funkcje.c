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

void loadingFromFile(const char *nameOfEntryFile, PayNode **node) {
    FILE *entryFile = fopen(nameOfEntryFile, "r");
    if (entryFile) {
        char temporaryLine[con];
        while(fgets(temporaryLine, con, entryFile)){

            Info temp; // temporary struct
            char* piece = strtok(temporaryLine, " "); // value
            strcpy(temp.value, piece);
            piece = strtok(NULL, " "); //currency
            strcpy(temp.currency, piece);
            piece = strtok(NULL, " "); // acountnumber
            strcpy(temp.accountNumber, piece);
            piece = strtok(NULL, ":"); // year
            temp.timeOfP.year = convertToInt(piece);
            piece = strtok(NULL, ":"); // month
            temp.timeOfP.month = convertToInt(piece);
            piece = strtok(NULL, " "); // day
            temp.timeOfP.day = convertToInt(piece);
            piece = strtok(NULL, ":"); // hour
            temp.timeOfP.hour = convertToInt(piece);
            piece = strtok(NULL, ":"); // minute
            temp.timeOfP.minute = convertToInt(piece);
            piece = strtok(NULL, " "); // seconds
            temp.timeOfP.second = convertToInt(piece);
            piece = strtok(NULL, "\n"); // category
            strcpy(temp.cat.category, piece);

            printf("%s %s %s %d\n", temp.value,temp.currency,temp.accountNumber, temp.timeOfP.year );
            addingPaymentToNode(node, temp);
        }
        fclose(entryFile);
    }
    else{
        printf("couldn't open text file\n");
    }
}
Info addingToStruct(const char * temporaryLine, Info temp){

}

int convertToInt(const char* chToInt){
    int t = atoi(chToInt);
    return t;
}

void addingPaymentToNode(PayNode **node, Info infAboutPayment){
    PayNode* newNode = malloc(sizeof(PayNode));
    newNode->pNext = NULL;
    newNode->info = infAboutPayment;
    if(*node == NULL){
        printf("firstNode\n");
        *node = newNode;
    }
    else{
        printf("newNode\n");
        PayNode* temp = *node;
        while(temp->pNext != NULL){
            temp = temp->pNext;
        }
        temp->pNext = newNode;
    }
}

void readingNodes(PayNode* node){
    PayNode* temp = node;
    if(node->pNext == NULL){
        printf("empty");
    }
    while(temp){
        printf("%s %s %s \n", temp->info.value, temp->info.currency, temp->info.accountNumber);
        temp = temp->pNext;
    }
}

void sortedby(PayNode* node, int option){
    switch(option){
        case 1:
            //expences only
            if(node->pNext == NULL){
                printf("empty");
            }
            while(node){
                if(node->info.plusminus[0] == '+'){ // trzeba jeszcze ustawic
                    printf("%s %s %s", node->info.value, node->info.currency, node->info.accountNumber);
                }
                node = node->pNext;
            }
            break;
        case 2:
            if(node->pNext == NULL){
                printf("empty");
            }
            while(node){
                if(node->info.plusminus[0] == '-'){ // trzeba jeszcze ustawic
                    printf("%s %s %s", node->info.value, node->info.currency, node->info.accountNumber);
                }
                node = node->pNext;
            }
            break;
        case 3:
            break;
    }
}

