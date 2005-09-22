FLAGS = -ggdb3
EXEC = Mvm

all: convenience.o ctype.o itype.o jtype.o rtype.o main.o
	g++ $(FLAGS) -o $(EXEC) convenience.o ctype.o itype.o jtype.o rtype.o main.o

main.o : main.cpp
	g++ $(FLAGS) -c main.cpp

rtype.o : rtype.cpp
	g++ $(FLAGS) -c rtype.cpp

jtype.o : jtype.cpp
	g++ $(FLAGS) -c jtype.cpp

itype.o : itype.cpp
	g++ $(FLAGS) -c itype.cpp

ctype.o : ctype.cpp
	g++ $(FLAGS) -c ctype.cpp

convenience.o : convenience.cpp
	g++ $(FLAGS) -c convenience.cpp

run: all
	./$(EXEC)

clean:
	rm -f *.o *.gch $(EXEC)
