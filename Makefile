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

all: compila gera_lib liga
	
compila:
	#-m32 para compilar em sistemas de 32bits pois support.o está compilada em 32bits
	$(CC) -o $(BIN_DIR)/cthread.o -c $(SRC_DIR)/cthread.c -Wall -m32

gera_lib:
	ar crs $(LIB_DIR)/libcthread.a $(BIN_DIR)/cthread.o $(BIN_DIR)/support.o
	#objdump -a ./lib/libcthread.a para mostar o que está contido na libthread.a

liga:
	$(CC) -o cthread $(SRC_DIR)/cthread.c -L $(LIB_DIR) -lcthread -Wall -m32
	#$(CC) -o cthread $(SRC_DIR)/cthread.c -L $(LIB_DIR) -lcthread -Wall

clean:
	rm cthread $(BIN_DIR)/cthread.o $(LIB_DIR)/libcthread.a 

