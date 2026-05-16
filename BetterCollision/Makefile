all:
	g++ -c settings/settings.cpp include/vector2f.cpp include/object.cpp include/grid.cpp include/array.cpp -lsfml-graphics -lsfml-window -lsfml-system
	g++ -o main src/main.cpp *.o -lsfml-graphics -lsfml-window -lsfml-system
clean:
	rm -f *.o
	rm -f main