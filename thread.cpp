#include "thread.h"
#include "pcb.h"
#include "define.h"
#include "schedule.h"
#include "timer.h"
#include <iostream.h>


Thread::Thread(StackSize stackSize, Time timeSlice){
#ifndef BCC_BLOCK_IGNORE
	lock;
#endif
	myPCB = new PCB(this,stackSize,timeSlice);
#ifndef BCC_BLOCK_IGNORE
	unlock;
#endif
}

Thread::~Thread(){
#ifndef BCC_BLOCK_IGNORE
	lock;
#endif
	if(this->myPCB->tId != 0){
		waitToComplete();
		delete myPCB;
	}
#ifndef BCC_BLOCK_IGNORE
	unlock;
#endif
}

void Thread::start(){
#ifndef BCC_BLOCK_IGNORE
	lock;
#endif
	myPCB->state = PCB::RDY;
	myPCB->createStack();
	if(myPCB->tId != 0){
		Scheduler::put(myPCB);
	}
#ifndef BCC_BLOCK_IGNORE
	unlock;
#endif
}

void Thread::waitToComplete(){
#ifndef BCC_BLOCK_IGNORE
	lock;
#endif
	/*if(this->myPCB->tId == 0) { unlock; return; }
	if(this == 0) { unlock; return; }
	if(this->myPCB == running) { unlock; return; }
	if(this->myPCB->state == PCB::FIN) { unlock; return; }*/
	if(this->myPCB->tId != 0 && this != 0 && this->myPCB != running && this->myPCB->state != PCB::FIN){
		running->state = PCB::BLK;
		this->myPCB->queue->put((PCB*)running);
		dispatch();
	}
#ifndef BCC_BLOCK_IGNORE
	unlock;
#endif
}

ID Thread::getId() { return myPCB->tId; }

ID Thread::getRunningId(){ return running->tId; }

Thread* Thread::getThreadById(ID id){
	return PCB::getThreadById(id);
}

void dispatch(){
#ifndef BCC_BLOCK_IGNORE
	lock;
#endif
	ccr = 1;
	timer();
#ifndef BCC_BLOCK_IGNORE
	unlock;
#endif
}
