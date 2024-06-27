CC = gcc -Wall
objects = main.o person.o population.o filemanager.o htmlexport.o menu.o

main: $(objects)
	gcc -o $@ $(objects)

$(objects): %.o: %.c

clean:
	rm *.o main export/*.html