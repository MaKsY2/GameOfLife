SFMLpath ?= SfmlPath 

all: life

life: main.o
	g++ main.o -o life -I$(SFMLpath)/include -L$(SFMLpath)/lib -lsfml-graphics -lsfml-window -lsfml-system -lstdc++

main.o: main.cpp
	g++ -c main.cpp --std c++20

clean:
	rm -rf *o life
