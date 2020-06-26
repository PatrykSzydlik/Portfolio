#include "main.h"
#include "edit.h"
#include "file.h"

int main(int argc, char *argv[]) {
int opcja;
int iter=0;
char argumenty[10]="0";

while((opcja=getopt(argc, argv, ":a:bc")) != -1)
{
switch(opcja)
{

case 'a':
printf("\n opcja: %c", opcja);
break;
case 'b':
printf("\n opcja: %c",opcja);break;
case 'c':
printf("\n opcja: %c",opcja);break;
case ':':
printf("\n BRAK");break;
case '?':
printf("\n CO");break;

};
};
printf("\n Koniec\n");


}
