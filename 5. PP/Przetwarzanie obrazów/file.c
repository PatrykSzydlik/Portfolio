#include "main.h"
#include "file.h"



/************************************************************************************
 * Funkcja wczytuje obraz PGM z pliku do tablicy       	       	       	       	    *
 *										    *
 * \param[in] plik_we uchwyt do pliku z obrazem w formacie PGM			    *
 * \param[out] obraz_pgm tablica, do ktorej zostanie zapisany obraz		    *
 * \param[out] wymx szerokosc obrazka						    *
 * \param[out] wymy wysokosc obrazka						    *
 * \param[out] szarosci liczba odcieni szarosci					    *
 * \param[out] komunikat zmienna ktora sluzy do obslugi komunikatow w menu          *
 *                                                                                  *
 * \return liczba wczytanych pikseli						    *
 ************************************************************************************/


int czytaj(FILE *plik_we,t_obraz *obraz,int *komunikat) {
  char buf[DL_LINII];      /* bufor pomocniczy do czytania naglowka i komentarzy */
  int znak;                /* zmienna pomocnicza do czytania komentarzy */
  int koniec=0;            /* czy napotkano koniec danych w pliku */
  int i,j,bajt;

  /*Sprawdzenie czy podano prawidłowy uchwyt pliku */
  if (plik_we==NULL) {
    fprintf(stderr,"Blad: Nie podano uchwytu do pliku\n");
    *komunikat=BRAK_UCHWYTU;
    return(0);
  }

  /* Sprawdzenie "numeru magicznego" - powinien być P2 lub P5 */
  
  if (fgets(buf,DL_LINII,plik_we)==NULL)   /* Wczytanie pierwszej linii pliku do bufora */
    {
      koniec=1;                            /* Nie udalo sie? Koniec danych! */
      *komunikat=PUSTY_PLIK;
      fprintf(stderr,"Blad: Pierwsza linia pusta, nie udalo sie odczytac formatu.");
	};                             

  if ( (buf[0]!='P') || (buf[1]!='2'&& buf[1]!='5' && buf[1]!='3') || koniec) {  /* Czy jest magiczne "P2 albo P5 albo P3"? */
    fprintf(stderr,"Blad: To nie jest plik PGM\n");
    *komunikat=ZLY_FORMAT;
    return(0);
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
    fprintf(stderr,"Blad: Brak wymiarow obrazu lub liczby stopni szarosci\n");
    *komunikat=BRAK_WYMIAROW;
    return(0);
  };
  if(obraz->wymy<0 || obraz->wymx<0 || obraz->szarosci<0){
    *komunikat=ZLE_PARAMETRY;
    fprintf(stderr,"Blad: Niewlasciwe parametry obrazu\n");
    return(0);
  };


/* Alokacja dynamicznej tablicy pikseli. A dokladniej jest to tablica jednowymiarowa przechowujaca wskazniki na tablice jednowymiarowe pikseli. Dzieki temu możemy odwolywac sie do pikseli obrazu tak jak to robilismy wczesniej w tablicy statycznej.*/


obraz->piksele = malloc(obraz->wymy*sizeof(int*));
for(int y=0; y<obraz->wymy;y++){
obraz->piksele[y]=malloc(obraz->wymx*sizeof(int));
};


  /* Pobranie obrazu i zapisanie w tablicy obraz_pgm*/

for (i=0;i<obraz->wymy;i++) {
    for (j=0;j<obraz->wymx;j++) {
      if(obraz->wariant[1]=='2'){
	if (fscanf(plik_we,"%d",&obraz->piksele[i][j])!=1) {
	fprintf(stderr,"Blad: Niewlasciwe parametry obrazu\n");
	*komunikat=ZLE_PARAMETRY;
	return(0);
	};

	/* Tutaj wprowadzilem troche zmian aby program prawidlowo wczytywal obrazy pgm w wariancie P5 */
	
      }else if(obraz->wariant[1]=='5'){         
	bajt=fgetc(plik_we);
	if(bajt==EOF && feof(plik_we)==0){
	  fprintf(stderr,"Blad: Niewlasciwe parametry obrazu\n");
	  *komunikat=ZLE_PARAMETRY;
	  return(0);
	  }else{
	  obraz->piksele[i][j]=bajt;}
	
	
      }; }
  }
  *komunikat=WSZYSTKO_DOBRZE;
  return obraz->wymx*obraz->wymy;   /* Czytanie zakonczone sukcesem    */
}                       /* Zwroc liczbe wczytanych pikseli */



/************************************************************************************
 * Funkcja zapisuje obraz PGM z pamieci do pliku       	       	       	       	    *
 *										    *
 * \param[in] obraz_pgm tablica,ktorej kopia zostanie zapisana jako nowy plik	    *
 * \param[in] wymx szerokosc obrazka						    *
 * \param[in] wymy wysokosc obrazka						    *
 * \param[in] szarosci liczba odcieni szarosci					    *
 * \param[in] wariant[] tablica pozwalajaca obsluzyc wybor uzytkownika              *
 *                                                                                  *
 *                                                                                  *
 *                                                                                  *
 * W Wyniku działania funkcji utworzony zostanie nowy plik z obrazem                *
 * Zaleznie od wyboru moze to byc PGM w wariancie P2 lub P5 (binarnym)              *
 *                                                                                  *
 * Warunki PRE zostaly sprawdzone w funkcji edytuj zanim                            *
 * wywolana zostala funkcja zapisz.                                                 *
 ************************************************************************************/


int zapisz(FILE *plik_wy,t_obraz obraz, char magiczna_liczba[]){
  char ASCI_BIT;
  int ile=1;

  /*Moga byc problemy z magiczna liczba*/ 
  fprintf(plik_wy,"%s\n%d %d %d\n",magiczna_liczba,obraz.wymx,obraz.wymy,obraz.szarosci);/*Przepisanie naglowka do nowego pliku*/
  for (int i=0;i<obraz.wymy;i++) {
    for (int j=0;j<obraz.wymx;j++) {
      if(magiczna_liczba[1]=='2'){                                      /*Wybor wariantu zapisu P5 lub P2*/
	if(obraz.szarosci>MAX_1BAJT){
	  
                   /* Zapisywanie maks 70 znakow na linie kodu*/
	  
	  if((i*obraz.wymx+j)*BAJTY2_ILE_CYFR==BAJTY2_ILE_CYFR*BAJTY2_ILE_LINIA*ile){fprintf(plik_wy,"\n");ile++;};
	  fprintf(plik_wy,"%-6.5d",obraz.piksele[i][j]);
	}else{
	  if((i*obraz.wymx+j)*BAJT1_ILE_CYFR==BAJT1_ILE_CYFR*BAJT1_ILE_LINIA*ile){fprintf(plik_wy,"\n");ile++;};
	  fprintf(plik_wy,"%-4.3d",obraz.piksele[i][j]);
	    };	
      };
      if(magiczna_liczba[1]=='5'){
	ASCI_BIT=obraz.piksele[i][j];
	fprintf(plik_wy,"%c",ASCI_BIT);
	if(i==obraz.wymy-1){fprintf(plik_wy,"\n");};                    /*Niewielka sztuczka ze zmiana miejsca postawienia endline*/
	                                              /* Sprawila ze odczyt i zapis P5 nie wymagal innej interpretacji tablicy niz P2*/
      };
    };
  };
  return obraz.wymx*obraz.wymy;   /*Zapisano pomyślnie. Zwroc liczbe wczytanych pikseli */
}



/************************************************************************************
 * Funkcja wyświetla  obraz PGM z pliku tymczasowego za pomocą programu display     *
 *										    *
 * \param[in] obraz_pgm -- tablica,ktorej kopia zostanie zapisana jako nowy plik    *
 * \param[in] wymx,wymy -- wymiary obrazka	   				    *
 * \param[in] szarosci  -- maks. szarosci piksela                                   *
 *                                                                                  *
 * W Wyniku działania funkcji wyświetlony zostanie obraz w programie display.       *
 * W tym celu program tworzy tymaczasowy plik TMP_image.pgm ,                       *
 * ktory usuwa od razu po jego wyswietleniu.                                        *
 ************************************************************************************/


void wyswietl(t_obraz obraz) {
  char tmp_name[MAX_NAZWA]="./TMP_Image.pgm";
  char polecenie[DL_LINII];  
  FILE* f;
  char magiczna_liczba[WYBOR]="P2";

   
   f=fopen(tmp_name,"w");                              /* */
   zapisz(f,obraz,magiczna_liczba);
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
