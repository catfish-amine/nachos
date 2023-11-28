#include "syscall.h"
/*

Test de l'appel système PutChar.

Ecrit un  entier sur la console.
Ce test permet de vérifier si l'appel système fonctionne correctement.

Pour lancer le test, se placer dans le répertoire code, puis effectuer les commandes :
  > make
  > ./userprog/nachos -x test/putint

*/

// Ecrit le caractère c ainsi que les n suivants sur la console.
void print(int c, int n){
    int i;
    for(i=0; i<n; i++) {
        PutInt(c + i);
        PutChar(' ');
    }
    PutChar('\n');
}

int main() {
    print(10,6);
    print(60,5);
    Halt();
}
