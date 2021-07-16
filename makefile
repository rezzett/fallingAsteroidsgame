all:
	c++ -c main.cpp
	c++ -c Game.cpp
	c++ -o fallingAsteroids main.o Game.o -lsfml-graphics -lsfml-window -lsfml-system
	./fallingAsteroids

run:
	./fallingAsteroids


clean:
	rm -f *.o fallingAsteroids

