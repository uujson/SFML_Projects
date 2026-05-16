all:
	g++ -c settings.cpp -lsfml-graphics -lsfml-window -lsfml-system
	g++ -c object.cpp -lsfml-graphics -lsfml-window -lsfml-system
	g++ -c quadtree.cpp -lsfml-graphics -lsfml-window -lsfml-system
	g++ -o main main.cpp settings.o object.o quadtree.o -lsfml-graphics -lsfml-window -lsfml-system
clean:
	rm -f *.o
	rm -f main