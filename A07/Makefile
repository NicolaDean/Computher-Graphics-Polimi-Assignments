CFLAGS = -std=c++17 -O2
INC=-I./headers
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

VulkanTest: main.cpp
	g++ $(CFLAGS) $(INC) -o VulkanTest main.cpp $(LDFLAGS)

.PHONY: test clean run

test: VulkanTest
	./VulkanTest

clean:
	rm -f VulkanTest
	
run: clean test
