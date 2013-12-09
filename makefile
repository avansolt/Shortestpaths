CXX = g++  
CFLAGS = -Wall
run: shortespath.cpp
	$(CXX) shortespath.cpp
clean:
	rm -f run *.o *~ a.out
