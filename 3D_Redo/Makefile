quadTest: prepare
	g++ -o quadTest src/quadTest.cpp *.o -lsfml-graphics -lsfml-window -lsfml-system

isoTest: prepare
	g++ -o isoTest src/isoTest.cpp *.o -lsfml-graphics -lsfml-window -lsfml-system

main: prepare
	g++ -o main src/main.cpp *.o -lsfml-graphics -lsfml-window -lsfml-system

prepare:
	g++ -c math/math.cpp src/globals.cpp -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm -f *.o
	rm -f main
	rm -f quadTest
	rm -f isoTest
