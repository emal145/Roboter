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
    this->endeffektorx = endeffektor[0];
    this->endeffektory = endeffektor[1];
    this->endeffektorz = endeffektor[2];

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

    //Arm Rotationen
    //Betrag (Hypotenuse) von Roboter bis zum Punkt
    float c = sqrt(pow((x-endeffektorx),2) + pow((endeffektory),2));

    //Winkel des ersten Arms mittels Kosinussatz berechnen
    //b^2 = c^2 + a^2 - 2ca*cos(beta)
    //Umgestellt nach cos(beta)
    // cos(beta) = (c^2 + a^2 - 2ca) /b^2
    float a = roboterHeights[0];
    float b = roboterHeights[1];
    float cos_arm1Theta = (pow(c,2) + pow(a,2) - 2*c*a) / pow(b,2);
    float arm1Theta = acos(cos_arm1Theta)*180/pi;

    //Winkel des ersten Arms mittels Kosinussatz berechnen
    //c^2 = a^2 + b^2 - 2ab*cos(gamma)
    //Umgestellt nach cos(gamma)
    // cos(gamma) = (a^2 + b^2 - 2ab) /c^2
    float cos_arm2Theta = (pow(a,2) + pow(b,2) - 2*a*b) /pow(c,2);
    float arm2Theta = acos(cos_arm2Theta)*180/pi;

    armsz[0] = arm1Theta;
    armsz[1] = arm2Theta;
    armsz[2] = (90 + (90-armsz[1])) - armsz[0];

}
