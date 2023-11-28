#include "syscall.h"

/*
Teste pour la question 2.3
Le test plusieursthreads génerer un troisième thread.
Prenons une variable volatile allant de 0 a 8 exclu. Chaque Thread affiche 8 'a'.
Pour lancer le test, se placer dans le répertoire code et entrer les commandes suivantes :
  > make
  > ./userprog/nachos -x test/plusieursthreads1

*/

void print(void *arg)
{
  volatile int i;
  for (i = 0; i < 8; i++)
    PutChar('a');
  
  ThreadExit();
}


int main() {
  ThreadCreate(&print, 0);
  ThreadCreate(&print, 0);
  return 0;
}