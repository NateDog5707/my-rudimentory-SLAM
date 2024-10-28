#default target
all: mapping

#object files

setup.o: src/setup.h src/setup.c
	gcc -Wall -std=c11 -lm -g -c src/setup.c -o setup.o 
	
coordsList.o: src/coordsList.c src/coordsList.h src/setup.h
	gcc -Wall -std=c11 -lm -g -c src/coordsList.c -o coordsList.o
	
scan.o: src/scan.c src/scan.h src/coordsList.h src/setup.h
	gcc -Wall -std=c11 -lm -g -c src/scan.c -o scan.o
	
	
#executable
mapping: src/main.c setup.o coordsList.o scan.o
	gcc -lm src/main.c setup.o coordsList.o scan.o -o bin/mapping

#clean
	
clean:	
	rm *.o
	rm bin/mapping #the exec

#target for tar
tar:
	gtar cvzf mapping_V1.0_src.tar.gz README.txt COPYRIGHT.txt Makefile bin/ src/

# Target for tar
#tar: 
#	gtar cvzf Chess_V1.0_src.tar.gz README.txt COPYRIGHT.txt INSTALL.txt Makefile bin/ doc/ src/