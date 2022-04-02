/**************
 Function Triangle(float x1, float y1, float x2, float y2, float x3, float y3, float r, float g, float b)

 draws a triangle connecting points (x1,y1)  (x2, y2) and (x3, y3), colored with the (r,g,b) specified color.
 vertex are expressed in Normalized screen coordinates, (i.e. in range [-1,+1]), following the Vulkan convention.
 The red, green and blue (r,g,b) values are in the range [0,1].
 
 Using function Triangle(...) try to draw a children house, similar to the one below.
 
 First remove the two function below (given only as an example), and replace them with your own.
 Since it is a C program, you can use for loops if you think it can be helpful in your drawing.
 The for() command below that draws a sun like shape in exact center of the screen near the top,
 is an example on how you can use it: please remove it, and replace it with your own code.
 It is not necessery to use a for loop if you do not really need it: it has been put here only as
 an example to help students not familiar with C++.
***************/



auto triangle = [&] (P* v1,P* v2,P* v3,Color* c){
    Triangle(v1->x,v1->y,v2->x,v2->y,v3->x,v3->y,c->r,c->g,c->b);
};


auto square = [&] (float x1, float y1, float x2, float y2, float r, float g, float b){
    Triangle(x1,y1,x1,y2,x2,y1,r,g,b);
    Triangle(x2,y2,x1,y2,x2,y1,r,g,b);
};

//FIRST TEST WITH REGULAR POLY
auto exagon = [&] (P* c,float range,Color* col){

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

auto poly = [&] (P* c,float range,int n,Color* col){

    P* p[n]; //List of vertex of our poly

    int pi = 3.14;
    float angle;
    float angle_rad;

    angle = 30;
    angle_rad = pi / 180 * angle;

    P* p1 = new P(c->x + range * cos(angle_rad),c->y + range*sin(angle_rad));
    P* p2;
    for(int i=1;i<n;i++){

        angle = 60 * (i) - 30;
        angle_rad = 3.14 / 180 * angle;
        p2 = new P(c->x + range*cos(angle_rad),c->y + range*sin(angle_rad));
        triangle(p1,p2,c,col);
        p1 = p2;
        //p[i] = P* p2 = new P(c->x + range * cos(angle_rad),c->y + range*sin(angle_rad))
    }

    /*for(int i=0;i<n-1;i++){
        triangle(p[i],p[i+1],c,col);
    }
    triangle(p[0],p[n-1],c,col);*/

};

//pippo();
pippo(new P(0,0),0.5,6,new Color(1,1,0));
//Triangle(1,0.08, 0,1, -1,1,   1,0,0);	// Draws a red triangle pointing right
//Triangle(1,-1, 0,1, 1,1,   0,1,0);	// Draws a green triangle pointing left

//square(0,0,1,1,0,0,1);
//exagon(new P(0,0),0.5,new Color(0,1,0));

poly(new P(0,0),0.5,6,new Color(1,1,0));

/*
for(int i = 0; i < 32; i++) {
	Triangle( 0.00 + 0.05 * cos(6.28/32*(i-0.5)), -0.80 + 0.05 * sin(6.28/32*(i-0.5)),
			  0.00 + 0.10 * cos(6.28/32*i), -0.80 + 0.10 * sin(6.28/32*i),
			  0.00 + 0.05 * cos(6.28/32*(i+0.5)), -0.80 + 0.05 * sin(6.28/32*(i+0.5)),
			  1,0,0);
}*/
