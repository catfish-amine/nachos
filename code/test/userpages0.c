#include "syscall.h"

//Le test makeThreads :
// 	- Le Thread principal va créer plusieurs threads fils
// 	- Les threads fils vont chacun afficher une string avec leur numéro
//  - Le Thread principal attend que chaque threads ait fini de s'exécuter avant de quitter


void print(char* string){
  PutString(string);
}


int
main()
{
print("3 \n");
print("ass \n");
print("ba \n");
}
