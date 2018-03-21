#ifndef PCB_H_
#define PCB_H_

#include "thread.h"
#include "queue.h"

static int id = 0;
class Thread;
class Queue;

class PCB{

public:
	PCB(Thread* myThread, StackSize stackSize, Time timeSlice);
	~PCB();
	ID tId;
	Thread *myThread;
	unsigned int sp, ss, bp;
	unsigned *stack;
	StackSize stackSize;
	Time timeSlice;
	static const int NEW, RDY, BLK, FIN;
	volatile int state;
	void createStack();
	Thread* getThread();
	Queue *queue;
	static Thread *getThreadById(ID id);
	static void wrapper();
	Time maxTimeToWait;
	int ret;
};


#endif
