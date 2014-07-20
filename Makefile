CC = g++
CFLAGS = -Wall
LDFLAGS = -lm -lGL -lGLU -lglut

game : main.o game.o object.o terrain.o
	${CC} ${CFLAGS} -o game main.o game.o object.o terrain.o ${LDFLAGS} 

game.o : game.cpp game.h
	${CC} ${CFLAGS} -c game.cpp

object.o : object.cpp object.h
	${CC} ${CFLAGS} -c object.cpp

terrain.o : terrain.cpp terrain.h
	${CC} ${CFLAGS} -c terrain.cpp

main.o : main.cpp
	${CC} ${CFLAGS} -c main.cpp

clean:
	rm -f *.o
