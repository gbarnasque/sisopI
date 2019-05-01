#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/support.h"
#include "../include/cthread.h"
#include "../include/cdata.h"

#define ERRO -9;

#define ALTA 0
#define MEDIA 1
#define BAIXA 2

int main(){
	char *name;
	int size = 74;
	name = malloc(size);
	cidentify(name, size);
	printf("%s", name);

}

int ccreate (void* (*start)(void*), void *arg, int prio) {
	return ERRO;
}

int csetprio(int tid, int prio) {
	return ERRO;
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


