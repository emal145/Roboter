#include "kugel.h"
#include <math.h>
#include <iostream>


kugel::kugel(float r, float g, float b){
    red = r;
    green = g;
    blue = b;
    this->armPos = 0;
    rotationsZ = new float[0];
    jointaddHeights = new float[0];
    initialize();
}

kugel::kugel(float r, float g, float b, int armPos){
    red = r;
    green = g;
    blue = b;
    this->armPos = armPos;
    rotationsZ = new float[armPos];
    jointaddHeights = new float[armPos];
    initialize();
}

void kugel::initialize(){
    rotm = rotationsmatrix();
    dx = 0;
    dy = 0;
    dz = 0;
    rotx = 0;
    roty = 0;
    rotz = 0;
}

void kugel::drawQuad(float radius, float dx, float dy, float dz, float alpha, float beta){
   float breite = 2; //10*pi/180;

   //Urpsrungskoordinaten als Matrix speichern um nach derm Zeichnen wieder zurückzusetzen
    glPushMatrix();
    glTranslatef(dx,dy,dz);

    float *points1 = rotm.rotatez(1.0, radius, 0, 0, alpha);
    points1 = rotm.rotatey(1.0, points1[0], points1[1], points1[2], beta);
    float *points2 = rotm.rotatez(1.0, radius, 0, 0, alpha+breite);
    points2 = rotm.rotatey(1.0, points2[0], points2[1], points2[2], beta);
    float *points3 = rotm.rotatez(1.0, radius, 0, 0, alpha+breite);
    points3 = rotm.rotatey(1.0, points3[0], points3[1], points3[2], beta+breite);
    float *points4 = rotm.rotatez(1.0, radius, 0, 0, alpha);
    points4 = rotm.rotatey(1.0, points4[0], points4[1], points4[2], beta+breite);

    //Rotation der Arme um Y-Achse
    glRotatef(-roty, 0.0f, 1.0f, 0.0f);

    glTranslatef(0.0, -radius*2, 0.0);

    float jointheight = 0;
    //ab dem 2. Arm die Rotationen der vorgänger Arme mit einbeziehen
    if(this->armPos != 0){
        for(int i = 0; i < this->armPos; i++){
               //Höhe des vorherigen Roboterarms
              if(i != 0){
                    jointheight = jointaddHeights[i-1];
               }
              //Urpsprung auf den jeweiligen Arm versetzen und Rotieren
             glTranslatef(0.0, jointheight, 0.0);
             glRotatef(rotationsZ[i], 0.0f, 0.0f, 1.0f);
          }
      }

    //höhen variable auf den Parent Arm setzen
    if(this->armPos != 0){
        jointheight = jointaddHeights[this->armPos-1];
    }

    //Ursprung transformieren und die eigene rotation anwenden
    glTranslatef(0.0, jointheight, 0.0);
    glRotatef(rotz, 0.0f, 0.0f, 1.0f);

    glRotatef(roty, 0.0, 1.0, 0.0);

   glBegin(GL_QUADS);
   glColor4f(red, green, blue, 1.0);
    glVertex3f(points1[0], points1[1], points1[2]);
    glVertex3f(points2[0], points2[1], points2[2]);
    glVertex3f(points3[0], points3[1], points3[2]);
    glVertex3f(points4[0], points4[1], points4[2]);
   glEnd();

    glPopMatrix();
}

 void kugel::drawKugel(float radius, float x, float y, float z, int kreisHoehe, int kreisBreite){
        double alpha = 270;
        double beta = 0.01;
        //beta = z achse, alpha = y achse
        while(alpha >= kreisHoehe){
               beta = 0.0;
             int teilBreite = 360;
             if(alpha <= kreisHoehe + 2){
                 teilBreite = 360 - kreisBreite;
             }

            while(beta <= teilBreite){
             drawQuad(radius, x, y, z, alpha, beta);
             beta+= 2;
            }
            alpha -= 2;
      }
   }

 void kugel::setRotationX(float rotx){
     this->rotx = rotx;
 }

 void kugel::setRotationY(float roty){
     this->roty = roty;
 }

 void kugel::setRotationZ(float rotz){
     this->rotz = rotz;

 }

 void kugel::setRotationsZvalue(float* rotationsZ, float* jointaddHeights){
     this->rotationsZ = &rotationsZ[0];
     this->jointaddHeights = &jointaddHeights[0];
 }
