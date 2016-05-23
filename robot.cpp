#include "robot.h"

robot::robot()
{

    width = 0.3;
    height = 4.0;
    nRobotarms = 3;
    robotarms = new robotarm[nRobotarms];

    x = 5;
    y = -5;
    z = 0;

    //n-Roboterarme anlegen
    float diffh = height;
    float dy = 0;
    for(int i = 0; i < nRobotarms; i++){
       robotarms[i] = robotarm(width, height, x, y, z, i, dy);
       dy = dy + height + width;
       diffh = height - i;
    }

    //Jedem Arm einen Nachfolger zuweisen
    for(int j = nRobotarms-1; j >= 0; j--){
        //letzen arm den vorletzen arm hinzufügen
        if((j-1) == 0){
            robotarms[0].setChildArm(robotarms[j]);
        }else{
            robotarms[j-1].setChildArm(robotarms[j]);
        }
    }
 }

void robot::drawRobot(){
    //moveJoint(0, 45.0);
    //moveJoint(1, 20.0);
    //moveJoint(2, 30.0);
    for(int i = 0; i < nRobotarms; i++){
       robotarms[i].drawRobot();
    }
}

void robot::moveJoint(int position, float rotZ){
    robotarms[position].rotateZ(rotZ);
}
