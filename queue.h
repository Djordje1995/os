#ifndef QUEUE_H_
#define QUEUE_H_

#include "pcb.h"

class PCB;

class Elem{
public:
	PCB *pcb;
	Elem *next;
	Elem(PCB *p){ pcb = p; next = 0; }
	~Elem(){}
};

class Queue{
private:
	Elem *head;
	Elem *tail;

public:
	Queue();
	~Queue();
	void put(PCB *pcb);
	PCB* get();
	Elem* getHead();
};

#endif
