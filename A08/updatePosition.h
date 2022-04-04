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
//AXIS DEFINITION
const glm::vec3 x_axis = glm::vec3(1,0,0);
const glm::vec3 y_axis = glm::vec3(0,1,0);
const glm::vec3 z_axis = glm::vec3(0,0,1);

// Create the world matrix for the robot

class Robot{
public:
    float rotation_speed = glm::radians(60.0f);;
    float movement_speed = 0.75f;

    GLFWwindow* window;

    glm::mat3 camDir = glm::mat3(1.0f);
    glm::vec3 camPos = glm::vec3 (0,0,0);
    float rotation = 0.0f;

    Robot(){}

    Robot(glm::vec3 initialPos,GLFWwindow* win){
        camPos = initialPos;
        window = win;
    }

    glm::mat4 getMatrix()
    {
        return glm::translate(I, camPos) * glm::rotate(I,glm::radians(rotation),y_axis);
        //return glm::translate(glm::transpose(glm::mat4(camDir)), -camPos);
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
            turnRobot(CAMERA_TURN_LEFT,deltaT);
        }
        if(glfwGetKey(window, GLFW_KEY_RIGHT)) {
            turnRobot(CAMERA_TURN_RIGHT,deltaT);
        }
        if(glfwGetKey(window, GLFW_KEY_UP)) {
            lookUpRobot(CAMERA_LOOK_UP,deltaT);
        }
        if(glfwGetKey(window, GLFW_KEY_DOWN)) {
            lookUpRobot(CAMERA_LOOK_DOWN,deltaT);
        }
        if(glfwGetKey(window, GLFW_KEY_Q)) {
            rotateRobot(CAMERA_CLOCKWISE_ROTATION,deltaT);
        }
        if(glfwGetKey(window, GLFW_KEY_E)) {
            rotateRobot(CAMERA_COUNTER_CLOCKWISE_ROTATION,deltaT);
        }
    }

    /**
     * Update camera position in space
     * @param deltaT
     */
    void updatePosition(float deltaT){
        if(glfwGetKey(window, GLFW_KEY_A)) {
            rotation = 180.0f;
            camPos -= movement_speed * glm::vec3(camDir[SIDE_AXIS]) * deltaT;
        }
        if(glfwGetKey(window, GLFW_KEY_D)) {
            rotation = 0.0f;
            camPos += movement_speed * glm::vec3(camDir[SIDE_AXIS]) * deltaT;
        }
        if(glfwGetKey(window, GLFW_KEY_S)) {
            rotation = -90.0f;
            camPos += movement_speed * glm::vec3(camDir[FORWARD_AXIS]) * deltaT;
        }
        if(glfwGetKey(window, GLFW_KEY_W)) {
            rotation = 90.0f;
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
    void rotateRobot(bool clockwise, double deltaT)
    {
        float camSpeed = deltaT * rotation_speed;

        if(clockwise == CAMERA_COUNTER_CLOCKWISE_ROTATION){
            camSpeed = - camSpeed;
        }
        glm::mat4 rotation = glm::rotate(I,camSpeed,glm::vec3(camDir[FORWARD_AXIS]));

        camDir = glm::mat3(rotation* glm::mat4(camDir));

    }

    /**
     * turn camera left or right
     * rotate around vertical axis
     * @param right if true turn right otherwise left
     * @param deltaT
     */
    void turnRobot(bool right, double deltaT){
        float camSpeed = deltaT * rotation_speed;

        if(right == CAMERA_TURN_LEFT){
            camSpeed = - camSpeed;
        }

        //glm::mat4 rotation = glm::rotate(I,camSpeed,glm::vec3(camDir[VERTICAL_AXIS]));
        glm::mat4 rotation = glm::rotate(I,camSpeed,y_axis); //THIS SHOULD ROTATE ROBOT ON X AXIS
        camDir = glm::mat3(rotation* glm::mat4(camDir));
    }

    /**
     * rotate camera up or down
     * rotate around side axis
     * @param up if true rotate up otherwise down
     * @param deltaT
     */
    void lookUpRobot(bool up, double deltaT){
        float camSpeed = deltaT * rotation_speed;

        if(up == CAMERA_LOOK_DOWN){
            camSpeed = - camSpeed;
        }

        glm::mat4 rotation = glm::rotate(I,camSpeed,glm::vec3(camDir[SIDE_AXIS]));

        camDir = glm::mat3(rotation* glm::mat4(camDir));
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
static Robot robot;
static TimeKeeper time_keeper;
static glm::vec3 initialPos = glm::vec3(-3, 0, 2);

/**
 * Create the world matrix for he robot
 * @param window
 * @return
 */
glm::mat4 getRobotWorldMatrix(GLFWwindow *window) {

    //IF FIRST CALL OF FUNCTION INITIALIZE VARIABLES
    if(firstCall){
        //CREATE ROBOT TRACKING
        robot = Robot(initialPos,window);
        //TIME KEEPER
        time_keeper = TimeKeeper();
        //RESET FIRSTCALL FLAG
        firstCall = false;
    }

    //UPDATE ROBOT POSITION USING deltaT
    robot.update(time_keeper.update());

    //GET RESULTING ROBOT MATRIX
    glm::mat4 out = robot.getMatrix();
    return out;
}


