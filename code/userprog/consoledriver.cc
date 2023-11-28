#ifdef CHANGED
#include "copyright.h"
#include "system.h"
#include "consoledriver.h"
#include "synch.h"

static Semaphore *readAvail;
static Semaphore *writeDone;
static Lock *lock_char;
static Lock *lock_int;

static void ReadAvailHandler(void *arg) { (void) arg; readAvail->V(); }
static void WriteDoneHandler(void *arg) { (void) arg; writeDone->V(); }

ConsoleDriver::ConsoleDriver(const char *in, const char *out)
{
readAvail = new Semaphore("read avail", 0);
writeDone = new Semaphore("write done", 0);
console = new Console (in, out, ReadAvailHandler, WriteDoneHandler, 0);
lock_char = new Lock("Char Lock");
lock_int = new Lock("int Lock");
}

ConsoleDriver::~ConsoleDriver()
{
delete console;
delete writeDone;
delete readAvail;
delete lock_char;
delete lock_int;
}

void ConsoleDriver::PutChar(int ch)
{
    lock_char->Acquire();
    console->TX(ch);
    writeDone->P ();
    lock_char->Release();
}
int ConsoleDriver::GetChar()
{
  lock_char->Acquire();
	readAvail->P();
  int r = console->RX();
  lock_char->Release();
  return r;
}
void ConsoleDriver::PutString(const char s[])
{
	for (int i=0; s[i] != '\0'; i++)
	{
		PutChar(s[i]);
	}
}

void ConsoleDriver::GetString(char *s, int n)
{
  for (int i = 0; i < n; i++) {
    int c = GetChar();
    if (c == EOF) {
      s[i] = '\0';
      break;
    }

    s[i] = c;
    
    if (c == '\n') {
      s[i + 1] = '\0';
      break;
    }
  }
  s[n] = '\0';
}
void ConsoleDriver::PutInt(int s)
{
  lock_int->Acquire();
  char buff[MAX_STRING_SIZE];
  int j = snprintf(buff, 4, "%d", s);
  PutString(buff);
  lock_int->Release();
}

void ConsoleDriver::GetInt(int *n)
{
  lock_int->Acquire();
  char buff[MAX_STRING_SIZE];
  GetString(buff,MAX_STRING_SIZE);
  int j =sscanf(buff, "%d",n);
  lock_int->Release();
}

int ConsoleDriver::copyStringFromMachine(int from, char *to, unsigned size)
{
      	unsigned int read = 0;
      	int c;
      	char ch;
    	int i = 0;
       	while(read < size){
        	machine->ReadMem(from, 1, &c);
          	ch = (char) c;
       		if (ch == '\0'){
                i = 1;
                break;
             }
        	from++;
            to[read++] = ch;
         }

        to[read] = '\0';
  
           return i;
  }

int ConsoleDriver::copyStringToMachine(int to, char *from, unsigned size)
{
  int i = 0;
  for (; (unsigned) i < size; i++) {
    machine->WriteMem(to + i, 1, from[i]);
    if (from[i] == '\0')
      break;
  }
  return i;
}

#endif // CHANGED*/