all:
	gcc -Wall -c ./src/main.c
	gcc -Wall -c ./src/table.c                         
	gcc -Wall -c ./src/executeCommand.c
	gcc -Wall -c ./src/parseCommand.c                                                            
	gcc -Wall -c ./src/IO.c       
	gcc -Wall -c ./src/pager.c  
	gcc -Wall -c ./src/cursor.c         
	gcc -Wall -c ./src/node.c
	gcc -Wall -c ./src/tree.c
	gcc main.o tree.o node.o executeCommand.o cursor.o parseCommand.o pager.o table.o IO.o -o main