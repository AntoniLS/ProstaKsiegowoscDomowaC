#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

#include "Funkcje.h"

void printingMenu(){
    char decission[10];
    printf("[1] Show whole bill from all forwarded transactions\n");
    printf("[2] Show daily spending\n");
    printf("[3] Show weekly spending\n");
    printf("[4] Show yearly spending\n");
    printf("[5] Show all spending by specific family member\n");
    printf("Choose one of above [first digit is valid] >");
    scanf("%s",decission);
    printf("%s %c",decission, decission[0]);
    printf("\n");
    int ifCorrect = check(decission);
    printf("in main %d", ifCorrect);
    switch(ifCorrect){
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

int check(const char* decission){
    if(isdigit(decission[0])){
        int r = atoi(decission);
        printf("in funct %d\n", r);
        return r;
    }
    else return 0;
}
