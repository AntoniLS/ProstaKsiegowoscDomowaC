
#ifndef PROSTAKSIEGOWOSCDOMOWAC_FUNKCJE_H
#define PROSTAKSIEGOWOSCDOMOWAC_FUNKCJE_H
#define con 100

struct Time{
    int second;
    int minute;
    int hour;
    int day;
    int month;
    int year;
};
struct Category{
    char category[con];
};
typedef struct PaymentInfo{
    char plusminus[2];
    char accountNumber[con];
    char value[con];
    char currency[con];
    struct Category cat;
    struct Time timeOfP;
}Info;

typedef struct Payment{
    struct Payment* pNext;
    struct PaymentInfo info;
}PayNode;

typedef struct Profile{
    char accountNumber[con];
    char profileName[con];
    struct Profile* pNext;
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
void timeList(PayNode* node);
void familyMemberList(PayNode* node);
void clearBuffer();
void programExecution(PayNode** node);
void waiting();
void optionsMenu(Prof** profNode);
void showProfiles(Prof* profNode);
void addProfileNode(Prof** profNode);

#endif //PROSTAKSIEGOWOSCDOMOWAC_FUNKCJE_H
