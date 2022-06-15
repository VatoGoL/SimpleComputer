LIB_PATH = library/
OB_PATH = object/
SOURCES = sat.o scMemory.o scRegistr.o
SOURCES_OBJ = ${OB_PATH}sat.o ${OB_PATH}scMemory.o ${OB_PATH}scRegistr.o
CC = g++
ARGS = -Wall

all: ${SOURCES}
	@${CC} ${ARGS} ${SOURCES_OBJ} -o bin/sat
sat.o: sat.cpp
	@${CC} ${ARGS} sat.cpp -c -o ${OB_PATH}sat.o
scMemory.o: ${LIB_PATH}scMemory.cpp
	@${CC} ${ARGS} ${LIB_PATH}scMemory.cpp -c -o ${OB_PATH}scMemory.o
scRegistr.o: ${LIB_PATH}scRegistr.cpp
	@${CC} ${ARGS} ${LIB_PATH}scRegistr.cpp -c -o ${OB_PATH}scRegistr.o


clear:
	@rm ${OB_PATH}*
	@rm bin/*