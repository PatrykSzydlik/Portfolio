#include "main.h"
#include "edit.h"



/*********************************************************************
*                      PROGRAM NEGATYW                               *
**********************************************************************
* Na wejsciu otrzymuje:                                              *
*    braz[][]  -- oryginalny obraz, ktorego negatyw ma obliczyc      *
*    wymx,wymy -- wymiary obrazu                                     *
*    szarosci  -- wartosc maksymalne szarosci pikseli                *
*                                                                    *
* Na wyjsciu program zmienia oryginalny obraz tworzac jego negatyw   *
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
*    obraz[][]  -- oryginalny obraz, ktorego piksele ma obliczyc     *
*    kopia[][]  -- kopie obrazu, ktora sluzy do obliczen             *
*    wymx,wymy -- wymiary obrazu                                     *
*    szarosci  -- wartosc maksymalne szarosci pikseli                *
*    opcja,promien -- sluza do wyboru rodzaju i poziomu rozmycia     *
*                                                                    *
* Program tworzy kopie oryginalnego obrazu i na jej                  *
* podstawie dokonuje obliczen aby wyliczyc rozmyte piksele i         *
* zapisac ich wartosc w oryginalnej tablicy obraz[][]                *
*                                                                    *
* Na wyjsciu zwraca obraz[][] po rozmyciu.                           *
**********************************************************************/



void rozmycie(t_obraz *obraz,int kopia[][MAX],char opcja[WYBOR],int promien){
  int suma=0;
  for (int i=0;i<obraz->wymy;i++) {
    for (int j=0;j<obraz->wymx;j++) {
      kopia[i][j]=obraz->piksele[i][j];
    };
  };
  for (int i=0;i<obraz->wymy;i++) {
    for (int j=0;j<obraz->wymx;j++) {
      for (int k=promien;k>=(-1*promien);k--) {
	if(opcja[0]=='1'){
	  if( (i+k)>=0 && (i+k)<obraz->wymy ){
	    suma=suma+kopia[i+k][j];
	  }else{
	    suma=suma+kopia[i][j];};
	}else if(opcja[0]=='2'){
	  if( (j+k)>=0 && (j+k)<obraz->wymx ){
	    suma=suma+kopia[i][j+k];
	  }else{
	    suma=suma+kopia[i][j];};
	};	
      };
      obraz->piksele[i][j]=(suma/(2*promien+1));
      suma=0;
    };
  };	    
}


/*********************************************************************
*                      PROGRAM PROGOWANIE                            *
**********************************************************************
* Na wejsciu otrzymuje:                                              *
*    braz[][]  -- oryginalny obraz, ktorego piksele ma obliczyc      *
*    wymx,wymy -- wymiary obrazu                                     *
*    szarosci  -- wartosc maksymalne szarosci pikseli                *
*    prog      -- wartosc procentowa progu                           *
*                                                                    *
* Na wyjsciu program zwraca obraz[][] po przeliczeniu pikseli        *
* wzgledem podanego poziomu progowania obrazu.                       *
**********************************************************************/



void progowanie(t_obraz *obraz, int prog){
  prog=(prog*obraz->szarosci)/100;   
  for (int i=0;i<obraz->wymy;i++) {
    for (int j=0;j<obraz->wymx;j++) {
      if(obraz->piksele[i][j]>prog){obraz->piksele[i][j]=obraz->szarosci;}
      else{obraz->piksele[i][j]=0;};
    };
  };
}



/*********************************************************************
*                      PROGRAM KONTUROWANIE                          *
**********************************************************************
* Na wejsciu otrzymuje:                                              *
*    obraz[][]  -- oryginalny obraz, ktorego piksele ma obliczyc     *
*    kopia[][]  -- kopie obrazu, ktora sluzy do obliczen             *
*    wymx,wymy -- wymiary obrazu                                     *
*    szarosci  -- wartosc maksymalne szarosci pikseli                *
*                                                                    *
* Program tworzy kopie oryginalnego obrazu i na jej                  *
* podstawie dokonuje obliczen aby wyliczyc piksele po konturowaniu   *
* i zapisac ich wartosc w oryginalnej tablicy obraz[][]              *
*                                                                    *
* Na wyjsciu zwraca obraz[][] po konturowaniu.                       *
**********************************************************************/


void konturowanie(t_obraz *obraz,int kopia[][MAX]){
  for (int i=0;i<obraz->wymy;i++) {
    for (int j=0;j<obraz->wymx;j++) {
      kopia[i][j]=obraz->piksele[i][j];
    };
  };
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
}
