#include "robotarm.h"
#include <iostream>
robotarm::robotarm(){

}

robotarm::~robotarm(){

}

robotarm::robotarm(float width, float height, float x, float y, float z, int robotPosition, float robotdypos)
{
    quad = quader(robotPosition, robotdypos);
    kug = kugel(0.07, 0.04, 0.0, robotPosition);
    rotm = rotationsmatrix();
    rotx = 0;
    roty = 0;
    rotz = 0;
    rotzParent = 0;
    rotationsZ = new float[robotPosition];
    jointaddHeights = new float[robotPosition];
    jointaddHeightsKugel = new float[robotPosition];
    this->robotPosition = robotPosition;
    this->robotdypos = robotdypos;
    this->width = width;
    this->height = height;
    this->x = x;
    this->y = y;
    this->z = z;
    this->childArm = 0;
}
void robotarm::drawRobot(){

    if(rotx != 0){
     quad.rotateX(radius, rotx);
     //kug.setRotationX(radius,rotx);
   }

   if(roty != 0){
     quad.rotateY(height, roty);
     //kug.setRotationY(radius,roty);
   }

   if(rotz != 0){
       if(robotPosition == 0){
            quad.rotateZ(0, rotz);
       }
       else{
           quad.rotateZ(width, rotz);
       }
       kug.setRotationZ((height+width),rotz);
   }

   /*if(rotzParent != 0){
       quad.rotateZ1(radius, rotz1, jointaddHeight1);
       kug.setRotationZ(radius+jointaddHeightKugel,rotz);
   }*/

   quad.setRotationsZvalue(rotationsZ, jointaddHeights);
   kug.setRotationsZvalue(rotationsZ, jointaddHeightsKugel);
   quad.drawCube(0.8,0.3,0.5,width, height, x, y, z, true);
   kug.drawKugel(width/2.0, x, y+height, z, 90, 360);

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

void robotarm::rotateZfromParent(int position, float rotz, float jointaddHeight){
    if(position == 0){
        this->rotationsZ[0] = rotz;
        this->jointaddHeights[0] = jointaddHeight + width;
        this->jointaddHeightsKugel[0] = jointaddHeight+height;
        if(this->childArm != 0){
            this->childArm->rotateZfromParent(position, rotz, jointaddHeight);
        }
    }
    else{
        this->rotationsZ[position] = rotz;
        this->jointaddHeights[position] = jointaddHeight + width;
        this->jointaddHeightsKugel[position] = jointaddHeight+height;
        if(this->childArm != 0){
            this->childArm->rotateZfromParent(position, rotz, jointaddHeight);
        }
    }
}

void robotarm::setChildArm(robotarm &childArm){
    this->childArm = &childArm;
}
