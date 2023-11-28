#include "syscall.h"

/*

Test de l'appel système GetInt.

Demande à l'utilisateur d'entrer un entier sur la console, et le reécrire.
Si l'utilisateur écrit plus d'un entier, seul le premier sera affiché.

Pour lancer le test, se placer dans le répertoire code, puis effectuer les commandes :
  > make
  > ./userprog/nachos -x test/getint

*/

int main() {
  int c;
  PutString("Entrez un entier :\n");
  GetInt(&c);
  PutString("Vous avez ecrit : ");
  PutInt(c);
  PutChar('\n');
  return 0;
}
