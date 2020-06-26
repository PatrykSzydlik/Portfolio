#include "main.h"
#include "arg.h"

/********************************************************************/
/*                                                                  */
/* ALTERNATYWNA DO PRZEDSTAWIONEJ NA WYKLADZIE WERSJA OPRACOWANIA   */
/* PARAMETROW WYWOLANIA PROGRAMU UWZGLEDNIAJACA OPCJE Z PARAMETRAMI */
/* Z ODPOWIEDNIO ZAPROPONOWANYMI STRUKTURAMI DANYCH PRZEKAZUJACYMI  */
/* WCZYTANE USTAWIENIA                                              */
/*                                    COPYRIGHT (c) 2007-2013 ZPCiR */
/*                                                                  */
/* Autorzy udzielaja kazdemu prawa do kopiowania tego programu      */
/* w calosci lub czesci i wykorzystania go w dowolnym celu, pod     */
/* warunkiem zacytowania zrodla                                     */
/*                                                                  */
/********************************************************************/


int **alokuj(int wymx, int wymy){
  int **tablica;
  tablica = malloc(wymy*sizeof(int*));
  for(int y=0; y<wymy;y++){
  tablica[y]=malloc(wymx*sizeof(int));
};
  return tablica;
}

/********************************************
*    Funkcja zwalnia pamiec dynamiczna      *
*                                           *
*    Brak warunkow PRE i POST               *
*                                           *
********************************************/

void zwolnij(int **tablica, int wymy){
for(int y=0; y<wymy;y++){
free(tablica[y]);
};
free(tablica);
}

/********************************************
*    Funkcja inicjuje strukture danych.     *
*                                           *
*  PRE:                                     *
* prawidlowo zainicjowana zmienna *obraz    *
*                                           *
*    POST: zainicjowana struktura           *
********************************************/

void inicjuj_obraz(t_obraz *obraz){
obraz->wymx=0;
obraz->wymy=0;
obraz->szarosci=0;
for(int i=0; i<WYBOR; i++){obraz->wariant[i]='\0';};
obraz->piksele=NULL;
}

/*******************************************************/
/* Funkcja inicjuje strukture wskazywana przez wybor   */
/* PRE:                                                */
/*      poprawnie zainicjowany argument wybor (!=NULL) */
/* POST:                                               */
/*      "wyzerowana" struktura wybor wybranych opcji   */
/*******************************************************/



void wyzeruj_opcje(w_opcje * wybor) {
  wybor->plik_we=NULL; /*i*/
  wybor->plik_wy=NULL; /*o*/
  wybor->negatyw=0;    /*n*/
  wybor->konturowanie=0;   /*k*/
  wybor->progowanie=0;    /*p*/
  wybor->wyswietlenie=0; /*d*/
  wybor->konwersja=0;
  wybor->zamiana=0;
wybor->rozmycie=0;	 /*rx i ry*/
wybor->prog=0;
wybor->promien=0;
wybor->czern=0;
wybor->biel=0;
}


/************************************************************************/
/* Funkcja rozpoznaje opcje wywolania programu zapisane w tablicy argv  */
/* i zapisuje je w strukturze wybor                                     */
/* Skladnia opcji wywolania programu                                    */
/*         program {[-i nazwa] [-o nazwa] [-p liczba] [-n] [-r] [-d] }  */
/* Argumenty funkcji:                                                   */
/*         argc  -  liczba argumentow wywolania wraz z nazwa programu   */
/*         argv  -  tablica argumentow wywolania                        */
/*         wybor -  struktura z informacjami o wywolanych opcjach       */
/* PRE:                                                                 */
/*      brak                                                            */
/* POST:                                                                */
/*      funkcja otwiera odpowiednie pliki, zwraca uchwyty do nich       */
/*      w strukturze wyb�r, do tego ustawia na 1 pola, ktore            */
/*	poprawnie wystapily w linii wywolania programu,                 */
/*	pola opcji nie wystepujacych w wywolaniu ustawione sa na 0;     */
/*	zwraca wartosc W_OK, gdy wywolanie bylo poprawne                */
/*	lub kod bledu zdefiniowany stalymi B_* (<0)                     */
/* UWAGA:                                                               */
/*      funkcja nie sprawdza istnienia i praw dostepu do plikow         */
/*      w takich przypadkach zwracane uchwyty maja wartosc NULL         */
/************************************************************************/

int przetwarzaj_opcje(int argc, char **argv, w_opcje *wybor) {
  int i, prog;
  char *nazwa_pliku_we, *nazwa_pliku_wy;

  wyzeruj_opcje(wybor);
  wybor->plik_wy=stdout;        /* na wypadek gdy nie podano opcji "-o" */

  for (i=1; i<argc; i++) {
    if (argv[i][0] != '-')  /* blad: to nie jest opcja - brak znaku "-" */
      return B_NIEPOPRAWNAOPCJA;
    switch (argv[i][1]) {
    case 'i': {                 /* opcja z nazwa pliku wejsciowego */
      if (++i<argc) {   /* wczytujemy kolejny argument jako nazwe pliku */
	       nazwa_pliku_we=argv[i];
	        if (strcmp(nazwa_pliku_we,"-")==0) /* gdy nazwa jest "-"        */
	         wybor->plik_we=stdin;            /* ustwiamy wejscie na stdin */
	          else                               /* otwieramy wskazany plik   */
	           wybor->plik_we=fopen(nazwa_pliku_we,"r");
           } else
	          return B_BRAKNAZWY;                   /* blad: brak nazwy pliku */
            break;
          }
    case 'o': {                 /* opcja z nazwa pliku wyjsciowego */
      if (++i<argc) {   /* wczytujemy kolejny argument jako nazwe pliku */
	       nazwa_pliku_wy=argv[i];
	        if (strcmp(nazwa_pliku_wy,"-")==0)/* gdy nazwa jest "-"         */
	         wybor->plik_wy=stdout;          /* ustwiamy wyjscie na stdout */
	          else                              /* otwieramy wskazany plik    */
	           wybor->plik_wy=fopen(nazwa_pliku_wy,"w");
           } else
	          return B_BRAKNAZWY;                   /* blad: brak nazwy pliku */
            break;
          }
    case 'p': {
        if (++i<argc) { /* wczytujemy kolejny argument jako wartosc progu */
	         if (sscanf(argv[i],"%d",&prog)==1) {
	            wybor->progowanie=1;
	             wybor->prog=prog;
	            } else
	             return B_BRAKWARTOSCI;     /* blad: niepoprawna wartosc progu */
             } else
	            return B_BRAKWARTOSCI;             /* blad: brak wartosci progu */
              break;
            }
    case 'n': {                 /* mamy wykonac negatyw */
        wybor->negatyw=1;
        break;
      }
    case 'k': {                 /* mamy wykonac konturowanie */
        wybor->konturowanie=1;
        break;
      }
    case 'd': {                 /* mamy wyswietlic obraz */
        wybor->wyswietlenie=1;
        break;
      }
    case 'r':{
      if(argv[i][2]=='y'){wybor->rozmycie=1;};
      if(argv[i][2]=='x'){wybor->rozmycie=2;};
      if (++i<argc) { /* wczytujemy kolejny argument jako wartosc progu */
	       if (sscanf(argv[i],"%d",&wybor->promien)!=1) {
           return B_BRAKWARTOSCI; };    /* blad: niepoprawna wartosc promienia */
         } else
	        return B_BRAKWARTOSCI;             /* blad: brak wartosci promienia */
          break;
        }
    case 's': {                 /* mamy wykonac konwersje do szarosci*/
        wybor->konwersja=1;
        break;
          }
    case 'z': {  /* Wykonamy zamiane poziomow czerni i bieli*/
        wybor->zamiana=1;
              if (++i<argc) { /* wczytujemy kolejny argument jako wartosc czerni*/
                 if (sscanf(argv[i],"%d",&wybor->czern)!=1) {
                     return B_BRAKWARTOSCI;};     /* blad: niepoprawna wartosc */
                   } else {
                    return B_BRAKWARTOSCI;             /* blad: brak wartosci*/
                  };
              if (++i<argc) { /* wczytujemy kolejny argument jako wartosc bieli*/
                 if (sscanf(argv[i],"%d",&wybor->biel)!=1) {
                     return B_BRAKWARTOSCI;};     /* blad: niepoprawna wartosc */
                   } else {
                    return B_BRAKWARTOSCI;             /* blad: brak wartosci*/
                  };
                  break;

                  }

    default:                    /* nierozpoznana opcja */
      return B_NIEPOPRAWNAOPCJA;
   }; /*koniec switch */
 }; /* koniec for */
 return WSZYSTKO_OK;
}
