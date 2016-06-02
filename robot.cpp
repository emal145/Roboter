#include "robot.h"

robot::robot()
{

    //Armbreite und gleichzeitig Gelenkkugel Durchmesser
    width = 0.3;
    //Armhöhe
    height = 4.0;
    //Anzahl der Arme des Roboters
    nRobotarms = 3;
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
    //Rotation der Einzelnen Arme durchführen weiter geben
    for(int i = 0; i < nRobotarms; i++){
        moveJoint(i, armsz[i]);
    }

    //jeden einzelnen Arm zeichen
    for(int i = 0; i < nRobotarms; i++){
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
