#include "robotarm.h"
#include <iostream>
robotarm::robotarm(){
}

robotarm::~robotarm(){

}

robotarm::robotarm(float width, float height, float x, float y, float z, int robotPosition)
{
    quad = quader(robotPosition);
    kug = kugel(0.7, 0.7, 0.7, robotPosition);
    rotm = rotationsmatrix();
    rotx = 0;
    roty = 0;
    rotz = 0; //Eigene Rotation um Z-Achse
    rotationsZ = new float[robotPosition]; //Parent Rotationswerte
    jointaddHeights = new float[robotPosition]; //Parent Höhen
    jointaddHeightsKugel = new float[robotPosition]; //Parent Höhen der Kugel
    this->robotPosition = robotPosition; //Eigene Position der Gesamt Arme im Array
    this->width = width;
    this->height = height;
    this->x = x;
    this->y = y;
    this->z = z;
    this->childArm = 0;
}
void robotarm::drawRobot(){

   if(rotz != 0){
       if(robotPosition == 0){
            quad.rotateZ(rotz);
       }
       else{
           quad.rotateZ(rotz);
       }
       kug.setRotationZ(rotz);
   }

   quad.setRotationsZvalue(rotationsZ, jointaddHeights);
   kug.setRotationsZvalue(rotationsZ, jointaddHeights);
   quad.drawCube(0.8,0.4,0.0,width, height, x, y, z, true);
   kug.drawKugel(width/2.0, x, y+width/2, z, 90, 360);

}

void robotarm::setWidth(float width){
    this->width = width;
}

void robotarm::setHeight(float height){
    this->height = height;
}

void robotarm::translateX(float x){
    this->x = x;
}

void robotarm::translateY(float y){
    this->y = y;
}

void robotarm::translateZ(float z){
    this->z = z;
}


void robotarm::rotateX(float radius, float rotx){
    this->rotx = rotx;
    this->radius = radius;

}
void robotarm::rotateY(float radius, float roty){
    this->roty = roty;
    this->radius = radius;
}

void robotarm::rotateZ(float rotz){
      this->rotz = rotz;
        if(this->childArm != 0){
          childArm->rotateZfromParent(robotPosition, rotz, height);
       }
}

//Berechnung der Höhe des Robotorarms
void robotarm::rotateZfromParent(int position, float rotz, float jointaddHeight){
    this->rotationsZ[position] = rotz;
        this->jointaddHeights[position] = jointaddHeight + width;
        if(this->childArm != 0){
            this->childArm->rotateZfromParent(position, rotz, jointaddHeight);
        }
}

void robotarm::setChildArm(robotarm &childArm){
    this->childArm = &childArm;
}
