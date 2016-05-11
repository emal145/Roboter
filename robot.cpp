#include "robot.h"

robot::robot()
{
    arm1 = robotarm(0.3, 4.0, 5.0, 0.0, 0.0);
    arm2 = robotarm(0.3, 2.0, 5.0, 4.3, 0.0);
    arm2.rotateZ(0.0);
    arm3 = robotarm(0.3, 1.0, 4.7, 6.3, 0.0);
    arm3.rotateZ(90.0);
}

void robot::drawRobot(){
    arm1.drawRobot();
    arm2.drawRobot();
    arm3.drawRobot();
}
