LB_PATH = library/
OB_PATH = object/
SOURCES = main.o mySimpleComputer.o scMemory.o scRegistr.o scTerm.o
SOURCES_PATH = $(OB_PATH)main.o $(OB_PATH)mySimpleComputer.o $(OB_PATH)scMemory.o $(OB_PATH)scRegistr.o $(OB_PATH)scTerm.o
all: $(SOURCES) 
	@g++ -Wall $(SOURCES_PATH) -o bin/main
	@./bin/main

main.o: main.cpp
	@g++ -Wall main.cpp -c -o $(OB_PATH)main.o
	
scMemory.o: $(LB_PATH)scMemory.cpp 
	@g++ -Wall $(LB_PATH)scMemory.cpp -c -o $(OB_PATH)scMemory.o 

scRegistr.o: $(LB_PATH)scRegistr.cpp
	@g++ -Wall $(LB_PATH)scRegistr.cpp -c -o $(OB_PATH)scRegistr.o 
scTerm.o: $(LB_PATH)scTerm.cpp
	@g++ -Wall $(LB_PATH)scTerm.cpp -c -o $(OB_PATH)scTerm.o
mySimpleComputer.o: $(LB_PATH)mySimpleComputer.cpp
	@g++ -Wall $(LB_PATH)mySimpleComputer.cpp -c -o $(OB_PATH)mySimpleComputer.o
clean: 
	@rm -f $(OB_PATH)* bin/*