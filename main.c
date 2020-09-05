#include <stdio.h>
#include <string.h>

#include "FunkcjeObslugujaceMenu.c"
#include "Funkcje.h"
#include "Funkcje.c"

int main(int argc, char* argv[]){
    ///////////// pliki wejsciowe / wyjsciowe //////////////
    char* nameOfEntryFile;
    char* nameOfFileWithDefaultProfiles;
    ///////// sprawdzenie czy argumenty zostaly wprowadzone poprawnie (plik wejsciowy przez -i x) x to nazwa pliku///////////////
    for(int counter = 0; counter < argc ; counter++){
        char* param = argv[counter];
        if(!strcmp(param,"-i")){
            printf("correct input file\n");
            nameOfEntryFile = argv[counter + 1];
            }
        if(!strcmp(param,"-idp")){
            printf("correct default profile input file\n");
            nameOfFileWithDefaultProfiles = argv[counter + 1];
            }
        }
    // printf("%s\n", nameOfEntryFile); // spradzenie

    //////////////// wlasciwy program... wczytywanie danych... menu... //////////////

    PayNode *pHead = NULL;// poczatek listy rachunkow
    Prof *profileList = NULL; // poczatek listy profilow
    loadingFromFile(nameOfEntryFile, &pHead); // wczytywanie danych poczatkowych z pliku
    defaultProfileList(&profileList, nameOfFileWithDefaultProfiles); // wczytywanie domyślnych profilow z pliku
    //readingNodes(pHead); // sprawdzenie
    //showIncomeOutcome(pHead, 2); // gdy jest aktywne przy uruchomieniu z pustym buforem (chyba wywoluje blad)? //TODO
    programExecution(&pHead, &profileList); // wywolanie wlasciwego programu, przekazanie listy rachunkow i profilow

    /////////// czyszczenie pamieci //////////////
    exitDeleteProfiles(&profileList);
    exitDeleteNodes(&pHead);
    return 0;
}


