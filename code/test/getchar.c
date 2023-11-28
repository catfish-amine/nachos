#include "syscall.h"

/*

Test de l'appel système GetChar.

Demande à l'utilisateur d'entrer un caractère sur la console, et le reécrire.
Si l'utilisateur écrit plus d'un caractère, seul le premier sera affiché.

Pour lancer le test, se placer dans le répertoire code, puis effectuer les commandes :
  > make
  > ./userprog/nachos -x test/getchar

*/

int main() {
  char c;
  PutString("Entrez un caractere :\n");
  c = GetChar();
  PutString("Vous avez ecrit : ");
  PutChar(c);
  PutChar('\n');
  return 0;
}
