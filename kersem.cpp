#include "semaphor.h"
#include "define.h"
#include "kersem.h"
#include "pcb.h"
#include "semq.h"
#include "schedule.h"
#include <iostream.h>

KernelSem *s[100];

KernelSem::KernelSem (int init){
	value = init;
	if(sid == 0){
		for(int i = 0; i < 100; i++){
			s[i] = 0;
		}
	}
	semid = sid++;
	s[semid] = this;
	semQueue = new SemQueue();
}

KernelSem::~KernelSem (){
	if(semQueue != 0) signalAll();
	delete semQueue;
}

void KernelSem::signalAll(){
	while(value++ < 0){
		PCB* temp = semQueue->get();
		temp->state = PCB::RDY;
		temp->ret = 1;
		Scheduler::put(temp);
	}
}

int KernelSem::wait (Time maxTimeToWait){
	value--;
	if(value < 0){
		running->state = PCB::BLK;
		running->maxTimeToWait = maxTimeToWait;
		this->semQueue->put((PCB*)running);
		dispatch();
	}
	else running->ret = 1;

	return running->ret;
}

void KernelSem::signal(){
	if(value++ < 0){
		PCB* temp = semQueue->get();
		temp->state = PCB::RDY;
		temp->ret = 1;
		Scheduler::put(temp);
	}
}
