#ifndef ROBOT_H
#define ROBOT_H
#include "robotarm.h"

class robot
{
public:
    robot();
    void drawRobot();

private:
    robotarm arm1;
    robotarm arm2;
    robotarm arm3;
};

#endif // ROBOT_H
