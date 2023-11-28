#include "syscall.h"

/*

Teste pour la question 2.1
Nous testons l'appel de PutString dans deux threads différents.

Pour lancer le test, se placer dans le répertoire code et entrer les commandes suivantes :
  > make
  > ./userprog/nachos -x test/verrouString

*/

void print(void *arg)
{
  PutString("ABCD"); 
  ThreadExit();
}


int main() {
  ThreadCreate(&print, 0);
  PutString("EFGH"); 
  return 0;
}
