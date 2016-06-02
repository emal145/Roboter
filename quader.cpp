#include "quader.h"
#include <iostream>

quader::quader(){
    this->armsPos = 0;
    rotationsZ = new float[1];
    rotationsZ[0] = 0;
    jointaddHeight = new float[1];
    jointaddHeight[0] = 0.0;

    initialize();
}

quader::quader(int armsPos)
{
    this->armsPos = armsPos;
    rotationsZ = new float[armsPos];
    jointaddHeight = new float[armsPos];
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
}

void quader::drawGroundorTop(float s, float h){
    //Startkoordinate ergibt sich durch die hälfte der Seitenlänge,
    //damit das Koordinatensystem in der Mitte des Würfels ist.

   /*Startkoordinaten für 1 Teilviereck
    *p, 0, p
    *p, 0 + höhe, p
    *p, 0+höhe , -p
    *p, 0,-p
    */
    //dadurch ergeben sich neue Start x, y, z -Koordinatem:
    float p = s/2;
    float x = p;
    float y = 0; //y ist negativ, damit der Startpunkt unterhalb des Koordinatensystems ist
    float z = p;
    rotm = rotationsmatrix();
   //Teilviereck jeder Seite
   glPushMatrix();
   glTranslatef(dx,dy,dz);
   float *quad1 = rotm.rotatey(1.0,x,y+h,z, 90.0f);
   float *quad2 = rotm.rotatey(1.0,x,y+h,z, 180.0f);
   float *quad3 = rotm.rotatey(1.0,x,y+h,z, 270.0f);
   float *quad4 = rotm.rotatey(1.0,x,y+h,z, 360.0f);

   //START - ROBOTERARM ROTATIONEN (Parent Rotations)
   float jointheight = 0;
   if(this->armsPos != 0){
       for(int i = 0; i < this->armsPos; i++){
             if(i != 0){
                   jointheight = jointaddHeight[i-1];
              }

            glTranslatef(0.0, jointheight, 0.0);
            glRotatef(rotationsZ[i], 0.0f, 0.0f, 1.0f);
         }
     }

   if(this->armsPos != 0){
       jointheight = jointaddHeight[this->armsPos-1];
   }
   //END

   //EIGENE ROTATION
   glTranslatef(0.0, jointheight, 0.0);
   glRotatef(rotz, 0.0f, 0.0f, 1.0f);

   glBegin(GL_QUADS);
    glColor3f(red, yellow, blue);
    glVertex3f(quad1[0],quad1[1], quad1[2]);
    glVertex3f(quad2[0],quad2[1], quad2[2]);
    glVertex3f(quad3[0],quad3[1], quad3[2]);
    glVertex3f(quad4[0],quad4[1], quad4[2]);
   glEnd();

  glPopMatrix();

}

/* Methode zum Zeichnen eines 3D-Vierecks
 * parameter:
 * red, yellow, blue entsprechend der Farbe
 * s = Seitenlänge des Vierecks
 * h = //die höhe des einzelnen Teilvierecks

 * dx, dy, dz sind die Werte, welche den Würfel verschieben
 */
void quader::drawQuads(float s, float h){
     //Startkoordinate ergibt sich durch die hälfte der Seitenlänge,
    //damit das Koordinatensystem in der Mitte des Würfels ist.

   /*Startkoordinaten für 1 Teilviereck
    *p, 0, p
    *p, 0 + höhe, p
    *p, 0 + höhe , -p
    *p, 0, -p
    */
    //dadurch ergeben sich neue Start x, y, z -Koordinatem:
    float p = s/2;
    float x = p;
    float y = 0;
    float z = p;
    rotm = rotationsmatrix();
   //Teilviereck jeder Seite
   glPushMatrix();
   //Verschiebung um den Versatz
   glTranslatef(dx, dy, dz);
   float *quad1 = rotm.rotatey(1.0,x,y,z, counter*90.0f); //Unten links
   float *quad2 = rotm.rotatey(1.0,x,y+h,z, counter*90.0f); //Oben links
   float *quad3 = rotm.rotatey(1.0,x,y+h,-z, counter*90.0f); //Oben rechts
   float *quad4 = rotm.rotatey(1.0,x,y,-z, counter*90.0f); //Unten rechts

   //Urpsrungskoordinaten als Matrix speichern um nach derm Zeichnen wieder zurückzusetzen
    float jointheight = 0;
   //ab dem 2. Arm die Rotationen der vorgänger Arme mit einbeziehen
   if(this->armsPos != 0){
       for(int i = 0; i < this->armsPos; i++){
              //Höhe des vorherigen Roboterarms
             if(i != 0){
                   jointheight = jointaddHeight[i-1];
              }
             //Urpsprung auf den jeweiligen Arm versetzen und Rotieren
            glTranslatef(0.0, jointheight, 0.0);
            glTranslatef(0.0, -s/2, 0.0);
            glRotatef(rotationsZ[i], 0.0f, 0.0f, 1.0f);
            glTranslatef(0.0, s/2, 0.0);
         }
     }

   //höhen variable auf den Parent Arm setzen
   if(this->armsPos != 0){
       jointheight = jointaddHeight[this->armsPos-1];
   }

   //Ursprung transformieren und die eigene rotation anwenden
   glTranslatef(0.0, jointheight, 0.0);
   glTranslatef(0.0, -s/2, 0.0);
   glRotatef(rotz, 0.0f,0.0f, 1.0f);
   glTranslatef(0.0, s/2, 0.0);

   glBegin(GL_QUADS);
    glColor3f(red, yellow, blue);
    glVertex3f(quad1[0], quad1[1], quad1[2]);
    glVertex3f(quad2[0], quad2[1], quad2[2]);
    glVertex3f(quad3[0], quad3[1], quad3[2]);
    glVertex3f(quad4[0], quad4[1], quad4[2]);
    glEnd();
    glPopMatrix();
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
    this->counter = 1;

    //Boden Zeichnen
    drawGroundorTop(s, 0);

    //Seitenwände
    for(int i = 1; i < 5; i++){
        this->counter = i;
        drawQuads(s,h);
    }

    //Deckel
    if(top == true){
       drawGroundorTop(s, h);
    }
}

void quader::rotateX(float rotx){
    this->rotx = rotx;
}

void quader::rotateY(float roty){
    this->roty = roty;
}

//Eigene Rotation setzen
void quader::rotateZ(float rotz){
    this->rotz = rotz;
}

//Rotationswerte und Höhen der Parents setzen
void quader::setRotationsZvalue(float* rotationZvalue, float* jointaddHeights){
    this->rotationsZ = &rotationZvalue[0];
    this->jointaddHeight = &jointaddHeights[0];
}


