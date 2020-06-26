#ifndef main_h
#define main_h

#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include <sys/unistd.h>

#define WYBOR 2            /* Wielkosc tablic uzywanych do buforowania wyboru uzytkownika*/
#define KOLOR 3             /* Ilosc wartosci opisujacych jeden piksel kolorowego obrazu*/
#define WSP_MASKI 9   /* Ilosc wspolczynnikow do przetwarzania macierza konwolucji*/


#define WSZYSTKO_OK 0                   /* wartosc oznaczajaca brak bledow */
#define B_NIEPOPRAWNAOPCJA -1    /* kody bledow */
#define B_BRAKNAZWY   -2
#define B_BRAKWARTOSCI  -3
#define B_BLEDNAWARTOSCI -5
#define ZLY_FORMAT -6
#define PUSTY_PLIK -7
#define BRAK_UCHWYTU -8
#define BLAD_PAMIECI -9



/**********************************************************
*                                                         *
*   Wartosci przypisane argumentom wywolania programu     *
*                                                         *
***********************************************************/

#define ROZMYCIEY -100
#define ROZMYCIEX -101
#define NEGATYW -102
#define PROGOWANIE -103
#define KONTUROWANIE -104
#define WYSWIETLENIE -105
#define ZAMIANA -106
#define MASKA -107
#define HISTOGRAM -108

#define HELP 42






/*struktura obrazu*/
typedef struct {
  char wariant[WYBOR];
  int wymx, wymy, szarosci;
  int **piksele;
} t_obraz;

/* strukura do zapamietywania opcji podanych w wywolaniu programu */
typedef struct {
  FILE *plik_we, *plik_wy;        /* uchwyty do pliku wej. i wyj. */
  int pomoc,konwersja;      /* pomoc i konwersja wykonuja sie priorytetowo*/
  int *opcje; /*Cala liste zmiennych od operacji zastapimy tablica, ktora zapamieta kolejnosc*/
  int prog,promien,czern,biel; /* wartosc progu, promienia, czerni i bieli dla odpowiednich operacji */
  int wspolczynniki[WSP_MASKI];      /*wartosci wspolczynnikow dla operacji maski*/
} w_opcje;


#endif
