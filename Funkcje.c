#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <stdbool.h>

#include "Funkcje.h"

void printingMenu(PayNode** node) {
    bool repeatMenu = true;
    do {
        char decision[10];
        int decisionInsideSwitch;
        //TODO paski procentowe
        puts("[1] Show whole bill from all forwarded transactions");
        puts("[2] Show income");
        puts("[3] Show outcome");
        puts("[4] Show spending through time");
        puts("[5] Show all spending by specific family member");
        puts("[6] Show sorted by categories");
        puts("[7] OPTIONS");
        puts("[8] Quit");
        printf("Choose one of above [first digit is valid] >");
        scanf("%s", decision);
        printf("%s %c", decision, decision[0]);// check
        printf("\n");
        int ifCorrect = check(decision);
        printf("in main %d", ifCorrect); // sprawdzenie ktora liczba zostala przyjeta jako  wybór

        switch (ifCorrect) {
            case 1: //Show whole bill from all forwarded transactions
                readingNodes(*node);
                break;
            case 2: //Show income
                decisionInsideSwitch = 1; // w funkcji oznacza dochód
                showIncomeOutcome(*node, decisionInsideSwitch);
                break;
            case 3: //Show outcome
                decisionInsideSwitch = 2; // w funkcji oznacza pieniądze wydane
                showIncomeOutcome(*node, decisionInsideSwitch);
                break;
            case 4: //Show spending through time
                timeList(*node); //?
                break;
            case 5: //Show all spending by specific family member
                familyMemberList(*node); //?
                break;
            case 6: //Show sorted by categories
                //TODO zgodnie z kategiariami
                break;
            case 7: // OPTIONS
                //TODO OPCJE dodawanie profilow / usuwanie profilow
                break;
            case 8:
                repeatMenu = false;
                break;
            default: // gdy check zwroci 0
                printf("Incorrect decision\n");
                sleep(3);
                //printf("\033c"); // wipe terminal //doesnt work at all
                system("clear");
                break;
        }
        printf("\n");
    }while(repeatMenu);
};

void timeList(PayNode* node){ // drukowanie zgdonie z ramami czasowymi

}
void familyMemberList(PayNode* node){

}

int check(const char *decision) { // sprawdza czy podany string jest liczba
    if (isdigit(decision[0])) {
        int r = atoi(decision);
        printf("in funct %d\n", r);
        return r; // jest zwraca to samo w formie liczy calkowitej
    } else return 0; // nie jest, domyslnie zwraca zero
}
void clearBuffer(){
    char temp;
    while((temp = getchar()) != '\n' && temp != EOF) {/*run*/}
}

void loadingFromFile(const char *nameOfEntryFile, PayNode **node) {
    FILE *entryFile = fopen(nameOfEntryFile, "r");
    if (entryFile) {
        char temporaryLine[con];
        while(fgets(temporaryLine, con, entryFile)){

            Info temp = addingToStruct(temporaryLine); // temporary struct

            //printf("%s %s %s %d\n", temp.value,temp.currency,temp.accountNumber, temp.timeOfP.year ); //sprawdzenie poprawnosci wczywtywania z pliku

            addingPaymentToNode(node, temp);
        }
        fclose(entryFile);
    }
    else{
        printf("couldn't open text file\n");
    }
}
Info addingToStruct(char * temporaryLine){
    char* tempLine = temporaryLine;
    Info temp;
    char* piece = strtok(tempLine, " "); // value
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

    //income or outcome
    if(temp.value[0] == '+'){
        strcpy(temp.plusminus, "+");
    }
    else if(temp.value[0] == '-'){
        strcpy(temp.plusminus, "-");
    }

    return temp;
}

int convertToInt(const char* chToInt){
    int t = atoi(chToInt);
    return t;
} // convrting char to integer

void addingPaymentToNode(PayNode **node, Info infAboutPayment){ // creating node that will contain payment info
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
    if(temp == NULL){
        printf("empty");
    }
    while(temp){
        printWholeLine(temp);
        temp = temp->pNext;
    }
}

void showIncomeOutcome(PayNode* node, int option){
    switch(option){
        case 1:
            //outcome
            if(node->pNext == NULL){
                printf("empty");
            }
            while(node){
                if(memchr(node->info.plusminus, '+', sizeof(node->info.plusminus))){ // jesli w tablicy znajduje sie char ''
                    printWholeLine(node);
                }
                node = node->pNext;
            }
            clearBuffer();
            puts("Press enter to continue");
            getchar(); // to temporary pause
            break;
        case 2:
            //income
            if(node->pNext == NULL){
                printf("empty");
            }
            while(node){
                if(memchr(node->info.plusminus, '-', sizeof(node->info.plusminus))){ // jesli w tablicy znajduje sie char ''
                    printWholeLine(node);
                }
                node = node->pNext;
            }
            break;
        default:
            printf("nothing was chosen, (Error)");
            break;
    }
}

void printWholeLine(PayNode* node){ // wyswietla wszystkie dane na temat transakcji
   printf("%s ",node->info.value);
   printf("%s ",node->info.currency);
   printf("%s ",node->info.accountNumber);
   printf("%d:%02d:%02d ",node->info.timeOfP.year,node->info.timeOfP.month,node->info.timeOfP.day); // dane odpowiednio sformatowane
   printf("%02d:%02d:%02d ", node->info.timeOfP.hour, node->info.timeOfP.minute, node->info.timeOfP.second);
   printf("%s \n", node->info.cat.category);
}

void  conditionalReading(PayNode* node, char pm){ // ???
    if(node->pNext == NULL){
        printf("empty");
    }
    while(node){
        if(node->info.plusminus[0] == pm){ // trzeba jeszcze ustawic
            /* printf("%s %s %s", node->info.value, node->info.currency, node->info.accountNumber);*/
        }
        node = node->pNext;
    }
}