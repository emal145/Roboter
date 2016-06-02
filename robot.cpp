#include "robot.h"
#include <iostream>

robot::robot() //: robotBottom(zylinder(0.8, 0.4, 0.0))
{
    //Armbreite und gleichzeitig Gelenkkugel Durchmesser
    width = 0.3;
    //Armhöhe
    height = 4.0;
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

    armsz[0] = 45.0;
    armsz[1] = 20;
    //Verschiebung auf x, y und z der Roboter gezeichnet werden soll
    x = 5;
    y = 0;
    z = 0;

    //n-Roboterarme anlegen
    float* diffh = new float[nRobotarms];
    diffh[0] = 3.0;
    diffh[1] = 4.0;
    diffh[2] = 2.0;
    for(int i = 0; i < nRobotarms; i++){
       robotarms[i] = robotarm(width, diffh[i], x, y, z, i);
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
 }



void robot::drawRobot(){
    calculatRotations();
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

void robot::calculatRotations(){
    float pi = 3.1415926;

    //Zylinder Rotation
    float endeffectorX = 2;
    float endeffectorZ = 2;

    float hyp = sqrt(pow(x-endeffectorX,2.0) + pow(z-endeffectorZ,2.0));

    float theta = asin((x-endeffectorX)/hyp)*180/pi;
    robotBottomRotY = theta;
    //std::cout <<"theta: " << theta << std::endl;
}
