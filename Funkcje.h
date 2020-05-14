
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
    char product[con];
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

void printingMenu();
int check(const char *);
void loadingFromFile(const char*, PayNode**);
void addingPaymentToNode(PayNode**, Info);
void readingNodes(PayNode*);
void sortedby(PayNode*, int);
int convertToInt(const char* chToInt);

#endif //PROSTAKSIEGOWOSCDOMOWAC_FUNKCJE_H
