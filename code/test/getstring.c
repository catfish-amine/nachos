#include "syscall.h"

/*

Test de l'appel système GetString.

Demande à l'utilisateur d'entrer une chaine de caractères sur la console, et la reécrire.
Si l'utilisateur écrit une chaine plus grande que 20, seuls les 20 premiers caractères
seront affichés.

Pour lancer le test, se placer dans le répertoire code, puis effectuer les commandes :
  > make
  > ./userprog/nachos -x test/getstring

*/

int main() {
  char s[20];
  PutString("Entrez une chaine de caractères de longueur 20 ou moins :\n");
  GetString(s, 20);
  PutString("Vous avez écrit : ");
  PutString(s);
  return 0;
}
