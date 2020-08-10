#include <stdio.h>
#include <string.h>
#include "Funkcje.h"
#include "Funkcje.c"

int main(int argc, char* argv[]){
    // pliki wejsciowe / wyjsciowe //////////////
    char* nameOfEntryFile;

    // sprawdzenie czy argumenty zostaly wprowadzone poprawnie (plik wejsciowy przez -i x) ///////////////
    for(int counter = 0; counter < argc ; counter++){
        char* param = argv[counter];
        int boolean = strcmp(param,"-i"); // zwraca 0 w przypadku zgodności
        if(boolean == 0){
            printf("correct input file\n");
            nameOfEntryFile = argv[counter + 1];
            }
        }
   // printf("%s\n", nameOfEntryFile); // spradzenie

    // wlasciwy program... wczytywanie danych... opcje... //////////////

    PayNode *pHead = NULL;// poczatek listy rachunkow
    Prof *profileList = NULL; // poczatek listy profilow
    loadingFromFile(nameOfEntryFile, &pHead);
    readingNodes(pHead);
    printf("========\n");
   // showIncomeOutcome(pHead, 2); // gdy jest aktywne przy uruchomieniu z pustym buforem (chyba wywoluje blad)?
    programExecution(&pHead, &profileList);

    // czyszczenie pamieci /////////////
        //TODO
    return 0;
}


