#include "syscall.h"

/*

Test de l'appel système PutString.

Ecrit la chaine de caractères suivie d'un retour à la ligne sur la console.

Pour lancer le test, se placer dans le répertoire code, puis effectuer les commandes :
  > make
  > ./userprog/nachos -x test/putstring
*/

void print(char* c){
    int i;
    PutString(c);
    PutChar('\n');
}

int main() {
    print("Hicham");
    print(" ");
    print("t");
    print("abcdef");
    Halt();
}