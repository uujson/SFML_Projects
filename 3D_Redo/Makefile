main: prepare
	g++ -o main src/main.cpp *.o -lsfml-graphics -lsfml-window -lsfml-system

prepare:
	g++ -c math/math.cpp src/globals.cpp -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm -f *.o
	rm -f mmain
