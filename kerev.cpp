#include <iostream.h>
#include "schedule.h"
#include "pcb.h"
#include "thread.h"
#include "nit.h"
#include "define.h"
#include "timer.h"
#include "kersem.h"
#include "kerev.h"

KernelEv::KernelEv (IVTNo ivtNo){
	ivtEntry = ivtNo;
	myEvent = 0;
	value = 0;
	myPCB = (PCB*)running;
	IVTable[ivtEntry]->kernelEvent = this;
}

KernelEv::~KernelEv (){
	IVTable[ivtEntry]->kernelEvent = 0;
}

void KernelEv::wait (){
	if((PCB*)running == myPCB){
		if(!value){
			value = 1;
			running->state = PCB::BLK;
			dispatch();
		}
	}
}

void KernelEv::signal(){
	if(value){
		value = 0;
		myPCB->state = PCB::RDY;
		Scheduler::put(myPCB);
	}
}
