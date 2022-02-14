LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

main: clean
	g++ src/main.cpp src/Game.cpp src/Tile.cpp -o main $(LDFLAGS)

clean:
	rm -f main main.o

debug: clean
	g++ -Wall -g -o main src/main.cpp src/Game.cpp src/Tile.cpp $(LDFLAGS)

.PHONY: clean
