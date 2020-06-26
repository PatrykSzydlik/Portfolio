#include "main.h"
#include "file.h"
#include "arg.h"






/************************************************************************************
 * Funkcja wczytuje obraz PGM z pliku do tablicy       	       	       	       	    *
 *										                                                              *
 *		Wejscie:					                                                            *
 *				- obraz - struktura danych w ktorej zapiszemy obraz	                      *
 *				- plik-we - plik z ktorego mamy wczytac obraz                             *
 *										                                                              *
 *    PRE:                                                                          *
 *			Prawidlowy uchwyt do plik		                                                *
 *		  							                                                              *
 *										                                                              *
 * Zapisuje informacje o obrazie w strukturze danych		                            *
 *										                                                              *
 * Return zwraca wartosci bledow jesli takie wystapia                               *
 ************************************************************************************/


int czytaj(FILE *plik_we,t_obraz *obraz) {
  char buf[DL_LINII];      /* bufor pomocniczy do czytania naglowka i komentarzy */
  int znak;                /* zmienna pomocnicza do czytania komentarzy */
  int koniec=0;            /* czy napotkano koniec danych w pliku */
  int i,j,bajt;
   /*Asercja. Sprawdzenie czy podano prawidłowy uchwyt pliku */
  if (plik_we==NULL) {
    fprintf(stderr,"Plik: file2.c   Funkcja: czytaj   Linia: 33\n");
    return(BRAK_UCHWYTU);
  };
  /* Sprawdzenie "numeru magicznego" - powinien być P2 lub P5 */
  if (fgets(buf,DL_LINII,plik_we)==NULL)   /* Wczytanie pierwszej linii pliku do bufora */
    {
      koniec=1;                            /* Nie udalo sie? Koniec danych! */
      fprintf(stderr,"Plik: file2.c   Funkcja: czytaj   Linia: 38\n");
      return(PUSTY_PLIK);
	};
  if ( (buf[0]!='P') || (buf[1]!='2'&& buf[1]!='5' && buf[1]!='3') || koniec) {  /* Czy jest magiczne "P2 albo P5 albo P3"? */
    fprintf(stderr,"Plik: file2.c   Funkcja: czytaj   Linia: 44\n");
    return(ZLY_FORMAT);
  }
  obraz->wariant[0]='P';
  obraz->wariant[1]=buf[1];

  /* Pominiecie komentarzy */
  do {
    if ((znak=fgetc(plik_we))=='#') {         /* Czy linia rozpoczyna sie od znaku '#'? */
      if (fgets(buf,DL_LINII,plik_we)==NULL)  /* Przeczytaj ja do bufora                */
	koniec=1;                   /* Zapamietaj ewentualny koniec danych */
    }  else {
      ungetc(znak,plik_we);                   /* Gdy przeczytany znak z poczatku linii */
    }                                         /* nie jest '#' zwroc go                 */
  } while (znak=='#' && !koniec);   /* Powtarzaj dopoki sa linie komentarza */
                                    /* i nie nastapil koniec danych         */

  /* Pobranie wymiarow obrazu i liczby odcieni szarosci */

/* Tutaj chyba jakoś trzeba przekazać adres a nie wartość ale nie wiem*/

if (fscanf(plik_we,"%d %d %d",&obraz->wymx,&obraz->wymy,&obraz->szarosci)!=3) {
    fprintf(stderr,"Plik: file2.c   Funkcja: czytaj   Linia: 66\n");
    return(B_BRAKWARTOSCI);
  };
  if(obraz->wymy<0 || obraz->wymx<0 || obraz->szarosci<0){
    fprintf(stderr,"Plik: file2.c   Funkcja: czytaj   Linia: 70\n");
    return(B_BLEDNAWARTOSCI);
  };


/* Alokacja dynamicznej tablicy pikseli. A dokladniej jest to tablica jednowymiarowa przechowujaca wskazniki na tablice jednowymiarowe pikseli. Dzieki temu możemy odwolywac sie do pikseli obrazu tak jak to robilismy wczesniej w tablicy statycznej.*/

if(obraz->wariant[1]=='3'){
 obraz->piksele = alokuj(KOLOR*obraz->wymx,obraz->wymy);
}else{
 obraz->piksele = alokuj(obraz->wymx,obraz->wymy);
};

if(obraz->piksele==NULL){
  fprintf(stderr,"Plik: file2.c   Funkcja: czytaj   Linia: 84\n");
  return BLAD_PAMIECI;
};


  /* Pobranie obrazu i zapisanie w tablicy obraz_pgm*/


if(obraz->wariant[1]=='3'){
  for (i=0;i<obraz->wymy;i++) {
    for (j=0;j<KOLOR*obraz->wymx;j++) {
      if (fscanf(plik_we,"%d",&obraz->piksele[i][j])!=1) {
	       fprintf(stderr,"Plik: file2.c   Funkcja: czytaj   Linia: 96\n");
	        return B_BLEDNAWARTOSCI;
        };
      };
    };
  };

if(obraz->wariant[1]=='2'){
  for (i=0;i<obraz->wymy;i++) {
    for (j=0;j<obraz->wymx;j++) {
	     if (fscanf(plik_we,"%d",&obraz->piksele[i][j])!=1) {
	        fprintf(stderr,"Plik: file2.c   Funkcja: czytaj   Linia: 107\n");
	         return(B_BLEDNAWARTOSCI);
         };
       };
     };
};

	/* Tutaj wprowadzilem troche zmian aby program prawidlowo wczytywal obrazy pgm w wariancie P5 */


if(obraz->wariant[1]=='5'){
for (i=0;i<obraz->wymy;i++) {
    for (j=0;j<obraz->wymx;j++) {
	bajt=fgetc(plik_we);
	if(bajt==EOF && feof(plik_we)==0){
	  fprintf(stderr,"Plik: file2.c   Funkcja: czytaj   Linia: 122\n");
	  return(B_BLEDNAWARTOSCI);
	  }else{
	  obraz->piksele[i][j]=bajt;
	 };
	 };
};
};
  fclose(plik_we);
  return(WSZYSTKO_OK);   /* Czytanie zakonczone sukcesem    */
}


/************************************************************************************
 * Funkcja zapisuje obraz z pamieci do pliku       	       	       	          	    *
 *										                                                              *
 *   Wejscie:                                                                       *
 *       - plik_wy  - wskaznik na plik zapisu                                       *
 *       - obraz    - struktura danych obrazu                                       *
 *                                                                                  *
 *                                                                                  *
 *                                                                                  *
 * W Wyniku działania funkcji utworzony zostanie nowy plik z obrazem                *
 * Zaleznie od wyboru moze to byc PGM w wariancie P2 lub P5 (binarnym)              *
 * Albo jesli wczytany zostal plik PPM i nie edytowano go to mozna go zapisac.      *                                                                            *
 *                                                                                  *
 *                                                                                  *
 * Warunki PRE: sprawdzenie czy plik zostal otwarty poprawnie                       *
 ************************************************************************************/


int zapisz(FILE *plik_wy,t_obraz obraz){
  char ASCI_BIT;
  int ile=1;
  /*Asercja. Czy udalo sie otworzyc plik do zapisu*/
  if(plik_wy==NULL){
    fprintf(stderr,"Plik: file2.c  Funkcja: zapisz   Linia: 158 \n");
    return BRAK_UCHWYTU;
  };
  /*Moga byc problemy z magiczna liczba*/
  fprintf(plik_wy,"%c%c\n%d %d %d\n",obraz.wariant[0],obraz.wariant[1],obraz.wymx,obraz.wymy,obraz.szarosci);/*Przepisanie naglowka do nowego pliku*/
  if(obraz.wariant[1]=='2'){                                      /*Wybor wariantu zapisu P5 lub P2*/
	   if(obraz.szarosci>MAX_1BAJT){
       for (int i=0;i<obraz.wymy;i++) {
         for (int j=0;j<obraz.wymx;j++) {
                   /* Zapisywanie maks 70 znakow na linie kodu*/
	                  if((i*obraz.wymx+j)*BAJTY2_ILE_CYFR==BAJTY2_ILE_CYFR*BAJTY2_ILE_LINIA*ile){fprintf(plik_wy,"\n");ile++;};
	                   fprintf(plik_wy,"%-6.5d",obraz.piksele[i][j]);
          };
        };
	    }else{
        for (int i=0;i<obraz.wymy;i++) {
          for (int j=0;j<obraz.wymx;j++) {
	           if((i*obraz.wymx+j)*BAJT1_ILE_CYFR==BAJT1_ILE_CYFR*BAJT1_ILE_LINIA*ile){fprintf(plik_wy,"\n");ile++;};
	            fprintf(plik_wy,"%-4.3d",obraz.piksele[i][j]);
          };
        };
	    };
  };

  if(obraz.wariant[1]=='5'){
      for (int i=0;i<obraz.wymy;i++) {
        for (int j=0;j<obraz.wymx;j++) {
	         ASCI_BIT=obraz.piksele[i][j];
	          fprintf(plik_wy,"%c",ASCI_BIT);
	           if(i==obraz.wymy-1){fprintf(plik_wy,"\n");};
         };
       };                    /*Niewielka sztuczka ze zmiana miejsca postawienia endline*/
	                     /* Sprawila ze odczyt i zapis P5 nie wymagal innej interpretacji tablicy niz P2*/
  };

  if(obraz.wariant[1]=='3'){
    if(obraz.szarosci>MAX_1BAJT){
      for (int i=0;i<obraz.wymy;i++) {
        for (int j=0;j<KOLOR*obraz.wymx;j++) {
	         if((i*KOLOR*obraz.wymx+j)*BAJTY2_ILE_CYFR==BAJTY2_ILE_CYFR*BAJTY2_ILE_LINIA*ile){fprintf(plik_wy,"\n");ile++;};
	          fprintf(plik_wy,"%-6.5d",obraz.piksele[i][j]);
          };
        };
	   }else{
       for (int i=0;i<obraz.wymy;i++) {
         for (int j=0;j<KOLOR*obraz.wymx;j++) {
	          if((i*KOLOR*obraz.wymx+j)*BAJT1_ILE_CYFR==BAJT1_ILE_CYFR*BAJT1_ILE_LINIA*ile){fprintf(plik_wy,"\n");ile++;};
	           fprintf(plik_wy,"%-4.3d",obraz.piksele[i][j]);};};
	   };
  };
  fclose(plik_wy);
  return WSZYSTKO_OK;   /*Zapisano pomyślnie */
}



/************************************************************************************
 * Funkcja wyświetla  obraz PGM z pliku tymczasowego za pomocą programu display     *
 *						                                                          				    *
 *	Wejscie:	                                                          				    *
 *			- obraz - struktura danych o obrazie 			                       				    *
 *                                                                                  *
 * W Wyniku działania funkcji wyświetlony zostanie obraz w programie display.       *
 * W tym celu program tworzy tymaczasowy plik TMP_image.pgm ,                       *
 * ktory usuwa od razu po jego wyswietleniu.                                        *
 ************************************************************************************/


void wyswietl(t_obraz obraz) {
  char tmp_name[]="./TMP_Image.pgm";
  char polecenie[DL_LINII];
  FILE* f;


   f=fopen(tmp_name,"w");                              /* */
   zapisz(f,obraz);
   fclose(f);


     /* bufor pomocniczy do zestawienia polecenia */

   strcpy(polecenie,"display ");  /* konstrukcja polecenia postaci */
   strcat(polecenie,tmp_name);     /* display "nazwa_pliku" &       */
   strcat(polecenie," &");
   printf("%s\n",polecenie);      /* wydruk kontrolny polecenia */
   system(polecenie);             /* wykonanie polecenia        */

   sleep(1);                      /* Wymagana przerwa aby display uruchomil obraz zanim ten sie usunie*/
   remove(tmp_name);

}
