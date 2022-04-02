#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

#include <chrono>

// Create the world matrix for the robot

class Camera{
public:
    double fov;
    double aspect_ratio;
    double near_plane;
    double far_plane;

    Camera(double FOV,double a_r, double n,double f){
        fov = FOV;
        aspect_ratio = a_r;
        near_plane = n;
        far_plane = f;
    }
};

class WorldMatrix{


    Camera camera = Camera(1,1,1,1);

    glm::mat4 getWorldMatrix()
    {
        glm::mat4 localCoordinates;
        glm::mat4 step1 = this->step1();
        glm::mat4 step2 = this->step2();
        glm::mat4 step3 = this->step3();

        glm::mat4 world_view_projection = step3 * step2 * step1;

        return world_view_projection;
    }
    /**
     *
     * @return
     */
    glm::mat4 step1(){

    }
    /**
     *
     * @return
     */
    glm::mat4 step2(){

    }

    /**
     *
     * @return
     */
    glm::mat4 step3(){

    }

};
/**
 * Create the world matrix for he robot
 * @param window
 * @return
 */
glm::mat4 getRobotWorldMatrix(GLFWwindow* window) {
	static glm::vec3 pos = glm::vec3(-3,0,2);	// variable to store robot position
												// here glm::vec3(-3,0,2) represents a
												// meaningful initial position for the robot
												//
												// this variable is here just as an example!
												// it should replaced or combined with
												//  the ones you think necessary for the task
	glm::mat4 out;
    //KEY W
    if(glfwGetKey(window, GLFW_KEY_W)){

    }
    //KEY A
    if(glfwGetKey(window, GLFW_KEY_A)){

    }
    //KEY S
    if(glfwGetKey(window, GLFW_KEY_S)){

    }
    //KEY D
    if(glfwGetKey(window, GLFW_KEY_D)){

    }

	out = glm::translate(glm::mat4(1), pos);	// this line has to be changed!
												// it is here just to allow the program to
												// be compiled and run
	return out;
}

