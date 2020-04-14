
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
struct Payment{
    char* accountNumber;
    struct Payment *pNext;
    struct Payment *pPrev;
    struct Time TimeOfPaymanet;
    struct Category CategoryOfProduct;
}PayNode;

void printingMenu();

int check(const char *);

#endif //PROSTAKSIEGOWOSCDOMOWAC_FUNKCJE_H
