#include "geozylinder.h"
#include "rotationsmatrix.h"
#include <iostream>

geozylinder::geozylinder(){

}

geozylinder::geozylinder(float red, float green, float blue)
{
    this->red = red;
    this->green = green;
    this->blue = blue;
    this->radius = 0.0;
    this->height = 0.0;
    this->dx = 0.0;
    this->dy = 0.0;
    this->dz = 0.0;
}


void geozylinder::drawBoden(float radius, float dx, float dy, float dz){
    float pi = 3.1415926;
    glPushMatrix();
    glTranslatef(dx, dy, dz);
    for(double i = 0; i < 360; i++){

        float gegenkat = sin(pi/180)*radius;
        float ankat = cos(pi/180)*radius;

        glBegin(GL_TRIANGLES);
        glColor3f(red, green, blue);
           glVertex3d(0.0, 0.0,0.0);
           glVertex3d(radius, 0.0, 0.0);
           glVertex3f(ankat, 0, gegenkat);
         glEnd();

         glRotatef(1.0,0.0,1.0,0.0);
    }
    glPopMatrix();
}


float* geozylinder::drawQuad(float radius, float height, float stepheight, int breite, float dx, float dy, float dz){
   float *quad1 = new float[3];
    float *quad2 = new float[3];
    float *quad3 = new float[3];
    float *quad4 = new float[3];

    rotationsmatrix rotm = rotationsmatrix();

    for(double i = 1; i <= breite; i++){

        quad1 = rotm.rotatey(1.0,radius, 0.0, 0.0, i);
        quad2 = rotm.rotatey(1.0,radius, 0.0, 0.0, i+1.0f);
        quad3 = rotm.rotatey(1.0,radius, 0.0, 0.0, i+1.0f);;
        quad4 = rotm.rotatey(1.0,radius, 0.0, 0.0, i);

        quad1[1] = quad1[1] + dy + stepheight;
        quad2[1] = quad2[1] + dy + stepheight;
        quad3[1] = quad3[1] + dy + height + stepheight;
        quad4[1] = quad4[1] + dy + height + stepheight;

        quad1[0] = quad1[0] + dx;
        quad2[0] = quad2[0] + dx;
        quad3[0] = quad3[0] + dx;
        quad4[0] = quad4[0] + dx;

        quad1[2] = quad1[2] + dz;
        quad2[2] = quad2[2] + dz;
        quad3[2] = quad3[2] + dz;
        quad4[2] = quad4[2] + dz;

        glBegin(GL_QUADS);
        glColor3f(red, green, blue);
        glVertex3f(quad1[0],quad1[1], quad1[2]);
        glVertex3f(quad2[0],quad2[1], quad2[2]);
        glVertex3f(quad3[0],quad3[1], quad3[2]);
        glVertex3f(quad4[0],quad4[1], quad4[2]);
        glEnd();
    }
    return quad4;

}

float* geozylinder::drawZylinder(float radius, float height, int counter, int breite, float dx, float dy, float dz){
   drawBoden(radius, dx, dy, dz);
   float *endpoints = new float[4];
   endpoints[0] = 0.0;
   endpoints[1] = 0.0;
   endpoints[2] = 0.0;
   endpoints[3] = 0.0;

   float newheight = height/30;
   for(int i = 0; i < (counter-1); i++){
      drawQuad(radius, newheight, newheight*i, 360, dx, dy, dz);
   }
   endpoints = drawQuad(radius, newheight, newheight*(counter-1), breite, dx, dy, dz);

   return endpoints;

}

