#ifndef file_h
#define file_h

#define DL_LINII 1024       /* Dlugosc buforow pomocniczych */
#define MAX_1BAJT 255       /* Wartosc powyzej ktorej zapisu dokonuje sie w 2 Bajtach danych*/
#define BAJTY2_ILE_CYFR 6   /* Ile cyfr w zapisie dziesietnym ma liczba 2 bajtowa (+1 na odstep) */
#define BAJT1_ILE_CYFR 4    /* Ile cyfr w zapisie dziesietnym ma liczba 1 bajtowa (+1 na odstep) */
#define BAJTY2_ILE_LINIA 11 /* Ile liczb 2 bajtowych w zapisie dzies. zmiesci sie w 70 znakowej linii tekstu*/
#define BAJT1_ILE_LINIA 18  /* Ile liczb 1 bajtowych w zapisie dzies. zmiesci sie w 70 znakowej linii tekstu*/


int czytaj(FILE *plik_we,t_obraz *obraz);
int zapisz(FILE *plik_wy,t_obraz obraz);
void wyswietl(t_obraz obraz);


#endif
