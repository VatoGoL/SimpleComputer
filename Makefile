LB_PATH = library/
OB_PATH = object/
SOURCES = main.o scMemory.o scRegistr.o
SOURCES_PATH = $(OB_PATH)main.o $(OB_PATH)scMemory.o $(OB_PATH)scRegistr.o
all: $(SOURCES) 
	@g++ -Wall $(SOURCES_PATH) -o bin/main
	@./bin/main

main.o: main.cpp
	@g++ -Wall main.cpp -c -o $(OB_PATH)main.o
	
scMemory.o: $(LB_PATH)scMemory.cpp 
	@g++ -Wall $(LB_PATH)scMemory.cpp -c -o $(OB_PATH)scMemory.o 

scRegistr.o: $(LB_PATH)scRegistr.cpp
	@g++ -Wall $(LB_PATH)scRegistr.cpp -c -o $(OB_PATH)scRegistr.o 
clean: 
	@rm -f $(OB_PATH)* bin/*