#include "timer.h"
#include "pcb.h"
#include "define.h"
#include <iostream.h>
#include "schedule.h"
#include "thread.h"
#include "kersem.h"
#include "semq.h"


void tick();

unsigned oldTimerSEG, oldTimerOFF;
unsigned tsp,tss,tbp;
volatile int ccr = 0;
volatile int counter;
int pom;
volatile int retToMain = 0;
volatile int unsigned lockFlag = 1;
volatile PCB *running;
Idle *idle;
int g;
unsigned msp;
unsigned mss;
unsigned mbp;
volatile int provera = 0;

void inic(){
#ifndef BCC_BLOCK_IGNORE
	asm{
	cli
	push es
	push ax

	mov ax, 0
	mov es, ax

	mov ax, word ptr es : 0022h
	mov word ptr oldTimerSEG, ax
	mov ax, word ptr es : 0020h
	mov word ptr oldTimerOFF, ax

	mov word ptr es : 0022h, seg timer
	mov word ptr es : 0020h, offset timer

	mov ax, oldTimerSEG
	mov word ptr es : 0182h, ax
	mov ax, oldTimerOFF
	mov word ptr es : 0180h, ax

	pop ax
	pop es

	sti
	}
#endif
};

void restore(){
#ifndef BCC_BLOCK_IGNORE
	asm{
	cli
	push es
	push ax

	mov ax, 0
	mov es, ax


	mov ax, word ptr oldTimerSEG
	mov word ptr es : 0022h, ax
	mov ax, word ptr oldTimerOFF
	mov word ptr es : 0020h, ax

	pop ax
	pop es
	sti
	}
#endif
};

void interrupt timer(){
	if (!ccr ) {
		if(running->timeSlice != 0)
			{ counter--; }
		tick();
		for(int i = 0; i < 100 ; i++){
			if(s[i] == 0) break;
			s[i]->semQueue->getHead()->pcb->maxTimeToWait--;
			while(s[i]->semQueue->getHead()->pcb->maxTimeToWait == 0 && s[i]->semQueue->getHead()){
				PCB* temp = s[i]->semQueue->get();
				temp->state = PCB::RDY;
				s[i]->value++;
				temp->ret = 0;
				Scheduler::put(temp);
			}
		}/*
	#ifndef BCC_BLOCK_IGNORE
		asm int 60h;
	#endif*/
	}
	if (counter == 0 || ccr) {
		if(lockFlag){
			ccr = 0;
			if(g == 1){
#ifndef BCC_BLOCK_IGNORE
		asm {
			mov msp, sp
			mov mss, ss
			mov mbp, bp
		}
#endif
				g = 0;
			}else {
#ifndef BCC_BLOCK_IGNORE
		asm {
			mov tsp, sp
			mov tss, ss
			mov tbp, bp
		}
#endif

		running->sp = tsp;
		running->ss = tss;
		running->bp = tbp;

		if((running->state != PCB::FIN && running->state != PCB::BLK) && running->tId != 0){ Scheduler::put((PCB*)running);}
			}
		running = Scheduler::get();
		if(running == 0){
			if(retToMain || count == 1){
				running->sp = msp;
				running->ss = mss;
				running->bp = mbp;
				g = 1;
				retToMain = 1;
			}
			else{
				running = p[0];
			}
		}

		tsp = running->sp;
		tss = running->ss;
		tbp = running->bp;

		if(running->timeSlice == 0){ counter = 0;}
		else{
			counter = running->timeSlice;
		}
#ifndef BCC_BLOCK_IGNORE
		asm {
			mov sp, tsp
			mov ss, tss
			mov bp, tbp
		}
#endif
		}
		else ccr = 1;
	}
	if(!ccr){/*
		tick();
		for(int i = 0; i < 100 ; i++){
			if(s[i] == 0) break;
			//s[i]->semQueue->getHead()->pcb->maxTimeToWait--;
			while(--s[i]->semQueue->getHead()->pcb->maxTimeToWait == 0 && s[i]->semQueue->getHead()){
				PCB* temp = s[i]->semQueue->get();
				temp->state = PCB::RDY;
				s[i]->value++;
				temp->ret = 0;
				Scheduler::put(temp);
			}
		}*/
#ifndef BCC_BLOCK_IGNORE
		asm int 60h;
#endif
	}
}

