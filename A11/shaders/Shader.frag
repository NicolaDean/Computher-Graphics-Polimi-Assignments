#version 450

layout(location = 0) out vec4 outColor;

layout(set = 0, binding = 1) uniform GlobalUniformBufferObject {
	float time;
} gubo;


void main() {

	float t = gubo.time;

	float red = 0.0;
	float green = 0.0;
	float blue = 0.0;


	if(t<0.5){
		red = t*2;
		blue = (1- t) * 2;
	}

	if(t>0.5){
		red = (1- t) * 2;
		blue = t * 2;
	}
	outColor = vec4(red, 0.0, blue, 1.0f);
}