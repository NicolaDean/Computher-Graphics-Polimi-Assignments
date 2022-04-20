CFLAGS = -std=c++17 -O2
INC=-I./headers
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

#SOURCES PATHS
ENGINE_FOLDER = src/engine
ENGINE = $(ENGINE_FOLDER)/*.cpp $(ENGINE_FOLDER)/*.h
MAIN = src/main.cpp
#SOURCE COMPOSITION
SOURCES = $(MAIN) $(ENGINE)

VulkanTest: $(SOURCES)
	g++ $(CFLAGS) $(INC) -o VulkanTest $(SOURCES) $(LDFLAGS)

.PHONY: test clean

test: VulkanTest
	./VulkanTest

clean:
	rm -f VulkanTest

run: clean test

shaders:
	$(GLSLC_PATH)/glslc $(SHADER_FOLDER)/Shader.frag -o $(SHADER_FOLDER)/Frag.spv
	$(GLSLC_PATH)/glslc $(SHADER_FOLDER)/Shader.vert -o $(SHADER_FOLDER)/Vert.spv

