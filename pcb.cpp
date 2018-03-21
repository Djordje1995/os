#include "pcb.h"
#include "define.h"
#include <iostream.h>
#include <dos.h>
#include "schedule.h"

const int PCB::NEW = 0;
const int PCB::RDY = 1;
const int PCB::BLK = 2;
const int PCB::FIN = 3;

PCB* p[100];
int count = 0;

PCB::PCB(Thread *myThread, StackSize stackSize,Time timeSlice){
#ifndef BCC_BLOCK_IGNORE
	lock;
#endif
	ss = sp = bp = 0;
	tId = id++;
	count++;
	this->timeSlice = timeSlice;
	stack = 0;
	state = NEW;
	this->myThread = myThread;
	this->stackSize = stackSize/sizeof(unsigned);
	p[tId] = this;
	queue = new Queue();
	maxTimeToWait = 0;
	ret = 1;
#ifndef BCC_BLOCK_IGNORE
	unlock;
#endif
}

PCB::~PCB(){
#ifndef BCC_BLOCK_IGNORE
	lock;
#endif
	delete queue;
	delete stack;
#ifndef BCC_BLOCK_IGNORE
	unlock;
#endif
}

Thread* PCB::getThread(){
	return myThread;
}

Thread* PCB::getThreadById(ID id){
	return p[id]->myThread;
}

void PCB::wrapper(){
	running->myThread->run();
#ifndef BCC_BLOCK_IGNORE
	lock;
#endif
	running->state = PCB::FIN;
	count--;
	Elem* pom1 = running->queue->getHead();
	while(pom1){
		pom1->pcb->state = PCB::RDY;
		Scheduler::put(pom1->pcb);
		pom1 = pom1->next;
	}
	if(running->tId == 1 || count == 1) retToMain = 1;
#ifndef BCC_BLOCK_IGNORE
	unlock;
#endif
	dispatch();
}

void PCB::createStack(){
#ifndef BCC_BLOCK_IGNORE
	lock;
#endif
	stack = new unsigned[stackSize];
#ifndef BCC_BLOCK_IGNORE
	stack[stackSize - 1] = FP_SEG(myThread);	//mozda treba psw na -1 , a wraper na -2,-3, pa ostalo da rokam dole pa tek na -12
	stack[stackSize - 2] = FP_OFF(myThread);
	//stack[stackSize - 3] = FP_SEG(&dispatch);
	//stack[stackSize - 4] = FP_OFF(&dispatch);
	stack[stackSize - 5] = 0x200;
	stack[stackSize - 6] = FP_SEG(&wrapper);
	stack[stackSize - 7] = FP_OFF(&wrapper);
	ss = FP_SEG(stack + stackSize - 16);
	sp = FP_OFF(stack + stackSize - 16); //mozda 12
#endif
	bp = sp;

/*#ifndef BCC_BLOCK_IGNORE
	stack[stackSize - 1] = 0x200;
	stack[stackSize - 2] = FP_SEG(&wrapper);
	stack[stackSize - 3] = FP_OFF(&wrapper);
	ss = FP_SEG(stack + stackSize - 12);
	sp = FP_OFF(stack + stackSize - 12);
	bp = sp;
#endif*/
#ifndef BCC_BLOCK_IGNORE
	unlock;
#endif
}

