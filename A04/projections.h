#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

//IDENTITY MATRIX
const glm::mat4 I = glm::mat4(1);
//AXIS DEFINITION
const glm::vec3 x_axis = glm::vec3(1,0,0);
const glm::vec3 y_axis = glm::vec3(0,1,0);
const glm::vec3 z_axis = glm::vec3(0,0,1);

/**
 * rotate around x
 * @param angle rotation angle
 * @return matrix to rotate around x
 */
glm::mat4 x_rotation(float angle)
{
    return glm::rotate(I,angle,x_axis);
}
/**
 * rotate around y
 * @param angle rotation angle
 * @return matrix to rotate around y
 */
glm::mat4 y_rotation(float angle)
{
    return glm::rotate(I,angle,y_axis);
}
/**
 * rotate around z
 * @param angle rotation angle
 * @return matrix to rotate around z
 */
glm::mat4 z_rotation(float angle)
{
    return glm::rotate(I,angle,z_axis);
}

/**
 * Apply a shear on Z axis
 * @param hx factor for x axis
 * @param hy factor for z axis
 * @return shear matrix
 */
glm::mat4 shear_z(float hx,float hy)
{
    glm::mat4 shear_matrix =  glm::mat4(
            1.0,		0.0,		0.0,		0.0,
            0.0,		1.0,		0.0,		0.0,
            hx     ,		hy     ,		1.0,		0.0,
            0.0,		0.0,		0.0,		1.0);

    return shear_matrix;

}
//SCREEN VARIABLES:
const float width = 2;
const float nearest_barrier = -4;
const float farest_barrier = 12;
/**
 * This class contain all the screen and viewport information
 * offer also a method to get a basic projection
 */
class Screen{
    float w = width;
    float l;
    float b;
    float t;
    float r;
    float n = nearest_barrier;
    float f = farest_barrier;
    float a;

public:
    Screen(float aspect_ratio){
        a = aspect_ratio;
        l = -w;
        r = w;
        b = -w/a;
        t = w/a;
    }

    glm::mat4 getBasicOrtho()
    {
        glm::mat4 vulkan_correction = glm::scale(I,glm::vec3(1,-1,1));
        glm::mat4 basicMat = glm::ortho(l,r,b,t,n,f);

        return vulkan_correction * basicMat;
    }
};

/**
 * Create a matrix for Isometric projection with the given aspect ration a
 * @param a aspect ratio
 * @return projection matrix
 */
glm::mat4 PO1(float a) {
    Screen s = Screen(a);

    glm::mat4 base = s.getBasicOrtho();
    glm::mat4 rot_y = y_rotation(glm::radians(45.0f));
    glm::mat4 rot_x = x_rotation(glm::radians(35.26f));

	glm::mat4 out = base * rot_x * rot_y;
	return out;
}

/**
 * Create a matrix for Dimnetric projection (alpha = 45 degree)
 * with the given aspect ration a
 * @param a aspect ratio
 * @return projection matrix
 */
glm::mat4 PO2(float a) {
    Screen s = Screen(a);

    float alpha = glm::radians(45.0f);

    glm::mat4 base = s.getBasicOrtho();
    glm::mat4 rot_y = y_rotation(glm::radians(45.0f));
    glm::mat4 rot_x = x_rotation(alpha);

    glm::mat4 out = base * rot_x * rot_y;
	return out;
}



/**
 * Create a matrix for Trimetric projection (alpha = 45 degree, beta = 60 degree)
 * with the given aspect ration a
 * @param a aspect ratio
 * @return projection matrix
 */
glm::mat4 PO3(float a) {
    Screen s = Screen(a);

    float alpha = glm::radians(30.0f);
    float beta  = glm::radians(60.0f);

    glm::mat4 base = s.getBasicOrtho();
    glm::mat4 rot_y = y_rotation(beta);
    glm::mat4 rot_x = x_rotation(alpha);

    glm::mat4 out = base * rot_x * rot_y;
    return out;
}



/**
 * Create a matrix for Cabinet projection (alpha = 45)
 * with the given aspect ration a
 * @param a aspect ratio
 * @return projection matrix
 */
glm::mat4 PO4(float a) {
    Screen s = Screen(a);

    float roh = 0.5;
    float alpha = glm::radians(45.0f);

    glm::mat4 base = s.getBasicOrtho();
    glm::mat4 shear = shear_z(-roh*cos(alpha),-roh*sin(alpha));

    glm::mat4 out = base * shear;
	return out;
}

