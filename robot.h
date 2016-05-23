#ifndef ROBOT_H
#define ROBOT_H
#include "robotarm.h"

class robot
{
public:
    robot();
    void drawRobot();
    void moveJoint(int position, float rotZ);
    /*void moveJoint1(float rotZ);
    void moveJoint2(float rotZ);
    void moveJoint3(float rotZ);
    */

private:
    robotarm *robotarms;
    float width;
    float height;
    int nRobotarms;
    float x;
    float y;
    float z;
};

#endif // ROBOT_H
