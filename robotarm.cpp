#include "robotarm.h"

robotarm::robotarm()
{
    quad = quader();
    kug = kugel(0.07, 0.04, 0.0);
    rotm = rotationsmatrix();
    rotx = 0;
    roty = 0;
    rotz = 0;
}


void robotarm::drawRobot(){
    float widthR1 = 1.0;
    float heightR1 = 0.5;
    float xR1 = 0.0;
    float yR1 = 7.0;
    float zR1 = 0.0;
    float rR1 = 0.15;


    quad.drawCube(0.8,0.3,0.5,widthR1,heightR1,xR1, yR1, zR1, true);
    kug.drawKugel(rR1, xR1-widthR1/2.0-rR1, yR1-heightR1/2.0, zR1, 90, 360);

    float widthR2 = widthR1+1.0;
    float heightR2 = heightR1+0.5;
    float rR2 = rR1;
    float xR2 = xR1 + widthR1/2.0 + widthR2/2.0 +rR2*2.0;
    float yR2 = yR1+heightR1/2.0;
    float zR2 = zR1;

    quad.drawCube(0.8,0.3,0.5,widthR2,heightR2,xR2, yR2, zR2, true);
    kug.drawKugel(rR2, xR2-widthR2/2.0-rR2, yR2-heightR1, zR2, 90, 360);

    float widthR3 = widthR2+1;
    float heightR3 = heightR2+0.5;
    float rR3 = rR2;
    float xR3 = xR2 + widthR2/2.0 + widthR3/2.0 +rR3*2.0;
    float yR3 = yR1 + heightR2/2.0;
    float zR3 = zR2;

    quad.drawCube(0.8,0.3,0.5,widthR3,heightR3,xR3, yR3, zR3, true);
    kug.drawKugel(rR3, xR3-widthR3/2.0-rR3, yR2-heightR1, zR3, 90, 360);

   if(rotx != 0){
     quad.rotateX(rotx);
     kug.setRotationX(rotx);
   }

   if(roty != 0){
     quad.rotateY(roty);
     kug.setRotationX(roty);
   }

   if(rotz != 0){
     quad.rotateZ(rotz);
     kug.setRotationX(rotz);
   }
}

void robotarm::setRotationX(float rotx){
    this->rotx = rotx;

}
void robotarm::setRotationY(float roty){
    this->roty = roty;
}
void robotarm::setRotationZ(float rotz){
    this->rotz = rotz;
}

