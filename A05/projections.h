#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

#include <chrono>

//IDENTITY MATRIX
const glm::mat4 I = glm::mat4(1);
//AXIS DEFINITION
const glm::vec3 x_axis = glm::vec3(1,0,0);
const glm::vec3 y_axis = glm::vec3(0,1,0);
const glm::vec3 z_axis = glm::vec3(0,0,1);

const float nearest_plane   = 0.1;
const float farest_plane    = 9.9;

class Screen{
    float nearest = nearest_plane;
    float farest  = farest_plane;
    float a;
    float fov;
public:
    Screen(float field_of_view,float aspect_ratio)
    {
        a = aspect_ratio;
        fov = field_of_view;
    }

    glm::mat4 getPerspective()
    {
        glm::mat4 perspective = glm::perspective(fov,a,nearest,farest);
        perspective[1][1] *= -1;

        return perspective;
    }
};

// Create a matrix for Perspecrtive projection with the given aspect ratio a,
// and a FovY = 90o
glm::mat4 PO1(float a) {
    Screen s = Screen(glm::radians(90.0f),a);
	return s.getPerspective();
}

// Create a matrix for Perspecrtive projection with the given aspect ratio a,
// and a FovY = 120o
glm::mat4 PO2(float a) {
    Screen s = Screen(glm::radians(120.0f),a);
    return s.getPerspective();
}

// Create a matrix for Perspecrtive projection with the given aspect ratio a,
// and a FovY = 30o
glm::mat4 PO3(float a) {
    Screen s = Screen(glm::radians(30.0f),a);
    return s.getPerspective();
}

// Create a matrix for Perspecrtive projection, with the given aspect ratio a.
// Here the perspective should only show the left side of the view
// with a FovY = 90o. Here r=0, and l, t and b should be computed
// to match both the aspect ratio and the FovY
glm::mat4 PO4(float a) {
    float fov = glm::radians(90.0f);
    float tan_fov = std::tan(fov/2);

    a = a;
	float r = 0;
    float l = -a * nearest_plane * tan_fov;
    float b = -nearest_plane * tan_fov;
    float t = nearest_plane * tan_fov;

    glm::mat4 perspective = glm::frustum(l,r,b,t,nearest_plane,farest_plane);
    perspective[1][1] *= -1;

    return perspective;
}

