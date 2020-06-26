#include "main.h"
#include "strukt.h"


void push(t_stos *stos, int dana){
  t_elem *elem=NULL;
  elem=malloc(sizeof(t_elem)); /* tworzymy nowy element*/
  if(elem==NULL){fprintf(stderr,"Blad alokacji pamieci.");}; /* jesli zle zaalokowano*/
  elem->dana=dana;
  elem->nastepny=stos->head;
  stos->head=elem;
}

int pop(t_stos *stos,int *dana){
  t_elem *elem;

  if(stos->head!=NULL){
    *dana=stos->head->dana;
    elem=stos->head;
    stos->head=stos->head->nastepny;
    free(elem);
  }else{
    return 0;
  };
  return OK;
}

void fullprint(t_stos stos){
  printf("Początek kolejki ->  ");
  while(stos.head!=NULL){
    printf("%d ",stos.head->dana);
    stos.head=stos.head->nastepny;
  };
  printf("\n");
}

void print(t_stos stos){
  printf("Na poczatku -> ");
  if(stos.head!=NULL){
    printf("%d\n",stos.head->dana);
 };
}

int reverse(t_stos *stos){
int in_1,in_2;

  if(pop(stos,&in_2)){
    if(pop(stos,&in_1)){
      push(stos,in_2);
      push(stos,in_1);
      return OK;
    }else{
      fprintf(stderr,"Za malo argumentow na stosie \n");
      push(stos,in_1);
      return ZA_MALO;
    };
  }else{
    fprintf(stderr,"Brak argumentow na stosie \n");
    return BRAK;
  };
}

int dubluj(t_stos *stos){
int dana;
  if(pop(stos,&dana)){
    push(stos,dana);
    push(stos,dana);
    return OK;
	}else{
	  fprintf(stderr,"Brak argumentow na stosie \n");
    return BRAK;
  };
}
