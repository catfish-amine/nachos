#ifdef CHANGED
#include "userthread.h"
#include "bitmap.h"

struct arg_tuple {
  int func;
  int arg;
};

static void StartUserThread(void *schmurtz) {
  int i;
  for (i = 0; i < NumTotalRegs; i++)
    machine->WriteRegister(i, 0);
  
  struct arg_tuple *thread_tuple = (struct arg_tuple *) schmurtz;
  machine->WriteRegister(PCReg, thread_tuple->func);
  machine->WriteRegister(4, thread_tuple->arg);
  machine->WriteRegister(NextPCReg, machine->ReadRegister(PCReg) + 4);
  machine->WriteRegister(StackReg, currentThread->space->AllocateUserStack(currentThread->GetPlace()));
  machine->WriteRegister(31, 0);
  free(schmurtz);
  machine->Run();
}

int do_ThreadCreate(int f, int arg) {
  int place = currentThread->space->bitmap->Find();//Check for an available place
  if (place == -1) {

    currentThread->space->getLock()->Acquire();
    currentThread->space->dimNumThread();
    currentThread->space->getLock()->Release();
    //return -1 when we fail to start the thread
    return -1;
  }

  Thread *newThread = new Thread("myThread");
  newThread->SetPlace(place);

  if (!newThread)
    return -1;
  
  struct arg_tuple *thread_tuple = (struct arg_tuple*) malloc(sizeof(struct arg_tuple));
  thread_tuple->func = f;
  thread_tuple->arg = arg;
  newThread->Start(StartUserThread, thread_tuple);

  return 0;
}

void do_ThreadExit() {
  currentThread->space->getLock()->Acquire();
  currentThread->space->dimNumThread(); 
  currentThread->space->bitmap->Clear(currentThread->GetPlace());
  currentThread->space->getLock()->Release();
  
  currentThread->Finish();
}
#endif
