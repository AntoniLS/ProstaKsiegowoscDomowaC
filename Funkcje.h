/** @file */

#ifndef PROSTAKSIEGOWOSCDOMOWAC_FUNKCJE_H
#define PROSTAKSIEGOWOSCDOMOWAC_FUNKCJE_H
#define con 100
#define numberOfCategories 4
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
 * @param node początek listy płatności
 * @param profileList początek listy profilów
 * */
void programExecution(PayNode** node, Prof** profileList);
/**
 * Funkcja wyświetlająca menu z wszystkimi opcjami do wyboru
 * @param node początek listy płatności
 * @param profNode początek listy profilów
 */
void printingMenu(PayNode** node,Prof** profNode);
/**
 * Funkcja wyświetlająca menu (Profilów) z wszystkimi opcjami do wyboru
 * @param profNode początek listy profilów
 * */
void profilesMenu(Prof** profNode);


        // Pliki Tekstowe //
/**
 * Funkcja ładowanie danych z pliku do struktury
 * @param x nazwa pliku wejściowego
 * @param node początek listy płatności
 * */
void loadingFromFile(const char* x, PayNode** node);
/**
 * Funkcja obsługująca plik zawierający domyślną listę profilów [nazwa | numer konta]
 * @param profNode początek listy profilów
 * @param defaultProfileInputFile nazwa pliku wejściowego zawierającego domyślną liste profilów
 * */
void defaultProfileList(Prof** profNode, const char* defaultProfileInputFile);
/**
 * Zapisywanie domyślnych + utworzonych w trakcie dzialania programu profilów do pliku
 * @param profList początek listy profilów
 * */
void saveProfiles(Prof* profileList ,const char *nameOfFileWithDefaultProfiles);


        // Poprawność danych, zgodność z przyjętym formatem //
/**
 * Sprawdzenie poprwaności danych z pobranej linii, (czy format jest odpowiedni) jeśli nie, pomiń
 * @param x linia pobrana z pliku tekstowego
 * */
int checkIfLineIsCorrect(const char* x);
/**
 * Sprawdzenie poprawności danych z pobranej linii, (czy format jest odpowiedni [nazwaProfilu | numer konta]) jeśli nie, pomiń
 * @param line linia pobrana z pliku tekstowego
 * */
int checkIfLineIsCorrectProfile(const char* line);


        // Lista Jednokierunkowa Płatności //
/**
 * Funkcja dodająca węzeł oraz przypisujaca mu strukturę zwierającą informacje o płatności
 * @param node początek listy płatności
 * @param info struktura zawierająca informacje o płatności (wyłuskane z pliku txt)
 * */
void addingPaymentToNode(PayNode** node, Info info);
/**
 * Funkcja iterująca przez listę
 * @param node początek listy płatności
 * */
void readingNodes(PayNode* node);
/**
 * Funkcja wyświetlająca przychód lub straty, w zależności od wybranej opcji
 * @param node początek listy płatności
 * @param option liczba określająca opcje (dochód/straty)
 * */
void showIncomeOutcome(PayNode* node, int option);
/**
 * Funkcja wyświetla płatności zgdonie z ramami czasowymi
 * @param node początek listy płatności
 **/
void timeList(PayNode** node);
/**
 * Funkcja wyświetla wydatki poszczególych (wczesniej dodanych) profilow
 * @param node początek listy płatności
 * @param profNode początek listy profilów
 * */
void expensesSortedByMemberList(PayNode* node, Prof* profNode);
/**
 * Fukcja wyświetlająca liste płatnośći zgdonie z możliwymi kategoriami
 * @param node początek listy płatności
 * */
void showByCategories(PayNode* node);
/**
 * Funkcja wyświetlająca płatność ze wszystkimi jej szczegółami
 * @param node początek listy płatności
 * */
void printWholeLine(PayNode* node);


        // Lista Jednokierunkowa Profile //
/**
 * Funkcja wyświetlająca wszystkie utworzone wczesniej profile
 * @param profNode poczatek listy profilów
 * */
void showProfiles(Prof* profNode);
/**
 * Funkcja umożliwiająca dodanie nowego węzła profilu i powiazania go z numerem konta
 * @param profNode poczatek listy profilów
 * */
void addProfileNode(Prof** profNode);
/**
 * Funkcja umożliwiająca zmianę nazwy profilu
 * @param profNode poczatek listy profilów
 * */
void renameProfile(Prof** profNode);
/**
 * Dodawanie domyślnego profilu do listy
 * @param profNode poczatek listy profilów
 * @param x struktura zawierająca informacje o profilu
 * */
void addingDefaultProfiles(Prof** profNode, PInfo x);
/**
 * Funkcja umożliwiająca usunięcie profilu
 * @param node początek listy płatności
 * */
void deleteProfile(Prof** node);


        // Funkcje zwracające struktury //
/**
 * Funkcja odpowiadająca za wyłuskanie informacji z linii i zapis ich do struktury
 * @param temporaryLine linia pochodząca z pliku tekstowego
 * @return struktura zawierająca informacje o płatności
 * */
Info addingToStruct(char * temporaryLine);
/**
 * Wyłuskanie danych profilu z łańcucha znaków pobranego z pliku
 * @param temporaryLine linia pochodząca z pliku tekstowego
 * @return struktura zawierająca informacje o profilu
 * */
PInfo addingProfileFromLine(const char* temporaryLine);
/**
 * Składowa funkcji "addProfileNode" pozwala na interakcje z użytkownikiem przy dodawaniu profilu
 * @return struktura zawierająca informacje o profilu
 * */
PInfo getProfileNameAndAccountNumber();


        // Funkcje Pomocnicze //
/**
 * Funkcja sprawdzająca czy podany łańcuch jest liczbą
 * @param x wskaźnik na łańcuch znaków
 * @return łańcuch zamieniony na liczbę całkowitą
 * */
int check(const char *x);
/**
 * Funkcja konwertująca łańcuch na liczbę
 * @param chToInt wskaźnik na łańcuch znaków
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
 * @param inf struktura zawierająca informacje o płatności
 * @return unikalna liczba będąca reprezentacją czasu, w którym została dokonana płatność
 * */
long long getTimeValue(Info inf);
/**
 * Funkcja zwracająca ilość dokonanych płatności
 * @param node początek listy płatności
 * */
int countingList(PayNode* node);
/**
 * Funkcja sprawdzająca zawartość litery w łańcuchu znaków, jeśli ma zwraca 1 w przeciwnym wypadku 0
 * @param word wskaźnik na łańcuch znaków
 * */
int ifContainsLetter(const char* word);


        // Zwalnianie Pamięci //
/**
 * Zwalnianie zaalokowanej pamięci (Lista profilów)
 * @param profNode początek listy profilów
 * */
void exitDeleteProfiles(Prof** profNode);
/**
 * Zwalnianie zaalokowanej pamięci (Lista płatności)
 * @param node początek listy płatności
 * */
void exitDeleteNodes(PayNode** node);


#endif //PROSTAKSIEGOWOSCDOMOWAC_FUNKCJE_H
