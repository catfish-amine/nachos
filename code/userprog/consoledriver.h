#ifdef CHANGED
#ifndef CONSOLEDRIVER_H
#define CONSOLEDRIVER_H
#include "copyright.h"
#include "utility.h"
#include "console.h"

class ConsoleDriver:dontcopythis {
    public:
                    // initialize the hardware console device
    ConsoleDriver(const char *readFile, const char *writeFile);
    ~ConsoleDriver(); // clean up
    void PutChar(int ch); // Behaves like putchar(3S)
    int GetChar(); // Behaves like getchar(3S)
    void PutString(const char *s); // Behaves like fputs(3S)
    void GetString(char *s, int n); // Behaves like fgets(3S)
    void PutInt(int ch); // Behaves like putint(3S)
    void GetInt(int *n); // Behaves like putint(3S)
    int copyStringFromMachine(int from, char *to, unsigned size);
	int copyStringToMachine(int to, char *from, unsigned size);
private:
Console *console;
};

#endif // CONSOLEDRIVER_H
#endif // CHANGED
