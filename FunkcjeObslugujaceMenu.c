#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

#include "Funkcje.h"

void printingMenu(PayNode** node, Prof** profNode ) {
    bool repeatMenu = true;
    do {
        char decision[10];
        int decisionInsideSwitch;
        //TODO paski procentowe
        puts("[1] Show whole bill from all forwarded transactions"); //caly rachunek
        puts("[2] Show income"); // pokaz dochod z wszystkich transakcji
        puts("[3] Show outcome"); // pokaz wydatki z wszystkich transakcji
        puts("[4] Show spending through time");
        puts("[5] Show all spending by specific family member");
        puts("[6] Show sorted by categories");
        puts("[7] PROFILES");
        puts("[8] Quit");
        printf("Choose one of above [first digit is valid] >");
        scanf("%s", decision);
        //printf("%s %c", decision, decision[0]);// check
        printf("\n");
        int ifCorrect = check(decision);
        //printf("in main %d\n", ifCorrect); // sprawdzenie! ktora liczba zostala przyjeta jako  wybór

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
                timeList(*node /*,*profNode*/); //?
                break;
            case 5: //Show all spending by specific family member [after creating profiles]
                expensesSortedByMemberList(*node, *profNode);
                break;
            case 6: //Show sorted by categories
                //TODO zgodnie z kategiariami
                break;
            case 7: // PROFILES
                //TODO OPCJE dodawanie profilow / usuwanie profilow
                profilesMenu(profNode);
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
}

void profilesMenu(Prof** profNode){
    char decision[10];
    puts("[1] Show Profiles");
    puts("[2] Add Profile");
    puts("[3] Rename Profile");
    puts("[4] Delete Profile");
    scanf("%s", decision);
    int ifCorrect = check(decision);

    switch(ifCorrect){
        case 1: //Show Profiles
            showProfiles(*profNode);
//            printf("%s",(*profNode)->info.profileName); // SPRAWDZENIE
//            printf("%s",(*profNode)->info.accountNumber);
//            printf("%s",(*profNode)->pNext->info.profileName);
//            printf("%s",(*profNode)->pNext->info.accountNumber);
            break;
        case 2: //Add Profile
            addProfileNode(profNode);
            break;
        case 3: //Rename Profile
        //TODO
            renameProfile(profNode);
            break;
        case 4: //Delete Profile
        //TODO
            //deleteProfile(ProfNode);
            break;
        default:
            break;
    }
}