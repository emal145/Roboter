#include "table.h"

table::table()
{
}

void table::drawBoden(float red, float green, float blue){
   glBegin(GL_QUADS);
       glColor3f(red, green, blue);
       glVertex3f(4, 0, -8);
       glVertex3f( -4, 0, -8);
       glVertex3f( -4,  0, 8);
       glVertex3f( 4,  0, 8);
       glEnd();

   }

void table::seiteAB(float red, float green, float blue){
glBegin(GL_QUADS);
    glColor3f(red, green, blue);
    glVertex3f(4, 0, -8);
    glVertex3f( 4, 0.5, -8);
    glVertex3f( 4,  0.5, 8);
    glVertex3f(4,  0, 8);
    glEnd();
}

void table::seiteBC(float red, float green, float blue){
glBegin(GL_QUADS);
   glColor3f(red, green, blue);
     glVertex3f(4, 0, -8);
    glVertex3f(4, 0.5, -8);
    glVertex3f(-4, 0.5,-8);
    glVertex3f(-4,  0, -8);
    glEnd();
}

void table::seiteCD(float red, float green, float blue){
glBegin(GL_QUADS);
glColor3f(red, green, blue);
    glVertex3f(-4, 0, -8);
    glVertex3f( -4, 0.5, -8);
    glVertex3f( -4,  0.5, 8);
    glVertex3f( -4,  0, 8);
    glEnd();
}

void table::seiteAD(float red, float green, float blue){
glBegin(GL_QUADS);
glColor3f(red, green, blue);
    glVertex3f(-4, 0, 8);
    glVertex3f( -4, 0.5, 8);
    glVertex3f( 4,  0.5, 8);
    glVertex3f( 4,  0, 8);
    glEnd();
}

void table::drawTable(float red, float green, float blue){

    drawBoden(red,green,blue);
    seiteAB(1.0,0.0,0.0);
    seiteBC(1.0,0.0,0.0);
    seiteCD(1.0,0.0,0.0);
    seiteAD(1.0,0.0,0.0);

}

