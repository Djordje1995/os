#ifndef DEFINE_H_
#define DEFINE_H_

#include "pcb.h"
#include "kersem.h"
#include "idle.h"
#include "IVTEntry.h"

//#define lock asm sti
#define lock asm{pushf; cli;}
#define unlock asm { popf; }
//#define unlock asm cli

extern volatile unsigned int lockFlag;

#define lockCout lockFlag=0;
#define unlockCout lockFlag=1;\
if (ccr) {\
	dispatch();\
}

extern PCB* p[100];
extern volatile PCB* running;
extern Idle* idle;
extern KernelSem* s[100];
extern IVTEntry* IVTable[256];

extern volatile int counter;
extern volatile int ccr;
extern volatile int retToMain;
extern int pom;

extern int g;
extern int count;

extern unsigned msp;
extern unsigned mss;
extern unsigned mbp;

#endif
