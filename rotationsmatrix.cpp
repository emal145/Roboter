#include "rotationsmatrix.h"

rotationsmatrix::rotationsmatrix()
{
    pi = 3.1415926;

}

float rotationsmatrix::cosToDegree(float alpha){
    if(alpha == 90 || alpha == 270 || alpha == -90 || alpha == -270){
        return 0;
    }
    else if(alpha == 180 || alpha == -180){
        return -1;
    }
    else if(alpha == 360 || alpha == -360){
        return 1;
    }
    return  cos(alpha*pi/180);
}

float rotationsmatrix::sinToDegree(float alpha){
    if(alpha == 90 || alpha == -270){
        return 1;
    }
    else if(alpha == 180 || alpha == 360 || alpha == -180 || alpha == -360){
        return 0;
    }
    else if(alpha == 270 || alpha == -90){
        return -1;
    }
    return  sin(alpha*pi/180);
}

float* rotationsmatrix::rotateX(float r, float x, float y, float z, float alpha){
    //alpha rotation um x-achse;

    /*
     * [ x   y   z  ]
     * --           --
     * | 1   0    0  |
     * | 0  cos -sin |
     * | 0  sin  cos |
     * --           --
     */
    float *rpoints = new float[3];
    rpoints[0] = r*x;
    rpoints[1] = y * cosToDegree(alpha) + z * (-sinToDegree(alpha));
    rpoints[2] = y * sinToDegree(alpha) + z * cosToDegree(alpha);

    return rpoints;
}

float* rotationsmatrix::rotatey(float r, float x, float y, float z, float beta){
    //beta rotation um y-achse:

    /*
     * [ x   y   z  ]
     * --           --
     * | cos  0  sin  |
     * |  0   1   0   |
     * |-sin  0  cos  |
     * --           --
     */

    if(beta > 0){
        return nrotatey(r,x,y,z,beta);
    }
    float *rpoints = new float[3];
    rpoints[0] = x * cosToDegree(beta) + z * sinToDegree(beta);
    rpoints[1] = r*y;
    rpoints[2] = x * (-sinToDegree(beta)) + z * cosToDegree(beta);

    return rpoints;
}

float* rotationsmatrix::rotatez(float r, float x, float y, float z, float gamma){
    //gamma rotation um z-achse:

    /*
     * [ x   y   z  ]
     * --           --
     * | cos -sin  0 |
     * | sin  cos  0 |
     * |  0    0   1 |
     * --           --
     */

    if(gamma < 0){
        return nrotatez(r,x,y,z,gamma);
    }

    float *rpoints = new float[3];
    rpoints[0] = x * cosToDegree(gamma) + y * (-sinToDegree(gamma));
    rpoints[1] = x * sinToDegree(gamma) + y * cosToDegree(gamma);
    rpoints[2] = r*z;

    return rpoints;
}

float* rotationsmatrix::nrotatey(float r, float x, float y, float z, float beta){
    //beta rotation um y-achse:

    /*
     * [ x   y   z  ]
     * --           --
     * | cos  0  -sin  |
     * |  0   1   0    |
     * |sin  0  cos    |
     * --           --
     */
    float *rpoints = new float[3];
    rpoints[0] = x * cosToDegree(beta) + z * -sinToDegree(beta);
    rpoints[1] = r*y;
    rpoints[2] = x * sinToDegree(beta) + z * cosToDegree(beta);

    return rpoints;
}

float* rotationsmatrix::nrotatez(float r, float x, float y, float z, float gamma){
    //gamma rotation um z-achse:

    /*
     * [ x   y   z  ]
     * --           --
     * | cos sin  0 |
     * |-sin  cos  0 |
     * |  0    0   1 |
     * --           --
     */
    float *rpoints = new float[3];
    rpoints[0] = x * cosToDegree(gamma) + y * sinToDegree(gamma);
    rpoints[1] = x * (-sinToDegree(gamma)) + y * cosToDegree(gamma);
    rpoints[2] = r*z;

    return rpoints;
}
