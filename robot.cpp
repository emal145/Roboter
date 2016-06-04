#include "robot.h"
#include <iostream>

robot::robot() //: robotBottom(zylinder(0.8, 0.4, 0.0))
{
    //Armbreite und gleichzeitig Gelenkkugel Durchmesser
    width = 0.3;
    //Anzahl der Arme des Roboters
    nRobotarms = 3;
    robotBottom = zylinder(0.8, 0.4, 0.0);
    robotBottomRotY = 0.0;
    robotarms = new robotarm[nRobotarms];
    //Rotationen der einzelnen Arme
    armsz = new float[nRobotarms];

    //Default auf null setzen
    for(int a  = 0; a < nRobotarms; a++){
        armsz[a] = 0.0;
    }

    armsz[0] = 0.0;
    armsz[1] = 90.0;
    armsz[2] = (90 + (90-armsz[1])) - armsz[0];

    //Verschiebung auf x, y und z der Roboter gezeichnet werden soll
    x = 5;
    y = 2;
    z = 0;

    //n-Roboterarme anlegen
    roboterHeights = new float[nRobotarms];
    roboterHeights[0] = 3.0;
    roboterHeights[1] = 4.0;
    roboterHeights[2] = 2.0;
    for(int i = 0; i < nRobotarms; i++){
       robotarms[i] = robotarm(width, roboterHeights[i], x, y, z, i);
    }

    //Jedem Arm einen Nachfolger zuweisen
    for(int j = nRobotarms-1; j > 0; j--){
        //letzen arm den vorletzen arm hinzufügen
         robotarms[j-1].setChildArm(robotarms[j]);
    }

    //größen als default werte übergeben
    for(int k = 0; k < nRobotarms; k++){
        robotarms[k].rotateZ(0.0);
    }

    endeffektorx = 0;
    endeffektory = 0;
    endeffektorz = 0;
 }



void robot::drawRobot(){
    //calculatRotations(0);
    //Rotation der Einzelnen Arme durchführen weiter geben
    robotBottom.drawZylinder(1.0, 2.0, x,y-width,z);
    for(int i = 0; i < nRobotarms; i++){
        moveJoint(i, armsz[i]);
    }

    //jeden einzelnen Arm zeichen
    for(int i = 0; i < nRobotarms; i++){
       robotarms[i].rotateY(robotBottomRotY);
       robotarms[i].drawRobot();
    }
}

//Arm rotation einfügen
void robot::moveJoint(int position, float rotZ){
    robotarms[position].rotateZ(rotZ);
}

//Rotation eines speziellen Arms festlegen
void robot::setArmZ(int pos, float z){
    armsz[pos] = z;
}

void robot::setEndeffektorx(int x){
    this->endeffektorx = x;
}

void robot::setEndeffektory(int y){
    this->endeffektory = y;
}

void robot::setEndeffektorz(int z){
    this->endeffektorz = z;
}

void robot::calculatRotations(float* endeffektor){
    float pi = 3.1415926;
    float theta = 0;
    float hyp = 0;
    //Zylinder Rotation
    //if(endeffektor[0] != 0 && endeffektor[2] != 0){
      if((x-endeffektor[0]) == 0){
          theta = 90.0;
        }else{
          float gegenkat = x-endeffektor[0];
          float ankat = endeffektor[2]-z;
          hyp = sqrt(pow(gegenkat,2.0) + pow(ankat,2.0));
          theta = acos(gegenkat/hyp)*180/pi;
      }
    //}
    robotBottomRotY = theta;

    //Arm1 maximale reichweite bei 45 grad
    float a1maxHeight = cos(45*pi/180)*roboterHeights[0];

    //Arm1 Rotation
    float heightArmToPoint = roboterHeights[0] - endeffektor[1];
    float arm2ReachLength = roboterHeights[1];
    float theta1;//Wenn Arm 1 sich nicht weiter als 45Grad drehen muss...
    if((heightArmToPoint) < a1maxHeight){
        theta1 = acos(heightArmToPoint/roboterHeights[1])*180/pi;
        arm2ReachLength = cos(theta1*pi/180) * roboterHeights[1];

    }

    //Arm0 Rotation
    float lengthArmToPoint = hyp - arm2ReachLength;
    float theta0 = acos(lengthArmToPoint/roboterHeights[0])*180/pi;
    armsz[0] = theta0;
    armsz[1] = 90 - theta0 + theta1;
    armsz[2] = (90 + (90-armsz[1])) - armsz[0];


}
