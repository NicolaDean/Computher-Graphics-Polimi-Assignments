//
// Created by nicomane on 02/03/22.
//

#ifndef A01_CUSTOMDRAWING_H
#define A01_CUSTOMDRAWING_H

#endif //A01_CUSTOMDRAWING_H

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <optional>
#include <set>
#include <cstdint>
#include <algorithm>
#include <fstream>
#include <array>
#include <unordered_map>



class P {       // The class
    public:
        float x;
        float y;

        P(float x,float y)
        {
            this->x = x;
            this->y = y;
        }
};

class Color {
    public:
        float r;
        float g;
        float b;

        Color(float r,float g,float b)
        {
            this->r = r;
            this->g = g;
            this->b = b;
        }

        static Color* getColor(int r,int g,int b){

            return new Color((float)r/255,(float)g/255,(float)b/255);
        }
};

struct Tri {
    float x1, y1;
    float x2, y2;
    float x3, y3;
    float r, g, b;

    void print() {
        std::cout << x1 << " " << y1 << "\t";
        std::cout << x2 << " " << y2 << "\t";
        std::cout << x3 << " " << y3 << "\t";
        std::cout << "[" << r << "," << g << "," << b << "]\n";
    };
};

//GLOBAL TRIANGLES-----------------------------------------------------
std::vector<Tri> *triangles;
//-------------------------------------------------------------------------

void Triangle(float x1, float y1, float x2, float y2, float x3, float y3, float r, float g, float b) {
    Tri t;
    t.x1 = x1;
    t.y1 = y1;
    t.x2 = x2;
    t.y2 = y2;
    t.x3 = x3;
    t.y3 = y3;
    t.r = r;
    t.g = g;
    t.b = b;

    triangles->push_back(t);
}

void triangle(P* v1,P* v2,P* v3,Color* c){
    Tri t;
    t.x1 = v1->x;
    t.y1 = v1->y;
    t.x2 = v2->x;
    t.y2 = v2->y;
    t.x3 = v3->x;
    t.y3 = v3->y;
    t.r = c->r;
    t.g = c->g;
    t.b = c->b;

    triangles->push_back(t);
};

void drawPoly(P* center,float radius,int n,Color* col,float rotation=0){
    P* p[n]; //List of vertex of our poly
    float N = (float)n;
    float pi = 3.14;  //pi greco
    for(int i=0;i<n;i++){

        float i_angle = (float) i;
        float radRotation = rotation * pi/180;
        float angle_offset = (float)(2.0*pi)*(i_angle/N) + radRotation;

        float x_offset = radius*cos(angle_offset);
        float y_offset = radius*sin(angle_offset);

        std::cout<<"x: "<<x_offset<<" | y:"<< y_offset<<"\n";

        p[i] = new P(center->x + x_offset,center->y + y_offset);
    }

    for(int i=0;i<n-1;i++){
        //triangle(p[i],p[i+1],center,col);
        triangle(p[i],p[i+1],center,col);
    }
    triangle(p[0],p[n-1],center,col);

}


void rectangle (float x1, float y1, float x2, float y2, float r, float g, float b){
    Triangle(x1,y1,x1,y2,x2,y1,r,g,b);
    Triangle(x2,y2,x1,y2,x2,y1,r,g,b);
};

void rectangle (P* p1,P* p2,Color* col){
    rectangle(p1->x,p1->y,p2->x,p2->y,col->r,col->g,col->b);
}
void square(P* center,float l,Color* col,float rot =0){
    drawPoly(center,l*sqrt(2),4,col,45);
}
void circle(P* center,float radius,Color* col){
    drawPoly(center,radius,20,col);
}

//FIRST TEST WITH REGULAR POLY
void hexagon (P* c,float range,Color* col){

    float pi = 3.14;

    float rcos = range*cos(pi/3); //pi/3 = 60
    float rsin = range*sin(pi/3);

    P* V1 = new P(c->x + range,c->y );
    P* V2 = new P(c->x + rcos,c->y  + rsin);
    P* V3 = new P(c->x - rcos,c->y  + rsin);
    P* V4 = new P(c->x - range,c->y );
    P* V5 = new P(c->x - rcos,c->y  - rsin);
    P* V6 = new P(c->x + rcos,c->y - rsin);


    triangle(V1,V2,c,col);
    triangle(V2,V3,c,col);
    triangle(V3,V4,c,col);
    triangle(V4,V5,c,col);
    triangle(V5,V6,c,col);
    triangle(V6,V1,c,col);
};


void cloud(P* center,float size)
{
    Color* col = Color::getColor(147, 210, 219);
    circle(center,0.05,col);
    circle(new P(center->x + 0.045,center->y),0.05,col);
    circle(new P(center->x + 0.065,center->y + 0.045),0.05,col);
    circle(new P(center->x - 0.045,center->y + 0.045),0.05,col);
}

void flower(P* base,Color* col)
{
    P* center = new P(base->x,base->y - 0.1);

    rectangle(base,new P(base->x + 0.02,base->y - 0.05),new Color(0,1,0));
    circle(center,0.05,col);
    circle(center,0.01,new Color(1,1,0));
}

//-----------------------------------------------------------------------
void drawTriangles(std::vector<Tri>* vector){
    triangles = vector;

    //ALL MY DRAWINGS:---------------------------

    //House Body
    square(new P(0.35,0.5),0.32,new Color(0,0,1));
    //Tetto
    triangle(new P(0.35,-0.45),new P(-0.05,0.2),new P(0.72,0.2),new Color(1,0,0));
    //Door
    rectangle(new P(0.28,0.45), new P(0.42,0.8),new Color(1,1,0));

    //Windows
    square(new P(0.2,0.35),0.07,new Color(1,1,0));
    square(new P(0.5,0.35),0.07,new Color(1,1,0));
    //Sun
    circle(new P(0.65,-0.65),0.1,new Color(1,0.5,0));
    //Clouds
    cloud(new P(0,-0.25),2);
    cloud(new P(0.2,-0.7),2);
    cloud(new P(-0.75,-0.7),2);
    //Prato
    rectangle(new P(1,1), new P(-1,0.8),new Color(0,1,0));

    //Flowers
    flower(new P(-0.1,0.8),new Color(1,0.2,0.2));
    flower(new P(0.75,0.8),Color::getColor(218,112,214));
    flower(new P(-0.3,0.8),Color::getColor(235, 161, 52));
    flower(new P(-0.5,0.8),Color::getColor(218,112,214));

}







