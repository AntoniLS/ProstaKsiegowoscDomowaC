#include <stdio.h>
#include <string.h>
#include "Funkcje.h"
#include "Funkcje.c"

int main(int argc, char* argv[]){
    /// pliki wejsciowe / wyjsciowe
    char* nameOfEntryFile;

    /// sprawdzenie czy argumenty zostaly wprowadzone poprawnie (plik wejsciowy przez -i x)
    for(int counter = 0; counter < argc ; counter++){
        char* param = argv[counter];
        int bool = strcmp(param,"-i"); // zwraca 0 w przypadku zgodności
        if(bool == 0){
            printf("correct input file\n");
            nameOfEntryFile = argv[counter + 1];
            }
        }
    printf("%s\n", nameOfEntryFile); // spradzenie

    /// wlasciwy program... wczytywanie danych... opcje...
    PayNode *pHead = NULL;
    loadingFromFile(nameOfEntryFile, &pHead);
    readingNodes(pHead);
    /// czyszczenie pamieci
        //TODO
    return 0;
}


