#include "syscall.h"

/*

Le TEST makethreads génerer un Thread appelant PutChar.

Pour lancer le test, se placer dans le répertoire code et entrer les commandes suivantes :
  > make
  > ./userprog/nachos -x test/makethreads

*/

void print(void *arg)
{
  PutChar('A'); 
  ThreadExit();
}


int main() {
  ThreadCreate(&print, 0);
  return 0;
}
