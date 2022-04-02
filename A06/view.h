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
  * Create a look in direction matrix
  * @param Pos Position of the camera
  * @param Angs Angs.x -> direction (alpha)
  *             Angs.y -> elevation (beta)
  *             Angs.z -> roll (rho)
  * @return first person matrix
  */
glm::mat4 LookInDirMat(glm::vec3 Pos, glm::vec3 Angs) {

    //INVERSE TRANSFORMATION
    glm::mat4 T_inv = glm::translate(I,-Pos);
    glm::mat4 Ry_inv = y_rotation(-Angs.x);
    glm::mat4 Rx_inv = x_rotation(-Angs.y);
    glm::mat4 Rz_inv = z_rotation(-Angs.z);

	//glm::mat4 out = T_inv * Ry_inv * Rx_inv * Rz_inv;
     glm::mat4 out = Rz_inv * Rx_inv * Ry_inv * T_inv;
	return out;
}

/**
  * Create a look at matrix
  * @param Pos Position of the camera (c)
  * @param aim Position of the target (a)
  * @param Roll roll (rho)
  * @return
  */
glm::mat4 LookAtMat(glm::vec3 Pos, glm::vec3 aim, float Roll) {

    glm::vec3 u = glm::vec3(0,1,0);//Vertical orientation

    //ROLL is a z rotation before lookat
	return z_rotation(Roll) * glm::lookAt(Pos,aim,u);
}



