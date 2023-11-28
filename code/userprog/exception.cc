// exception.cc 
//      Entry point into the Nachos kernel from user programs.
//      There are two kinds of things that can cause control to
//      transfer back to here from user code:
//
//      syscall -- The user code explicitly requests to call a procedure
//      in the Nachos kernel.  Right now, the only function we support is
//      "Halt".
//
//      exceptions -- The user code does something that the CPU can't handle.
//      For instance, accessing memory that doesn't exist, arithmetic errors,
//      etc.  
//
//      Interrupts (which can also cause control to transfer from user
//      code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "syscall.h"

#ifdef CHANGED
#include "userthread.h"
#include "forkexec.h"

#include <unistd.h>
#endif // CHANGED
//----------------------------------------------------------------------
// UpdatePC : Increments the Program Counter register in order to resume
// the user program immediately after the "syscall" instruction.
//----------------------------------------------------------------------
static void
UpdatePC ()
{
    int pc = machine->ReadRegister (PCReg);
    machine->WriteRegister (PrevPCReg, pc);
    pc = machine->ReadRegister (NextPCReg);
    machine->WriteRegister (PCReg, pc);
    pc += 4;
    machine->WriteRegister (NextPCReg, pc);
}
static Lock *lock_processNum = new Lock("process number Lock");


//----------------------------------------------------------------------
// ExceptionHandler
//      Entry point into the Nachos kernel.  Called when a user program
//      is executing, and either does a syscall, or generates an addressing
//      or arithmetic exception.
//
//      For system calls, the following is the calling convention:
//
//      system call code -- r2
//              arg1 -- r4
//              arg2 -- r5
//              arg3 -- r6
//              arg4 -- r7
//
//      The result of the system call, if any, must be put back into r2. 
//
// And don't forget to increment the pc before returning. (Or else you'll
// loop making the same system call forever!
//
//      "which" is the kind of exception.  The list of possible exceptions 
//      are in machine.h.
//----------------------------------------------------------------------

void
ExceptionHandler (ExceptionType which)
{
    int type = machine->ReadRegister (2);
    int address = machine->registers[BadVAddrReg];

    switch (which)
      {
	case SyscallException:
          {
	    switch (type)
	      {
		case SC_Halt:
		  {
		    DEBUG ('s', "Shutdown, initiated by user program.\n");
		    interrupt->Powerdown ();
		    break;
		  }
		#ifdef CHANGED
		case SC_PutChar:
		  {
			  DEBUG('s', "PutChar\n");
			char ch = (char) machine->ReadRegister(4);
			consoledriver->PutChar(ch);
			  break;
		}
		case SC_GetChar:
		{
            DEBUG('s', "GetChar.\n");
	  		int ch = consoledriver->GetChar();
		  	if (ch == EOF) interrupt->Powerdown ();
			machine->WriteRegister(2, ch);
			break;
		}
		case SC_PutString :
		{
            DEBUG('a', "\nSystem call for PutString\n");
            char buff[MAX_STRING_SIZE];
            int from = machine->ReadRegister(4);
            int  i = consoledriver->copyStringFromMachine(from, buff, MAX_STRING_SIZE);
            consoledriver->PutString(buff);
                while (i == 0){
                        from = from  + MAX_STRING_SIZE;
                        i = consoledriver->copyStringFromMachine(from, buff, MAX_STRING_SIZE);
                        consoledriver->PutString(buff);
 
                }
                         break;
        }
		case SC_PutInt :
		{	
			DEBUG('a', "\nSystem call for PutInt\n");
            int i = machine->ReadRegister(4);
            consoledriver->PutInt(i);
			 break;
        }
		case SC_GetInt :
		{	
			DEBUG('a', "\nSystem call for PutInt\n");
			int n;
            consoledriver->GetInt(&n);
			machine->WriteRegister(2, n);
			 break;
        }
		case SC_GetString:
		{
		  
		    DEBUG('a', "\nSystem call for GetString\n");
		    char write_buf[MAX_STRING_SIZE + 1];
		    write_buf[MAX_STRING_SIZE] = '\0';
		    int written_char = 0;
		    int to = machine->ReadRegister(4);
		    int n  = machine->ReadRegister(5) - 1;
		    int nToGet;
		    bool too_long_input = true;
		    bool same_length_input = false;
		   
		    while(n > 0)
		    {
				nToGet = (n >= MAX_STRING_SIZE ? MAX_STRING_SIZE : n);
				n -= nToGet;
				consoledriver->GetString(write_buf, nToGet);
				written_char = consoledriver->copyStringToMachine(to, write_buf, nToGet);
				to += written_char;
				if (written_char < nToGet)
				{
				    too_long_input = false;
				    break;
				}
		    }

		    if ((write_buf[written_char-1] == '\n') || (write_buf[written_char-1] == '\0'))
		      same_length_input = true;

		    if (too_long_input && !same_length_input)
		    {
				int tmp;
				do {
				  tmp = consoledriver->GetChar();
				}while((tmp != '\n') && (tmp != EOF));
		    }
			break;
		}
		case SC_Exit:
		  {
              DEBUG('a', "\nSystem call for Exit\n");
              currentThread->space->getLock()->Acquire();
              currentThread->space->dimNumThread();

			  //check if last Thread
              while (currentThread->space->getNumThread() > 0) {
                currentThread->space->getLock()->Release();
                currentThread->Yield();
                currentThread->space->getLock()->Acquire();
              }

            currentThread->space->getLock()->Release();
            delete currentThread->space;

			
            lock_processNum->Acquire();
			processNum--;
			lock_processNum->Release();

			if (processNum == 0){ 

				int result = machine->ReadRegister(4);
				printf("Le programme s'est terminé avec le code de retour : %d\n", result);
				interrupt->Powerdown();
				break;
			}
		}
        case SC_ThreadCreate:
              {
				DEBUG('a', "\nSystem call for ThreadCreate\n");
				int f,arg;
             	f= machine->ReadRegister (4);
                arg = machine->ReadRegister (5);
                currentThread->space->getLock()->Acquire();
                currentThread->space->incrNumThread();
                currentThread->space->getLock()->Release();
                do_ThreadCreate(f, arg);
                break;
              }

        case SC_ThreadExit:
              {
				DEBUG('a', "\nSystem call for ThreadExit\n");
                do_ThreadExit();
                break;
              }

		case SC_ForkExec:
              {
				   	DEBUG('a', "\nSystem call for ForkExec\n ");
					char f[200];
          			int arg = machine->ReadRegister(4);
					consoledriver->copyStringFromMachine(arg,f,200);
					int res  = do_ForkExec(f);
					if (res ==-1) printf("Fail to create fork\n");
				break;
              }
		#endif // CHANGED
		default:
		  {
		    printf("Unimplemented system call %d\n", type);
		    ASSERT(FALSE);
		  }
	      }

	    // Do not forget to increment the pc before returning!
	    UpdatePC ();
	    break;
	  }

	case PageFaultException:
	  if (!address) {
	    printf("NULL dereference at PC %x!\n", machine->registers[PCReg]);
	    ASSERT (FALSE);
	  } else {
	    printf ("Page Fault at address %x at PC %x\n", address, machine->registers[PCReg]);
	    ASSERT (FALSE);	// For now
	  }
	  break;

	case ReadOnlyException:
	  printf ("Read-Only at address %x at PC %x\n", address, machine->registers[PCReg]);
	  ASSERT (FALSE);	// For now
	  break;

	case BusErrorException:
	  printf ("Invalid physical address at address %x at PC %x\n", address, machine->registers[PCReg]);
	  ASSERT (FALSE);	// For now
	  break;

	case AddressErrorException:
	  printf ("Invalid address %x at PC %x\n", address, machine->registers[PCReg]);
	  ASSERT (FALSE);	// For now
	  break;

	case OverflowException:
	  printf ("Overflow at PC %x\n", machine->registers[PCReg]);
	  ASSERT (FALSE);	// For now
	  break;

	case IllegalInstrException:
	  printf ("Illegal instruction at PC %x\n", machine->registers[PCReg]);
	  ASSERT (FALSE);	// For now
	  break;

	default:
	  printf ("Unexpected user mode exception %d %d %x at PC %x\n", which, type, address, machine->registers[PCReg]);
	  ASSERT (FALSE);
	  break;
      }
}
