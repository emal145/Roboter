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
    robotBottomHeight = 0.8;
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
    y = 0 + robotBottomHeight;
    z = 0;

    //n-Roboterarme anlegen
    roboterHeights = new float[nRobotarms];
    roboterHeights[0] = 4.0;
    roboterHeights[1] = 3.0;
    roboterHeights[2] = 0.3;
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

    endeffektorx = 0.0;
    endeffektory = 0.0;
    endeffektorz = 0.0;
 }



void robot::drawRobot(){
    //calculatRotations(0);
    //Rotation der Einzelnen Arme durchführen weiter geben
    robotBottom.drawZylinder(1.0, robotBottomHeight, x,y-width,z);
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

void robot::setEndeffektorx(float x){
    this->endeffektorx = x;
}

void robot::setEndeffektory(float y){
    this->endeffektory = y;
}

void robot::setEndeffektorz(float z){
    this->endeffektorz = z;
}

void robot::calculatRotations(float* endeffektor){
   /* this->endeffektorx = endeffektor[0];
    this->endeffektory = endeffektor[1];
    this->endeffektorz = endeffektor[2];
*/
    this->endeffektorx = 2;
    this->endeffektory = 2.0;
    this->endeffektorz = 1;

    float pi = 3.1415926;
    float theta = 0;
    float hyp = 0;
    //Zylinder Rotation
    //if(endeffektor[0] != 0 && endeffektor[2] != 0){
      if((x-endeffektor[0]) == 0){
          theta = 90.0;
        }else{
          float gegenkat = x-endeffektorx;
          float ankat = z-endeffektorz;
          hyp = sqrt(pow(gegenkat,2.0) + pow(ankat,2.0));
          theta = acos(gegenkat/hyp)*180/pi;
      }
    //}
    robotBottomRotY = theta;
    //Arm Rotationen
    //Betrag (Hypotenuse) von Roboter bis zum Punkt
    float* vektorC = new float[3];
    vektorC[0] = endeffektorx - x;
    vektorC[1] = (endeffektory + roboterHeights[2]+width) - y;
    vektorC[2] = endeffektorz - z;

    float a = roboterHeights[0]+width;
    float b = roboterHeights[1]+width;

    float c = sqrt(pow(vektorC[0], 2) + pow(vektorC[2], 2));
    float c2 = sqrt(pow(vektorC[0], 2) + pow(vektorC[1], 2) + pow(vektorC[2], 2));

    //Winkel des ersten Arms mittels Kosinussatz berechnen
    //b^2 = c^2 + a^2 - 2ca*cos(beta)
    //Umgestellt nach cos(beta)
    // cos(beta) = (b^2 - c^2 - a^2)/(-2*a*c)
    float cos_arm1Theta = (pow(b,2) - pow(c,2) - pow(a,2)) /(-2*a*c);
    float arm1Theta = acos(cos_arm1Theta)*180/pi;

    float cos_arm1Theta2 = (pow(vektorC[1],2) - pow(c2,2) - pow(c,2)) /(-2*c*c2);
    float arm1Theta2 = acos(cos_arm1Theta2)*180/pi;

    float cos_arm1Theta3 = (pow(b,2) - pow(c2,2) - pow(a,2)) /(-2*a*c2);
    float arm1Theta3 = acos(cos_arm1Theta3)*180/pi;

    arm1Theta = arm1Theta + (90 - arm1Theta + (arm1Theta2 - arm1Theta3));

    //Winkel des ersten Arms mittels Kosinussatz berechnen
    //c^2 = a^2 + b^2 - 2ab*cos(gamma)
    //Umgestellt nach cos(gamma)
    // cos(gamma) = (c^2 - a^2 - b^2) / (-2*a*b)
    float cos_arm2Theta = (pow(c2,2) - pow(a,2) - pow(b,2)) / (-2*a*b);
    float arm2Theta = acos(cos_arm2Theta)*180/pi;

   /* //Neigung nach Y - theta1 hinzufügen
    float thetaY = atan(vektorC[1]/c)*180/pi;

    arm1Theta = arm1Theta-thetaY;
    arm2Theta = arm2Theta+thetaY;
*/
    armsz[0] = arm1Theta;
    armsz[1] = 180 - arm2Theta;
    armsz[2] = (90 + (90-armsz[1])) - armsz[0];

}
