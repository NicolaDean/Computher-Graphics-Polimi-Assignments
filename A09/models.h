#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <array>
#include <cstring>
#include <optional>
#include <set>
#include <cstdint>
#include <algorithm>
#include <fstream>
#include <unordered_map>

std::vector<float> M1_vertices;
std::vector<uint32_t> M1_indices;
std::vector<float> M2_vertices;
std::vector<uint32_t> M2_indices;
std::vector<float> M3_vertices;
std::vector<uint32_t> M3_indices;
std::vector<float> M4_vertices;
std::vector<uint32_t> M4_indices;
int Mstart[4], Mlen[4];

class Vertex{
public:
    float x;
    float y;
    float z;

    Vertex(){}
    Vertex(float X,float Y,float Z){
        x = X;
        y = Y;
        z = Z;
    }
};

void addVertexToMesh(Vertex v,std::vector<float>* mesh){
    mesh->push_back(v.x);
    mesh->push_back(v.y);
    mesh->push_back(v.z);
}

void addTriangleToStrips(uint32_t x,uint32_t y,uint32_t z,std::vector<uint32_t>* indexes){
    indexes->push_back(x);
    indexes->push_back(y);
    indexes->push_back(z);
}

/**
 * Generate vertex of cubes
 */
void generateCubeVertex(){
    Vertex v;
// first vertex of M1
    v = Vertex(-1,-1,-1);
    addVertexToMesh(v,&M1_vertices);

// second vertex of M1
    v = Vertex(1,-1,-1);
    addVertexToMesh(v,&M1_vertices);

// third vertex of M1
    v = Vertex(1,1,-1);
    addVertexToMesh(v,&M1_vertices);

// fourth vertex of M1
    v = Vertex(-1,1,-1);
    addVertexToMesh(v,&M1_vertices);

// fifth vertex of M1
    v = Vertex(-1,-1,1);
    addVertexToMesh(v,&M1_vertices);

//sixth vertex of M1
    v = Vertex(1,-1,1);
    addVertexToMesh(v,&M1_vertices);

// seventh vertex of M1
    v = Vertex(1,1,1);
    addVertexToMesh(v,&M1_vertices);

// eights vertex of M1
    v = Vertex(-1,1,1);
    addVertexToMesh(v,&M1_vertices);
}

void generateCubeStrips(){

// first triangle
    addTriangleToStrips(0,1,2,&M1_indices);

// second triangle
    addTriangleToStrips(2,3,0,&M1_indices);

// third triangle
    addTriangleToStrips(0,3,4,&M1_indices);

// forth triangle
    addTriangleToStrips(4,3,7,&M1_indices);

// fifth triangle
    addTriangleToStrips(5,6,7,&M1_indices);

// six triangle
    addTriangleToStrips(7,4,5,&M1_indices);

// seven triangle
    addTriangleToStrips(1,6,5,&M1_indices);

// eight triangle
    addTriangleToStrips(1,2,6,&M1_indices);

// nine triangle
    addTriangleToStrips(7,6,2,&M1_indices);

//ten triangle
    addTriangleToStrips(3,2,7,&M1_indices);

// eleven triangle
    addTriangleToStrips(4,5,0,&M1_indices);

//twelve triangle
    addTriangleToStrips(1,0,5,&M1_indices);

}

void addCircleToMesh(Vertex center,float radius,float height,std::vector<float>* mesh,std::vector<uint32_t>* indexes)
{
    int NSlices = 72;
    float x;
    float y;
    float z;
    float slice;
    Vertex v;

    ////FIRST CIRCLE
    //CENTER
    v = Vertex(center.x,center.y+height/2,center.z);
    addVertexToMesh(v,mesh);
    //VERTEX
    for(int i = 0; i < NSlices; i++) {
        slice = (2.0 * M_PI) * ((float)i/(float)NSlices);
        x = center.x + radius * cos(slice) ;
        y = center.y + height/2; // y of the vertex
        z = center.z + radius * sin(slice); // z of the vertex

        v = Vertex(x,y,z);
        addVertexToMesh(v,mesh);
    }
    //INDEX
    for(int i = 0; i < NSlices; i++) {
        x = 0;
        y = i+1;
        z = ((i + 1) % NSlices) + 1;
        printf("Vertex [%d] = \t(%f,%f,%f)\n",i,x,y,z);
        addTriangleToStrips(x,y,z,indexes);
    }


    ////SECOND CIRCLE
    //CENTER
    v = Vertex(center.x,center.y-height/2,center.z);
    addVertexToMesh(v,mesh);

    //VERTEX
    for(int i = 0; i < NSlices; i++) {
        slice = (2.0 * M_PI) * ((float)i/(float)NSlices);
        x = center.x + radius * cos(slice) ;
        y = center.y - height/2; // y of the vertex
        z = center.z + radius * sin(slice); // z of the vertex

        v = Vertex(x,y,z);
        addVertexToMesh(v,mesh);
    }

    //INDEX
    for(int i = NSlices+1; i < 2*NSlices+1; i++) {
        x = NSlices+1;
        y = i+1;
        z = ((i + 1) % (2*NSlices+1)) + 1;
        if(z==1) z = x+1;

        printf("Vertex [%d] = \t(%f,%f,%f)\n",i,x,y,z);
        addTriangleToStrips(x,y,z,indexes);
    }

    ////SIDE RECTANGLES
    //INDEX
    for(int i = 1; i < NSlices+1; i++) {
        x = i;
        y = NSlices+ 1 + i;
        z = ((i + 1) % NSlices);

        printf("Vertex [%d] = \t(%f,%f,%f)\n",i,x,y,z);
        addTriangleToStrips(x,y,z,indexes);

        x = i+1;
        y = NSlices+ 1 + i;
        z = (NSlices+ 2 + i)%(2*NSlices +1);

        addTriangleToStrips(x,y,z,indexes);
    }
}

void addSphereToMesh(Vertex center,float radius,std::vector<float>* mesh,std::vector<uint32_t>* indexes){

    int NumSector = 20;
    int NumStack  = 20;

    float theta;
    float fi;

    float x;
    float y;
    float z;

    Vertex v;
    //GENERATING ALL VERTEX
    for(int curr_stack=0;curr_stack<NumStack;curr_stack++){
        fi = (M_PI/2) - M_PI*((float)curr_stack/NumStack);
        for(int curr_sector=0;curr_sector<NumSector;curr_sector++){
            theta = 2 * M_PI*((float)curr_sector/NumSector);

            x = (radius*cos(fi)) * cos(theta);
            y = (radius*cos(fi)) * sin(theta);
            z = (radius*sin(fi));
            v = Vertex(x,y,z);
            addVertexToMesh(v,mesh);
        }
    }

    //GENERATE ALL INDEX
    for(int curr_stack=0;curr_stack<NumStack;curr_stack++){
        for(int curr_sector=0;curr_sector<NumSector;curr_sector++){
            int i = curr_stack*NumSector +  curr_sector;
            int j = (curr_stack+1)*NumSector + curr_sector;
            int next_i = (i+1) % ((curr_stack+1)*NumSector);
            int next_j = (j+1);

            if(next_j == (curr_stack+2)*NumSector) next_j = (curr_stack+1)*NumSector;

            if(j == NumStack*NumSector + 1) return;

            addTriangleToStrips(i,j,i+1,indexes);
            printf("LINE ONE [%d][%d] = \t(%d,%d,%d)\n",curr_stack,curr_sector,i,j,next_i);
            addTriangleToStrips(i+1,j,j+1,indexes);
            printf("LINE TWO [%d][%d] = \t(%d,%d,%d)\n",curr_stack,curr_sector,next_i,j,next_j);
        }
    }

}

// this function creates the geometries to be shown, and output thems
// in global variables M1_vertices and M1_indices to M4_vertices and M4_indices
    void makeModels() {
    ////--------------------------------------------------------------------------
    //// M1 : Cube----------------------------------------------------------------
    ////--------------------------------------------------------------------------
    // CUBE VERTEX
    generateCubeVertex();
    //INDEX STRIPS
    generateCubeStrips();

    ////--------------------------------------------------------------------------
    //// M2 : Cylinder------------------------------------------------------------
    ////--------------------------------------------------------------------------

    float radius = 1;
    float height = 1;
    Vertex center = Vertex(0,0,-3);

    addCircleToMesh(center,radius,height,&M2_vertices,&M2_indices);

    ////--------------------------------------------------------------------------
    //// M3 : Sphere------------------------------------------------------------
    ////--------------------------------------------------------------------------

    addSphereToMesh(Vertex(1,1,1),1,&M3_vertices,&M3_indices);



////--------------------------------------------------------------------------
//// M4 : Spring------------------------------------------------------------
////--------------------------------------------------------------------------


// Replace the code below, that creates a simple octahedron, with the one to create a spring.
M4_vertices.resize(3 * 6);

// Vertices definitions
M4_vertices[0]  =  0.0;
M4_vertices[1]  =  1.414;
M4_vertices[2]  = -1.0;
M4_vertices[3]  =  0.0;
M4_vertices[4]  = -1.414;
M4_vertices[5]  = -1.0;
M4_vertices[6]  = -1.0;
M4_vertices[7]  =  0.0;
M4_vertices[8]  = -2.0;
M4_vertices[9]  = -1.0;
M4_vertices[10] =  0.0;
M4_vertices[11] =  0.0;
M4_vertices[12] =  1.0;
M4_vertices[13] =  0.0;
M4_vertices[14] =  0.0;
M4_vertices[15] =  1.0;
M4_vertices[16] =  0.0;
M4_vertices[17] = -2.0;


// Resizes the indices array. Repalce the values with the correct number of
// indices (3 * number of triangles)
M4_indices.resize(3 * 8);

// indices definitions
M4_indices[0]  = 0;
M4_indices[1]  = 2;
M4_indices[2]  = 3;
M4_indices[3]  = 1;
M4_indices[4]  = 3;
M4_indices[5]  = 2;
M4_indices[6]  = 0;
M4_indices[7]  = 3;
M4_indices[8]  = 4;
M4_indices[9]  = 1;
M4_indices[10] = 4;
M4_indices[11] = 3;
M4_indices[12] = 0;
M4_indices[13] = 4;
M4_indices[14] = 5;
M4_indices[15] = 1;
M4_indices[16] = 5;
M4_indices[17] = 4;
M4_indices[18] = 0;
M4_indices[19] = 5;
M4_indices[20] = 2;
M4_indices[21] = 1;
M4_indices[22] = 2;
M4_indices[23] = 5;
}