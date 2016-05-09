#ifndef TABLE_H
#define TABLE_H

#include <QWidget>
#include <QOpenGLWidget>

class table
{
public:
    table();
    void drawTable(float red, float green, float blue);

private:
    void drawBoden(float red, float green, float blue);
    void seiteAB(float red, float green, float blue);
    void seiteBC(float red, float green, float blue);
    void seiteCD(float red, float green, float blue);
    void seiteAD(float red, float green, float blue);
};



#endif // TABLE_H
