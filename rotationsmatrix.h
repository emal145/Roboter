#ifndef ROTATIONSMATRIX_H
#define ROTATIONSMATRIX_H
#include <math.h>


class rotationsmatrix
{
public:
    rotationsmatrix();
    float* rotateX(float r, float x, float y, float z, float alpha);
    float* rotatey(float r, float x, float y, float z, float beta);
    float* rotatez(float r, float x, float y, float z, float gamma);
    float* nrotatey(float r, float x, float y, float z, float beta);
    float* nrotatez(float r, float x, float y, float z, float gamma);
    float cosToDegree(float alpha);
    float sinToDegree(float alpha);

private:
    float pi;
};


#endif // ROTATIONSMATRIX_H
