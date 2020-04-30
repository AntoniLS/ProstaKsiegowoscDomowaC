
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
typedef struct Payment{
    char* accountNumber;
    struct Payment *pNext;
    struct Payment *pPrev;
    struct Time TimeOfPaymanet;
    struct Category CategoryOfProduct;
    struct HowMuch HowMuchMoney;
}PayNode;

void printingMenu();
int check(const char *);
void loadingFromFile(const char*, PayNode**);
void addingPaymentToNode(PayNode**,PayNode);

#endif //PROSTAKSIEGOWOSCDOMOWAC_FUNKCJE_H
