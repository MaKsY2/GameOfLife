SFMLpath ?= SfmlPath 

all: Life

Life: main.o
	g++ main.o -o life -I$(SFMLpath)/include -L$(SFMLpath)/lib -lsfml-graphics -lsfml-window -lsfml-system -lstdc++


main.o: main.cpp
	gcc -c main.cpp --std c++20