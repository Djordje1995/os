#include "semq.h"
#include "define.h"
#include "pcb.h"
#include <iostream.h>
#include "schedule.h"

SemQueue::SemQueue(){
#ifndef BCC_BLOCK_IGNORE
	lock;
#endif
	head = tail = 0;
#ifndef BCC_BLOCK_IGNORE
	unlock;
#endif
}

SemQueue::~SemQueue(){
#ifndef BCC_BLOCK_IGNORE
	lock;
#endif
	Selem *stari;
	while (head){
		stari = head;
		head = head->next;
		delete stari;
	}
#ifndef BCC_BLOCK_IGNORE
	unlock;
#endif
}

void SemQueue::put(PCB *pcb){
#ifndef BCC_BLOCK_IGNORE
	lock;
#endif
	Selem *novi = new Selem(pcb);
	if(novi->pcb->maxTimeToWait == 0) novi->check = 1;

	if (!head) head = tail = novi;
	else{
		if(novi->check == 1){
			for (Selem *pom = head; pom; pom = pom->next){
				if (pom->pcb == pcb) {
#ifndef BCC_BLOCK_IGNORE
					unlock;
#endif
					return; }
			}
			tail->next = novi;
			tail = tail->next;
		}
		else{
			Selem *pom = head;
			Selem *pom1 = 0;
			pom1->next = pom;
			while(pom != 0 && pom->check == 0){
				if(novi->pcb->maxTimeToWait >= pom->pcb->maxTimeToWait){
					novi->pcb->maxTimeToWait -= pom->pcb->maxTimeToWait;
				}
				else break;
				pom1 = pom;
				pom = pom->next;
			}
			if(pom == 0){
				tail->next = novi;
				tail = tail->next;
			}
			else{
				novi->next = pom;
				if(pom1 == 0) head = novi;
				else pom1->next = novi;
			}

			if(pom != 0 && pom->check == 0){
				pom->pcb->maxTimeToWait -= novi->pcb->maxTimeToWait;
			}
		}
	}
	/*Selem *pomocni = head;
	cout<<endl;
	while(pomocni){
		cout<<pomocni->pcb->maxTimeToWait<<" ";
		pomocni = pomocni->next;
	}
	cout<<endl;
	cout<<endl;*/
#ifndef BCC_BLOCK_IGNORE
	unlock;
#endif
}

PCB* SemQueue::get(){
	if (head == 0) return 0;
#ifndef BCC_BLOCK_IGNORE
	lock;
#endif
	PCB* temp = head->pcb;
	if(temp->maxTimeToWait != 0 && head->next){
		PCB* t = head->next->pcb;
		t->maxTimeToWait += temp->maxTimeToWait;
	}
	head = head->next;
#ifndef BCC_BLOCK_IGNORE
	unlock;
#endif
	return temp;
}

Selem* SemQueue::getHead(){
	return head;
}
