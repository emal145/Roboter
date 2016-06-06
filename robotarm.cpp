#include "robotarm.h"
#include <iostream>

robotarm::robotarm(){
}

robotarm::~robotarm(){

}

robotarm::robotarm(float width, float height, float x, float y, float z, int robotPosition, bool endArm)
{
    quad = quader(robotPosition);
    kug = kugel(0.7, 0.7, 0.7, robotPosition);
    keg = Kegel(0.8,0.4,0.0, robotPosition);
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
    this->endArm = endArm;
}
void robotarm::drawRobot(){

   if(rotz != 0){
       if(endArm){
          keg.rotateZ(rotz);
       }
       else{
          quad.rotateZ(rotz);
       }
       kug.setRotationZ(rotz);
   }

   kug.setRotationY(roty);
   kug.setRotationsZvalue(rotationsZ, jointaddHeights);
   kug.drawKugel(width/2.0, x, y+width/2, z, 90, 360);

   if(endArm){
       keg.rotateY(roty);
       keg.setRotationsZvalue(rotationsZ, jointaddHeights);
       keg.drawKegel(width/2,height,360,x,y,z);
   }else{
       quad.rotateY(roty);
       quad.setRotationsZvalue(rotationsZ, jointaddHeights);
       quad.drawCube(0.8,0.4,0.0,width, height, x, y, z, true);
   }

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


void robotarm::rotateX(float rotx){
    this->rotx = rotx;

}
void robotarm::rotateY(float roty){
    this->roty = roty;
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
