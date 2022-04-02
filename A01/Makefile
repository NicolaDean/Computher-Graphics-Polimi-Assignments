CFLAGS = -std=c++17 -O2
INC=-I./headers
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

.PHONY: run Assignment test clean

Assignment: main.cpp
	g++ $(CFLAGS) $(INC) -o Assignment main.cpp $(LDFLAGS)

test: Assignment
	./Assignment

clean:
	rm -f Assignment


run:clean test
