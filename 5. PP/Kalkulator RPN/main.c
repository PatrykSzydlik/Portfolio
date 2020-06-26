#include "main.h"
#include "strukt.h"
#include "kalk.h"


/*

Patryk Szydlik                 ind 248949

Kalkulator RPN

Zalaczone plik:
    - main.h
    - main.c
    - kalk.h
    - kalk.c
    - strukt.h
    -strukt.c
    - makefile

*****************************************
Update 22.01
  Do zrobienia:
   - podzial na moduly
   - prawidlowe wykonywanie dzialan

  Gotowe:
   - wyswietlanie wyniku "w"
   - usuwanie jednego elementu "u"
   - czyszczenie calego stosu clear - "c"
   - wyjscie z programu "k"
   - prawidlowo wpisuje liczbe na stos i przesuwa je

*****************************************

Update 25.01
  Bledy do poprawy:
    - rozpoznawanie znaku minus i liczby ujemnej
    - sprawdzanie kiedy wynik dzialania wychodzi poza granice wartosci inta

  Poprawione:
    - dzialania podstawowe (+ - * / )
    - dodano opcje potegowania (ograniczona dla wykladnika dodatniego)
    - asercja przed dzieleniem przez zero

 Konkluzja:
    - chyba rzeczywiście utworzenie funkcji dokonujących podstawowych operacji na liczbach
        jest dobrym pomyslem, poniewaz mozna w nich uzwglednic problem przekraczania zakresu
        ktory wymaga wielu porownan i przewidzenia kilku przypadkow
*****************************************************
Update 27.01 - Final
 Zrobione:
   - podzial na moduly
   - dodatkowe funkcje kalkulatora (pierwiastek, silnia, potega)
   - funkcje interfejsu f,p,P,d,r,c,
   - pelna funkcjonalnosc stosu pamieci
   - dodatkowa funkcjonalnosc stosu pamieci jako drugiego stosu roboczego (wszystkie operacje dzialaja)
   - mozliwosc wyswietlenia pomocy (h)
   - dzialajaca obsluga komunikatow o bledach

   */

int main(){
  int in_1;
  t_stos *stos;
  t_stos memory;
  t_stos working;
  char wczytane[BUFOR];
  int komunikat=0;


  memory.head=NULL;
  working.head=NULL; /* wskaznik na pierwszy element je zerem. Poniewaz nie ma jeszcze zadnego elementu*/

  while(komunikat!=KONIEC){ /* dopoki nie wybrano zamkniecia programu */
    printf(">> ");           /* zacheta do wpisania danych, wyswietla sie po kazdej operacji*/
    for(int i=0; i<BUFOR;i++){wczytane[i]='\0';};   /* czyszczenie wczytanych poprzednio danych */
    scanf("%s",wczytane);                              /* wczytanie nowych danych*/
    komunikat=OK;
    stos=&working;

    /* funkcja atoi, ktora byla zaproponowana na jednym z wykladow
       konwertuje ona ciag znakow ktory zawiera liczbe zapisana w ASCII na int
       liczba moze byc poprzedzona dowolna iloscia bialych znakow oraz znakiem + lub - (ale wylacznie bezposrednio)
       konczy konwersje gdy napotka pierwszy znak nie bedacy cyfra*/

    if(atoi(wczytane)!=0){    /* Gdy uda sie wczytac liczbe*/
      in_1=atoi(wczytane);
      push(stos,in_1);
    }else{                      /* Jesli nie uda sie wczytac liczby (lub wyjatek gdy wczytano zero, ktory jest rozpatrzony nizej)*/
      if(wczytane[1]=='M'){       /* Jesli ma byc wykonana operacja na stosie pamieci*/
        stos=&memory;
      };
      switch(wczytane[0]){      /*w celu wykonywania dzialan na liczbach*/
      case '+':   /* dodaj */
        komunikat=dodaj(stos);
	     break;
      case '-':   /* odejmij */
        komunikat=odejmij(stos);
	     break;
      case '*':   /* pomnoz */
      komunikat=pomnoz(stos);
	     break;
      case '/':   /* podziel */
        komunikat=podziel(stos);
	       break;
      case '^':
      komunikat=potega(stos);
	     break;
      case '~':
      komunikat=pierw_kwadr(stos);
	     break;
       case '!':
       komunikat=silnia(stos);
       break;
      case 'p':   /* wyswietl szczyt stosu */
      print(*stos);
	     break;
      case 'r':   /* zamienia kolejnosc na szczycie stosu */
      reverse(stos);
	     break;
      case 'd':   /* duplikuje liczbe bedaca na szczycie stosu */
      dubluj(stos);
	     break;
      case 'f':   /* wyswietl zawartosc stosu */
	     fullprint(*stos);
	      break;
      case 'P':   /* usun ostatnia wpisana liczbe */
	     if(pop(stos,&in_1)==0){komunikat=BRAK;};
	      break;
      case 'c':   /* wyczysc caly bufor operacji */
	      while(pop(stos,&in_1));
	    break;
      case 'M':    /* podstawowe operacje z uzyciem pamieci*/
      switch(wczytane[1]){
        case '+':   /* dodaj do pamieci */
        if(pop(&memory,&in_1)==0){in_1=0;};
        push(&memory,in_1);
        if(pop(&working,&in_1)==0){in_1=0;}else{push(&working,in_1);};
        push(&memory,in_1);
        dodaj(&memory);
        break;
        case '-':    /* odejmij z pamieci*/
        if(pop(&memory,&in_1)==0){in_1=0;};
        push(&memory,in_1);
        if(pop(&working,&in_1)==0){in_1=0;}else{push(&working,in_1);};
        push(&memory,in_1);
        odejmij(&memory);
        break;
        case 'c':   /* wyczysc pamiec */
         while(pop(&memory,&in_1));
        break;
        case 'r':  /* zwroc pamiec do stosu roboczego*/
          if(pop(&memory,&in_1)==0){
            komunikat=BRAK;
          }else{
            push(&memory,in_1);
            push(&working,in_1);
          };
        break;
        default:  /* Wypadek gdy dokonuje sie wpisania liczby bezposrednio do stosu pamieci*/
        for(int i=0; i<BUFOR-1;i++){wczytane[i]=wczytane[i+1];};
        if(atoi(wczytane)){
          in_1=atoi(wczytane);
          push(&memory,in_1);
        }else{
          if(wczytane[0]=='0'){push(&memory,in_1);};
        };
      };
      break;
      case 'q':
	komunikat=KONIEC;
	break;
      case '0': /* przypadek wyjatkowy poniewaz funkcja atoi zwraca ta sama wartosc dla 0 tak samo jak dla blednie wczytanej liczby*/

	  in_1=atoi(wczytane);
	  push(stos,in_1);
    break;
    case 'h':
printf("\n\
**************************************\n\
* Instrukcja obslugi kalkulatora RPN *\n\
**************************************\n\
\n\
Obsluga stosu:\n\
    p  -> pokazuje pierwsza liczbe na stosie \n\
    f  -> wyswietla caly stos\n\
    d  -> kopiuje pierwsza liczbe ze stosu i dodaje na stos\n\
    r  -> zamienia kolejnoscia 2 pierwsze liczby ze stosu\n\
    P  -> usuwa pierwsza liczbe ze stosu\n\
    c  -> oproznia stos\n\
    q  -> wyjscie z programu\n\
   \n\
Funkcje kalkulatora:\n\
    +  -> dodaje dwie pierwsze liczby ze stosu\n\
    -  -> odejmuje od drugiej liczby na stosie pierwsze liczbe ze stosu\n\
    *  -> mnozy dwie pierwsze liczby na stosie\n\
    /  -> dzieli druga liczbe na stosie przez pierwsza liczbe ze stosu\n\
    ~  -> oblicza pierwiastek kwadratowy z pierwszej liczby na stosie, \n\
           wynik jest czescia calkowita rzeczywistej wartosci\n\
    ^  -> oblicza wartosc drugiej liczby na stosie do potegi \n\
           o wartosci pierwszej liczby ze stosu \n\
    !  -> oblicza silnie z pierwszej liczby na stosie\n\
    \n\
Funkcje pamieci kalkulatora:\n\
   M+ -> dodaje do pierwszej liczby na stosie pamieci pierwsza liczbe ze stosu roboczego \n\
   M- -> odejmuje od pierwszej liczby ze stosu pamieci pierwsza liczbe ze stosu roboczego\n\
   Mr -> pierwsza liczbe ze stosu pamieci przepisuje na poczatek stosu roboczego\n\
   Mc -> oproznia caly stos pamieci\n\
\n\
Uwaga!\n\
Istnieje mozliwosc wykorzystania funkcji pamieci jako drugiego stosu roboczego.\n\
Kazda funkcja obslugiwana przez stos roboczy moze byc obslugiwana przez stos pamieci.\n\
Aby to wykonac nalezy bezposrednio na koncu wywolan funkcji programu dopisac litere M.\n\
Na przyklad: fM - wyswietla stos pamiec, rM - zamienia kolejnoscia liczby w pamieci itd..\n\
\n\
Dopisywanie liczb bezposrednio do stosu pamieci odbywa sie poprzez \n\
poprzedzenie danej liczby bezposrednio litera M. Np. M206 wpisze wartosc 206 do pamieci. \n\
");
    break;
      default:
      komunikat=NIE_OPCJA;
	break;
      };/*koniec switch*/
    };/*koniec if*/
   if(komunikat!=0){bledy(komunikat);};
  };/* koniec while*/
  return 0;
}




/*
************************************************
Testy.

Czesc 1.  Testy bledow.

1. Ilosc argumentow do operacji

-bash-3.2$ ./a.out
>> f
Początek kolejki ->
>> +
Brak argumentow na stosie
>> 5
>> +
Za malo argumentow na stosie
>> f
Początek kolejki ->  67197


Znaleziony blad do poprawy.

Funkcja gdy brakowalo drugiego argumentu zwracala nie wczytany (i nie zainijcowany) drugi argument zamiast pierwszego

Poprawione:

-bash-3.2$ ./a.out
>> 5
>> +
Za malo argumentow na stosie
>> f
Początek kolejki ->  5

2. Pierwiastek/silnia z ujemnej liczby

-bash-3.2$ ./a.out
>> -5
>> f
Początek kolejki ->  -5
>> ~
Nie mozna obliczyc pierwiastka z liczby ujemnej
>> !
Nie mozna obliczyc silni z liczby ujemnej


3. Potega 0 do 0 oraz dzielenie przez 0

Początek kolejki ->  0 0
>> ^
Wystapila nieoznaczonosc 0^0 . Brak okreslonej wartosci
>> f
Początek kolejki ->  0 0
>> /
Niedozwolona operacja dzielenia przez zero.

4. Niepoprawna opcja

>> g
Nie ma takiej opcji. Wpisz h aby zapoznac sie z instrukcja obslugi.


Czesc 2. Testy operacji matematycznych

1. Dodawanie

Początek kolejki ->  11 5
>> +
>> p

Na poczatku -> 16

2. Odejmowanie

Początek kolejki ->  12 16
>> -
>> p
Na poczatku -> 4

3. Mnozenie

Początek kolejki ->  3 4
>> *
>> p
Na poczatku -> 12


4. Dzielenie

Początek kolejki ->  2 12
>> /
>> p
Na poczatku -> 6


5. Silnia

Na poczatku -> 6
>> !
>> p
Na poczatku -> 720


6. Pierwiastek

-bash-3.2$ ./a.out
>> 81
>> ~
>> f
Początek kolejki ->  9


7. Potega

Początek kolejki ->  5 9
>> ^
>> f
Początek kolejki ->  59049


Czesc 3. Testy funkcji operujacych na strukturach

1. Wyswietl pierwsza

>> 5
>> 6
>> 7
>> 8
>> p
Na poczatku -> 8


2. Wyswietl wszystkie

>> 5
>> 6
>> 7
>> 8
>> f
Początek kolejki ->  8 7 6 5


3. Usun pierwsza

>> 5
>> 6
>> 7
>> 8
>> f
Początek kolejki ->  8 7 6 5
>> P
>> f
Początek kolejki ->  7 6 5


4. Usun wszystkie

>> 5
>> 6
>> 7
>> 8
>> f
Początek kolejki ->  8 7 6 5
>> c
>> f
Początek kolejki ->


5. Zamien kolejnsc

>> 5
>> 6
>> 7
>> 8
>> f
Początek kolejki ->  8 7 6 5
>> r
>> f
Początek kolejki ->  7 8 6 5


6. Dubluj

Początek kolejki ->  7 8 6 5
>> d
>> f
Początek kolejki ->  7 7 8 6 5


7. Help
 wyswietla pomoc




 -bash-3.2$ ./a.out
 >> 5
 >> 6
 >> f
 Początek kolejki ->  6 5
 >> fM
 Początek kolejki ->
 >> M+
 >> fM
 Początek kolejki ->  6
 >> f
 Początek kolejki ->  6 5

 >> fM
 Początek kolejki ->  6
 >> 1
 >> f
 Początek kolejki ->  1 6 5
 >> M-
 >> fM
 Początek kolejki ->  5 


 >> f
 Początek kolejki ->  1 6 5
 >> fM
 Początek kolejki ->  5
 >> Mr
 >> f
 Początek kolejki ->  5 1 6 5
 >> fM
 Początek kolejki ->  5


 >> fM
 Początek kolejki ->  5
 >> f
 Początek kolejki ->  5 1 6 5
 >> Mc
 >> fM
 Początek kolejki ->
 >> f
 Początek kolejki ->  5 1 6 5
 >>


*/
