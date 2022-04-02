#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

//PI GRECO
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
 *
 * @param through_point point the axis pass through
 * @param y_reset angle of arbitrary axis respect y
 * @param z_reset angle of arbitrary axis respect z
 * @param angle angle we want to rotate around axis
 * @return matrix to perform rotation around an arbitrary axis
 */
glm::mat4 rotate_axis(glm::vec3 through_point,float y_reset,float z_reset,float angle)
{
    //TRANSLATE
    glm::mat4 translation = glm::translate(I,through_point);

    //RESET Y AND Z AXIS
    glm::mat4 yRot = y_rotation(y_reset);
    glm::mat4 zRot = z_rotation(z_reset);

    //APPLY AXIS ROTATION
    glm::mat4 axisRot = x_rotation(angle);

    //BRING BACK Y AND Z AXIS
    glm::mat4 zRot_back = z_rotation(-z_reset);
    glm::mat4 yRot_back = y_rotation(-y_reset);

    //BRING BACK TRANSLATION
    glm::mat4 translation_back = glm::translate(I,-through_point);

    //COMPUTE TRANSFORMATION MATRIX:
    glm::mat4 result = translation * yRot * zRot * axisRot * zRot_back * yRot_back * translation_back;

    return  result;
}


/**
 * TASK M1:
 * Rotate 45 degrees around an arbitrary axis passing through (1,0,-1).
 *
 * The x-axis can be aligned to the arbitrary axis with follow:
 * rotate z by 30 degrees
 * rotate y by -60 degrees
 * @return matrix to perform this transformation
 */
glm::mat4 generateM1()
{
    float z_angle = glm::radians(30.0f);// pi/6;//30
    float y_angle = glm::radians(-60.0f);//-pi/3;//-60
    float axis_rot = glm::radians(45.0f);//pi/4;//45

    glm::vec3 point_through = glm::vec3(1,0,-1);

    glm::mat4 MT1 = rotate_axis(point_through,y_angle,z_angle,axis_rot);

    return MT1;
}
//_____________________________________________________________________________________
/**
 * TASK M2
 *  Half the size of an object, using as fixed point (5,0,-2)
 * @return
 */
glm::mat4 generateM2()
{
    glm::vec3 point = glm::vec3(5,0,-2);
    float scaling_factor = 0.5;

    //Go to new center
    glm::mat4 translate = glm::translate(I,point);
    //scale in new center
    glm::mat4 scale = glm::scale(I,glm::vec3(scaling_factor));
    //Go back to original point
    glm::mat4 translate_back = glm::translate(I,-point);

    glm::mat4 MT2 = translate * scale * translate_back;

    return MT2;
}
//_____________________________________________________________________________________
/**
 * Mirror the starship along a plane passing through (1,1,1),
 * and obtained rotating 15 degree around the x axis the xz plane
 * @return
 */
glm::mat4 generateM3()
{
    glm::vec3 point = glm::vec3(1,1,1);
    glm::vec3 mirror_factor =  glm::vec3(1,-1,1); //XZ plane
    float plane_angle = glm::radians(15.0f);

    //Emulate origin by rotating of 15 degrees and translate to point
    glm::mat4 translate = glm::translate(I,point);
    glm::mat4 rotate_plane = x_rotation(plane_angle);

    //Mirror around  fake "XZ"
    glm::mat4  mirror = glm::scale(I,mirror_factor);

    //bring back to original location and rotation
    glm::mat4 rotate_plane_back = x_rotation(-plane_angle);
    glm::mat4 translate_back = glm::translate(I,-point);

    //Compute matrix
    glm::mat4 MT3 = translate * rotate_plane * mirror * rotate_plane_back * translate_back;

    return MT3;
}
//_____________________________________________________________________________________
/**
 * Apply the inverse of the following sequence of transforms:
 * Translation of (0, 0, 5)
 * then rotation of 30 degree around the Y axis,
 * and finally a uniform scaling of a factor of 3.
 * @return
 */
glm::mat4 generateM4()
{
    glm::vec3 point = glm::vec3(0,0,5);
    float y_angle = glm::radians(30.0f);
    float scaling_factor = 3.0;

    glm::mat4 translate_back = glm::translate(I,-point);
    glm::mat4 rotate_back = y_rotation(-y_angle);
    glm::mat4 scaling_back = glm::scale(I,glm::vec3(1/scaling_factor));

    //INVERSE OF COMPOSITE TRANSFORM IS THE PRODUCT OF INVERSE IN OPPOSITE ORDER
    glm::mat4 MT4 = translate_back  * rotate_back  * scaling_back ;
    return MT4;
}
