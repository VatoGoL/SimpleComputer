LB_PATH = library/
OB_PATH = object/
SOURCES = main.o mySimpleComputer.o scMemory.o scRegistr.o scTerm.o myBigChars.o ScreenDrawer.o readKey.o
SOURCES_PATH = $(OB_PATH)main.o $(OB_PATH)mySimpleComputer.o $(OB_PATH)scMemory.o $(OB_PATH)scRegistr.o $(OB_PATH)scTerm.o $(OB_PATH)myBigChars.o $(OB_PATH)ScreenDrawer.o $(OB_PATH)readKey.o
all: $(SOURCES) 
	@clear
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
myBigChars.o: $(LB_PATH)myBigChars.cpp
	@g++ -Wall $(LB_PATH)myBigChars.cpp -c -o $(OB_PATH)myBigChars.o
ScreenDrawer.o: $(LB_PATH)ScreenDrawer.cpp
	@g++ -Wall $(LB_PATH)ScreenDrawer.cpp -c -o $(OB_PATH)ScreenDrawer.o
readKey.o: $(LB_PATH)readKey.cpp
	@g++ -Wall $(LB_PATH)readKey.cpp -c -o $(OB_PATH)readKey.o

clean: 
	@rm -f $(OB_PATH)* bin/*