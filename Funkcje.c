#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

#include "Funkcje.h"

void programExecution(PayNode** node, Prof** profileList){ // <----- Główna część programu

    printingMenu(node, profileList); // przekazanie parametrow do funkcji odpowiedzialnej za interakcje z programem

    //TODO czyszczenie pamieci
}

void addProfileNode(Prof** profNode){
    Prof* tempNode = malloc(sizeof(Prof));
    tempNode->pNext = NULL;
    PInfo tempInfo = getProfileNameAndAccountNumber();
    tempNode->info = tempInfo;
//    strcpy(tempNode->info.profileName, profileNewName());
//    printf("%s\n", tempNode->info.profileName); // sprawdzenie
//    char tempName[con];
//    strcpy(tempName, tempNode->info.profileName);
//    printf("%s\n", tempName); // sprawdzenie
//    strcpy(tempNode->info.accountNumber, profileNewAccountNumber(tempName));
//    printf("%s\n", tempNode->info.accountNumber);

    if(*profNode == NULL){
        printf("firstNode\n");
        *profNode = tempNode;
    }
    else {
        printf("newNode\n");
        Prof *temp = *profNode;
        while (temp->pNext != NULL) {
            temp = temp->pNext;
        }
        temp->pNext = tempNode;
    }
}
PInfo getProfileNameAndAccountNumber(){
    PInfo temporaryStruct;
    char temp[con];
    char yesOrNo[con];
    bool continueLoopOne = true;
    bool continueLoopTwo = true;
    do {
        printf("Profile Name >");
        clearBuffer();
        scanf("%s", temp);
        printf("New profile name: [%s] _is it ok?_\n", temp);
        puts("[1] Yes");
        puts("[2] No"); // tak naprawde cala reszta powoduje ponowne wykonanie

        clearBuffer();
        scanf("%s", yesOrNo);
        int ConvertedYesOrNo = check(yesOrNo);
        if(ConvertedYesOrNo == 1) {
            strcpy(temporaryStruct.profileName, temp);
            continueLoopOne = false;
        }
    }while(continueLoopOne);
    do {
        printf("Account Number assigned to profile %s >", temporaryStruct.profileName);
        clearBuffer();
        scanf("%s", temp);
        printf("AccountNumber: [%s] _is it ok?_\n", temp);
        puts("[1] Yes");
        puts("[2] No"); // tak naprawde cala reszta powoduje ponowne wykonanie

        clearBuffer();
        scanf("%s", yesOrNo);
        int ConvertedYesOrNo = check(yesOrNo);
        if(ConvertedYesOrNo == 1) {
            strcpy(temporaryStruct.accountNumber, temp);
            continueLoopTwo = false;
        }
    }while(continueLoopTwo);
    return temporaryStruct;
}

void renameProfile(Prof** profNode){
    if(*profNode == NULL){ // jesli nie ma zadnych profilow konczymy
        puts("There are no profiles, to rename");
        return;
    }
    showProfiles(*profNode);
    char tempName[con];

    Prof* temp = *profNode;
    printf("Type profile name that you want to rename >");
    clearBuffer();
    scanf("%s", tempName);
    while(temp != NULL){
        if(!strcmp(tempName, temp->info.profileName)){
            char tempNewName[con];
            char yesOrNo[con];
            bool continueLoop = true;
            do {
                printf("Changing %s to >", tempName);
                clearBuffer();
                scanf("%s", tempNewName);
                printf("New profile name: [%s] _is it ok?_\n", tempNewName);
                puts("[1] Yes");
                puts("[2] No"); // tak naprawde cala reszta powoduje ponowne wykonanie

                clearBuffer();
                scanf("%s", yesOrNo);
                int ConvertedYesOrNo = check(yesOrNo);
                if(ConvertedYesOrNo == 1) {
                    strcpy(temp->info.profileName, tempNewName);
                    continueLoop = false;
                    return;
                }
            }while(continueLoop);
        }
        temp = temp->pNext;
    }
    printf("There is no such profile");
    //TODO Ewentualne dodatki typu peta do czasu az zmienimy, chyba ze nie istnieje to return
}

void showProfiles(Prof* profNode){ // print profile names and assigned to them accountnumbers
    Prof* temp = profNode;
    if(temp == NULL){
        printf("Empty");
    }else{
        while(temp != NULL){
            printf("%s : %s\n",temp->info.profileName, temp->info.accountNumber );
            temp = temp->pNext;
        }
    }
}

void timeList(PayNode* node){ // drukowanie zgdonie z ramami czasowymi

}
void expensesSortedByMemberList(PayNode* node, Prof* profNode){

    Prof* temp = profNode;
    if(profNode == NULL){ // jesli nie ma profilow
        puts("Empty profile list");
    }
    else{

        while (temp != NULL) { // idziemy po wszystkich profilach
            printf("Name: %s | Account number: %s\n", temp->info.profileName, temp->info.accountNumber);
            PayNode *tempPayments = node;
            if (tempPayments == NULL) { // jesli nie ma zadnych platnosci
                puts("Empty");
            }
            else{
                while (tempPayments != NULL) { // jesli sa platnosci idziemy po wszystkich
                    if (!strcmp(temp->info.accountNumber, tempPayments->info.accountNumber)) { //jesli numer konta profilu jest zgodny z numerem konta zawargego w platnosci
                        printWholeLine(tempPayments); // pokazujmy platnosc przypisana do profilu
                    }
                    tempPayments = tempPayments->pNext;
                }
            }
            temp = temp->pNext;
        }
    }
}

int check(const char *decision) { // sprawdza czy podany string jest liczba
    if (isdigit(decision[0])) {
        int r = atoi(decision);
        //printf("in funct %d\n", r); // sprawdzenie!
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
Info addingToStruct(char * temporaryLine){ // Wyłuskanie informacji z pliku tekstowego
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

    //TODO jak ominac ewentualne bledy na poczatku ktore mogly by zastapic +/-
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
    waiting();
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
            waiting();
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
            waiting();
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

void waiting(){ // czeka na reakcje uzytkownika
    clearBuffer();
    puts("Press enter to continue");
    getchar(); // to temporary pause
}






/////////////////////////////////////// NA RAZIE NIEPOTRZEBNE ////////////////////////////////////////////////////

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
