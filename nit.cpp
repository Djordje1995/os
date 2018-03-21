#include "nit.h"
#include "thread.h"
#include "pcb.h"
#include "queue.h"
#include <iostream.h>
#include "define.h"
#include "kersem.h"

void Nit::run() {
	if(running->tId == 0){
		while(1){}
	}
	else{
		for (int i =0; i < 30; ++i) {
			lockCout;
			cout<<"u "<<running->tId<<"   i = "<<i<<endl;
			unlockCout;
			if(running->tId == 3 && i == 2)
				s[0]->wait(40);
			if(running->tId == 2 && i == 2)
				s[1]->wait(60);
			if(running->tId == 1 && i == 2)
				s[0]->wait(30);
			if(running->tId == 3 && i == 2)
				s[1]->wait(80);
			if(running->tId == 2 && i == 2)
				s[0]->wait(60);
			if(running->tId == 1 && i == 2)
				s[1]->wait(100);
			for (int k = 0; k<10000; ++k)
			for (int j = 0; j <20000; ++j);
		}
	}
	lockCout;
	cout<<"kraj!"<<endl;
	unlockCout;
}

Nit::~Nit(){}
