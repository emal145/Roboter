#include "zylinder.h"
#include "rotationsmatrix.h"

zylinder::zylinder(){

}

zylinder::zylinder(float red, float green, float blue)
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

void zylinder::drawZylinder(float radius, float height, float dx, float dy, float dz){
   glPushMatrix();
   glTranslatef(dx,dy-height,dz);
   float pi = 3.1415926;

   for(double i = 0; i < 360; i++){

       float gegenkat = sin(pi/180)*radius;
       float ankat = cos(pi/180)*radius;

       glBegin(GL_TRIANGLES);
       glColor3f(red, green, blue);
          glVertex3d(0.0, 0.0, 0.0);
          glVertex3d(radius, 0.0, 0.0);
          glVertex3f(ankat, 0.0, gegenkat);
        glEnd();

      glBegin(GL_QUADS);
        glColor3f(red, green, blue);
        glVertex3d(radius,0,0);
        glVertex3d(radius,0,gegenkat);
        glVertex3d(radius,height,gegenkat);
        glVertex3d(radius,height,0);
       glEnd();

       glBegin(GL_TRIANGLES);
        glColor3f(red, green, blue);
        glVertex3d(0.0,height,0.0);
        glVertex3d(radius,height,0.0);
        glVertex3f(ankat, height, gegenkat);
        glEnd();

      glRotatef(1.0,0.0f,1.0f,0.0f);

   }

    glPopMatrix();
}

