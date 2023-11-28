#include "syscall.h"

/*
Teste pour la question 2.1

Le TEST verrousChar nous permet de vérifier l'implémentation des verrous.


Nous testons l'appel de PutChar dans deux threads différents.

Pour lancer le test, se placer dans le répertoire code et entrer les commandes suivantes :
  > make
  > ./userprog/nachos -x test/verrouChar

*/

void print(void *arg)
{
  PutChar('b'); 
  ThreadExit();
}


int main() {
  PutChar('a'); 
  ThreadCreate(&print, 0);
  return 0;
}
