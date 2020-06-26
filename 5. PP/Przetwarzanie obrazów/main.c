#include "main.h"
#include "edit.h"
#include "file.h"


void edytuj(t_obraz *obraz, int *edytowane, int *menu_nr, int *komunikat);
void menu(int menu_nr, int komunikat);

int main() {
  int edytowane=0; /*Zmienna ktora moze posluzyc do sprawdzenia czy zapisano zmiany*/
  t_obraz obraz;
  int odczytano=0, zapisano=0;
  FILE *plik;
  char nazwa[MAX_NAZWA];
  char wybor[WYBOR]={0}; /* zmienna obslugujaca  menu i petle while*/
  char magiczna_liczba[WYBOR];
  int menu_nr=MENU_GLOWNE,komunikat=0;

  
/******************POCZATEK PETLI MENU*****************************
***************ROZPOCZECIE DZIALANIA PROGRAMU*********************/

 do{
   menu_nr=MENU_GLOWNE;
   menu(menu_nr,komunikat);
   printf("\n Twoj wybor:  ");
   scanf("%1s",wybor);
   switch(wybor[0]){
   
      
      /*****************WCZYTYWANIE PLIKU******************/
   case '1':
     menu_nr=MENU_WCZYTAJ;
     menu(menu_nr,komunikat);
     printf("\n\n Podaj nazwe:   ");
     scanf("%s",nazwa);
     plik=fopen(nazwa,"r");
     if (plik != NULL) {       /* co spowoduje zakomentowanie tego warunku */
       odczytano = czytaj(plik,&obraz,&komunikat);
       fclose(plik);
     }else{fprintf(stderr,"\n Blad: Nie udalo sie odczytac pliku! \n");komunikat=BLAD_ODCZYTU;}
     ;break;
     
     
     /**************ZAPISYWANIE DO PLIKU*****************/
   case '2':
     if(odczytano!=0){
       menu_nr=MENU_ZAPIS;
       komunikat=0;
       do{
	 menu(menu_nr,komunikat);
	 printf("\n\n Podaj nazwe:   ");
	 scanf("%s",nazwa);
	 if((plik=fopen(nazwa,"r"))!=NULL)  /*Sprawdzenie czy obraz o podanej nazwie przypadkiem juz nie istnieje*/
	   {
	     fclose(plik);
	     fprintf(stderr, "Blad: Plik o podanej nazwie juz istnieje!");
	     komunikat=ZLA_NAZWA;
	   }else{
	    plik=fopen(nazwa,"a");  /*fopen w trybie a pozwala dopisywac plik a jesli nie istnieje to go tworzy*/
	    komunikat=MENU_ZAPIS;
	   do{
	   menu(menu_nr,komunikat);
	   printf("\n\nPodaj wariant:    ");       /* pytanie o wariant formatu PGM w jakim zapisac obraz*/
	   scanf("%s",magiczna_liczba);
	   if(magiczna_liczba[0]=='P' && (magiczna_liczba[1]=='2' || magiczna_liczba[1]=='5')){
	     zapisano=zapisz(plik,obraz,magiczna_liczba);
	     fclose(plik);
	     if(zapisano>0){
	     komunikat=WSZYSTKO_DOBRZE;
	     edytowane=0;
	     };
	   }else{
	     fprintf(stderr,"Blad: Podano zly wariant zapisu pgm.");
	     komunikat=ZLY_WARIANT;
	     menu_nr=MENU_ZAPIS;
	   };}while(zapisano==0);
	 };
       }while(zapisano==0);
       
	 }else{
       fprintf(stderr,"\n Blad: Nie wczytano zadnego pliku, ktory mozna by zapisac. Bufor jest pusty. \n");
       komunikat=BLAD_ZAPISU;
     };
     ;break;
     
     
     
     /**********************EDYCJA OBRAZOW****************/
   case '3':
     if(odczytano!=0){
       edytuj(&obraz,&edytowane,&menu_nr,&komunikat);
     }else{
       fprintf(stderr,"\n Blad: Nie wczytano zadnego pliku, ktory mozna by edytowac. Bufor jest pusty.\n");
       komunikat=BLAD_EDYCJI;
     };
     break;
     
     
     /********************WYSWIETLANIE OBRAZU*************/
   case '4':
     /* Wyswietlenie poprawnie wczytanego obraza zewnetrznym programem */
     
     if (odczytano != 0){
       wyswietl(obraz);
     }else{
       fprintf(stderr,"\n Blad: Nie wczytano zadnego pliku, ktory mozna by wyswietlic. Bufor jest pusty\n");
       komunikat=BLAD_WYSW;
     };
     break;
     
     /**********OPCJA ZAKONCZENIA PRACY PROGRAMU**********/
     
   case '5':
     if(edytowane!=0){
       menu_nr=CZY_KONIEC;                  /* Jesli plik byl edytowany i nie zapisano zmian */
                                            /* To zapytaj uzytkownika co zrobic              */
       komunikat=0;
       do{
	 menu(menu_nr,komunikat);
	 printf("\n Wybierz (T/N):   ");
	 scanf("%1s",wybor);
	 if(wybor[0]=='N'||wybor[0]=='n'){
	   break;
	 }else if(wybor[0]=='T' || wybor[0]=='t'){
	   wybor[0]='5';
	 }else{
	   wybor[0]=0;
	   komunikat=ZLY_WYBOR;
	 };
       }while(wybor[0]!='5');
     };
     
     menu_nr=ZAKONCZ;
     komunikat=ZAKONCZ;
     menu(menu_nr,komunikat);
      break;
     
     /****************KOMENTARZ INFORMUJACY***************** 
      ***********O DOKONANIU BLEDNEGO WYBORU***************/
     
   default:
     fprintf(stderr,"\n Nie ma takiej pozycji na liscie!\n");
     komunikat=ZLY_WYBOR;
   };}while(wybor[0]!='5');
 
 /********************KONIEC PETLI********************************
  ******************ZAKONCZENIE PRACY PROGRAMU*********************/
 return 0;
 
}



/*********************************************************************
*                      PROGRAM EDYTUJ                                *
**********************************************************************
* Na wejsciu otrzymuje:                                              *
*    obraz[][]  -- ktora jest oryginalem obrazu                      *
*    wymx       -- szerokosc obrazu                                  *
*    wymy       -- wysokosc obrazu                                   *
*    szarosci   -- wartosc maks szarosci                             *
*    *edytowane -- zmienna podajaca czy obraz zostal edytowany       *
*    *menu_nr   -- zmienna do obslugi menu                           *
*    *komunikat -- zmienna do obslugi komunikatow                    *
*                                                                    *
* Na wyjsciu program wywoluje podprogramy edytujace obraz            *
* uprzednio sprawdzajac warunki PRE tych podprogramow.               *
*                                                                    *
* Warunek PRE sprawdzony w funkcji int main  (odczytano!=0).         *
**********************************************************************/



void edytuj(t_obraz *obraz, int *edytowane, int *menu_nr, int *komunikat){
  char opcja[WYBOR]={0};
  int prog; /*zmienna dla progowania*/
  int promien; /*zmienna do rozmycia o danym promieniu*/
  int kopia[MAX][MAX]; /*Kopia tablicy oryginalnej, ktora sluzy do obliczen przy rozmyciu i konturowaniu*/
  *komunikat=0;
  do{
    *menu_nr=MENU_EDYCJI;
    menu(*menu_nr,*komunikat);
    printf("\n\nTwoj wybor:   ");
    scanf("%1s",opcja);
    switch(opcja[0]){
      
    case '1':

	   /*************NEGATYW****************/	 
	   
	   negatyw(obraz);
	   *edytowane=1;
	   *komunikat=WSZYSTKO_DOBRZE;
	   break;
	       
	 case '2':

	   /***********ROZMYCIE*****************/

	   *menu_nr=MENU_ROZMYCIE;
	   *komunikat=0;

	   /* Ponizej sprawdzenie warunkow PRE funkcji rozmycie  */
	   /* Tutaj wybierany zostaje sposob rozmycia oraz wczytany promien z dozwolonego przedzialu*/
	   do{
	     menu(*menu_nr,*komunikat);
	     printf("\n\n Twoj wybor:   ");
	     scanf("%1s",opcja);
	     if(opcja[0]!='1' && opcja[0]!='2'){
	       *komunikat=ZLY_WYBOR;
	     };
	   }while(opcja[0]!='1' && opcja[0]!='2');

	   
	   
	   *komunikat=MENU_ROZMYCIE;
	   do{
	     menu(*menu_nr, *komunikat);
	     printf("\n\n Podaj wartosc:   ");
	     scanf("%d",&promien);
	     if(promien<0 || promien>ROZMYCIE_MAX){
	       *komunikat=ZLA_WARTOSC;
	     };
	   }while(promien<0 || promien>ROZMYCIE_MAX);
	     rozmycie(obraz,kopia,opcja,promien);
	     *edytowane=1;
	     *komunikat=WSZYSTKO_DOBRZE;
	     ;break;
	    
	 case '3':

	   /*********PROGOWANIE*****************/
	   *menu_nr=MENU_PROG;
	   *komunikat=0;


	   /*Sprawdzenie warunkow PRE czyli poprawnej  wartosci progu od 0 do 100 */

	   do{
	     menu(*menu_nr,*komunikat);
	     printf("\n\n Podaj wartosc:   ");
	     scanf("%d", &prog);
	     if(prog<0 || prog>PROG_MAX){
	       *komunikat=ZLA_WARTOSC;
	     };
	   }while(prog<0 || prog>PROG_MAX);
	   progowanie(obraz,prog);
	   *komunikat=WSZYSTKO_DOBRZE;
	   *edytowane=1;
	   break;
	   
	 case '4':

	   /***********KONTUROWANIE************/

	   konturowanie(obraz,kopia);
	   *edytowane=1;
	   *komunikat=WSZYSTKO_DOBRZE;
	   ;break;
	   
          /***********KOMUNIKAT O BLEDZIE***************/

    default:
      fprintf(stderr,"\n Nie ma takiej pozycji na liscie!\n");
      *komunikat=ZLY_WYBOR;
    };
  }while(opcja[0]!='5');
  
  *komunikat=0;
}



/*********************************************************************
*                      PROGRAM MENU                                  *
**********************************************************************
* Na wejsciu otrzymuje:                                              *
*    menu_nr  -- opisuje rodzaj menu ktore program ma wyswietlic     *
*    komunikat -- opisuje rodzaj komunikatu, ktory ma byc pokazany   *
*                                                                    *
* Na wyjsciu program wyswietla wybrane MENU                          *
**********************************************************************/




void menu(int menu_nr, int komunikat){

  /*Tutaj dochodzi do wyswietlenia Ekranow zakonczenia programu*/
  
  printf("\033[2J\033[1;1H");
  if(menu_nr==ZAKONCZ){
    printf("\n ______________________________________ \n");
    printf("|                                      |\n");
    printf("|      Koniec dzialania programu.      |\n");
    printf("|      Dziekuje za skorzystanie!       |\n");
    printf("|______________________________________|\n\n");	
  }else if(menu_nr==CZY_KONIEC){
    printf("\n ________________________________________________ \n");
    printf("|                                                |\n");
    printf("|      NIE ZAPISANO ZMIAN W OBRAZIE !!!          |\n");
    printf("|      CZY NA PEWNO CHCESZ WYJSC Z PROGRAMU?     |\n");
    printf("|________________________________________________|\n");
    if(komunikat==ZLY_WYBOR){
      printf("|                                                |\n");
      printf("|                  Zla odpowiedz!                |\n");
      printf("| Musisz wybrac 'T'-jesli tak lub 'N'-jesli nie. |\n");
      printf("|________________________________________________|\n\n");
    };
  }else{
    for(int i=1;i<=20;i++){

      /* Ponizszy kod sluzy do wyswietlenia linii uzytych we wszystkich menu */
      /* Sa to glowne brzegi ramki oraz przerwy miedzy opcjami do wyboru     */
      
      
      if(i==1){printf(" __________________________________________________________ \n");
      }else if( i==4 || i==5 || i==18 || i==20){printf("|__________________________________________________________|\n");
      }else if(i%2==0 && i<18 && i!=4){printf("|                                                          |\n");
      }else if(i==3){
	switch(menu_nr){
	case MENU_GLOWNE: printf("|                       MENU  GLOWNE                       |\n");break;
	case MENU_WCZYTAJ: printf("|                    WCZYTYWANIE OBRAZU                    |\n");break;
	case MENU_ZAPIS: printf("|                    ZAPISYWANIE OBRAZU                    |\n");break;
	case MENU_EDYCJI: printf("|                      EDYCJA  OBRAZU                      |\n");break;
	case MENU_ROZMYCIE: printf("|                     ROZMYCIE  OBRAZU                     |\n");break;
      case 32: printf("|                    PROGOWANIE  OBRAZU                    |\n");break;
	};
      }else if(i>6 && i<20 && i%2==1){
	if(i!=19){

	  /*Ponizej znajduje sie lista mozliwych do wyswietlenia ekranow MENU zalezna od paramteru menu_nr*/
	  
	  switch(menu_nr){
	  case MENU_GLOWNE:
	    switch(((i-5)/2)){
	    case 1:
	      printf("|          1 - WCZYTAJ                                     |\n");
	      break;
	    case 2:
	      printf("|          2 - ZAPISZ                                      |\n");
	      break;
	    case 3:
	      printf("|          3 - EDYCJA                                      |\n");
	      break;
	    case 4:
	      printf("|          4 - WYSWIETL                                    |\n");
	      break;
	    case 5:
	      printf("|          5 - ZAKONCZ DZIALANIE                           |\n");
	      break;
	    default:
	      printf("|                                                          |\n");
	    };
	    break;
	    
	  case MENU_WCZYTAJ:
	    if(i==11){
	      printf("|        PODAJ PELNA NAZWE OBRAZU W FORMACIE PGM,          |\n");
	    }else if(i==13){
	      printf("|        KTORY CHCESZ WCZYTAC.                             |\n");
	    }else{
	      printf("|                                                          |\n");
	    };
	    break;
	    
	  case MENU_ZAPIS:
	    
	    if(i==11){
	      if(komunikat==0){
		printf("|      PODAJ PELNA NAZWE POD JAKA CHCESZ ZAPISAC           |\n");
	      }else if(komunikat==MENU_ZAPIS || komunikat==ZLY_WARIANT){
		printf("|        PODAJ W JAKIM WARIANCIE CHCESZ ZAPISAC            |\n");
	      }else if(komunikat==ZLA_NAZWA){
		printf("|    PODAJ PONOWNIE NAZWE POD JAKA CHCESZ ZAPISAC OBRAZ    |\n");
	      };
	    }else if(i==13){
	      if(komunikat==0){
		printf("|      EDYTOWANY WCZESNIEJ OBRAZ PGM.                      |\n");
	      }else if(komunikat==MENU_ZAPIS || komunikat==ZLY_WARIANT){
		printf("|        NOWO UTWORZONY OBRAZ PGM. (P2 lub P5)             |\n");
	      }else if(komunikat==ZLA_NAZWA){
		printf("|     (WYBIERZ TAKA KTORA JESZCZE NIE ISTNIEJE )           |\n");
	      };
	    }else{
	      printf("|                                                          |\n");
	    };
	  break;
	  
	  
	  case MENU_EDYCJI:
	    
	    switch(((i-5)/2)){
	    case 1:
	      printf("|          1 - NEGATYW                                     |\n");
	      break;
	    case 2:
	      printf("|          2 - ROZMYCIE                                    |\n");
	      break;
	    case 3:
	      printf("|          3 - PROGOWANIE                                  |\n");
	    break;
	    case 4:
	      printf("|          4 - KONTUROWANIE                                |\n");
	      break;
	    case 5:
	      printf("|          5 - POWROT                                      |\n");
	      break;
	    default:
	      printf("|                                                          |\n");
	    };
	    break;
	    
	  case MENU_ROZMYCIE:
	    
	    
	    if(i==9){
	      if(komunikat==0||komunikat==ZLY_WYBOR){
		printf("|        WYBIERZ SPOSOB ROZMYCIA OBRAZU                    |\n");
	      }else{
		printf("|                                                          |\n");
	      };
	    }else if(i==11){
	      if(komunikat==0||komunikat==ZLY_WYBOR){
		printf("|              1 - ROZMYCIE PIONOWE                        |\n");
	      }else if(komunikat==MENU_ROZMYCIE||komunikat==ZLA_WARTOSC){
		printf("|       TERAZ PODAJ PROMIEN ROZMYCIA OBRAZU                |\n");
	      };
	    }else if(i==13){
	      if(komunikat==0||komunikat==ZLY_WYBOR){
		printf("|              2 - ROZMYCIE POZIOME                        |\n");
	      }else{
		printf("|           (WARTOSC Z PRZEDZIALU 0-10)                    |\n");
	      };
	    }else{
	      printf("|                                                          |\n");
	    };
	    break;
	    
	  case MENU_PROG:
	    if(i==11){
	      printf("|     PODAJ WARTOSC PROCENTOWA (od 0 do 100) JAKA          |\n");
	    }else if(i==13){
	      printf("|     MA STANOWIC PROG W ODNIESIENIU DO MAX SZAROSCI       |\n");
	    }else{
	      printf("|                                                          |\n");
	    };
	    break;
	    
	    
	    
	  };

	  /* Tutaj znajduje sie lista komunikatow o bledach (lub o ich braku) ktora wyswietla sie w interfejsie*/
	  /* Zastosowalem ja aby moc wykorzystac odswiezane menu z obsluga informacji o bledach w terminalu    */
	  /*  Pomimo tego wszystkie bledu sa i tak wypisywane na wyjscie stderr aby mozna bylo przekierowac strumien */

	}else{
	  switch(komunikat){
	  case WSZYSTKO_DOBRZE: printf("|    Ostatnia operacja wykonana poprawnie! :)              |\n");break;
	  case BLAD_ODCZYTU: printf("|   !!!  BLAD ODCZYTU: Nie udalo sie odczytac pliku  !!!   |\n");break;
	  case BRAK_UCHWYTU: printf("|   !!!  BLAD ODCZYTU: Nie podano uchwytu do pliku !!!     |\n");break;
	  case PUSTY_PLIK: printf("|   !!!  BLAD ODCZYTU: Pierwsza linia jest pusta !!!       |\n");break;
	  case ZLY_FORMAT: printf("|   !!!  BLAD ODCZYTU: Zly format. To nie jest PGM !!!     |\n");break;
	  case BRAK_WYMIAROW: printf("|   !!!  BLAD ODCZYTU: Brakuje ktoregos z parametrow !!!   |\n");break;
	  case ZLE_PARAMETRY: printf("|  !!!  BLAD ODCZYTU: Parametry obrazu sa niepoprawne !!!  |\n");break;
	  case BLAD_ZAPISU: printf("|   !!!  BLAD ZAPISU: Brak danych do zapisania. !!!        |\n");break;
	  case ZLA_NAZWA: printf("|  !!!  BLAD ZAPISU: Plik o takiej nazwie juz istnieje !!! |\n");break;
	  case ZLY_WARIANT: printf("|  !!!  BLAD ZAPISU: Podany wariant jest nieprawidlowy !!! |\n");break;
	  case BLAD_EDYCJI: printf("|  !!!  BLAD EDYCJI: Brak danych do edycji !!!             |\n");break;
	  case ZLY_WYBOR: printf("|  !!!  BLAD: Nie ma takiej pozycji w menu !!!             |\n");break;
	  case ZLA_WARTOSC: printf("|  !!!  BLAD EDYCJI: Podano wartosc spoza przedzialu !!!   |\n");break;
	  case BLAD_WYSW: printf("| !!!  BLAD WYSWIETLANIA: Brak danych do wyswietlenia !!!  |\n");break;
	  default:printf("|                                                          |\n");
	  };
	};
      };
    };
  };
}






