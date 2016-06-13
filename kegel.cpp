#include "kegel.h"
#include "rotationsmatrix.h"

Kegel::Kegel()
{

}

Kegel::Kegel(float red, float green, float blue, int armsPos){
    this->red = red;
    this->green = green;
    this->blue = blue;
    this->armsPos = armsPos;
    rotationsZ = new float[armsPos];
    jointaddHeight = new float[armsPos];
    dx = 0;
    dy = 0;
    dz = 0;
    rotx = 0;
    roty = 0;
    rotz = 0;

}

void Kegel::drawQuad(float radius, float hoehe){
    float *quad1 = new float[3];
    float *quad2 = new float[3];
    float *quad3 = new float[3];
    float *quad4 = new float[3];

    float pi = 3.1415926;
    float gegenkat = tan(pi/180)*radius;

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

    glBegin(GL_QUADS);
     glColor3f(red, green, blue);
     glVertex3f(quad1[0], quad1[1], quad1[2]);
     glVertex3f(quad2[0], quad2[1], quad2[2]);
     glVertex3f(quad3[0], quad3[1], quad3[2]);
     glVertex3f(quad4[0], quad4[1], quad4[2]);
     glEnd();

}

void Kegel::drawTriangle(float radius){
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

float* Kegel::drawKegel( float radius, float height, float heightCounter, float dx, float dy, float dz){
    glPushMatrix();
    this->dx = dx;
    this->dy = dy;
    this->dz = dz;

    float* endpoints = new float[4];
    endpoints[0] = 0;
    endpoints[1] = 0;
    endpoints[2] = 0;
    endpoints[3] = 0;

    float newRadius = radius;
    float hoehe = height/heightCounter; //Max = 360
    glTranslatef(dx,dy,dz);

    //Rotation der Arme um Y-Achse
    glRotatef(roty, 0.0f, 1.0f, 0.0f);

   //START - ROBOTERARM ROTATIONEN (Parent Rotations)
    float jointheight = 0;
    if(this->armsPos != 0){
        for(int i = 0; i < this->armsPos; i++){
               //Höhe des vorherigen Roboterarms
              if(i != 0){
                    jointheight = jointaddHeight[i-1];
               }
              //Urpsprung auf den jeweiligen Arm versetzen und Rotieren
             glTranslatef(0.0, jointheight, 0.0);
             glTranslatef(0.0, -radius/2, 0.0);
             glRotatef(rotationsZ[i], 0.0f, 0.0f, 1.0f);
             glTranslatef(0.0, radius/2, 0.0);
          }
      }

    if(this->armsPos != 0){
        jointheight = jointaddHeight[this->armsPos-1];
    }
    //END

    //Ursprung transformieren und die eigene rotation anwenden
    glTranslatef(0.0, jointheight, 0.0);
    glTranslatef(0.0, -radius/2, 0.0);
    glRotatef(rotz, 0.0f,0.0f, 1.0f);
    glTranslatef(0.0, radius/2, 0.0);

    //Bodenplatte
    for(int i = 0; i < 360; i++){
        drawTriangle(radius);
        glRotatef(1.0, 0.0f, 1.0f, 0.0f);
    }

    for(int j = 0; j < 360; j++){
      glPushMatrix();
      //Aussenwände
        for(int i = 0; i < 360; i++){
            drawQuad(newRadius, hoehe);
            glRotatef(1.0,0.0f,1.0f,0.0f);
        }
      glPopMatrix();
      glTranslatef(0.0, hoehe, 0.0);
      newRadius = newRadius-(radius/360);
    }
    glPopMatrix();

    return endpoints;
}

void Kegel::rotateX(float rotx){
    this->rotx = rotx;
}

void Kegel::rotateY(float roty){
    this->roty = roty;
}

//Eigene Rotation setzen
void Kegel::rotateZ(float rotz){
    this->rotz = rotz;
}

//Rotationswerte und Höhen der Parents setzen
void Kegel::setRotationsZvalue(float* rotationZvalue, float* jointaddHeights){
    this->rotationsZ = &rotationZvalue[0];
    this->jointaddHeight = &jointaddHeights[0];
}

