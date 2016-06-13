#include "geoquad.h"

GeoQuad::GeoQuad()
{
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
}

void GeoQuad::drawGroundorTop(float s, float h){
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
   float *quad1 = rotm.rotatey(1.0,x,y+h,z, 90.0f);
   float *quad2 = rotm.rotatey(1.0,x,y+h,z, 180.0f);
   float *quad3 = rotm.rotatey(1.0,x,y+h,z, 270.0f);
   float *quad4 = rotm.rotatey(1.0,x,y+h,z, 360.0f);

   glBegin(GL_QUADS);
    glColor3f(red, yellow, blue);
    glVertex3f(dx + quad1[0], dy + quad1[1], dz + quad1[2]);
    glVertex3f(dx + quad2[0], dy + quad2[1], dz + quad2[2]);
    glVertex3f(dx + quad3[0], dy + quad3[1], dz + quad3[2]);
    glVertex3f(dx + quad4[0], dy + quad4[1], dz + quad4[2]);
   glEnd();

}

/* Methode zum Zeichnen eines 3D-Vierecks
 * parameter:
 * red, yellow, blue entsprechend der Farbe
 * s = Seitenlänge des Vierecks
 * h = //die höhe des einzelnen Teilvierecks

 * dx, dy, dz sind die Werte, welche den Würfel verschieben
 */
float* GeoQuad::drawQuads(float s, float h){
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
   float *quad1 = rotm.rotatey(1.0,x,y,z, counter*90.0f); //Unten links
   float *quad2 = rotm.rotatey(1.0,x,y+h,z, counter*90.0f); //Oben links
   float *quad3 = rotm.rotatey(1.0,x,y+h,-z, counter*90.0f); //Oben rechts
   float *quad4 = rotm.rotatey(1.0,x,y,-z, counter*90.0f); //Unten rechts


   glBegin(GL_QUADS);
    glColor3f(red, yellow, blue);
    glVertex3f(dx + quad1[0], dy + quad1[1], dz + quad1[2]);
    glVertex3f(dx + quad2[0], dy + quad2[1], dz + quad2[2]);
    glVertex3f(dx + quad3[0], dy + quad3[1], dz + quad3[2]);
    glVertex3f(dx + quad4[0], dy + quad4[1], dz + quad4[2]);
    glEnd();

   quad4[0] = dx + quad4[0];
   quad4[1] = dy + quad4[1];
   quad4[2] = dz + quad4[2];

    return quad2;
}


float* GeoQuad::drawCube(float r, float y, float b, float s, float h, float cubesheight, int cubesSideCounter, float dx, float dy, float dz, bool top){
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

    float* endpoints = new float[4];
    endpoints[0] = 0;
    endpoints[1] = 0;
    endpoints[2] = 0;
    endpoints[3] = 0;

    if(this->counter == 1){
     // drawGroundorTop(s, 0);
    }

    float maxHeight = h*(cubesheight-1);
    for(int i = 0; i < maxHeight; i++){
     for(int x = 1; x < 5; x++){
          drawQuads(s,h);
          this->counter = x;
       }
    }

    this->dy = h * (cubesheight-1);
    this->counter = cubesSideCounter;
     endpoints = drawQuads(s,h);

    if(top == true){
      drawGroundorTop(s, h);
    }

    return endpoints;
}
