#include "robotarm.h"

robotarm::robotarm(){

}

robotarm::robotarm(float width, float height, float x, float y, float z)
{
    quad = quader();
    kug = kugel(0.07, 0.04, 0.0);
    rotm = rotationsmatrix();
    rotx = 0;
    roty = 0;
    rotz = 0;

    this->width = width;
    this->height = height;
    this->x = x;
    this->y = y;
    this->z = z;
}


void robotarm::drawRobot(){

    if(rotx != 0){
     quad.rotateX(rotx);
     kug.setRotationX(height,rotx);
   }

   if(roty != 0){
     quad.rotateY(roty);
     kug.setRotationY(height,roty);
   }

   if(rotz != 0){
     quad.rotateZ(rotz);
     kug.setRotationZ(height,rotz);
   }

   quad.drawCube(0.8,0.3,0.5,width,height,x, y, z, true);
   if(rotz != 0){
     kug.drawKugel(width/2.0, x, y+height, z, 90, 360);
    }else{
     kug.drawKugel(width/2.0, x, y+height, z, 90, 360);

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
}

