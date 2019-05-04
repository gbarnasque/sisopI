#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/cthread.h"
#include "../include/cdata.h"

#define ERRO -9

#define PRIO_ALTA 0
#define PRIO_MEDIA 1
#define PRIO_BAIXA 2

TCB_t *runningThread;
PFILA2 highPriorityQueue, mediumPriorityQueue, lowPriorityQueue;
PFILA2 bloqueados;

int checkPrio(int prio){
	if(prio < PRIO_ALTA || prio > PRIO_BAIXA){
		return ERRO;
	}
	return prio;
}

int main(){
	char *name;
	int size = 74;
	name = malloc(size);
	cidentify(name, size);
	printf("%s", name);

	csetprio(1,3);

}

int ccreate (void* (*start)(void*), void *arg, int prio) {
	return ERRO;
}

int csetprio(int tid, int prio){
	int retorno = ERRO;
	TCB_t* thread;

	if(checkPrio(prio) == ERRO){
		retorno = ERRO;
	}
	else{
		if(runningThread->tid == tid){
			runningThread->prio = prio;
			retorno = 0;
		}
		if(FirstFila2(highPriorityQueue) == 0){
			thread = (TCB_t *) GetAtIteratorFila2(highPriorityQueue);
			while(thread != NULL){
				if(thread->tid == tid){
					thread->prio = prio;
					retorno = 0;
				}
				thread = (TCB_t *) GetAtNextIteratorFila2(highPriorityQueue);
			}
		}
		if(FirstFila2(mediumPriorityQueue) == 0){
			thread = (TCB_t *) GetAtIteratorFila2(mediumPriorityQueue);
			while(thread != NULL){
				if(thread->tid == tid){
					thread->prio = prio;
					retorno = 0;
				}
				thread = (TCB_t *) GetAtNextIteratorFila2(mediumPriorityQueue);
			}
		}
		if(FirstFila2(lowPriorityQueue) == 0){
			thread = (TCB_t *) GetAtIteratorFila2(lowPriorityQueue);
			while(thread != NULL){
				if(thread->tid == tid){
					thread->prio = prio;
					retorno = 0;
				}
				thread = (TCB_t *) GetAtNextIteratorFila2(lowPriorityQueue);
			}
		}
		if(FirstFila2(bloqueados) == 0){
			thread = (TCB_t *) GetAtIteratorFila2(bloqueados);
			while(thread != NULL){
				if(thread->tid == tid){
					thread->prio = prio;
					retorno = 0;
				}
				thread = (TCB_t *) GetAtNextIteratorFila2(bloqueados);
			}
		}
	}
	return retorno;
}

int cyield(void) {
	return ERRO;
}

int cjoin(int tid) {
	return ERRO;
}

int csem_init(csem_t *sem, int count) {
	return ERRO;
}

int cwait(csem_t *sem) {
	return ERRO;
}

int csignal(csem_t *sem) {
	return ERRO;
}

int cidentify (char *name, int size) {
	strncpy (name, "Gustavo Oliva - 00263056\nLuine Gallois - 00205954\nTiago Villa - 00219144\n", size);
	return 0;
}


