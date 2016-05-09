#include "kugel.h"
#include <math.h>



kugel::kugel(float r, float g, float b){
    red = r;
    green = g;
    blue = b;
    rotm = rotationsmatrix();
    rotx = 0;
    roty = 0;
    rotz = 0;
}

void kugel::drawQuad(float radius, float dx, float dy, float dz, float alpha, float beta, float rotx, float roty, float rotz){
glBegin(GL_QUADS);
    glColor4f(red, green, blue, 1.0);
    float pi = 3.1415926;
    float breite = 5; //10*pi/180;

    float x1 = radius * cos(alpha  * pi /180) * cos(beta  * pi /180);
    float y1 = radius * sin(beta * pi /180);
    float z1 = radius * (-sin(alpha * pi /180)) * cos(beta * pi /180);

    float x2 = radius * cos((alpha+breite) * pi /180) * cos(beta * pi /180);
    float y2 = radius * sin(beta * pi /180);
    float z2 = radius * (-sin((alpha+breite) * pi /180)) * cos(beta * pi /180);

    float x3 = radius * cos((alpha+breite) * pi /180) * cos((beta+breite) * pi /180);
    float y3 = radius * sin((beta+breite) * pi /180);
    float z3 = radius * (-sin((alpha+breite)) * pi /180) * cos((beta+breite) * pi /180);

    float x4 = radius * cos(alpha * pi /180) * cos((beta+breite) * pi /180);
    float y4 = radius * sin((beta+breite) * pi /180);
    float z4 = radius * (-sin(alpha * pi /180)) * cos((beta+breite) * pi /180);


    if(rotx != 0.0){
        float *points =  rotm.rotateX(0,x1,y1,z1,rotx);
        float *points2 =  rotm.rotateX(0,x2,y2,z2,rotx);
        float *points3 =  rotm.rotateX(0,x3,y3,z3,rotx);
        float *points4 =  rotm.rotateX(0,x4,y4,z4,rotx);

        x1 = points[0];
        y1 = points[1];
        z1 = points[2];

        x2 = points2[0];
        y2 = points2[1];
        z2 = points2[2];

        x3 = points2[0];
        y3 = points2[1];
        z3 = points2[2];

        x4 = points4[0];
        y4 = points4[1];
        z4 = points4[2];
    }
    if(roty != 0.0){
        float *points =  rotm.rotatey(0,x1,y1,z1,roty);
        float *points2 =  rotm.rotatey(0,x2,y2,z2,roty);
        float *points3 =  rotm.rotatey(0,x3,y3,z3,roty);
        float *points4 =  rotm.rotatey(0,x4,y4,z4,roty);

        x1 = points[0];
        y1 = points[1];
        z1 = points[2];

        x2 = points2[0];
        y2 = points2[1];
        z2 = points2[2];

        x3 = points2[0];
        y3 = points2[1];
        z3 = points2[2];

        x4 = points4[0];
        y4 = points4[1];
        z4 = points4[2];
    }
    if(rotz != 0.0){
        float *points =  rotm.rotatez(0,x1,y1,z1,rotz);
        float *points2 =  rotm.rotatez(0,x2,y2,z2,rotz);
        float *points3 =  rotm.rotatez(0,x3,y3,z3,rotz);
        float *points4 =  rotm.rotatez(0,x4,y4,z4,rotz);

        x1 = points[0];
        y1 = points[1];
        z1 = points[2];

        x2 = points2[0];
        y2 = points2[1];
        z2 = points2[2];

        x3 = points2[0];
        y3 = points2[1];
        z3 = points2[2];

        x4 = points4[0];
        y4 = points4[1];
        z4 = points4[2];
    }

    glVertex3f(dx + x1, dy + y1, dz + z1);
    glVertex3f(dx + x2, dy + y2, dz + z2);
    glVertex3f(dx + x3, dy + y3, dz + z3);
    glVertex3f(dx + x4, dy + y4, dz + z4);

}

 void kugel::drawKugel(float radius, float x, float y, float z, int i, int j){
     drawKugel(radius, x, y, z, i, j, 0.0f, 0.0f, 0.0f);
 }

 void kugel::drawKugel(float radius, float x, float y, float z, int i, int j, float rotx, float roty, float rotz){

        double alpha = 0;
        double beta = -90;

        //beta = z achse, alpha = y achse
        while(beta <=i){
               alpha = 0.0;
            while(alpha <= j){
                drawQuad(radius, x, y, z, alpha, beta, rotx, roty, rotz);
                alpha+= 5;
            }

            beta += 5;
      }
   }

 void kugel::setRotationX(float rotx){
     this->rotx = rotx;
 }

 void kugel::setRotationY(float roty){
     this->roty = roty;
 }

 void kugel::setRotationZ(float rotz){
     this->rotz = rotz;
 }
