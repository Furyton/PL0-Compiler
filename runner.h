#include "def.h"
#include "PL0.h"

#define MAX_RUNNING_STACK 1024

int ALU;
int stack[MAX_RUNNING_STACK];
int top;
int pc;

void run(int entry);
int exec(Code* code);