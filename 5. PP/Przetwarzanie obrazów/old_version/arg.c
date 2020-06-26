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
/*      w strukturze wybor, do tego ustawia na 1 pola, ktore            */
/*	    poprawnie wystapily w linii wywolania programu,                 */
/*	    pola opcji nie wystepujacych w wywolaniu ustawione sa na 0;     */
/*	    zwraca wartosc W_OK, gdy wywolanie bylo poprawne                */
/*	    lub kod bledu zdefiniowany stalymi B_* (<0)                     */
/* UWAGA:                                                               */
/*      funkcja nie sprawdza istnienia i praw dostepu do plikow         */
/*      w takich przypadkach zwracane uchwyty maja wartosc NULL         */
/************************************************************************/

int przetwarzaj_opcje(int argc, char **argv, w_opcje *wybor) {
  int i,k,kolejna=0;
  /*Zaalokowanie pamieci na tablice obslugujaca opcje*/
  char *nazwa_pliku_we, *nazwa_pliku_wy;
  wybor->opcje=malloc(argc*sizeof(int));
  wyzeruj_opcje(wybor,argc);




  wybor->plik_wy=stdout;        /* na wypadek gdy nie podano opcji "-o" */

  for (i=1; i<argc; i++) {
    if (argv[i][0] != '-'){  /* blad: to nie jest opcja - brak znaku "-" */
      fprintf(stderr,"Plik: arg.c Funkcja: Przetwarzaj_opcje\nArgument %s  ",argv[i]);
      return B_NIEPOPRAWNAOPCJA;
    };


    switch (argv[i][1]) {


      case 'i': {                 /* opcja z nazwa pliku wejsciowego */
        if (++i<argc) {   /* wczytujemy kolejny argument jako nazwe pliku */
	        nazwa_pliku_we=argv[i];
	        if (strcmp(nazwa_pliku_we,"-")==0){ /* gdy nazwa jest "-"        */
	            wybor->plik_we=stdin;            /* ustwiamy wejscie na stdin */
           }else{                               /* otwieramy wskazany plik   */
             if(argv[i][0]!='-'){
              wybor->plik_we=fopen(nazwa_pliku_we,"r");
            }else{

            };
           };
        }else{
          fprintf(stderr,"Plik: arg.c Funkcja: Przetwarzaj_opcje\nArgument %s  ",argv[--i]);
	          return B_BRAKNAZWY;  /* blad: brak nazwy pliku */
        };
      break;
          }


      case 'o': {                 /* opcja z nazwa pliku wyjsciowego */
        if (++i<argc) {   /* wczytujemy kolejny argument jako nazwe pliku */
	         nazwa_pliku_wy=argv[i];
	         if (strcmp(nazwa_pliku_wy,"-")==0){/* gdy nazwa jest "-"         */
	             wybor->plik_wy=stdout;   /* ustwiamy wyjscie na stdout */
           }else{                              /* otwieramy wskazany plik    */
	             wybor->plik_wy=fopen(nazwa_pliku_wy,"w");
           };
        }else{
          fprintf(stderr,"Plik: arg.c Funkcja: Przetwarzaj_opcje\nArgument %s  ",argv[--i]);
	          return B_BRAKNAZWY; /* blad: brak nazwy pliku */
        };
      break;
          }



      case 'p': {
         if (++i<argc) { /* wczytujemy kolejny argument jako wartosc progu */
	         if (sscanf(argv[i],"%d",&wybor->prog)==1){
	            wybor->opcje[kolejna]=PROGOWANIE;
              kolejna++;
	         }else{
             fprintf(stderr,"Plik: arg.c Funkcja: Przetwarzaj_opcje\nArgument %s  ",argv[i]);
	             return B_BLEDNAWARTOSCI;   /* blad: niepoprawna wartosc progu */
           };
         }else{
           fprintf(stderr,"Plik: arg.c Funkcja: Przetwarzaj_opcje\nArgument %s  ",argv[--i]);
	         return B_BRAKWARTOSCI;
         };            /* blad: brak wartosci progu */
      break;
            }



      case 'n': {                 /* mamy wykonac negatyw */
        wybor->opcje[kolejna]=NEGATYW;
        kolejna++;
      break;
      }



      case 'k': {                 /* mamy wykonac konturowanie */
        wybor->opcje[kolejna]=KONTUROWANIE;
        kolejna++;
      break;
      }



      case 'd': {                 /* mamy wyswietlic obraz */
        wybor->opcje[kolejna]=WYSWIETLENIE;
        kolejna++;
      break;
      }


      case 'h': {                 /* mamy wyswietlic instrukcje obslugi */
        wybor->pomoc=1;
      break;
      }



      case 'r':{
        if(argv[i][2]=='y'){
          wybor->opcje[kolejna]=ROZMYCIEY;
          kolejna++;
        }else if(argv[i][2]=='x'){
          wybor->opcje[kolejna]=ROZMYCIEX;
          kolejna++;
        }else{
          fprintf(stderr,"Plik: arg.c Funkcja: Przetwarzaj_opcje\nArgument %s",argv[i]);
          return B_NIEPOPRAWNAOPCJA;
        };
        if (++i<argc){ /* wczytujemy kolejny argument jako wartosc progu */
	         if (sscanf(argv[i],"%d",&wybor->promien)!=1){
               fprintf(stderr,"Plik: arg.c Funkcja: Przetwarzaj_opcje\nArgument %s",argv[i]);
               return B_BLEDNAWARTOSCI;   /* blad: niepoprawna wartosc promienia */
           };
        }else{
           fprintf(stderr,"Plik: arg.c Funkcja: Przetwarzaj_opcje\nArgument %s  ",argv[--i]);
           return B_BRAKWARTOSCI;
        };             /* blad: brak wartosci promienia */
      break;
      }


      case 's':{                 /* mamy wykonac konwersje do szarosci*/
        wybor->konwersja=1;
      break;
      }


      case 'e':{                 /* mamy wykonac rozciaganie histogramu*/
        wybor->opcje[kolejna]=HISTOGRAM;
        kolejna++;
      break;
      }



      case 'z': {  /* Wykonamy zamiane poziomow czerni i bieli*/
        wybor->opcje[kolejna]=ZAMIANA;
        kolejna++;
              if (++i<argc) { /* wczytujemy kolejny argument jako wartosc czerni*/
                 if (sscanf(argv[i],"%d",&wybor->czern)!=1) {
                     fprintf(stderr,"Plik: arg.c Funkcja: Przetwarzaj_opcje\nArgument %s %s  ",argv[i-1],argv[i]);
                     return B_BLEDNAWARTOSCI;};     /* blad: niepoprawna wartosc */
                   } else {
                    fprintf(stderr,"Plik: arg.c Funkcja: Przetwarzaj_opcje\nArgument %s  ",argv[--i]);
                    return B_BRAKWARTOSCI;             /* blad: brak wartosci*/
                  };
              if (++i<argc) { /* wczytujemy kolejny argument jako wartosc bieli*/
                 if (sscanf(argv[i],"%d",&wybor->biel)!=1) {
                     fprintf(stderr,"Plik: arg.c Funkcja: Przetwarzaj_opcje\nArgument %s %s  ",argv[i-2],argv[i]);
                     return B_BLEDNAWARTOSCI;};     /* blad: niepoprawna wartosc */
                   } else {
                    fprintf(stderr,"Plik: arg.c Funkcja: Przetwarzaj_opcje\nArgument %s  ",argv[i-2]);
                    return B_BRAKWARTOSCI;             /* blad: brak wartosci*/
                  };
                  break;

                  }

      case 'm': {  /* Operacja przetwarzania macierza*/
        wybor->opcje[kolejna]=MASKA;
        kolejna++;
          for(k=0;k<WSP_MASKI;k++){
            if (++i<argc) { /* wczytujemy kolejne wspolczynniki*/
              if (sscanf(argv[i],"%d",&wybor->wspolczynniki[k])!=1) {
                  fprintf(stderr,"Plik: arg.c Funkcja: Przetwarzaj_opcje\nArgument %s %s",argv[i-k-1],argv[i]);
                  return B_BLEDNAWARTOSCI;
              };     /* blad: niepoprawna wartosc */
            }else {
              fprintf(stderr,"Plik: arg.c Funkcja: Przetwarzaj_opcje\nArgument %s  ",argv[i-k-1]);
              return B_BRAKWARTOSCI;             /* blad: brak wartosci*/
            };
          };
      break;
      }



    case '?': /*Gdy podano nieprawidlowe opcje*/
      printf("Dostepne opcje:\n");
      printf("-i [nazwa_pliku]- wczytanie pliku wejsciowego\n");
      printf("-o [nazwa_pliku]- zapis do pliku wyjsciowego\n");
      printf("-d - wyswietlenie programem display\n");
      printf("-n - negatyw\n");
      printf("-k - konturowanie\n");
      printf("-s - konwersja obrazu kolorowego do szarosci\n");
      printf("-z [czern] [biel] - zamiana poziomow czerni i bieli\n");
      printf("-rx [promien] - rozmycie poziome\n");
      printf("-ry [promien] - rozmycie pionowe\n");
      printf("-e - rozciaganie histogramu\n");
      printf("-p [prog] - progowanie\n");
      printf("-m <w1-w9> - przetwarzanie macierza konwolucji o wsp w1-w9");
      printf("-h - pomoc, wyswietla pelna instrukcje obslugi programu\n");
      printf("\n");
      break;


    default:                    /* nierozpoznana opcja */
      fprintf(stderr,"Plik: arg.c Funkcja: Przetwarzaj_opcje\nArgument %s",argv[i]);
      return B_NIEPOPRAWNAOPCJA;
   }; /*koniec switch */
 }; /* koniec for */
 return WSZYSTKO_OK;
}


/********************************************
*    Funkcja alokuje pamiec dynamiczna      *
*                                           *
*  Wejscie:                                 *
*      wymx, wymy - wymiary tablicy         *
*                                           *
*  Wyjscie                                  *
*      wskaznik na zaalokowana pamiec       *
*                                           *
*                                           *
*    Brak warunkow PRE i POST               *
*                                           *
*  Poprawnosc alokacji pamieci sprawdzana   *
*  jest w miejscach uzycia funkcji alokuj   *
*  ze wzgledu na lokalna komunikacje bledow *
*                                           *
********************************************/

int **alokuj(int wymx, int wymy){
  int **tablica=NULL;
  tablica = malloc(wymy*sizeof(int*));
  /* Jesli uda sie zaalokowac pamiec to alokuj dalej*/
  if(tablica!=NULL){
      for(int y=0; y<wymy;y++){
        tablica[y]=malloc(wymx*sizeof(int));
        /*Jesli nie udalo sie zaalokowac calej potrzebnej pamieci
        To zwolnij wszystko co udalo Ci sie zaalokowac i zwroc NULL*/
        if(tablica[y]==NULL){
        zwolnij(tablica,wymy);
        return NULL;
        };
      };
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
  if(tablica!=NULL){
    for(int y=0; y<wymy;y++){
      /* Tylko gdy dana pamiec byla poprawnie zaalokowana to ja zwolnij*/
      if((tablica[y])!=NULL){
        free(tablica[y]);
      };
    };
    free(tablica);
  };
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

/********************************************
*    Funkcja kopiuje tablice pikseli        *
*                                           *
*  Wejscie:                                 *
*     tab - wskaznik na kopie               *
*     obraz - oryginalny obraz              *
*                                           *
*    Brak warunkow PRE                      *
*                                           *
*  POST - kopiuje oryginalna tablice        *
*                                           *
********************************************/

void kopiuj_tab(int **tab,t_obraz obraz){
  int wymx;
  if(obraz.wariant[1]=='3'){wymx=KOLOR*obraz.wymx;}else{wymx=obraz.wymx;};
  for (int i=0; i<obraz.wymy; i++){ /*kopiowanie tablicy*/
    for(int j=0; j<wymx; j++){
      tab[i][j]=obraz.piksele[i][j];
    };
  };
}

/*******************************************************/
/* Funkcja inicjuje strukture wskazywana przez wybor   */
/* PRE:                                                */
/*      poprawnie zainicjowany argument wybor (!=NULL) */
/* POST:                                               */
/*      "wyzerowana" struktura wybor wybranych opcji   */
/*******************************************************/



void wyzeruj_opcje(w_opcje * wybor, int ile) {
  int k;
  wybor->plik_we=NULL; /*i*/
  wybor->plik_wy=NULL; /*o*/
  wybor->pomoc=0;
 wybor->prog=0;
 wybor->konwersja=0;
 wybor->promien=0;
 wybor->czern=0;
 wybor->biel=0;
 for(int k=0;k<WSP_MASKI;k++){wybor->wspolczynniki[k]=0;};
 for(k=0;k<ile;k++){wybor->opcje[k]=0;};
}


/*******************************************************/
/* Funkcja zwalnia pamiec dynamiczna programu,         */
/*  a nastepnie wyswietla komunikat bledu.             */
/*                                                     */
/*  Wejscie:                                           */
/*    - numer bledu ktory wystapil                     */
/*    - wskaznik do struktury obrazu                   */
/*    - wskaznik do tablicy z opcjami                  */
/*                                                     */
/*                                                     */
/* POST:                                               */
/*      zwalnia pamiec i wyswietla komunikat bledu     */
/*******************************************************/

void komunikat(int blad, t_obraz *obraz, int *opcje){
  /* Najpierw zwalniamy pamiec dynamiczna*/
if(obraz->piksele!=NULL){zwolnij(obraz->piksele,obraz->wymy);};
if(opcje!=NULL){free(opcje);};

/* Teraz rozpoznamy blad i poinformujemy o nim uzytkownika.
   Przekazujemy tylko informacje o rodzaju bledu, poniewaz jego
   lokalizacja wyswietla sie lokalnie wewnatrz funkcji */
switch (blad) {
  case HELP:
  fprintf(stderr,"Mam ogromna nadzieje, ze udalo mi sie pomoc ;) \nKomunikat %d\n",blad);
  break;
  case B_NIEPOPRAWNAOPCJA:
  fprintf(stderr,"Niepoprawna opcja \nError %d\n",blad);
  break;
  case B_BRAKNAZWY:
  fprintf(stderr,"Brak nazwy pliku \nError %d\n",blad);
  break;
  case B_BRAKWARTOSCI:
  fprintf(stderr,"Brak wymaganej wartosci \nError %d\n",blad);
  break;
  case B_BLEDNAWARTOSCI:
  fprintf(stderr," Bledna wartosc argumentu \nError %d\n",blad);
  break;
  case ZLY_FORMAT:
  fprintf(stderr,"Niepoprawny format obrazu! \nError %d\n",blad);
  break;
  case PUSTY_PLIK:
  fprintf(stderr,"Plik, ktory probujesz wczytac jest pusty! \nError %d\n",blad);
  break;
  case BRAK_UCHWYTU:
  fprintf(stderr,"Niepoprawne dowiazanie do pliku! Nie udalo sie go otworzyc. \nError %d\n",blad);
  break;
  case BLAD_PAMIECI:
  fprintf(stderr,"Nie udalo sie zaalokowac poprawnie pamieci! \nError %d\n",blad);
  break;
}

}

/*******************************************************/
/* Funkcja wyswietla tresc pomocy dla uzytkownika      */
/*                                                     */
/*  Wejscie:                                           */
/*    Otrzymuje nazwe programu glownego.               */
/*                                                     */
/* POST:                                               */
/*      wyswietla instrukcje obslugi programu          */
/*******************************************************/


void pomoc(char *nazwa){
fprintf(stderr," \n\
 ______________________________________\n\
|                                      |\n\
|    Instrukcja obslugi programu       |\n\
|______________________________________|\n\n");
fprintf(stderr,"Przedstawiony program dokonuje operacji edycji na obrazach w formacie .pgm {P2 i P5}.\n\
Umozliwia on rowniez wczytywanie i zapis obrazow kolorowych o formacie .ppm {P3}.\n\
Natomiast mozliwosc edycji obrazow kolorowych jest niedostepna. \n\
Program dokona wtedy konwersji obrazow kolorowych do skali szarosci.\n\n\
WZOR WYWOLANIA:    %s -i <arg> -o <arg> [opcje]  \n\n\
 __________________________________\n\
|                                  |\n\
|   OPCJE URUCHAMIANIA PROGRAMU    |\n\
|__________________________________|\n\n\
-i ('-'|<nazwa_pliku>) -> WYMAGANA! Ustawienie pliku zrodlowego obrazu. \
Argument '-' oznacza czytanie z stdin.\n\n\
-o ('-'|<nazwa_pliku>) -> WYMAGANA! Ustawienie pliku wynikowego obrazu. \
Argument '-' oznacza wypisanie na stdout.\n\n\
-d -> Wyswietla obraz przed zapisaniem przy uzyciu programu display.\n\n\
-h -> Wyswietla instrukcje obslugi programu ;)  \
Powoduje zignorowanie wszystkich innych opcji.\n\n\
 ____________________________\n\
|                            |\n\
|    OPCJE EDYCJI OBRAZU     |\n\
|____________________________|\n\n\
******  !!  UWAGA  !!  ******\nOperacje edycji przedstawione ponizej wykonywane \
beda tylko na obrazach w odcieniach szarosci. \nDlatego tez przy probie edycji obrazu kolorowego zostanie on automatycznie skonwertowany do szarosci.\n\n\
-s -> Dokonuje konwersji obrazy kolorowego .ppm do obrazu w odcieniach szarosci .pgm.\n\n\
-z <czern> <biel> -> Wykonuje na obrazie operacje zamiany poziomow czerni i bieli. \
Wartosci wymagane w argumentach tej opcji to wartosc procentowa nowego \
poziomu czerni i bieli w odniesieniu do wartosci maksymalnej szarosci piksela obrazu.\n\
WARUNEK KONIECZNY : 0 < czern < biel <= 100   oraz czern i biel musza byc liczbami calkowitymi\n\n\
-p <prog> -> Wykonuje operacje progowania obrazu względem zadanej wartosci progu.\n\
WARUNEK KONIECZNY : 0 < prog < 100  oraz prog musi byc liczba calkowita\n\n\
-r(x|y) <promien> -> Wykonuje operacje rozmycia poziomego(dla x) lub pionowego \
(dla y) o wartosci zadanej jako promien rozmycia.\n\
WARUNEK KONIECZNY : 0 < promien < 10  oraz promien musi byc liczba calkowita\n\n\
-k -> Wykonuje operacje konturowania obrazu.\n\n\
-n -> Wykonuje operacje obliczenia negatywu obrazu.\n\n\
-m <w1> <w2> <w3> <w4> <w5> <w6> <w7> <w8> <w9> -> Wykonuje operacje \
przetwarzania obrazu macierza konwolucji. \nWspolczynniki w1-w9 sluza do okreslenia\
 filtru maski, ktory ma byc wykonany w operacji. \nWspolczynniki musza być liczbami całkowitymi.\n\n\
",nazwa);
}
