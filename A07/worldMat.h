#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>
#include <glm/gtx/euler_angles.hpp>

const float pi = 3.14;
//IDENTITY MATRIX
const glm::mat4 I = glm::mat4(1);
//AXIS DEFINITION
const glm::vec3 x_axis = glm::vec3(1,0,0);
const glm::vec3 y_axis = glm::vec3(0,1,0);
const glm::vec3 z_axis = glm::vec3(0,0,1);

//BASIC ROTATIONS AROUND X,Y,Z
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
 * Create a world matrix using position, Euler angles, and size
 * Euler angles are passed in YPR parameter:
 * @param pos
 * @param YPR YPR.x : Yaw
 *            YPR.y : Pitch
 *            YPR.z : Roll
 * @param size
 * @return
 */
glm::mat4 MakeWorldMatrixEuler(glm::vec3 pos, glm::vec3 YPR, glm::vec3 size) {

    //WHY I NEED TO USE GLM::RADIANS IF THEY ARE ALREADY RADIANTS????
    double Yaw_angle      = glm::radians(YPR.x);
    double Pitch_angle    = glm::radians(YPR.y);
    double Roll_angle     = glm::radians(YPR.z);

    printf("Radiants:\t%f\t%f\t%f\n",Yaw_angle,Pitch_angle,Roll_angle);
    printf("Degree:\t%f\t%f\t%f\n",YPR.x,YPR.y,YPR.z);
    //TRANSLATION
    glm::mat4 T = glm::translate(I,pos);
    //EULER ROTATION
    glm::mat4 Yaw = y_rotation(Yaw_angle);
    glm::mat4 Pitch = x_rotation(Pitch_angle);
    glm::mat4 Roll = z_rotation(Roll_angle);
    //SCALING
    glm::mat4 Scale = glm::scale(I,size);

    //Just to try out the other method calculate using glm function
    glm::mat4 MEa = glm::eulerAngleYXZ(Yaw_angle,
                                       Pitch_angle,
                                       Roll_angle);

    //RESULT
    glm::mat4 out = T * Roll * Pitch * Yaw * Scale;
    //glm::mat4 out = T * MEa * Scale;
	return out;
}

/**
 * Create a world matrix using position, quaternion angles, and size
 * @param pos
 * @param rQ
 * @param size
 * @return
 */
glm::mat4 MakeWorldMatrixQuat(glm::vec3 pos, glm::quat rQ, glm::vec3 size) {


    glm::mat4 T = glm::translate(I,pos);
    //GENERATE QUATERNION MATRIX FROM QUATERNION
    glm::mat4 Mq = glm::mat4 (rQ);
    glm::mat4 Scale = glm::scale(I,size);

    glm::mat4 out = T * Mq * Scale;

	return out;
}

