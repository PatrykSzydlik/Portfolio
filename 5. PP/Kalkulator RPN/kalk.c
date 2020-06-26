#include "main.h"
#include "strukt.h"
#include "kalk.h"


int potega(t_stos *stos){
int pods;
int wyk;
int wynik=1;

  if(pop(stos,&wyk)){
	  if(pop(stos,&pods)==0){
	    push(stos,wyk);
      return ZA_MALO;
	  };
	}else{
    return BRAK;
  };
for(int i=0;i<wyk;i++){
  wynik=wynik*pods;
};
push(stos,wynik);
return OK;
}

int pierw_kwadr(t_stos *stos){
  float c;
  float eps=0.1;
  float prev;
  float current;
  float diff;
  int dana;

  if(pop(stos,&dana)){
	  if(dana<0){
	    push(stos,dana);
      return PIERW_UJEM;
    };
	}else{
    return BRAK;
  };
  c=(float) dana;
	prev = c;
      do{
	       current=0.5*(prev+(c/prev));
 	       diff = prev - current;
	       if(diff<0){diff=-1*diff;};
       }while (diff >= eps);
         prev=current;
	dana = (int)prev;
  push(stos,dana);
  return OK;
}

int dodaj(t_stos *stos){
 int in_1,in_2;
 int wynik;

  if(pop(stos,&in_2)){
    if(pop(stos,&in_1)){
      wynik=in_1+in_2;
      push(stos,wynik);
      return OK;
    }else{
      push(stos,in_2);
      return ZA_MALO;
    };
  }else{
    return BRAK;
  };
}

int odejmij(t_stos *stos){
  int in_1,in_2;
  int wynik;

  if(pop(stos,&in_2)){
	  if(pop(stos,&in_1)){
	    wynik=in_1-in_2;
	    push(stos,wynik);
      return OK;
    }else{
	    push(stos,in_2);
      return ZA_MALO;
    };
	}else{
    return BRAK;
  };
}

int pomnoz(t_stos *stos){
  int in_1,in_2;
  int wynik;

  if(pop(stos,&in_2)){
	  if(pop(stos,&in_1)){
	    wynik=in_1*in_2;
	    push(stos,wynik);
      return OK;
    }else{
	    push(stos,in_2);
      return ZA_MALO;
    };
	}else{
    return BRAK;
  };
}

int podziel(t_stos *stos){
  int in_1,in_2;
  int wynik;

  if(pop(stos,&in_2)){
	  if(in_2!=0){
	    if(pop(stos,&in_1)){
	      wynik=in_1/in_2;
	      push(stos,wynik);
        return OK;
	    }else{
	      push(stos,in_2);
        return ZA_MALO;
      };
	  }else{
      return DZ_ZERO;
    };
	}else{
    return BRAK;
  };
}

int silnia(t_stos *stos){
  int dana;
  int wynik=1;

  if(pop(stos,&dana)){
	  if(dana<0){
	    push(stos,dana);
      return SILN_UJEM;
    };
	}else{
    return BRAK;
  };
for(int i=1;i<=dana;i++){
  wynik=wynik*i;
}
push(stos,wynik);
return OK;

}

void bledy(int komunikat){
switch(komunikat){
case KONIEC:
printf("Dziekuje za skorzystanie z programu ;)\n");
break;
case ZA_MALO:
fprintf(stderr,"Za malo argumentow na stosie \n");
break;
case BRAK:
fprintf(stderr,"Brak argumentow na stosie \n");
break;
case DZ_ZERO:
fprintf(stderr,"Niedozwolona operacja dzielenia przez zero.\n");
break;
case PIERW_UJEM:
fprintf(stderr,"Nie mozna obliczyc pierwiastka z liczby ujemnej\n");
break;
case SILN_UJEM:
fprintf(stderr,"Nie mozna obliczyc silni z liczby ujemnej\n");
break;
case NIE_OPCJA:
fprintf(stderr,"Nie ma takiej opcji. Wpisz h aby zapoznac sie z instrukcja obslugi.\n");
break;
}

}
