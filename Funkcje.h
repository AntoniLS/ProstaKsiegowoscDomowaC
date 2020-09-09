
#ifndef PROSTAKSIEGOWOSCDOMOWAC_FUNKCJE_H
#define PROSTAKSIEGOWOSCDOMOWAC_FUNKCJE_H
#define con 100
#define numberOfCategories 5
#define alot 30000000000000

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

        // Funkcje obsługujące Menu  //
/**
 * Uporządkowanie procesu wykonywania programu (początek głównej części programu)
 * */
void programExecution(PayNode** node, Prof** profileList);
/**
 * Funkcja wyświetlająca menu z wszystkimi opcjami do wyboru
 */
void printingMenu(PayNode** node,Prof** profNode);
/**
 * Funkcja wyświetlająca menu (Profilów) z wszystkimi opcjami do wyboru
 * */
void profilesMenu(Prof** profNode);


        // Pliki Tekstowe //
/**
 * Funkcja ładowanie danych z pliku do struktury
 * */
void loadingFromFile(const char*, PayNode**);
/**
 * Funkcja obsługująca plik zawierający domyślną listę profilów [nazwa | numer konta]
 * */
void defaultProfileList(Prof** profNode, const char* defaultProfileInputFile);
/**
 * Zapisywanie domyślnych + utworzonych w trakcie dzialania programu profilów do pliku
 * */
void saveProfiles(Prof* profileList ,const char *nameOfFileWithDefaultProfiles);


        // Poprawność danych, zgodność z przyjętym formatem //
/**
 * Sprawdzenie poprwaności danych z pobranej linii, (czy format jest odpowiedni) jeśli nie, pomiń
 * */
int checkIfLineIsCorrect(const char* x);
/**
 * Sprawdzenie poprawności danych z pobranej linii, (czy format jest odpowiedni [nazwaProfilu | numer konta]) jeśli nie, pomiń
 * */
int checkIfLineIsCorrectProfile(const char* line);


        // Lista Jednokierunkowa Płatności //
/**
 * Funkcja dodająca węzeł oraz przypisujaca mu strukturę zwierającą informacje o płatności
 * */
void addingPaymentToNode(PayNode**, Info x);
/**
 * Funkcja iterująca przez listę
 * */
void readingNodes(PayNode*);
/**
 * Funkcja wyświetlająca przychód lub straty, w zależności od wybranej opcji
 * */
void showIncomeOutcome(PayNode* node, int option);
/**
 * Funkcja wyświetla płatności zgdonie z ramami czasowymi
 **/
void timeList(PayNode** node);
/**
 * Funkcja wyświetla wydatki poszczególych (wczesniej dodanych) profilow
 * */
void expensesSortedByMemberList(PayNode* node, Prof* profNode);
/**
 * Fukcja wyświetlająca liste płatnośći zgdonie z możliwymi kategoriami
 * */
void showByCategories(PayNode* node);
/**
 * Funkcja wyświetlająca płatność ze wszystkimi jej szczegółami
 * */
void printWholeLine(PayNode* node);


        // Lista Jednokierunkowa Profile //
/**
 * Funkcja wyświetlająca wszystkie utworzone wczesniej profile
 * */
void showProfiles(Prof* profNode);
/**
 * Funkcja umożliwiająca dodanie nowego węzła profilu i powiazania go z numerem konta
 * */
void addProfileNode(Prof** profNode);
/**
 * Funkcja umożliwiająca zmianę nazwy profilu
 * */
void renameProfile(Prof** profNode);
/**
 * Dodawanie domyślnego profilu do listy
 * */
void addingDefaultProfiles(Prof**, PInfo x);
/**
 * Funkcja umożliwiająca usunięcie profilu
 * */
void deleteProfile(Prof** node);


        // Funkcje zwracające struktury //
/**
 * Funkcja odpowiadająca za wyłuskanie informacji z linii i zapis ich do struktury
 * */
Info addingToStruct(char * temporaryLine);
/**
 * Wyłuskanie danych profilu z łańcucha znaków pobranego z pliku
 * */
PInfo addingProfileFromLine(const char* temporaryLine);
/**
 * Składowa funkcji "addProfileNode" pozwala na interakcje z użytkownikiem przy dodawaniu profilu
 * */
PInfo getProfileNameAndAccountNumber();


        // Funkcje Pomocnicze //
/**
 * Funkcja sprawdzająca czy podany łańcuch jest liczbą
 * */
int check(const char *);
/**
 * Funkcja konwertująca łańcuch na liczbę
 * */
int convertToInt(const char* chToInt);
/**
 * Czyszczenie bufora
 * */
void clearBuffer();
/**
 * Funkcja oczekuje na input użytkowanika w tym celu tymczasowo pauzuje program
 * */
void waiting();
/**
 * Funkcja zwracajaca 'unikalną' liczbę ustalaną na podstawie czasu w którym została dokonana płatność
 * */
long long getTimeValue(Info inf);
/**
 * Funkcja zwracająca ilość dokonanych płatności
 * */
int countingList(PayNode* node);
/**
 * Funkcja sprawdzająca zawartość litery w łańcuchu znaków, jeśli ma zwraca 1 w przeciwnym wypadku 0
 * */
int ifContainsLetter(const char* word);


        // Zwalnianie Pamięci //
/**
 * Zwalnianie zaalokowanej pamięci (Lista profilów)
 * */
void exitDeleteProfiles(Prof** profNode);
/**
 * Zwalnianie zaalokowanej pamięci (Lista płatności)
 * */
void exitDeleteNodes(PayNode** node);


#endif //PROSTAKSIEGOWOSCDOMOWAC_FUNKCJE_H
