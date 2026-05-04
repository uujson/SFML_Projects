all: clean settings
	g++ -o main source/main.cpp settings.o -lsfml-graphics -lsfml-window -lsfml-system

settings:
	g++ -c include/settings/settings.cpp -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm -f *.o