#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/cthread.h"
#include "../include/cdata.h"

#define ERRO -9
#define OK 0

#define PRIO_ALTA 0
#define PRIO_MEDIA 1
#define PRIO_BAIXA 2

TCB_t *runningThread;
PFILA2 highPriorityQueue, mediumPriorityQueue, lowPriorityQueue;
PFILA2 bloqueados;

ucontext_t despachante;

int checkPrio(int prio){
	int retorno;
	if(prio < PRIO_ALTA || prio > PRIO_BAIXA){
		retorno = ERRO;
	}
	else{
		retorno = OK;
	}
	return retorno;
}

int changeFilaPorPrioridade(void *thread, int prio){
	int retorno;
	PFILA2 pFila2 = NULL;

	if(prio == PRIO_ALTA){
		pFila2 = highPriorityQueue;
	}
	else if(prio == PRIO_MEDIA)
	{
		pFila2 = mediumPriorityQueue;
	}
	else if(prio == PRIO_BAIXA){
		pFila2 = lowPriorityQueue;
	}
	
	if(AppendFila2(pFila2, thread) == 0){
		retorno = OK;
	}
	else{
		retorno = ERRO;
	}

	return retorno;
}

int main(){
	char *name;
	int size = 74;
	name = malloc(size);
	cidentify(name, size);
	printf("%s", name);

	csem_t *steste = (csem_t*) malloc(sizeof(csem_t));
	if(csem_init(steste, 4) == 0){
		printf("Deu-lhe, %d\n", steste->count);
	}

}

int ccreate (void* (*start)(void*), void *arg, int prio) {
	return ERRO;
}

int csetprio(int tid, int prio){
	TCB_t* thread;
	int oldPrio;

	if(checkPrio(prio) == ERRO){
		return ERRO;
	}
	else{
		if(runningThread->tid == tid){
			runningThread->prio = prio;
			return OK;
		}
		if(FirstFila2(highPriorityQueue) == 0){
			do{
				thread = (TCB_t *) GetAtIteratorFila2(highPriorityQueue);
				if(thread->tid == tid){
					oldPrio = thread->prio;
					thread->prio = prio;
					if(changeFilaPorPrioridade(thread, thread->prio) == OK){
						if(DeleteAtIteratorFila2(highPriorityQueue) == 0){
							return OK;
						}
						else{
							thread->prio = oldPrio;
							changeFilaPorPrioridade(thread, thread->prio);
							return ERRO;
						}
					}
					else{
						return ERRO;
					}
				}
				NextFila2(highPriorityQueue);

			} while(thread != NULL);
		}
		if(FirstFila2(mediumPriorityQueue) == 0){
			do{
				thread = (TCB_t *) GetAtIteratorFila2(mediumPriorityQueue);
				if(thread->tid == tid){
					oldPrio = thread->prio;
					thread->prio = prio;
					if(changeFilaPorPrioridade(thread, thread->prio) == OK){
						if(DeleteAtIteratorFila2(mediumPriorityQueue) == 0){
							return OK;
						}
						else{
							thread->prio = oldPrio;
							changeFilaPorPrioridade(thread, thread->prio);
							return ERRO;
						}
					}
					else{
						return ERRO;
					}
				}
				NextFila2(mediumPriorityQueue);
			} while(thread != NULL);
		}
		if(FirstFila2(lowPriorityQueue) == 0){
			do{
				thread = (TCB_t *) GetAtIteratorFila2(lowPriorityQueue);
				if(thread->tid == tid){
					oldPrio = thread->prio;
					thread->prio = prio;
					if(changeFilaPorPrioridade(thread, thread->prio) == OK){
						if(DeleteAtIteratorFila2(lowPriorityQueue) == 0){
							return OK;
						}
						else{
							thread->prio = oldPrio;
							changeFilaPorPrioridade(thread, thread->prio);
							return ERRO;
						}
					}
					else{
						return ERRO;
					}
				}
				NextFila2(lowPriorityQueue);
			} while(thread != NULL);
		}
		if(FirstFila2(bloqueados) == 0){
			do{
				thread = (TCB_t *) GetAtIteratorFila2(bloqueados);
				if(thread->tid == tid){
					thread->prio = prio;
					return OK;
				}
				NextFila2(bloqueados);
			} while(thread != NULL);
		}
	}
	return ERRO;
}

int cyield(void) {
	int retorno;
	TCB_t* oldThread;

	retorno = changeFilaPorPrioridade(runningThread, runningThread->prio);
	if(retorno == ERRO){
		runningThread->state = PROCST_EXEC;
	}
	else{
		runningThread->state = PROCST_APTO;
		oldThread = runningThread;
		runningThread = NULL;
		swapcontext(&oldThread->context, &despachante);
	}
	
	return retorno;
}

int cjoin(int tid) {
	return ERRO;
}

int csem_init(csem_t *sem, int count) {
	int retorno;

	PFILA2 newFila = (PFILA2) malloc(sizeof(PFILA2));;
	if(CreateFila2(newFila) == 0){
		sem->count = count;
		sem->fila = newFila;
		retorno = OK;
	}
	else{
		retorno = ERRO;
	}
	
	return retorno;
}

int cwait(csem_t *sem) {
	TCB_t* dummyThread;
	TCB_t* oldThread;

	sem->count--;
	if(sem->count <= 0){
		oldThread = runningThread;
		if(AppendFila2(bloqueados, oldThread) == 0){
			if(GetAtIteratorFila2(sem->fila) == NULL){
				if(AppendFila2(sem->fila, oldThread) == 0){
					oldThread->state = PROCST_BLOQ;
					runningThread = NULL;
					swapcontext(&oldThread->context, &despachante);
					return OK;
				}
				else{
					LastFila2(bloqueados);
					DeleteAtIteratorFila2(bloqueados);
					sem->count++;
					return ERRO;
				}
			}
			else{
				FirstFila2(sem->fila);
				dummyThread = (TCB_t *) GetAtIteratorFila2(sem->fila);
				do{
					if(oldThread->prio < dummyThread->prio){
						InsertBeforeIteratorFila2(sem->fila, oldThread);
						oldThread->state = PROCST_BLOQ;
						runningThread = NULL;
						swapcontext(&oldThread->context, &despachante);
						return OK;
					}
					NextFila2(sem->fila);
					dummyThread = (TCB_t *) GetAtIteratorFila2(sem->fila);
				} while(dummyThread != NULL);

				AppendFila2(sem->fila, oldThread);
				oldThread->state = PROCST_BLOQ;
				runningThread = NULL;
				swapcontext(&oldThread->context, &despachante);
				return OK;
			}
		}
		else{
			sem->count++;
			return ERRO;
		}
	}
	return OK;
}

int csignal(csem_t *sem) {
	return ERRO;
}

int cidentify (char *name, int size) {
	strncpy (name, "Gustavo Oliva - 00263056\nLuine Gallois - 00205954\nTiago Villa - 00219144\n", size);
	return 0;
}


