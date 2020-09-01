
#ifndef PROSTAKSIEGOWOSCDOMOWAC_FUNKCJE_H
#define PROSTAKSIEGOWOSCDOMOWAC_FUNKCJE_H
#define con 100

/**typ bool w c*/
typedef int bool;
#define true 1
#define false 0

/** struktura zawierajaca informacje na temat czasu płatności */
struct Time{
    int second;
    int minute;
    int hour;
    int day;
    int month;
    int year;
    long long sortValue;
    bool beforeOrAfter; // na poczatku false, potrzebne do wyswietlenia w odpowiedniej kolejnosci
};

/** struktura zawierajaca kategorie platnosci */
struct Category{
    char category[con];
};

/** struktura zawierajaca informacje na temat dokonanej platnosci */
typedef struct PaymentInfo{
    char plusminus[2];
    char accountNumber[con];
    char value[con];
    char currency[con];
    struct Category cat;
    struct Time timeOfP;
}Info;

/** node zawierajacy płatność */
typedef struct Payment{
    struct Payment* pNext; ///< następny node
    struct PaymentInfo info; ///< informacje na temat dokonanej platnosci
}PayNode;

/** struktura zawierajace informacje na temat profilu */
typedef struct ProfileInfo{
    char accountNumber[con];
    char profileName[con];
}PInfo;

/** node zawierajacy profil */
typedef struct Profile{
    struct Profile* pNext; ///< następny node
    struct ProfileInfo info; ///< informacje na temat profilu
}Prof;


void printingMenu();
int check(const char *);
void loadingFromFile(const char*, PayNode**);
void addingPaymentToNode(PayNode**, Info);
void readingNodes(PayNode*);
int convertToInt(const char* chToInt);
Info addingToStruct(char * temporaryLinep);
void showIncomeOutcome(PayNode* node, int option);
void printWholeLine(PayNode* node);
void printingMenu(PayNode** node,Prof** profNode);
void timeList(PayNode** node);
void expensesSortedByMemberList(PayNode* node, Prof* profNode);
void clearBuffer();
void programExecution(PayNode** node, Prof** profileList);
void waiting();
void profilesMenu(Prof** profNode);
void showProfiles(Prof* profNode);
void addProfileNode(Prof** profNode);
PInfo getProfileNameAndAccountNumber();
void renameProfile(Prof** profNode);
void showByCategories(PayNode* node);
long long getTimeValue(Info inf);
int countingList(PayNode* node);
void deleteProfile(Prof** node);
void exitDeleteProfiles(Prof** profNode);
void exitDeleteNodes(PayNode** node);

#endif //PROSTAKSIEGOWOSCDOMOWAC_FUNKCJE_H
