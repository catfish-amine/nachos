#ifdef CHANGED

#include "utility.h"
#include "system.h"
#include "pageprovider.h"


PageProvider::PageProvider(int num){
    bitmap = new BitMap(num);
}

PageProvider::~PageProvider(){
    delete bitmap;
}

int 
PageProvider::GetEmptyPage(){
    int page = bitmap->Find();
    int page2 = page*PageSize;
    memset(machine->mainMemory+page2,0,PageSize);
    return page;
}

void
PageProvider::ReleasePage(int page){
    bitmap->Clear(page);
}

int 
PageProvider::NumAvailPage(){
    return bitmap->NumClear();
}
#endif //CHANGED
