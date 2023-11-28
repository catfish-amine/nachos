#include "syscall.h"

/*
Teste pour la question 2.4
Le test plusieursthreads génerer beaucoup de threads.

Pour lancer le test, se placer dans le répertoire code et entrer les commandes suivantes :
  > make
  > ./userprog/nachos -x test/plusieursthreads2

*/

void print(void *arg)
{
  volatile int i;
  for (i = 0; i < 10; i++)
    PutChar('a');
  
  ThreadExit();
}


int main() {
  ThreadCreate(&print, 0);
  ThreadCreate(&print, 0);
  ThreadCreate(&print, 0);
  ThreadCreate(&print, 0);
  /*5éme thread ne se lance pas*/
  ThreadCreate(&print, 0);
  return 0;
}
