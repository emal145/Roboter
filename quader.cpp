#include "quader.h"
#include <iostream>

quader::quader(){
    this->armsCount = 0;
    rotationsZ = new float[0];
    jointaddHeight = new float[0];

    initialize();
}

quader::quader(int armsCount, float robotdypos)
{
    this->armsCount = armsCount;
    rotationsZ = new float[armsCount];
    jointaddHeight = new float[armsCount];
    this->robotdypos = robotdypos;
    initialize();
}

void quader::initialize(){
    counter = 1;
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
    rotr = 0;
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
   float *quad1 = rotm.rotatey(1.0,x,0+h,z, 90.0f);
   float *quad2 = rotm.rotatey(1.0,x,0+h,z, 180.0f);
   float *quad3 = rotm.rotatey(1.0,x,0+h,z, 270.0f);
   float *quad4 = rotm.rotatey(1.0,x,0+h,z, 360.0f);

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
       quad1 = rotm.rotatez(1.0,quad1[0],rotr+quad1[1], quad1[2], rotz);
       quad2 = rotm.rotatez(1.0,quad2[0],rotr+quad2[1],quad2[2], rotz);
       quad3 = rotm.rotatez(1.0,quad3[0],rotr+quad3[1],quad3[2], rotz);
       quad4 = rotm.rotatez(1.0,quad4[0],rotr+quad4[1],quad4[2], rotz);
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
    if(counter <= 4){
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
    float y = p;
    float z = p;
    rotm = rotationsmatrix();
   //Teilviereck jeder Seite

   float *quad1 = rotm.rotatey(1.0,x,0,z, counter*90.0f); //Unten links
   float *quad2 = rotm.rotatey(1.0,x,0+h,z, counter*90.0f); //Oben links
   float *quad3 = rotm.rotatey(1.0,x,0+h,-z, counter*90.0f); //Oben rechts
   float *quad4 = rotm.rotatey(1.0,x,0,-z, counter*90.0f); //Unten rechts

  if(rotx != 0){
   }

   if(roty != 0){
   }

   if(rotz != 0){
       quad1 = rotm.rotatez(1.0,quad1[0],rotr + quad1[1],quad1[2], rotz);
       quad2 = rotm.rotatez(1.0,quad2[0],rotr + quad2[1],quad2[2], rotz);
       quad3 = rotm.rotatez(1.0,quad3[0],rotr + quad3[1],quad3[2], rotz);
       quad4 = rotm.rotatez(1.0,quad4[0],rotr + quad4[1],quad4[2], rotz);
   }
   glPushMatrix();
   if(this->armsCount != 0){
       for(int i = 0; i < this->armsCount; i++){
           float jointheight = 0;
            for(int k = 0; k < i; k++){
                jointheight = jointheight + jointaddHeight[k];
            }
            std::cout << "height: " << jointheight << ", rot: " << rotationsZ[i] << ", arms: " << armsCount << std::endl;
            glTranslatef(0.0, jointheight, 0.0);
           glRotatef(rotationsZ[i], 0.0f, 0.0f, 1.0f);
           }
     }


   dx= 0;
   dy = 0;
   dz = 0;
   glBegin(GL_QUADS);
    glColor3f(red, yellow, blue);
    glVertex3f(dx + quad1[0], dy + quad1[1], dz + quad1[2]);
    glVertex3f(dx + quad2[0], dy + quad2[1], dz + quad2[2]);
    glVertex3f(dx + quad3[0], dy + quad3[1], dz + quad3[2]);
    glVertex3f(dx + quad4[0], dy + quad4[1], dz + quad4[2]);
    glEnd();

   glPopMatrix();

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

//    drawGroundorTop(s, 0);
    drawQuads(s,h);
    if(top == true){
//        drawGroundorTop(s, h);
    }
}

void quader::redrawCube(){
    drawCube(red, yellow, blue, s, h, dx, dy, dz, top);
}


void quader::rotateX(float radius, float rotx){
    this->rotx = rotx;
    this->rotr = radius;
 //   redrawCube();
}

void quader::rotateY(float radius, float roty){
    this->roty = roty;
    this->rotr = radius;
   // redrawCube();
}

void quader::rotateZ(float radius, float rotz){
    this->rotz = rotz;
    this->rotr = radius;
}

void quader::setRotationsZvalue(float* rotationZvalue, float* jointaddHeights){
    this->rotationsZ = &rotationZvalue[0];
    this->jointaddHeight = &jointaddHeights[0];
}


