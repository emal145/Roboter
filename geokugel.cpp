#include "geokugel.h"
#include <math.h>
#include <iostream>

geokugel::geokugel(){
}

geokugel::geokugel(float r, float g, float b){
    red = r;
    green = g;
    blue = b;
    rotm = rotationsmatrix();
    dx = 0;
    dy = 0;
    dz = 0;
}


float* geokugel::drawQuad(float radius, float dx, float dy, float dz, float alpha, float beta){
    float breite = 2; //10*pi/180;

    float *points1 = rotm.rotatez(1.0, radius, 0, 0, alpha);
    points1 = rotm.rotatey(1.0, points1[0], points1[1], points1[2], beta);
    float *points2 = rotm.rotatez(1.0, radius, 0, 0, alpha+breite);
    points2 = rotm.rotatey(1.0, points2[0], points2[1], points2[2], beta);
    float *points3 = rotm.rotatez(1.0, radius, 0, 0, alpha+breite);
    points3 = rotm.rotatey(1.0, points3[0], points3[1], points3[2], beta+breite);
    float *points4 = rotm.rotatez(1.0, radius, 0, 0, alpha);
    points4 = rotm.rotatey(1.0, points4[0], points4[1], points4[2], beta+breite);

   glBegin(GL_QUADS);
   glColor4f(red, green, blue, 1.0);
    glVertex3f(dx + points1[0], dy +points1[1], dz + points1[2]);
    glVertex3f(dx + points2[0], dy + points2[1], dz + points2[2]);
    glVertex3f(dx + points3[0], dy + points3[1], dz + points3[2]);
    glVertex3f(dx + points4[0], dy + points4[1], dz + points4[2]);
    glEnd();

    points4[0] = dx + points4[0];
    points4[1] = dy + points4[1];
    points4[2] = dz + points4[2];

    return points4;
}

 float* geokugel::drawKugel(float radius, float x, float y, float z, int kreisHoehe, int kreisBreite){
        double alpha = 270;
        double beta = 0.01;
        float* endeffektor = new float[3];
        endeffektor[0] = 0;
        endeffektor[1] = 0;
        endeffektor[2] = 0;

        //beta = z achse, alpha = y achse
        while(alpha >= kreisHoehe){
               beta = 0.0;
             int teilBreite = 360;
             if(alpha <= kreisHoehe + 2){
                 teilBreite = 360 - kreisBreite;
             }

            while(beta <= teilBreite){
            endeffektor = drawQuad(radius, x, y, z, alpha, beta);
             beta+= 2;
            }
            alpha -= 2;
      }
        return endeffektor;
   }
