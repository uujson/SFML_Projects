all:
	g++ -c include/settings/settings.cpp include/utils/utils.cpp include/algebra/linalg.cpp -lsfml-graphics -lsfml-window -lsfml-system
	g++ -o main src/main.cpp *.o -lsfml-graphics -lsfml-window -lsfml-system
	g++ -o cubeTest src/cubeTest.cpp *.o -lsfml-graphics -lsfml-window -lsfml-system
clean:
	rm -f *.o
	rm -f main