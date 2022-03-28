all:
	g++ -c -std=c++17 main.cpp
	g++ -c -std=c++17 globals.cpp
	g++ -c -std=c++17 book_request.cpp
	g++ -c -std=c++17 room.cpp	
	g++ -c -std=c++17 hotel.cpp
	g++ -c -std=c++17 experiment.cpp
	g++ *.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
	rm -f *.o
