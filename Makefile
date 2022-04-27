all:
	gcc -Wall -c main.c
	gcc -Wall -c table.c                         
	gcc -Wall -c executeCommand.c
	gcc -Wall -c parseCommand.c                                                            
	gcc -Wall -c IO.c       
	gcc -Wall -c pager.c  
	gcc -Wall -c cursor.c         
	gcc -Wall -c node.c
	gcc -Wall -c tree.c
	gcc main.o tree.o node.o executeCommand.o cursor.o parseCommand.o pager.o table.o IO.o -o main