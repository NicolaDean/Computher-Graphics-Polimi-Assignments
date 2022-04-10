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

//OLD FUNCTIONS
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

////------------------------------------------------------
////------------------------------------------------------
////---------NEW CODE VERSION-----------------------------
////------------------------------------------------------
////------------------------------------------------------

/**
 * Contain a List for Vertex and one for Indexes to represent Meshes
 */
class Mesh{
protected:
    std::vector<float>* mesh;
    std::vector<uint32_t>* indexes;

public:
    Mesh(std::vector<float>* mesh_vec,std::vector<uint32_t>* indexes_vec){
        mesh = mesh_vec;
        indexes = indexes_vec;
    }

    void addVertex(Vertex v){
        mesh->push_back(v.x);
        mesh->push_back(v.y);
        mesh->push_back(v.z);
    }

    void addTriangle(uint32_t x,uint32_t y,uint32_t z){
        indexes->push_back(x);
        indexes->push_back(y);
        indexes->push_back(z);
    }
};

/**
 * Definition of cubes in form of vertex and indexes
 */
class Cube : public Mesh{

public:
    Cube(std::vector<float>* mesh_vec,std::vector<uint32_t>* indexes_vec): Mesh(mesh_vec,indexes_vec){
        generateCubeVertex();
        generateCubeStrips();
    }

    /**
 * Generate vertex of cubes
 */
    void generateCubeVertex(){
        Vertex v;
// first vertex of M1
        v = Vertex(-1,-1,-1);
        this->addVertex(v);

// second vertex of M1
        v = Vertex(1,-1,-1);
        this->addVertex(v);

// third vertex of M1
        v = Vertex(1,1,-1);
        this->addVertex(v);

// fourth vertex of M1
        v = Vertex(-1,1,-1);
        this->addVertex(v);

// fifth vertex of M1
        v = Vertex(-1,-1,1);
        this->addVertex(v);

//sixth vertex of M1
        v = Vertex(1,-1,1);
        this->addVertex(v);

// seventh vertex of M1
        v = Vertex(1,1,1);
        this->addVertex(v);

// eights vertex of M1
        v = Vertex(-1,1,1);
        this->addVertex(v);
    }

    void generateCubeStrips(){

// first triangle
        this->addTriangle(0,1,2);

// second triangle
        this->addTriangle(2,3,0);

// third triangle
        this->addTriangle(0,3,4);

// forth triangle
        this->addTriangle(4,3,7);

// fifth triangle
        this->addTriangle(5,6,7);

// six triangle
        this->addTriangle(7,4,5);

// seven triangle
        this->addTriangle(1,6,5);

// eight triangle
        this->addTriangle(1,2,6);

// nine triangle
        this->addTriangle(7,6,2);

//ten triangle
        this->addTriangle(3,2,7);

// eleven triangle
        this->addTriangle(4,5,0);

//twelve triangle
        this->addTriangle(1,0,5);

    }
};

/**
 * Definition of cylinder in form of vertex and indexes
 */
class Cylinder : public Mesh{
public:
    Cylinder(Vertex center,float height,float radius,int NSlices,std::vector<float>* mesh_vec,std::vector<uint32_t>* indexes_vec): Mesh(mesh_vec,indexes_vec){
        ////FIRST CIRCLE
        drawCircle(center,height/2,radius,NSlices,0);

        ////SECOND CIRCLE
        drawCircle(center,-height/2,radius,NSlices,NSlices+1);

        ////BORDERS OF CYLINDER
        drawBorders(NSlices);
    }

    void drawCircle(Vertex center,float height,float radius,int NSlices,int indexStart){

        //CENTER
        Vertex v = Vertex(center.x,center.y+height,center.z);
        this->addVertex(v);
        float slice=0;
        float x,y,z = 0;

        //VERTEX
        for(int i = 0; i < NSlices; i++) {
            slice = (2.0 * M_PI) * ((float)i/(float)NSlices);
            x = center.x + radius * cos(slice) ;
            y = center.y + height; // y of the vertex
            z = center.z + radius * sin(slice); // z of the vertex

            v = Vertex(x,y,z);
            this->addVertex(v);
        }

        //INDEX
        for(int i = indexStart; i < (NSlices + indexStart); i++) {
            x = indexStart;
            y = i+1;
            z = ((i + 1) % (NSlices + indexStart)) + 1;

            if(z==1) z=indexStart+1;

            //printf("Vertex [%d] = \t(%f,%f,%f)\n",i,x,y,z);
            this->addTriangle(x,y,z);
        }
    }

    void drawBorders(int NSlices){
        float x,y,z = 0;

        for(int i = 1; i < NSlices+1; i++) {
            x = i;
            y = NSlices+ 1 + i;
            z = ((i + 1) % (NSlices+1));

            if(z==0) z=1;

            //printf("Triangle 1 [%d] = \t(%f,%f,%f)\n",i,x,y,z);

            this->addTriangle(x,y,z);

            x = i+1;
            y = NSlices+ 1 + i;
            z = (NSlices+ 2 + i)%(2*NSlices +2);

            if(x==NSlices+1) x = 1;
            if(z==0) z=NSlices+2;

            //printf("Triangle 2 [%d] = \t(%f,%f,%f)\n",i,x,y,z);
            this->addTriangle(x,y,z);
        }
    }
};

/**
 * Definition of Sphere in form of vertex and indexes
 */
class Sphere : public Mesh{
public:
    Sphere(Vertex center,float radius,int NumStack,int NumSector,std::vector<float>* mesh_vec,std::vector<uint32_t>* indexes_vec): Mesh(mesh_vec,indexes_vec){

        generateVertex(center,radius,NumStack,NumSector);

        generateIndex(NumStack,NumSector);
    }

    void generateVertex(Vertex center,float radius,int NumStack,int NumSector){
        float theta;
        float fi;

        float x;
        float y;
        float z;

        Vertex v;
        int a=0;
        //GENERATING ALL VERTEX

        //FIRST VERTEX 0 (first)
        v = Vertex(0,0,1);
        this->addVertex(v);

        for(int curr_stack=1;curr_stack<NumStack;curr_stack++){
            fi = (M_PI/2) - M_PI*((float)curr_stack/NumStack);
            for(int curr_sector=0;curr_sector<NumSector;curr_sector++){
                theta = 2 * M_PI*((float)curr_sector/NumSector);

                x = (radius*cos(fi)) * cos(theta);
                y = (radius*cos(fi)) * sin(theta);
                z = (radius*sin(fi));

                //printf("VERTEX (%d)  [%d][%d] (%f,%f,%f)\n", a,curr_stack, curr_sector,x,y,z);
                a++;
                v = Vertex(x,y,z);
                this->addVertex(v);
            }
        }
        //LAST VERTEX
        v = Vertex(0,0,-1);
        this->addVertex(v);

        a=0;
        for(int i=0;i<mesh->size();i=i+3){
            printf("VERTEX (%d) (%f,%f,%f)\n", a,mesh->at(i),mesh->at(i+1),mesh->at(i+2));
            a++;
        }
    }

    void generateIndex(int NumStack,int NumSector){
        int first =1;
        //GENERATE ALL INDEX
        for(int curr_stack=0;curr_stack<NumStack-1;curr_stack++){
            for(int curr_sector=0;curr_sector<NumSector;curr_sector++){
                int i = curr_stack*NumSector +  curr_sector+1;
                int j = (curr_stack+1)*NumSector + curr_sector+1;

                int next_i = i + 1;
                int next_j = j + 1;


                if(next_i == (curr_stack+1)*NumSector+1)next_i=(curr_stack)*NumSector+1;
                if(next_j == (curr_stack+2)*NumSector+1) next_j=(curr_stack+1)*NumSector+1;

                //DRAW MIDDLE SQUARES SECTOR BY SECTOR (2 TRIANGLE EACH SQUARE)
                if(curr_stack<NumStack-2)
                {
                    this->addTriangle(i, j, next_i);
                    //printf("TRI ONE [%d][%d] = \t(%d,%d,%d)\n", curr_stack, curr_sector, i, j, next_i);

                    this->addTriangle(next_i, j, next_j);
                    //printf("TRI TWO [%d][%d] = \t(%d,%d,%d)\n",curr_stack,curr_sector,next_i,j,next_j);
                }

                i--;
                j--;

                //DRAW FIRST CIRCLE (ONLY TRIANGLE)
                if(curr_stack == 0){
                    i=i+1;
                    next_i = i+1;

                    if(next_i == NumSector+1) next_i = 1;
                    this->addTriangle(0, i, next_i);
                    //printf("LINE ONE [%d][%d] = \t(%d,%d,%d)\n", curr_stack, curr_sector, 0, i, next_i);

                }
                //DRAW LAST CIRCLE (ONLY TRIANGLE)
                if(curr_stack == (NumStack-2))
                {
                    i=i+1;
                    next_i = i+1;

                    if(next_i == (curr_stack+1)*NumSector+1) next_i = curr_stack*NumSector+1;
                    this->addTriangle((curr_stack+1)*NumSector, i, next_i);
                    //printf("LINE TWO [%d][%d] = \t(%d,%d,%d)\n", curr_stack, curr_sector, (curr_stack+1)*NumSector+1, i, next_i);

                }

            }
        }
    }
};

/**
 * Definition of Spiral in form of vertex and indexes
 */
class Spiral : public Mesh{
public:
    Spiral(float helix_radius,float ring_radius,int NumHelix,int NumRings,int levels,std::vector<float>* mesh_vec,std::vector<uint32_t>* indexes_vec): Mesh(mesh_vec,indexes_vec){

        generateSpiralVertex(helix_radius,ring_radius,NumHelix,NumRings,levels);

        generateSpringIndex(NumHelix,NumRings);
    }

    void generateSpiralVertex(float helix_radius,float ring_radius,int NumHelix,int NumRings,int levels){

        float helix_x,helix_y,helix_z;
        float x,y,z;
        float theta,ring_slice;
        float constant = 0.2;

        int c = 0;
        levels = levels * 2;
        //Generate Helix path (and use helix points as centers for Rings)
        for(int helix = 0;helix < NumHelix;helix++,c=c+levels){
            theta = -M_PI/2 + M_PI * ((float)c/NumHelix);

            //Helix point coordinatex
            helix_x = helix_radius * cos(theta);
            helix_y = constant * theta;
            helix_z = helix_radius * sin(theta);

            //Use Helix Point as center for a ring
            for(int ring = 0;ring < NumRings;ring++){
                ring_slice = (2.0 * M_PI) * ((float)ring/(float)NumRings);

                x = ring_radius * cos(theta) * sin(ring_slice) + helix_x;
                y = ring_radius * cos(ring_slice) + helix_y;
                z = ring_radius * sin(theta) * sin(ring_slice) + helix_z;

                Vertex v = Vertex(x,y,z);
                this->addVertex(v);
            }
        }
    }

    void generateSpringIndex(int NumHelix,int NumRings){
        //TODO check for last RING triangles
        int x,y,z = 0;
        int offset = 0;
        for(int helix=0;helix<NumHelix-1;helix++){
            offset = helix*NumRings;
            for(int ring=0;ring<NumRings;ring++){

                x = ring + offset;//i
                y = NumRings + ring + offset;//j
                z = NumRings + ring + 1 + offset;//j+1

                if(z == 2*NumRings + offset) z = NumRings + offset;

                printf("Triangle 1 [%d] = \t(%d,%d,%d)\n",ring,x,y,z);

                this->addTriangle(x,y,z);

                x = ring + offset;//i
                y = NumRings + ring + 1 + offset;//j+1
                z = ring + 1 + offset;//i+1

                if(y == 2*NumRings + offset) y = NumRings + offset;
                if(z == NumRings + offset) z = offset;

                //printf("Triangle 2 [%d] = \t(%d,%d,%d)\n",ring,x,y,z);
                this->addTriangle(x,y,z);
            }
        }
    }
};


////------------------------------------------------------
////------------------------------------------------------
////---------ASSIGNMENT MAIN CODE-------------------------
////------------------------------------------------------
////------------------------------------------------------
// this function creates the geometries to be shown, and output thems
// in global variables M1_vertices and M1_indices to M4_vertices and M4_indices
void makeModels() {

    ////--------------------------------------------------------------------------
    //// M1 : Cube----------------------------------------------------------------
    ////--------------------------------------------------------------------------
    Cube cube = Cube(&M1_vertices,&M1_indices);

    ////--------------------------------------------------------------------------
    //// M2 : Cylinder------------------------------------------------------------
    ////--------------------------------------------------------------------------

    float radius = 1;
    float height = 1;
    Vertex center = Vertex(0,0,-3);

    Cylinder cylinder = Cylinder(center,height,radius,72,&M2_vertices,&M2_indices);
    //addCircleToMesh(center,radius,height,&M2_vertices,&M2_indices);

    ////--------------------------------------------------------------------------
    //// M3 : Sphere------------------------------------------------------------
    ////--------------------------------------------------------------------------

    Sphere sphere = Sphere(Vertex(1,1,1),1,20,20,&M3_vertices,&M3_indices);
    //addSphereToMesh(Vertex(1,1,1),1,&M3_vertices,&M3_indices);

////--------------------------------------------------------------------------
//// M4 : Spring------------------------------------------------------------
////--------------------------------------------------------------------------

    Spiral spiral = Spiral(1,0.2,1000,72,20,&M4_vertices,&M4_indices);

}