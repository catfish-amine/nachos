#ifdef CHANGED

#ifndef PAGEPROVIDER_H
#define PAGEPROVIDER_H

#include "bitmap.h"
#include "copyright.h"
#include "synch.h"

class PageProvider:public dontcopythis
{

    public:
        PageProvider(int num);
        ~PageProvider();
        int GetEmptyPage();
        void ReleasePage(int page);
        int NumAvailPage();

    private:
        BitMap *bitmap;

};

#endif //CHANGED
#endif // ADDRSPACE_H