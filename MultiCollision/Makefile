all:
	g++ -c settings/settings.cpp -lsfml-graphics -lsfml-window -lsfml-system
	g++ -c object/obj.cpp -lsfml-graphics -lsfml-window -lsfml-system
	g++ -o main source/main.cpp settings.o obj.o -lsfml-graphics -lsfml-window -lsfml-system
clean:
	rm -f *.o