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

//CAMERA MACRO VARIABLES
#define CAMERA_CLOCKWISE_ROTATION true
#define CAMERA_COUNTER_CLOCKWISE_ROTATION false
#define CAMERA_LOOK_UP true
#define CAMERA_LOOK_DOWN false
#define CAMERA_TURN_RIGHT true
#define CAMERA_TURN_LEFT false

//AXIS
#define FORWARD_AXIS 2
#define SIDE_AXIS 0
#define VERTICAL_AXIS 1

//IDENTITY MATRIX
const glm::mat4 I = glm::mat4(1);

// Create the world matrix for the robot

class Camera{
public:
    double fov;
    double aspect_ratio;
    double near_plane;
    double far_plane;
    float rotation_speed = glm::radians(60.0f);;
    float movement_speed = 0.75f;

    GLFWwindow* window;

    glm::mat3 camDir = glm::mat3(1);
    glm::vec3 camPos = glm::vec3 (0,0,0);

    Camera(){}
    /*Camera(double FOV,double a_r, double n,double f,GLFWimage* win){
        fov = FOV;
        aspect_ratio = a_r;
        near_plane = n;
        far_plane = f;
        window = win;
    }*/

    Camera(glm::vec3 initialPos,GLFWwindow* win){
        camPos = initialPos;
        window = win;
    }

    glm::mat4 getMatrix()
    {
        return glm::translate(I, camPos);
    }

    /**
     * update camera position and direction based on user inputs
     * @param deltaT
     */
    void update(double deltaT){
        updateDirection(deltaT);
        updatePosition(deltaT);
    }
private:
    /**
     * Update Camera Direction
     * @param deltaT
     */
    void updateDirection(double deltaT){
        if(glfwGetKey(window, GLFW_KEY_LEFT)) {
            turnCamera(CAMERA_TURN_LEFT,deltaT);
        }
        if(glfwGetKey(window, GLFW_KEY_RIGHT)) {
            turnCamera(CAMERA_TURN_RIGHT,deltaT);
        }
        if(glfwGetKey(window, GLFW_KEY_UP)) {
            lookUpCamera(CAMERA_LOOK_UP,deltaT);
        }
        if(glfwGetKey(window, GLFW_KEY_DOWN)) {
            lookUpCamera(CAMERA_LOOK_DOWN,deltaT);
        }
        if(glfwGetKey(window, GLFW_KEY_Q)) {
            rotateCamera(CAMERA_CLOCKWISE_ROTATION,deltaT);
        }
        if(glfwGetKey(window, GLFW_KEY_E)) {
            rotateCamera(CAMERA_COUNTER_CLOCKWISE_ROTATION,deltaT);
        }
    }

    /**
     * Update camera position in space
     * @param deltaT
     */
    void updatePosition(float deltaT){
        if(glfwGetKey(window, GLFW_KEY_A)) {
            camPos -= movement_speed * glm::vec3(camDir[SIDE_AXIS]) * deltaT;
        }
        if(glfwGetKey(window, GLFW_KEY_D)) {
            camPos += movement_speed * glm::vec3(camDir[SIDE_AXIS]) * deltaT;
        }
        if(glfwGetKey(window, GLFW_KEY_S)) {
            camPos += movement_speed * glm::vec3(camDir[FORWARD_AXIS]) * deltaT;
        }
        if(glfwGetKey(window, GLFW_KEY_W)) {
            camPos -= movement_speed * glm::vec3(camDir[FORWARD_AXIS]) * deltaT;
        }
        if(glfwGetKey(window, GLFW_KEY_F)) {
            camPos -= movement_speed * glm::vec3(camDir[VERTICAL_AXIS]) * deltaT;
        }
        if(glfwGetKey(window, GLFW_KEY_R)) {
            camPos += movement_speed * glm::vec3(camDir[VERTICAL_AXIS]) * deltaT;
        }
    }
    /**
     * Rotate camera clockwise or counterclockwise
     * rotate around Forward axis
     * @param clockwise if true clockwise otherwise counterclockwise
     * @param deltaT
     */
    void rotateCamera(bool clockwise,double deltaT)
    {
        double camSpeed = deltaT * rotation_speed;

        if(clockwise == CAMERA_COUNTER_CLOCKWISE_ROTATION){
            camSpeed = - camSpeed;
        }

        //camDir = glm::mat3(glm::rotate(I,camSpeed,glm::vec3(camDir[FORWARD_AXIS])) * glm::mat4(camDir)));
    }

    /**
     * turn camera left or right
     * rotate around vertical axis
     * @param right if true turn right otherwise left
     * @param deltaT
     */
    void turnCamera(bool right,double deltaT){
        double camSpeed = deltaT * rotation_speed;

        if(right == CAMERA_TURN_LEFT){
            camSpeed = - camSpeed;
        }

        //camDir = glm::mat3(glm::rotate(I,camSpeed,glm::vec3(camDir[VERTICAL_AXIS]))* glm::mat4(camDir);
    }

    /**
     * rotate camera up or down
     * rotate around side axis
     * @param up if true rotate up otherwise down
     * @param deltaT
     */
    void lookUpCamera(bool up,double deltaT){
        double camSpeed = deltaT * rotation_speed;

        if(up == CAMERA_LOOK_DOWN){
            camSpeed = - camSpeed;
        }

        //camDir = glm::mat3(glm::rotate(I,camSpeed,glm::vec3(camDir[SIDE_AXIS])) * glm::mat4(camDir));
    }


};


class TimeKeeper{
    float lastTime;
public:
    TimeKeeper()
    {

        lastTime = 0.0f;
    }

    double update(){
        static auto startTime = std::chrono::high_resolution_clock::now();
        auto currentTime = std::chrono::high_resolution_clock::now();
        float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();
        float deltaT = time - lastTime;

        lastTime = time;
        return deltaT;
    }
};
/* ----------------------------------------------------------------------------------------------------
 * ----------------------------------------------------------------------------------------------------
 * ----------------------------------------------------------------------------------------------------
 * ASSIGMENT MAIN CODE:
 * ----------------------------------------------------------------------------------------------------
 * ----------------------------------------------------------------------------------------------------
 * ----------------------------------------------------------------------------------------------------
 */

static bool firstCall = true;
static Camera cam;
static TimeKeeper time_keeper;
static glm::vec3 initialPos = glm::vec3(-3, 0, 2);

/**
 * Create the world matrix for he robot
 * @param window
 * @return
 */
glm::mat4 getRobotWorldMatrix(GLFWwindow *window) {

    if(firstCall){
        cam = Camera(initialPos,window);
        time_keeper = TimeKeeper();
        firstCall = false;
    }

    cam.update(time_keeper.update());

    glm::mat4 out = cam.getMatrix();
    return out;
}



/*
 *
 * static glm::vec3 pos = glm::vec3(-3,0,2);	// variable to store robot position
												// here glm::vec3(-3,0,2) represents a
												// meaningful initial position for the robot
												//
												// this variable is here just as an example!
												// it should replaced or combined with
												//  the ones you think necessary for the task
 */