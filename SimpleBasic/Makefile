LIB_PATH = library/
OB_PATH = object/
SOURCES = sbt.o
SOURCES_OBJ = ${OB_PATH}sbt.o
CC = g++
ARGS = -Wall

all: ${SOURCES}
	@${CC} ${ARGS} ${SOURCES_OBJ} -o bin/sbt
sbt.o: sbt.cpp
	@${CC} ${ARGS} sbt.cpp -c -o ${OB_PATH}sbt.o


clear:
	@rm ${OB_PATH}*
	@rm bin/*