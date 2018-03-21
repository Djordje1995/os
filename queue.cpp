#include "queue.h"
#include "define.h"
#include "pcb.h"
#include <iostream.h>

Queue::Queue(){
#ifndef BCC_BLOCK_IGNORE
	lock;
#endif
	head = tail = 0;
#ifndef BCC_BLOCK_IGNORE
	unlock;
#endif
}

Queue::~Queue(){
#ifndef BCC_BLOCK_IGNORE
	lock;
#endif
	Elem *stari;
	while (head){
		stari = head;
		head = head->next;
		delete stari;
	}
#ifndef BCC_BLOCK_IGNORE
	unlock;
#endif
}

void Queue::put(PCB *pcb){
#ifndef BCC_BLOCK_IGNORE
	lock;
#endif
	Elem *novi = new Elem(pcb);
	if (!head) head = tail = novi;
	else{
		for (Elem *pom = head; pom; pom = pom->next){
			if (pom->pcb == pcb) {
#ifndef BCC_BLOCK_IGNORE
				unlock;
#endif
				return;
			}
		}
		tail->next = novi;
		tail = tail->next;
	}
#ifndef BCC_BLOCK_IGNORE
	unlock;
#endif
}

PCB* Queue::get(){
	if (head == 0) return 0;
#ifndef BCC_BLOCK_IGNORE
	lock;
#endif
	Elem *pom = head;
	head = head->next;
#ifndef BCC_BLOCK_IGNORE
	unlock;
#endif
	return pom->pcb;
}

Elem* Queue::getHead(){
	return head;
}
