#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "Funkcje.h"

        // Pliki Tekstowe //

void loadingFromFile(const char *nameOfEntryFile, PayNode **node) {
    FILE *entryFile = fopen(nameOfEntryFile, "r");
    if (entryFile) {
        char temporaryLine[con];
        while(fgets(temporaryLine, con, entryFile)){
            // sprawdzenie poprawności danych //
            int x = checkIfLineIsCorrect(temporaryLine);
            if(x == 1){
                continue;
            }
            // poprawne dane zostaja wczytywane do struktury //
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
void defaultProfileList(Prof** profNode, const char* nameOfFileWithDefaultProfiles){

    FILE *entryFile = fopen(nameOfFileWithDefaultProfiles, "r");
    if (entryFile) {
        char temporaryLine[con];
        while(fgets(temporaryLine, con, entryFile)){

            int x = checkIfLineIsCorrectProfile(temporaryLine);
            if(x == 1){
                continue;
            }
            PInfo temp = addingProfileFromLine(temporaryLine); // temporary struct

            addingDefaultProfiles(profNode, temp);
        }
        fclose(entryFile);
    }
    else{
        printf("couldn't open text file\n");
    }
}
void saveProfiles(Prof* profileList ,const char *nameOfFileWithDefaultProfiles){ // zapis dodanych profilow do pliku, z ktorego przy nastepnym uruchomieniu wczytają się te same profile

    FILE* saveProfilesFile = fopen(nameOfFileWithDefaultProfiles, "w"); // otwarcie pliku ktory juz istnieje -> nadpisanie
    if(saveProfilesFile){
        Prof* temp = profileList;
        if(temp == NULL){
            puts("There is no profiles to save");
            return;
        }
        while(temp != NULL){
            fprintf(saveProfilesFile, "%s %s\n", temp->info.profileName, temp->info.accountNumber);
            temp = temp->pNext;
        }
        fclose(saveProfilesFile);
    }
    else{
        puts("Problem with opening file for saving data.");
    }
}

        // Poprawność danych, zgodność z przyjętym formatem //

int checkIfLineIsCorrect(const char* temporaryLine){

    char testWord[con];
    //int testNumber;

    char tempLine[con];            // to tez moze byc problemem w normalnym programie
    strcpy(tempLine, temporaryLine); // kopia linii zawierajacej dane o płatności

    char* piece = strtok(tempLine, " "); // value +/-X.YZ..
    strcpy(testWord, piece);
    if(isspace(testWord[0])){
        puts("detected wrong line");
        return 1;
    }

    piece = strtok(NULL, " "); //currency EUR, PLN itd..
    strcpy(testWord, piece);
    if(check(piece)){   //jesli liczba, błąd
        puts("detected wrong line, currency format is not valid");
        return 1;
    }

    piece = strtok(NULL, " "); // acountnumber 1233211233211233215
    strcpy(testWord, piece);
    if(!check(piece) || ifContainsLetter(piece)){
        puts("detected wrong line, accountnumber is not valid");
        return 1;
    }

    piece = strtok(NULL, ":"); // year YYYY
    if(ifContainsLetter(piece)){
        puts("detected wrong line, year contain letter so its not valid");
        return 1;
    }
    //testNumber = convertToInt(piece);


    piece = strtok(NULL, ":"); // month MM
    if(ifContainsLetter(piece)){
        puts("detected wrong line, month contain letter so its not valid");
        return 1;
    }
    //testNumber = convertToInt(piece);

    piece = strtok(NULL, " "); // day DD
    if(ifContainsLetter(piece)){
        puts("detected wrong line, day contain letter so its not valid");
        return 1;
    }
    //testNumber = convertToInt(piece);

    piece = strtok(NULL, ":"); // hour HH
    if(ifContainsLetter(piece)){
        puts("detected wrong line, hour contain letter so its not valid");
        return 1;
    }
    //testNumber = convertToInt(piece);

    piece = strtok(NULL, ":"); // minute MM
    if(ifContainsLetter(piece)){
        puts("detected wrong line, minute contain letter so its not valid");
        return 1;
    }
    //testNumber = convertToInt(piece);

    piece = strtok(NULL, " "); // seconds SS
    if(ifContainsLetter(piece)){
        puts("detected wrong line, second contain letter so its not valid");
        return 1;
    }
    //testNumber = convertToInt(piece);

    piece = strtok(NULL, "\n"); // category
    if(check(piece)){   //jesli liczba, błąd
        puts("detected wrong line, category format is not valid");
        return 1;
    }
    strcpy(testWord, piece);

    return 0;
}

int checkIfLineIsCorrectProfile(const char* tempLine){ //sprawdzenie poprawnosci wprowadzonych danych (domyslna lista profilów)

    char line[con];
    char part[con];

    strcpy(line, tempLine);
    char* piece = strtok(line, " "); // name
    strcpy(part, piece);
    if(isspace(part[0])){
        puts("[Profile] detected wrong line");
        return 1;
    }
    piece = strtok(NULL ,"\n");
    strcpy(part, piece);
    if(!check(part) || ifContainsLetter(part)){
        puts("[Profile] detected wrong line, accountnumber is not valid");
        return 1;
    }

    return 0;
}

    // Lista Jednokierunkowa Płatności //

void addingPaymentToNode(PayNode **node, Info infAboutPayment){ // tworzenie node'a zawierajacego informacje o platnosci
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

void timeList(PayNode** node){ // print zgdonie z ramami czasowymi

    long long min = alot;
    int howManyNodes = countingList(*node);
    //printf("%d", howManyNodes);
    for(int i = howManyNodes; i>0 ; i--){
        PayNode* temp = *node;
        while(temp){
            if(temp->info.timeOfP.sortValue < min && temp->info.timeOfP.beforeOrAfter == false){
                min = temp->info.timeOfP.sortValue;
            }
            temp = temp->pNext;
        }
        //printf("%lld\n", min);
        PayNode* temp2 = *node;
        while(temp2){
            if(temp2->info.timeOfP.sortValue == min){
                temp2->info.timeOfP.beforeOrAfter = true;
                printWholeLine(temp2);
            }
            temp2 = temp2->pNext;
        }
        //printf("%lld\n", min);
        min = alot;
    }
    waiting();
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
    waiting();
}

void showByCategories(PayNode* node){
    //dostepne kategoire
    const char* categories[numberOfCategories] = {"BANK", "SUBSCRIPTION", "ELECTROMARKET", "CLOTHES"};

    //wypisywanie
    for(int i = 0; i<numberOfCategories; i++){
        printf("%s\n", categories[i]);
        PayNode* temp = node;
        if(!temp){
            puts("[empty]");
        }while(temp){
            if(!strcmp(temp->info.cat.category,categories[i])){
                printWholeLine(temp);
            }
            temp = temp->pNext;
        }
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

    // Lista Jednokierunkowa Profile //

void showProfiles(Prof* profNode){ // print nazwy profilow i przypisane do nich numery konta
    Prof* temp = profNode;
    if(temp == NULL){
        printf("Empty");
    }else{
        while(temp != NULL){
            printf("%s : %s\n",temp->info.profileName, temp->info.accountNumber );
            temp = temp->pNext;
        }
    }
    printf("\n");

}

void addProfileNode(Prof** profNode){
    Prof* tempNode = malloc(sizeof(Prof));
    tempNode->pNext = NULL;
    PInfo tempInfo = getProfileNameAndAccountNumber();
    tempNode->info = tempInfo;

    if(*profNode == NULL){ // jesli pierwszy jest null
        printf("firstNode\n");
        *profNode = tempNode;
    }
    else {                  // do ostatniego
        printf("newNode\n");
        Prof *temp = *profNode;
        while (temp->pNext != NULL) {
            temp = temp->pNext;
        }
        temp->pNext = tempNode;
    }
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
}

void addingDefaultProfiles(Prof** profNode, PInfo temp){

    Prof* tempNode = malloc(sizeof(Prof));
    tempNode->pNext = NULL;
    tempNode->info = temp;

    if(*profNode == NULL){
        printf("firstDefaultProfileNode\n");
        *profNode = tempNode;
    }
    else {
        printf("newDefaultProfileNode\n");
        Prof *temp = *profNode;
        while (temp->pNext != NULL) {
            temp = temp->pNext;
        }
        temp->pNext = tempNode;
    }

}

void deleteProfile(Prof** node){

    showProfiles(*node);

    if(*node == NULL){
        //puts("There is no Profiles!"); // w show profiles wyswietli sie to samo
        return;
    }

    char nameOfProfileToDelete[con];
    printf("Type profile name that you want to delete >");
    clearBuffer();
    scanf("%s", nameOfProfileToDelete);

    if(!strcmp((*node)->info.profileName,nameOfProfileToDelete)){
        Prof* temp = *node;
        (*node) = (*node)->pNext;
        free(temp);
        printf("Deleted profile: %s successfully!", nameOfProfileToDelete);
        return;
    }
    for(Prof* copy = *node; copy->pNext != NULL; copy = copy->pNext){
        if(!strcmp(copy->pNext->info.profileName, nameOfProfileToDelete)){
            Prof* temp = copy->pNext;
            copy->pNext = copy->pNext->pNext;
            free(temp);
            return;
        }
    }
    puts("There is no profile with such name!");
}

        // Funkcje zwracające struktury //

Info addingToStruct(char * temporaryLine) { // Wyłuskanie informacji z pliku tekstowego

    Info temp;
    char *piece = strtok(temporaryLine, " "); // value
    strcpy(temp.value, piece);
    // printf("[%s]", piece);
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

    //pseudo wyjatkowa liczba dla kazdego node'a bazujaca na czasie w ktorym zostala wykonana platnosc
    long long valueSetFromTime = getTimeValue(temp);
    //printf("%lld", valueSetFromTime); // sprawdzenie
    temp.timeOfP.sortValue = valueSetFromTime;

    //aby latwiej wyswitlic w odpowiedniej kolejnosci
    temp.timeOfP.beforeOrAfter = false;

    //income or outcome
    if (temp.value[0] == '+') {
        strcpy(temp.plusminus, "+");
    } else if (temp.value[0] == '-') {
        strcpy(temp.plusminus, "-");
    }

    return temp;
}

PInfo addingProfileFromLine(const char* temporaryLine){
    PInfo temp;
    //char* line = temporaryLine; // byl warning
    char line[con];
    strcpy(line, temporaryLine);
    char* piece = strtok(line, " "); // name
    strcpy(temp.profileName, piece);
    piece = strtok(NULL ,"\n");
    strcpy(temp.accountNumber, piece);

    return temp;
}

PInfo getProfileNameAndAccountNumber(){ // dodawanie nowego profilu (nazwa + numer konta)
    PInfo temporaryStruct;
    char temp[con];
    char yesOrNo[con];
    bool continueLoopOne = true;
    bool continueLoopTwo = true;
    do {
        printf("Profile Name >");
        clearBuffer();
        scanf("%s", temp);
        printf("New profile name: [%s] _is it ok?_\n", temp); // potwierdzenia
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
        printf("AccountNumber: [%s] _is it ok?_\n", temp); // potwierdzenia
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

        // Funkcje Pomocnicze //

int check(const char *decision) { // sprawdza czy podany string jest liczba
    if (isdigit(decision[0])) {
        int r = atoi(decision);
        //printf("in funct %d\n", r); // sprawdzenie!
        return r; // jest zwraca to samo w formie liczy calkowitej
    } else return 0; // nie jest, domyslnie zwraca zero
}

int convertToInt(const char* chToInt){
    int t = atoi(chToInt);
    return t;
} // convrting char to integer

void clearBuffer(){
    char temp;
    while((temp = getchar()) != '\n' && temp != EOF) {/*run*/}
}

void waiting(){ // czeka na reakcje uzytkownika
    clearBuffer();
    puts("Press enter to continue");
    getchar(); // to temporary pause
}

long long getTimeValue(Info inf){
    long long year = inf.timeOfP.year * 10000000000;
    long long month = inf.timeOfP.month * 100000000;
    long long day = inf.timeOfP.day * 1000000;
    long long hour = inf.timeOfP.hour * 10000;
    long long minute = inf.timeOfP.minute * 100;
    long long  second = inf.timeOfP.second;

    // now add together to get one number and return it
    return year + month + day + hour + minute + second;
}

int countingList(PayNode* node){
    PayNode* temp = node;
    int counter = 0;
    if(temp == NULL){
        printf("empty");
        return counter;
    }
    while(temp){
        counter++;
        temp = temp->pNext;
    }
    return counter;
}

int ifContainsLetter(const char* word){
    int counter = 0;
    while(word[counter] != '\0'){
        if(isalpha(word[counter])){ // jesli znak bedzie litera, true
            return 1;
        }
        counter++;
    }
    return 0;
}

        // Zwalnianie Pamięci //

void exitDeleteProfiles(Prof** profNode){
    Prof* copy = *profNode;
    while(copy){
        Prof* temp = copy;
        copy = copy->pNext;
        free(temp);
        puts("deleted profile");
    }
    *profNode = NULL;
}

void exitDeleteNodes(PayNode** node) {
    PayNode *copy = *node;
    while (copy) {
        PayNode *temp = copy;
        copy = copy->pNext;
        free(temp);
        puts("deleted node");
    }
    *node = NULL;
}