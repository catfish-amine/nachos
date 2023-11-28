#ifdef CHANGED
#include "forkexec.h"
#include "system.h"

void StartUserProc(void *schmurtz)
{ 
  //printf("test num:  11\n");
  currentThread->space->InitRegisters();
  //printf("test num:  12\n");
  currentThread->space->RestoreState();
  //printf("test num:  13\n");
  currentThread->SetPlace(0);
  //printf("test num:  14\n");
  machine->Run();
  //printf("test num:  15\n");
}

int do_ForkExec(const char* forkName) {
      
      printf("dans forkexec: %s\n",forkName);
      OpenFile *executable = fileSystem->Open (forkName);
      if(executable == NULL)
      {
        delete executable;
        machine->WriteRegister(2,0);
        return -1;
      }

      else{
        printf("test num:  1\n");
        Thread *newThread = new Thread("thread_2");
        //printf("test num:  2\n");
        AddrSpace *newSpace;
        //printf("test num:  3\n");
        currentThread->space = newSpace;
        //printf("test num:  4\n");
        newSpace = new AddrSpace(executable);
        //printf("test num:  5\n");
        delete executable;
        //printf("test num:  6\n");
        newThread->Start(StartUserProc,newSpace);
        //printf("test num:  7\n");
        processNum++;
        //printf("test num:  8\n");
        machine->WriteRegister(2,processNum);
        //printf("test num:  9\n");
        return 0;

      }
}



#endif // CHANGED