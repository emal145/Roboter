#ifndef QUADER_H
#define QUADER_H
#include <QWidget>
#include <QOpenGLWidget>
#include "rotationsmatrix.h"

class quader
{
public:
    quader();
    void drawCube(float red, float yellow, float blue, float s, float h, float dx, float dy, float dz, bool top);
    void rotateX(float rotx);
    void rotateY(float roty);
    void rotateZ(float rotz);
    float* endp1;
    float* endp2;
    float* endp3;
    float* endp4;


private:
    void drawGroundorTop(float s, float h);
    void drawQuads(float s, float h);
    void redrawCube();

    float red;
    float yellow;
    float blue;
    float s;
    float h;
    float dx;
    float dy;
    float dz;
    bool top;
    float rotx;
    float roty;
    float rotz;

protected:
    rotationsmatrix rotm;
    int counter;


};

#endif // QUADER_H
