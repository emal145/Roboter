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
    float *quad1 = new float[3];
    float *quad2 = new float[3];
    float *quad3 = new float[3];
    float *quad4 = new float[3];

     rotationsmatrix rotm = rotationsmatrix();

        quad1 = rotm.rotatey(1.0, s, h, 0.0, 0.0);
        quad2 = rotm.rotatey(1.0, s, h, s, 0.0);
        quad3 = rotm.rotatey(1.0, 0.0, h, s, 0.0);
        quad4 = rotm.rotatey(1.0, 0.0, h, 0.0, 0.0);

        quad1[1] = quad1[1] + dy;
        quad2[1] = quad2[1] + dy;
        quad3[1] = quad3[1] + dy;
        quad4[1] = quad4[1] + dy;

        quad1[0] = quad1[0] + dx;
        quad2[0] = quad2[0] + dx;
        quad3[0] = quad3[0] + dx;
        quad4[0] = quad4[0] + dx;

        quad1[2] = quad1[2] + dz;
        quad2[2] = quad2[2] + dz;
        quad3[2] = quad3[2] + dz;
        quad4[2] = quad4[2] + dz;

        glBegin(GL_QUADS);
        glColor3f(red, yellow, blue);
        glVertex3f(quad1[0],quad1[1], quad1[2]);
        glVertex3f(quad2[0],quad2[1], quad2[2]);
        glVertex3f(quad3[0],quad3[1], quad3[2]);
        glVertex3f(quad4[0],quad4[1], quad4[2]);
        glEnd();
}

/* Methode zum Zeichnen eines 3D-Vierecks
 * parameter:
 * red, yellow, blue entsprechend der Farbe
 * s = Seitenlänge des Vierecks
 * h = //die höhe des einzelnen Teilvierecks

 * dx, dy, dz sind die Werte, welche den Würfel verschieben
 */
float* GeoQuad::drawQuads(float s, float h, float stepheight, int sideCounter){
    float *quad1 = new float[3];
    float *quad2 = new float[3];
    float *quad3 = new float[3];
    float *quad4 = new float[3];

    rotationsmatrix rotm = rotationsmatrix();

        quad1 = rotm.rotatey(1.0, s, 0.0, 0.0, 0.0);
        quad2 = rotm.rotatey(1.0, s, 0.0, s, 0.0);
        quad3 = rotm.rotatey(1.0, s, h, s, 0.0 );
        quad4 = rotm.rotatey(1.0, s, h, 0.0, 0.0 );

        quad1 = rotm.rotatey(s/2, quad1[0], quad1[1], quad1[2], (sideCounter*90));
        quad2 = rotm.rotatey(s/2, quad2[0], quad2[1], quad2[2], (sideCounter*90));
        quad3 = rotm.rotatey(s/2, quad3[0], quad3[1], quad3[2], (sideCounter*90));
        quad4 = rotm.rotatey(s/2, quad4[0], quad4[1], quad4[2], (sideCounter*90));

        quad1[1] = quad1[1] + dy + stepheight;
        quad2[1] = quad2[1] + dy + stepheight;
        quad3[1] = quad3[1] + dy + stepheight;
        quad4[1] = quad4[1] + dy + stepheight;

       float xversatz = 0.0;
       float zversatz = 0.0;


       if(sideCounter == 1){
           xversatz = s;
       }
       else if(sideCounter == 2){
           xversatz = s;
           zversatz = s;
       }
       else if(sideCounter == 3){
           zversatz = s;
       }

        quad1[0] = quad1[0] + dx + xversatz;
        quad2[0] = quad2[0] + dx + xversatz;
        quad3[0] = quad3[0] + dx + xversatz;
        quad4[0] = quad4[0] + dx + xversatz;

        quad1[2] = quad1[2] + dz + zversatz;
        quad2[2] = quad2[2] + dz + zversatz;
        quad3[2] = quad3[2] + dz + zversatz;
        quad4[2] = quad4[2] + dz + zversatz;

        glBegin(GL_QUADS);
        glColor3f(red, yellow, blue);
        glVertex3f(quad1[0],quad1[1], quad1[2]);
        glVertex3f(quad2[0],quad2[1], quad2[2]);
        glVertex3f(quad3[0],quad3[1], quad3[2]);
        glVertex3f(quad4[0],quad4[1], quad4[2]);
        glEnd();

    return quad4;
}


float* GeoQuad::drawCube(float r, float y, float b, float s, float h, int qubescounter, int sideCounter, float dx, float dy, float dz, bool top){
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
      drawGroundorTop(s, 0);
    }

    float newHeight = h/30;
    for(int i = 0; i < (qubescounter-1); i++){
        for(int x = 1; x <= 4; x++){
         drawQuads(s, newHeight, newHeight*i, x);
        }
    }

    for(int x = 1; x <= sideCounter; x++){
     endpoints = drawQuads(s, newHeight, newHeight*(qubescounter-1), x);
    }

    if(top == true){
      drawGroundorTop(s, h);
    }

    return endpoints;
}
