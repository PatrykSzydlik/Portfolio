#ifndef main_h
#define main_h

#include <stdio.h>
#include <stdlib.h>

#define OK 42
#define BUFOR 80


#define KONIEC -1
#define ZA_MALO -2
#define BRAK -3
#define DZ_ZERO -4
#define PIERW_UJEM -5
#define SILN_UJEM -6
#define NIE_OPCJA -7

typedef struct elem {
  int dana;
  struct elem *nastepny;
} t_elem;

typedef struct stos {
  t_elem *head;
} t_stos;



#endif
