
#include <stdio.h>
#include <string.h>
#include "../include/support.h"
#include "../include/cthread.h"
#include "../include/cdata.h"

#define MIN_PRIORITY 1
#define MAX_PRIORITY 3

int tidCounter;
PFILA2 highPriorityQueue, mediumPriorityQueue, lowPriorityQueue;

void getContext(TCB_t *tcb) {
	//Initialize new thread context
	getcontext(&tcb->context);
	tcb->context.uc_link = &returnContext;
   	tcb->context.uc_stack.ss_sp = tcb->stack;
	tcb->context.uc_stack.ss_size = sizeof(tcb->stack);	

	makecontext(&tcb->context, (void*)(*start), 1, arg);

	return tcb->context;
}

int ccreate (void* (*start)(void*), void *arg, int prio) {
	TCB_t *tcb = (TCB_t*)malloc(sizeof(TCB_t));

	tcb->tid = getTid();
	tcb->state = READY;
	tcb->prio = prio;
	tcb->context = getContext();

	return tcb->tid;
}

int csetprio(int tid, int prio) {
	return -1;
}

int cyield(void) {
	return -1;
}

int cjoin(int tid) {
	return -1;
}

int csem_init(csem_t *sem, int count) {
	return -1;
}

int cwait(csem_t *sem) {
	return -1;
}

int csignal(csem_t *sem) {
	return -1;
}

int cidentify (char *name, int size) {
	strncpy (name, "Sergio Cechin - 2017/1 - Teste de compilacao.", size);
	return 0;
}


