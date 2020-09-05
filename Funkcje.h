
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

/**
 * Funkcja wyświetlająca menu z wszystkimi opcjami do wyboru
 */
void printingMenu(PayNode** node,Prof** profNode);
/**
 * Funkcja sprawdzająca czy podany łańcuch jest liczbą
 * */
int check(const char *);
/**
 * Funkcja ładowanie danych z pliku do struktury
 * */
void loadingFromFile(const char*, PayNode**);
/**
 * Funkcja dodająca węzeł oraz przypisujaca mu strukturę zwierającą informacje o płatności
 * */
void addingPaymentToNode(PayNode**, Info x);
/**
 * Funkcja iterująca przez listę
 * */
void readingNodes(PayNode*);
/**
 * Funkcja konwertująca łańcuch na liczbę
 * */
int convertToInt(const char* chToInt);
/**
 * Funkcja odpowiadająca za wyłuskanie informacji z linii i zapis ich do struktury
 * */
Info addingToStruct(char * temporaryLine);
/**
 * Funkcja wyświetlająca przychód lub straty, w zależności od wybranej opcji
 * */
void showIncomeOutcome(PayNode* node, int option);
/**
 * Funkcja wyświetlająca płatność ze wszystkimi jej szczegółami
 * */
void printWholeLine(PayNode* node);
/**
 * Funkcja wyświetla płatności zgdonie z ramami czasowymi
 **/
void timeList(PayNode** node);
/**
 * Funkcja wyświetla wydatki poszczególych (wczesniej dodanych) profilow
 * */
void expensesSortedByMemberList(PayNode* node, Prof* profNode);
/**
 * Czyszczenie bufora
 * */
void clearBuffer();
/**
 * Uporządkowanie procesu wykonywania programu (początek głównej części programu)
 * */
void programExecution(PayNode** node, Prof** profileList);
/**
 * Funkcja oczekuje na input użytkowanika w tym celu tymczasowo pauzuje program
 * */
void waiting();
/**
 * Funkcja wyświetlająca menu (Profilów) z wszystkimi opcjami do wyboru
 * */
void profilesMenu(Prof** profNode);
/**
 * Funkcja wyświetlająca wszystkie utworzone wczesniej profile
 * */
void showProfiles(Prof* profNode);
/**
 * Funkcja umożliwiająca dodanie nowego węzła profilu i powiazania go z numerem konta
 * */
void addProfileNode(Prof** profNode);
/**
 * Składowa funkcji "addProfileNode" pozwala na interakcje z użytkownikiem przy dodawaniu profilu
 * */
PInfo getProfileNameAndAccountNumber();
/**
 * Funkcja umożliwiająca zmianę nazwy profilu
 * */
void renameProfile(Prof** profNode);
/**
 * Fukcja wyświetlająca liste płatnośći zgdonie z możliwymi kategoriami
 * */
void showByCategories(PayNode* node);
/**
 * Funkcja zwracajaca 'unikalną' liczbę ustalaną na podstawie czasu w którym została dokonana płatność
 * */
long long getTimeValue(Info inf);
/**
 * Funkcja zwracająca ilość dokonanych płatności
 * */
int countingList(PayNode* node);
/**
 * Funkcja umożliwiająca usunięcie profilu
 * */
void deleteProfile(Prof** node);
/**
 * Zwalnianie zaalokowanej pamięci (Lista profilów)
 * */
void exitDeleteProfiles(Prof** profNode);
/**
 * Zwalnianie zaalokowanej pamięci (Lista płatności)
 * */
void exitDeleteNodes(PayNode** node);

void defaulProfileList(Prof** profNode, const char* defaultProfileInputFile);
PInfo addingProfileFromLine(const char* temporaryLine);
void addingDefaultProfiles(Prof**, PInfo x);

#endif //PROSTAKSIEGOWOSCDOMOWAC_FUNKCJE_H
