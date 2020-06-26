#ifndef arg_h
#define arg_h






/*W tym module naglowkowym znajduja sie funkcje sluzace do obslugi argumentow wywolania oraz tablic dynamicznych.*/

void kopiuj_tab(int **tab,t_obraz obraz);
void zwolnij(int **tablica, int wymy);
void inicjuj_obraz(t_obraz *obraz);
void wyzeruj_opcje(w_opcje * wybor, int ile);
int przetwarzaj_opcje(int argc, char **argv, w_opcje *wybor);
int **alokuj(int wymx, int wymy);
void pomoc(char *nazwa);
void komunikat(int blad, t_obraz *obraz, int *opcje);

#endif
