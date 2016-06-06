#include "geokegel.h"
#include "rotationsmatrix.h"

geoKegel::geoKegel()
{

}

geoKegel::geoKegel(float red, float green, float blue){
    this->red = red;
    this->green = green;
    this->blue = blue;
}

float* geoKegel::drawQuad(float radius, float hoehe, float alpha){
    rotationsmatrix rotm = rotationsmatrix();
    float *quad1 = new float[3];
    float *quad2 = new float[3];
    float *quad3 = new float[3];
    float *quad4 = new float[3];

    float pi = 3.1415926;
    float gegenkat = sin(pi/180)*radius;

    quad1[0] = radius;
    quad1[1] = 0.0;
    quad1[2] = 0.0;

    quad2[0] = radius;
    quad2[1] = 0.0;
    quad2[2] = gegenkat;

    quad3[0] = radius;
    quad3[1] = hoehe;
    quad3[2] = gegenkat;

    quad4[0] = radius;
    quad4[1] = hoehe;
    quad4[2] = 0.0;

    quad1 = rotm.rotatey(radius, 0.0,1.0,0.0, alpha);
    quad2 = rotm.rotatey(radius, 0.0,1.0,0.0, alpha);
    quad3 = rotm.rotatey(radius, 0.0,1.0,0.0, alpha);
    quad4 = rotm.rotatey(radius, 0.0,1.0,0.0, alpha);

    glBegin(GL_QUADS);
     glColor3f(red, green, blue);
     glVertex3f(quad1[0], quad1[1], quad1[2]);
     glVertex3f(quad2[0], quad2[1], quad2[2]);
     glVertex3f(quad3[0], quad3[1], quad3[2]);
     glVertex3f(quad4[0], quad4[1], quad4[2]);
     glEnd();

     return quad4;
}

void geoKegel::drawTriangle(float radius){
    float pi = 3.1415926;
    float gegenkat = sin(pi/180)*radius;
    float ankat = cos(pi/180)*radius;

    glBegin(GL_TRIANGLES);
    glColor3f(red, green, blue);
            glVertex3d(0,0,0);
            glVertex3d(radius,0,0);
            glVertex3f(ankat, 0.0, gegenkat);
     glEnd();
}

float* geoKegel::drawKegel( float radius, float height, float heightCounter, float kegelBreite, float dx, float dy, float dz){
    this->dx = dx;
    this->dy = dy;
    this->dz = dz;

    float* endpoints = new float[4];
    endpoints[0] = 0;
    endpoints[1] = 0;
    endpoints[2] = 0;
    endpoints[3] = 0;

    float newRadius = newRadius-(radius/360);
    float hoehe = height/360; //Max = 360
    glPushMatrix();
    glTranslatef(dx,dy,dz);

    //Bodenplatte
    for(int i = 0; i < 360; i++){
        drawTriangle(radius);
        glRotatef(1.0, 0.0f, 1.0f, 0.0f);
    }

    for(int j = 0; j < heightCounter; j++){
      glPushMatrix();
      //Aussenwände
      if(j == (heightCounter-1)){
        for(int i = 0; i < kegelBreite; i++){
            endpoints = drawQuad(newRadius, hoehe, i);
        }
      }
      else{
          for(int i = 0; i < 360; i++){
              endpoints = drawQuad(newRadius, hoehe, i);
          }
      }
      glPopMatrix();
      glTranslatef(0.0, hoehe, 0.0);
      newRadius = newRadius-(radius/360);
    }
    glPopMatrix();

    endpoints[0] = dx + endpoints[0];
    endpoints[1] = dy + (heightCounter*hoehe) + endpoints[1];
    endpoints[2] = dz + endpoints[2];

    return endpoints;
}

