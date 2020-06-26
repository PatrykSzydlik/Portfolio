#include "main.h"
#include "edit.h"
#include "arg.h"



/*********************************************************************
*                      PROGRAM NEGATYW                               *
**********************************************************************
* Na wejsciu otrzymuje:                                              *
*    t_obraz *obraz  -- strukture zawierajaca informacje o obrazie   *
*                                                                    *
* Na wyjsciu program zmienia oryginalny obraz tworzac jego negatyw   *
*                                                                    *
* Brak PRE i POST                                                    *
**********************************************************************/


void negatyw(t_obraz *obraz){
  for (int i=0;i<obraz->wymy;i++) {
    for (int j=0;j<obraz->wymx;j++) {
      obraz->piksele[i][j]=obraz->szarosci-obraz->piksele[i][j];
    };
  };
}



/*********************************************************************
*                      PROGRAM ROZMYCIE                              *
**********************************************************************
* Na wejsciu otrzymuje:                                              *
*    t_obraz obraz  -- struktura z danymi o obrazie                  *
*    opcja,promien -- sluza do wyboru rodzaju i poziomu rozmycia     *
*                                                                    *
* Program tworzy dynamiczna kopie oryginalnego obrazu i na jej       *
* podstawie dokonuje obliczen aby wyliczyc rozmyte piksele i         *
* zapisac ich wartosc w oryginalnej tablicy obraz->piksele           *
*                                                                    *
* Na wyjsciu zwraca obraz[][] po rozmyciu.                           *
*                                                                    *
*                                                                    *
* PRE :                                                              *
*      - wartosc promienia nalezaca do dozwolonego przedzialu        *
*      - prawidlowo zaalokowana pamiec dla kopii obrazu              *
**********************************************************************/



int rozmycie(t_obraz *obraz,int opcja,int promien){
  int suma=0;
  int **kopia=alokuj(obraz->wymx,obraz->wymy);
  /*Asercja. Czy udalo sie zaalokowac pamiec.*/
  if(kopia==NULL){fprintf(stderr,"Plik: edit2.c Funkcja: Rozmycie Linia: 54\n");return BLAD_PAMIECI;};
  kopiuj_tab(kopia,*obraz);
  /*Asercja. Czy promien ma prawidlowa wartosc*/
  if(promien<0||promien>ROZMYCIE_MAX){fprintf(stderr,"Plik: edit2.c Funkcja: Rozmycie Linia: 57\n");return B_BLEDNAWARTOSCI;};


  for (int i=0;i<obraz->wymy;i++) {
    for (int j=0;j<obraz->wymx;j++) {
      for (int k=promien;k>=(-1*promien);k--) {
	       if(opcja==1){
	          if( (i+k)>=0 && (i+k)<obraz->wymy ){
	             suma=suma+kopia[i+k][j];
	            }else{
	               suma=suma+kopia[i][j];};
	       }else if(opcja==2){
	          if( (j+k)>=0 && (j+k)<obraz->wymx ){
	            suma=suma+kopia[i][j+k];
	           }else{
	              suma=suma+kopia[i][j];
            };
	       };
    };
    obraz->piksele[i][j]=(suma/(2*promien+1));
    suma=0;
   };
 };
 zwolnij(kopia,obraz->wymy);
 return WSZYSTKO_OK;
}


/*********************************************************************
*                      PROGRAM PROGOWANIE                            *
**********************************************************************
* Na wejsciu otrzymuje:                                              *
*    obraz  -- struktura z danymi o obrazie                          *
*    prog   -- wartosc procentowa progu                              *
*                                                                    *
* Na wyjsciu program zwraca obraz[][] po przeliczeniu pikseli        *
* wzgledem podanego poziomu progowania obrazu.                       *
*                                                                    *
* Warunki PRE:                                                       *
*       - prawidlowa wartosc progu                                   *
**********************************************************************/



int progowanie(t_obraz *obraz, int prog){
  /*Asercja. Czy prog ma prawidlowa wartosc*/
  if(prog<0||prog>PROG_MAX){fprintf(stderr,"Plik: edit2.c Funkcja: Progowanie Linia: 103\n");return B_BLEDNAWARTOSCI;} ;
  prog=(prog*obraz->szarosci)/100;
  for (int i=0;i<obraz->wymy;i++) {
    for (int j=0;j<obraz->wymx;j++) {
      if(obraz->piksele[i][j]>prog){obraz->piksele[i][j]=obraz->szarosci;}
      else{obraz->piksele[i][j]=0;};
    };
  };
  return WSZYSTKO_OK;
}



/*********************************************************************
*                      PROGRAM KONTUROWANIE                          *
**********************************************************************
* Na wejsciu otrzymuje:                                              *
*    obraz  -- struktura z danymi o obrazie                          *
*                                                                    *
* Program tworzy kopie oryginalnego obrazu i na jej                  *
* podstawie dokonuje obliczen aby wyliczyc piksele po konturowaniu   *
* i zapisac ich wartosc w oryginalnej tablicy obraz[][]              *
*                                                                    *
* Na wyjsciu zwraca zmieniony obraz->piksele po konturowaniu.        *
*                                                                    *
* Warunki PRE:                                                       *
*       - poprawnie zaalokowana kopia obrazu                         *
**********************************************************************/


int konturowanie(t_obraz *obraz){
  int **kopia=alokuj(obraz->wymx,obraz->wymy);
  if(kopia==NULL){fprintf(stderr,"Plik: edit2.c Funkcja: Konturowanie Linia: 135\n");return BLAD_PAMIECI;};
  kopiuj_tab(kopia,*obraz);
  for (int i=0;i<obraz->wymy;i++) {
    for (int j=0;j<obraz->wymx;j++) {

      /* Pierwsze linie sprawdzaja czy piksele nie znajduja sie na krawedziach obrazu   */
      /* bo jesli tak to nie mozna stosowac oryginalnego wzoru, poniewaz moglo by dojsc */
      /* do bledu ochrony pamieci. Lub najczesciej do dokonaniu blednych obliczen       */

      if(i==obraz->wymy-1 && j!=obraz->wymx-1){
	       obraz->piksele[i][j]=abs(kopia[i-1][j]-kopia[i][j])+abs(kopia[i][j+1]-kopia[i][j]);
      }else if(j==obraz->wymx-1 &&  i!=obraz->wymy-1){
	       obraz->piksele[i][j]=abs(kopia[i][j-1]-kopia[i][j])+abs(kopia[i+1][j]-kopia[i][j]);
      }else if(i==obraz->wymy-1 && j==obraz->wymx-1){
	       obraz->piksele[i][j]=abs(kopia[i][j-1]-kopia[i][j])+abs(kopia[i-1][j]-kopia[i][j]);
      }else{

	/* Tutaj sprawdzane sa wszystkie piksele dla ktorych nie powinny wystepowac bledy */
	/* uzyty jest wzor podany w materialach do zajec                                  */

	       obraz->piksele[i][j]=abs(kopia[i+1][j]-kopia[i][j])+abs(kopia[i][j+1]-kopia[i][j]);
      };
      if(obraz->piksele[i][j]>obraz->szarosci){obraz->piksele[i][j]=obraz->szarosci;};           /* Kontrola czy wartosc pikseli nie wykracza ponad maks szarosc*/
    };
  };
  /* zwolnienie pamięcy zaalokowanej na kopie*/
  zwolnij(kopia,obraz->wymy);
  return WSZYSTKO_OK;
}

/*********************************************************************
*                      PROGRAM KONWERSJA                             *
**********************************************************************
* Na wejsciu otrzymuje:                                              *
*    obraz  -- struktura z danymi o obrazie                          *
*                                                                    *
* Na wyjsciu program zwraca obraz po przeliczeniu pikseli            *
* kolorowych na skale szarosci.                                      *
*                                                                    *
* Warunki PRE:                                                       *
*       - prawidlowa wariant obrazu                                  *
*       - prawidlowo zaalokowana kopia obrazu oraz nowy obraz        *
**********************************************************************/


int konwersja(t_obraz *obraz){
  /*zapamietanie wskaznika do zwolnienia pamieci*/
  int **staryobraz = obraz->piksele;
  int **kopia=NULL;
  /*Asercja. Czy obraz jet obrazem kolorowym P3*/
  if(obraz->wariant[1]!='3'){fprintf(stderr,"Plik: edit2.c Funkcja: Konwersja Linia: 185\n");return ZLY_FORMAT;};
  kopia=alokuj(KOLOR*obraz->wymx,obraz->wymy);
  /*Asercja. Czy poprawnie zaalokowano pamiec?*/
  if(kopia==NULL){fprintf(stderr,"Plik: edit2.c Funkcja: Konwersja Linia: 188\n");return BLAD_PAMIECI;};
  kopiuj_tab(kopia,*obraz);
  obraz->piksele=alokuj(obraz->wymx, obraz->wymy);
  /*Asercja. Czy poprawnie zaalokowano pamiec?
  Jesli nie to wyczysc wczesniej alokowana pamiec dynamiczna, przywroc stara tablice i przerwij prace*/
  if(obraz->piksele==NULL){
    fprintf(stderr,"Plik: edit2.c Funkcja: Konwersja Linia: 193\n");
    zwolnij(kopia,obraz->wymy);
    obraz->piksele=staryobraz;
    return BLAD_PAMIECI;
  };
  if(obraz->wariant[1]=='3'){
    for (int i=0;i<obraz->wymy;i++) {
      for (int j=0;j<obraz->wymx;j++) {
        obraz->piksele[i][j]=(kopia[i][KOLOR*j]+kopia[i][KOLOR*j+1]+kopia[i][KOLOR*j+2])/KOLOR;
      };
    };
  };
  obraz->wariant[1]='2';
  zwolnij(staryobraz, obraz->wymy);
  zwolnij(kopia,obraz->wymy);
  return WSZYSTKO_OK;
}

/*********************************************************************
*                   PROGRAM ZAMIANA POZIOMOW                         *
**********************************************************************
* Na wejsciu otrzymuje:                                              *
*    obraz  -- struktura z danymi o obrazie                          *
*    czern  -- wartosc nowego poziomu czerni                         *
*    biel   -- wartosc nowego poziomu bieli                          *
*                                                                    *
* Na wyjsciu program zwraca obraz po przeliczeniu nowych wartosi     *
* pikseli.                                                           *
*                                                                    *
* Warunki PRE:                                                       *
*       - prawidlowa wartosc czerni                                  *
*       - prawidlowa wartosc bieli                                   *
**********************************************************************/

int zamiana(t_obraz *obraz,int czern,int biel){
/*Wykorzystuje juz zdefiniowana wartosc PROG_MAX poniewaz ona rowniez odnosila sie do wartosci procentowych*/
/*Asercja. Czy wartosci czerni i bieli sa prawidlowe.*/
if(czern<0 || czern>=PROG_MAX){fprintf(stderr,"Plik: edit2.c Funkcja: Zamiana Linia: 231\n"); return B_BLEDNAWARTOSCI;};
if(biel<czern || biel>PROG_MAX){fprintf(stderr,"Plik: edit2.c Funkcja: Zamiana Linia: 232\n"); return B_BLEDNAWARTOSCI;};

 czern= (czern * obraz->szarosci)/100;
 biel= (biel * obraz->szarosci)/100;


  for (int i=0;i<obraz->wymy;i++) {
    for (int j=0;j<obraz->wymx;j++) {
      if(obraz->piksele[i][j]<=czern){obraz->piksele[i][j]=0;};
      if(obraz->piksele[i][j]>czern && obraz->piksele[i][j]<biel){
        obraz->piksele[i][j]=((obraz->piksele[i][j]-czern)*obraz->szarosci)/(biel-czern);
      };
      if(obraz->piksele[i][j]>=biel){obraz->piksele[i][j]=obraz->szarosci;};
    };
  };
  return WSZYSTKO_OK;

}

/*********************************************************************
*                       PROGRAM MASKA                                *
**********************************************************************
* Na wejsciu otrzymuje:                                              *
*    obraz  -- struktura z danymi o obrazie                          *
*    wsp    -- tablice wspolczynnikow maski                          *
*                                                                    *
* Na wyjsciu program zwraca obraz po przeliczeniu nowych wartosi     *
* pikseli. Po dokonaniu operacji przetwarzania maska.                *
*                                                                    *
* Warunki PRE:                                                       *
*       - prawidlowa alokacja obrazu                                 *
**********************************************************************/

int maska(t_obraz *obraz,int *wsp){
  int **kopia=alokuj(obraz->wymx,obraz->wymy);
  /*Asercja. Czy udalo sie zaalokowac pamiec?*/
  if(kopia==NULL){fprintf(stderr,"Plik: edit2.c Funkcja: Maska Linia: 268\n");return BLAD_PAMIECI;};
  kopiuj_tab(kopia,*obraz);
  int suma=wsp[0]+wsp[1]+wsp[2]+wsp[3]+wsp[4]+wsp[5]+wsp[6]+wsp[7]+wsp[8];
  /*Zastosowanie operacji dodania i odjecia M=1 spowoduje, ze maska nie zostanie przeliczona dla krawedzi obrazu*/
    for (int i=M;i<(obraz->wymy-M);i++) {
      for (int j=M;j<(obraz->wymx-M);j++) {
        obraz->piksele[i][j]=(wsp[0]*kopia[i-M][j-M]+wsp[1]*kopia[i-M][j]+wsp[2]*kopia[i-M][j+M]+wsp[3]*kopia[i][j-M]+wsp[4]*kopia[i][j]+wsp[5]*kopia[i][j+M]+wsp[6]*kopia[i+M][j-M]+wsp[7]*kopia[i+M][j]+wsp[8]*kopia[i+M][j+M]);
        /*Nie jestem pewien czy prawidlowo ale przyjalem ze piksele nie moga miec wartosci ujemnej
        uznajac ze wartosc ujemna jest po prostu wartoscia czerni rowna 0. Natomiast normalizacja
        obejmuje tylko zakres maksymalnej dodatniej wartosci pikseli.*/
        if(obraz->piksele[i][j]<0){obraz->piksele[i][j]=0;};
      };
    };
    if(wsp[0]<0||wsp[1]<0||wsp[2]<0||wsp[3]<0||wsp[4]<0||wsp[5]<0||wsp[6]<0||wsp[7]<0||wsp[8]<0){
      /*Optymalizacje wartosci pikseli nalezy dokonac przez rozciaganie histogramu*/
      rozciaganie(obraz);
    }else{
      /*Gdy wszystkie wspolczynniki sa dodatnie to optymalizacji wartosci mozna dokonac wzorem*/
      for (int i=M;i<(obraz->wymy-M);i++) {
        for (int j=M;j<(obraz->wymx-M);j++) {
          obraz->piksele[i][j]=obraz->piksele[i][j]/(suma);
        };
      };
    };
    zwolnij(kopia,obraz->wymy);
    return WSZYSTKO_OK;
}

/*********************************************************************
*                       PROGRAM ROZCIAGANIE                          *
**********************************************************************
* Na wejsciu otrzymuje:                                              *
*    obraz  -- struktura z danymi o obrazie                          *
*                                                                    *
* Na wyjsciu program zwraca obraz po przeliczeniu nowych wartosi     *
* pikseli. Dla rozciagania histogramu do min i max szarosci.         *
*                                                                    *
* Warunki PRE:                                                       *
*       - BRAK                                                       *
**********************************************************************/

void rozciaganie(t_obraz *obraz) { /*rozciaganie histogramu*/
  int i, j, Lmin=obraz->szarosci, Lmax=0;
  for (i=0; i<obraz->wymy; i++){ /*Wyszukanie najmniejszej i najwiekszej wartosci*/
    for(j=0; j<obraz->wymx; j++){
      if(obraz->piksele[i][j]<Lmin){ Lmin=obraz->piksele[i][j];};
      if(obraz->piksele[i][j]>Lmax){ Lmax=obraz->piksele[i][j];};
    };
  };
  for (i=0; i<obraz->wymy; i++){ /*modyfikacja obrazu*/
    for(j=0; j<obraz->wymx; j++){
      obraz->piksele[i][j] = ((obraz->piksele[i][j]-Lmin)*obraz->szarosci)/(Lmax-Lmin);
    }
  }
}
