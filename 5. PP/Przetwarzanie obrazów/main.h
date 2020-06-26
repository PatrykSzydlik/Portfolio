#ifndef main_h
#define main_h

#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include <sys/unistd.h>

#define MAX 512             /* Maksymalny rozmiar wczytywanego obrazu */
#define WYBOR 10            /* Wielkosc tablic uzywanych do buforowania wyboru uzytkownika*/

#define MAX_NAZWA 100       /* Dozwolona dlugosc nazw do wpisania*/


#define ROZMYCIE_MAX 10     /* Sztuczne ograniczenie maksymalnego rozmycia obrazu*/
#define PROG_MAX 100        /* Sztuczne ograniczenie maksymalnego progu do 100% maks\
			       szarosci, poniewaz wiecej nie ma sensu*/



#define MENU_GLOWNE 100
#define MENU_WCZYTAJ 110
#define MENU_ZAPIS 120
#define MENU_EDYCJI 130
#define MENU_ROZMYCIE 131
#define MENU_PROG 132
#define ZAKONCZ 42
#define CZY_KONIEC 200

/*Ponizej sa opisane definicje numerow komunikatow do wyswietlenia*/

#define WSZYSTKO_DOBRZE 1
#define BLAD_ODCZYTU -1
#define BRAK_UCHWYTU -2
#define PUSTY_PLIK -3
#define ZLY_FORMAT -4
#define BRAK_WYMIAROW -5
#define ZLE_PARAMETRY -6
#define BLAD_ZAPISU -7
#define ZLA_NAZWA -8
#define ZLY_WARIANT -9
#define BLAD_EDYCJI -10
#define ZLY_WYBOR -11
#define ZLA_WARTOSC -12
#define BLAD_WYSW -13

#define WSZYSTKO_OK 0                   /* wartosc oznaczajaca brak bledow */
#define B_NIEPOPRAWNAOPCJA -1    /* kody bledow rozpoznawania opcji */
#define B_BRAKNAZWY   -2
#define B_BRAKWARTOSCI  -3
#define B_BRAKPLIKU   -4




typedef struct {
  char wariant[WYBOR];
  int wymx, wymy, szarosci;
  int **piksele;
} t_obraz;

/* strukura do zapamietywania opcji podanych w wywolaniu programu */
typedef struct {
  FILE *plik_we, *plik_wy;        /* uchwyty do pliku wej. i wyj. */
  int negatyw,progowanie,konturowanie,wyswietlenie,rozmycie;      /* opcje */
  int prog,promien;              /* wartosc progu dla opcji progowanie */ 
} w_opcje;




#endif
