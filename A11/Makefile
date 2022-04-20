CFLAGS = -std=c++17 -O2
INC=-I./headers
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi
GLSLC_PATH = /usr/local/bin
SHADER_FOLDER = ./shaders

VulkanTest: main.cpp
	g++ $(CFLAGS) $(INC) -o VulkanTest main.cpp $(LDFLAGS)

.PHONY: test clean run shaders

test: VulkanTest
	./VulkanTest

clean:
	rm -f VulkanTest
	
run: clean test

shaders:
	$(GLSLC_PATH)/glslc $(SHADER_FOLDER)/Shader.frag -o $(SHADER_FOLDER)/Frag.spv
	$(GLSLC_PATH)/glslc $(SHADER_FOLDER)/Shader.vert -o $(SHADER_FOLDER)/Vert.spv

