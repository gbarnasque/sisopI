TCB_t *runningThread;

void initializeLists() {
	if (highPriorityQueue == NULL && mediumPriorityQueue == NULL && lowPriorityQueue == NULL) {
		//Initialize lists
		highPriorityQueue = (PFILA2)malloc(sizeof(FILA2));
        mediumPriorityQueue = (PFILA2)malloc(sizeof(FILA2));
        lowPriorityQueue = (PFILA2)malloc(sizeof(FILA2));
	}
}



int dispatcher() {
	initializeLists();
}

int getTid() {
	if (tid == NULL) {
		return 1;
	} else {
		return tid++;
	}
}