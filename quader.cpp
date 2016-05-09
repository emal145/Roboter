#include "quader.h"
#include <iostream>

quader::quader()
{
    counter = 0;
    red = 0;
    yellow = 0;
    blue = 0;
    s = 0;
    h = 0;
    dx = 0;
    dy = 0;
    dz = 0;
    top = false;
    rotx = 0;
    roty = 0;
    rotz = 0;
}

void quader::drawGroundorTop(float s, float h){
    //Startkoordinate ergibt sich durch die hälfte der Seitenlänge,
    //damit das Koordinatensystem in der Mitte des Würfels ist.

   /*Startkoordinaten für 1 Teilviereck
    *p, -p, p
    *p, -p + höhe, p
    *p, -p+höhe , -p
    *p, -p,-p
    */
    //dadurch ergeben sich neue Start x, y, z -Koordinatem:
    float p = s/2;
    float x = p;
    float y = p; //y ist negativ, damit der Startpunkt unterhalb des Koordinatensystems ist
    float z = p;
    rotm = rotationsmatrix();
   //Teilviereck jeder Seite
   float *quad1 = rotm.rotatey(1.0,x,-y+h,z, 90.0f);
   float *quad2 = rotm.rotatey(1.0,x,-y+h,z, 180.0f);
   float *quad3 = rotm.rotatey(1.0,x,-y+h,z, 270.0f);
   float *quad4 = rotm.rotatey(1.0,x,-y+h,z, 360.0f);

   if(rotx != 0){
       quad1 = rotm.rotateX(1.0,quad1[0],quad1[1],quad1[2], rotx);
       quad2 = rotm.rotateX(1.0,quad2[0],quad2[1],quad2[2], rotx);
       quad3 = rotm.rotateX(1.0,quad3[0],quad3[1],quad3[2], rotx);
       quad4 = rotm.rotateX(1.0,quad4[0],quad4[1],quad4[2], rotx);
   }

   if(roty != 0){
       quad1 = rotm.rotatey(1.0,quad1[0],quad1[1],quad1[2], roty);
       quad2 = rotm.rotatey(1.0,quad2[0],quad2[1],quad2[2], roty);
       quad3 = rotm.rotatey(1.0,quad3[0],quad3[1],quad3[2], roty);
       quad4 = rotm.rotatey(1.0,quad4[0],quad4[1],quad4[2], roty);
   }

   if(rotz != 0){
       quad1 = rotm.rotatez(1.0,quad1[0],quad1[1],quad1[2], rotz);
       quad2 = rotm.rotatez(1.0,quad2[0],quad2[1],quad2[2], rotz);
       quad3 = rotm.rotatez(1.0,quad3[0],quad3[1],quad3[2], rotz);
       quad4 = rotm.rotatez(1.0,quad4[0],quad4[1],quad4[2], rotz);
   }

   glBegin(GL_QUADS);
    glColor3f(red, yellow, blue);
    glVertex3f( dx +quad1[0], dy + quad1[1], dz + quad1[2]);
    glVertex3f( dx +quad2[0], dy + quad2[1], dz + quad2[2]);
    glVertex3f( dx +quad3[0], dy + quad3[1], dz + quad3[2]);
    glVertex3f( dx +quad4[0], dy + quad4[1], dz + quad4[2]);
    glEnd();
}


/* Methode zum Zeichnen eines 3D-Vierecks
 * parameter:
 * red, yellow, blue entsprechend der Farbe
 * s = Seitenlänge des Vierecks
 * h = //die höhe des einzelnen Teilvierecks

 * dx, dy, dz sind die Werte, welche den Würfel verschieben
 */
void quader::drawQuads(float s, float h){
    if(counter < 4){
    //Startkoordinate ergibt sich durch die hälfte der Seitenlänge,
    //damit das Koordinatensystem in der Mitte des Würfels ist.

   /*Startkoordinaten für 1 Teilviereck
    *p, -p, p
    *p, -p + höhe, p
    *p, -p+höhe , -p
    *p, -p,-p
    */
    //dadurch ergeben sich neue Start x, y, z -Koordinatem:
    float p = s/2;
    float x = p;
    float y = p; //y ist negativ, damit der Startpunkt unterhalb des Koordinatensystems ist
    float z = p;
    rotm = rotationsmatrix();
   //Teilviereck jeder Seite
   float *quad1 = rotm.rotatey(1.0,x,-y,z, counter*90.0f);
   float *quad2 = rotm.rotatey(1.0,x,-y+h,z, counter*90.0f);
   float *quad3 = rotm.rotatey(1.0,x,-y+h,-z, counter*90.0f);
   float *quad4 = rotm.rotatey(1.0,x,-y,-z, counter*90.0f);

   /*std::cout << "x1: " << quad1[0] << " y1: " << quad1[1] << " z1: " << quad1[2] << std::endl;
   std::cout << "x2: " << quad2[0] << " y2: " << quad2[1] << " z2: " << quad2[2] << std::endl;
   std::cout << "x3: " << quad3[0] << " y3: " << quad3[1] << " z3: " << quad3[2] << std::endl;
   std::cout << "x4: " << quad4[0] << " y4: " << quad4[1] << " z4: " << quad4[2] << std::endl << std::endl;
*/
   if(rotx != 0){
       quad1 = rotm.rotateX(1.0,quad1[0],quad1[1],quad1[2], rotx);
       quad2 = rotm.rotateX(1.0,quad2[0],quad2[1],quad2[2], rotx);
       quad3 = rotm.rotateX(1.0,quad3[0],quad3[1],quad3[2], rotx);
       quad4 = rotm.rotateX(1.0,quad4[0],quad4[1],quad4[2], rotx);
   }

   if(roty != 0){
       quad1 = rotm.rotatey(1.0,quad1[0],quad1[1],quad1[2], roty);
       quad2 = rotm.rotatey(1.0,quad2[0],quad2[1],quad2[2], roty);
       quad3 = rotm.rotatey(1.0,quad3[0],quad3[1],quad3[2], roty);
       quad4 = rotm.rotatey(1.0,quad4[0],quad4[1],quad4[2], roty);
   }

   if(rotz != 0){
       quad1 = rotm.rotatez(1.0,quad1[0],quad1[1],quad1[2], rotz);
       quad2 = rotm.rotatez(1.0,quad2[0],quad2[1],quad2[2], rotz);
       quad3 = rotm.rotatez(1.0,quad3[0],quad3[1],quad3[2], rotz);
       quad4 = rotm.rotatez(1.0,quad4[0],quad4[1],quad4[2], rotz);
   }

   std::cout << "x1: " << quad1[0] << " y1: " << quad1[1] << " z1: " << quad1[2] << std::endl;
   std::cout << "x2: " << quad2[0] << " y2: " << quad2[1] << " z2: " << quad2[2] << std::endl;
   std::cout << "x3: " << quad3[0] << " y3: " << quad3[1] << " z3: " << quad3[2] << std::endl;
   std::cout << "x4: " << quad4[0] << " y4: " << quad4[1] << " z4: " << quad4[2] << std::endl << std::endl;

   glBegin(GL_QUADS);
    glColor3f(red, yellow, blue);
    glVertex3f(dx + quad1[0], dy + quad1[1], dz + quad1[2]);
    glVertex3f(dx + quad2[0], dy + quad2[1], dz + quad2[2]);
    glVertex3f(dx + quad3[0], dy + quad3[1], dz + quad3[2]);
    glVertex3f(dx + quad4[0], dy + quad4[1], dz + quad4[2]);
    glEnd();

    counter++;
    drawQuads(s, h);
    }
    else{
        counter = 0;
    }
}

void quader::drawCube(float r, float y, float b, float s, float h, float dx, float dy, float dz, bool top){
    //Höhe der Teildreiecke
    this->red = r;
    this->yellow = y;
    this->blue = b;
    this->s = s;
    this->h = h;
    this->dx = dx;
    this->dy = dy;
    this->dz = dz;
    this->top = top;

    drawGroundorTop(s, 0);
    drawQuads(s, h);
    if(top == true){
        drawGroundorTop(s, h);
    }

}

void quader::redrawCube(){
    drawCube(red, yellow, blue, s, h, dx, dy, dz, top);
}


void quader::rotateX(float rotx){
    this->rotx = rotx;
    redrawCube();
}

void quader::rotateY(float roty){
    this->roty = roty;
    redrawCube();
}

void quader::rotateZ(float rotz){
    this->rotz = rotz;
    redrawCube();
}

