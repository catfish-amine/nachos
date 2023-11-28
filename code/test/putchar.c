#include "syscall.h"
/*

Test de l'appel système PutChar.

Ecrit un ensemble de caractères sur la console.
Ce test permet de vérifier si l'appel système fonctionne correctement.

Pour lancer le test, se placer dans le répertoire code, puis effectuer les commandes :
  > make
  > ./userprog/nachos -x test/putchar

*/

// Ecrit le caractère c ainsi que les n suivants sur la console.
void print(char c, int n){
    int i;
    for(i=0; i<n; i++) {
        PutChar(c + i);
    }
    PutChar('\n');
}

int main() {
    print('a',6);
    print('d',5);
    //Halt();
}
