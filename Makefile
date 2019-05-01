#
# Makefile de EXEMPLO
#
# OBRIGATÓRIO ter uma regra "all" para geração da biblioteca e de uma
# regra "clean" para remover todos os objetos gerados.
#
# É NECESSARIO ADAPTAR ESSE ARQUIVO de makefile para suas necessidades.
#  1. Cuidado com a regra "clean" para não apagar o "support.o"
#
# OBSERVAR que as variáveis de ambiente consideram que o Makefile está no diretótio "cthread"
# 

CC=gcc
LIB_DIR=./lib
INC_DIR=./include
BIN_DIR=./bin
SRC_DIR=./src

all: teste
	#ar crs $(LIB_DIR)/libcthread.a $(BIN_DIR)/cthread.o $(BIN_DIR)/support.o

teste:
	#$(CC) -c $(SRC_DIR)/cthread.c -o cthread $(BIN_DIR)/cthread.o -lcthread -Wall
	$(CC)  -o cthread $(SRC_DIR)/cthread.c -Wall

#all: cthread.o
#	ar crs $(LIB_DIR)/libcthread.a $(BIN_DIR)/cthread.o $(BIN_DIR)/support.o
#cthread.o: include/cthread.h
#	$(CC) -c $(SRC_DIR)/cthread.c -o $(BIN_DIR)/cthread.o

#all: regra1 regra2 regran

#regra1: #dependências para a regra1
#	$(CC) -o $(BIN_DIR)regra1 $(SRC_DIR)regra1.c -Wall

#regra2: #dependências para a regra2
#	$(CC) -o $(BIN_DIR)regra2 $(SRC_DIR)regra2.c -Wall

#regran: #dependências para a regran
#	$(CC) -o $(BIN_DIR)regran $(SRC_DIR)regran.c -Wall

clean:
	rm $(BIN_DIR)/cthread.o $(LIB_DIR)/libcthread.a

#clean:
#	rm -rf $(LIB_DIR)/*.a $(BIN_DIR)/*.o $(SRC_DIR)/*~ $(INC_DIR)/*~ *~


