
#ifndef PROSTAKSIEGOWOSCDOMOWAC_FUNKCJE_H
#define PROSTAKSIEGOWOSCDOMOWAC_FUNKCJE_H

struct Time{
    int minute;
    int hour;
    int day;
    int month;
    int year;
};
struct Category{
    char* category;
    char* product;
};
struct HowMuch{
    char* value;
    char* currency;
};
typedef struct Info {
    char *accountNumber;
    struct Time TimeOfPaymanet;
    struct Category CategoryOfProduct;
    struct HowMuch HowMuchMoney;
}InfoToPayNode;

typedef struct Payment{
    struct Payment *pNext;
    struct Payment *pPrev;
    struct Info InfoAboutPayment;
}PayNode;

void printingMenu();
int check(const char *);
void loadingFromFile(const char*, PayNode**);
void addingPaymentToNode(PayNode**,InfoToPayNode);
void readingNodes(PayNode* pHead);

#endif //PROSTAKSIEGOWOSCDOMOWAC_FUNKCJE_H
