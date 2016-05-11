#include "kugel.h"
#include <math.h>
#include <iostream>


kugel::kugel(float r, float g, float b){
    red = r;
    green = g;
    blue = b;
    rotm = rotationsmatrix();
    dx = 0;
    dy = 0;
    dz = 0;
    rotx = 0;
    roty = 0;
    rotz = 0;
    rotr = 0;
}

void kugel::drawQuad(float radius, float dx, float dy, float dz, float alpha, float beta){
glBegin(GL_QUADS);
    glColor4f(red, green, blue, 1.0);
    float breite = 2; //10*pi/180;

    float *points1 = rotm.rotatez(1.0, radius, 0, 0, alpha);
    points1 = rotm.rotatey(1.0, points1[0], points1[1], points1[2], beta);

    float *points2 = rotm.rotatez(1.0, radius, 0, 0, alpha+breite);
    points2 = rotm.rotatey(1.0, points2[0], points2[1], points2[2], beta);

    float *points3 = rotm.rotatez(1.0, radius, 0, 0, alpha+breite);
    points3 = rotm.rotatey(1.0, points3[0], points3[1], points3[2], beta+breite);

    float *points4 = rotm.rotatez(1.0, radius, 0, 0, alpha);
    points4 = rotm.rotatey(1.0, points4[0], points4[1], points4[2], beta+breite);

    if(rotx != 0){
      // transd = rotm.rotateX(rotr, dx, dy,dz,360-rotx);
    }
    if(roty != 0){
      // transd = rotm.rotatey(rotr, dx, dy,dz,360-roty);
    }
    if(rotz != 0){
        points1 = rotm.rotatez(1.0, points1[0], rotr+points1[1],points1[2],rotz);
        points2 = rotm.rotatez(1.0, points2[0], rotr+points2[1],points2[2],rotz);
        points3 = rotm.rotatez(1.0, points3[0], rotr+points3[1],points3[2],rotz);
        points4 = rotm.rotatez(1.0, points4[0], rotr+points4[1],points4[2],rotz);

        dy = dy - rotr;
    }

    float x1 = points1[0];
    float y1 = points1[1];
    float z1 = points1[2];

    float x2 = points2[0];
    float y2 = points2[1];
    float z2 = points2[2];

    float x3 = points3[0];
    float y3 = points3[1];
    float z3 = points3[2];

    float x4 = points4[0];
    float y4 = points4[1];
    float z4 = points4[2];


    glVertex3f(dx + x1, dy + y1, dz + z1);
    glVertex3f(dx + x2, dy + y2, dz + z2);
    glVertex3f(dx + x3, dy + y3, dz + z3);
    glVertex3f(dx + x4, dy + y4, dz + z4);


}

 void kugel::drawKugel(float radius, float x, float y, float z, int kreisHoehe, int kreisBreite){
        double alpha = 270;
        double beta = 0.01;



        //beta = z achse, alpha = y achse
        while(alpha >= kreisHoehe){
               beta = 0.0;
             int teilBreite = 360;
             if(alpha <= kreisHoehe + 2){
                 teilBreite = 360 - kreisBreite;
             }

            while(beta <= teilBreite){
             drawQuad(radius, x, y, z, alpha, beta);
             beta+= 2;
            }
            alpha -= 2;
      }
   }

 void kugel::setRotationX(float radius,float rotx){
     this->rotx = rotx;
     this->rotr = radius;
 }

 void kugel::setRotationY(float radius, float roty){
     this->roty = roty;
      this->rotr = radius;
 }

 void kugel::setRotationZ(float radius, float rotz){
     this->rotz = rotz;
      this->rotr = radius;
 }
