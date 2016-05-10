#include "robot.h"

robot::robot()
{
    arm1 = robotarm(0.3, 4.0, 5.0, 0.0, 0.0);
    arm2 = robotarm(0.3, 2.0, 4.7, 4.0, 0.0);
    arm2.rotateZ(90.0);
}

void robot::drawRobot(){
    arm1.drawRobot();
    arm2.drawRobot();
}
