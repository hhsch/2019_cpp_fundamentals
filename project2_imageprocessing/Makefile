main: clean
	g++ -o Project2.out src/main.cpp src/TGA.cpp

clean:
	rm -f src/*.o output/* Project2.out debug

debug: clean
	g++ -Wall -g -o debug src/main.cpp src/TGA.cpp
