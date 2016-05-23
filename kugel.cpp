#include "kugel.h"
#include <math.h>
#include <iostream>


kugel::kugel(float r, float g, float b){
    red = r;
    green = g;
    blue = b;
    this->armCount = 0;
    rotationZvalue = new float[0];
    jointaddHeights = new float[0];

    initialize();
}

kugel::kugel(float r, float g, float b, int armCounts){
    red = r;
    green = g;
    blue = b;
    this->armCount = armCounts;
    rotationZvalue = new float[armCount];
    jointaddHeights = new float[armCount];
    initialize();
}

void kugel::initialize(){
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

    float newdy = dy;

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

        newdy = newdy - rotr;
    }
    if(this->armCount != 0){
    for(int i = 0; i < this->armCount; i++){
            float rad;
            if(rotationZvalue[i] != 0 && i == this->armCount-1){
                rad = jointaddHeights[i];
            }
            else{
                rad = 0;
            }
         if(i == 0){
              if(rotationZvalue[0] != 0){
                  points1 = rotm.rotatez(1.0,points1[0], rad + points1[1],points1[2], rotationZvalue[i]);
                  points2 = rotm.rotatez(1.0,points2[0], rad + points2[1],points2[2], rotationZvalue[i]);
                  points3 = rotm.rotatez(1.0,points3[0], rad + points3[1],points3[2], rotationZvalue[i]);
                  points4 = rotm.rotatez(1.0,points4[0], rad + points4[1],points4[2], rotationZvalue[i]);
                  newdy = newdy - rad;
              }
         }
         else{
            points1 = rotm.rotatez(1.0,points1[0], rad + points1[1],points1[2], rotationZvalue[i]);
            points2 = rotm.rotatez(1.0,points2[0], rad + points2[1],points2[2], rotationZvalue[i]);
            points3 = rotm.rotatez(1.0,points3[0], rad + points3[1],points3[2], rotationZvalue[i]);
            points4 = rotm.rotatez(1.0,points4[0], rad + points4[1],points4[2], rotationZvalue[i]);
            newdy = newdy - rad;
            }
         }
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


    glVertex3f(dx + x1, newdy + y1, dz + z1);
    glVertex3f(dx + x2, newdy + y2, dz + z2);
    glVertex3f(dx + x3, newdy + y3, dz + z3);
    glVertex3f(dx + x4, newdy + y4, dz + z4);


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

 void kugel::setRotationsZvalue(float* rotationZvalue, float* jointaddHeights){
     this->rotationZvalue = &rotationZvalue[0];
     this->jointaddHeights = &jointaddHeights[0];
 }
