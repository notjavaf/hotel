all:
	g++ -c -std=c++17 main.cpp
	g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
	./sfml-app
