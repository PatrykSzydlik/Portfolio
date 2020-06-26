#ifndef edit_h
#define edit_h


#define ROZMYCIE_MAX 10     /* Sztuczne ograniczenie maksymalnego rozmycia obrazu*/
#define PROG_MAX 100        /* Sztuczne ograniczenie maksymalnego progu do 100% maks szarosci, poniewaz wiecej nie ma sensu*/
#define M 1 /* Stala ktora jest wykorzystana wielokrotnie przy operacji maski*/

void negatyw(t_obraz *obraz);
int rozmycie(t_obraz *obraz,int opcja,int promien);
int progowanie(t_obraz *obraz, int prog);
int konturowanie(t_obraz *obraz);
int konwersja(t_obraz *obraz);
int zamiana(t_obraz *obraz,int czern,int biel);
int maska(t_obraz *obraz,int *wsp);
void rozciaganie(t_obraz *obraz);

#endif
