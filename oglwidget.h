#ifndef OGLWIDGET_H
#define OGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMouseEvent>
#include <QTimer>
#include "table.h"
#include "kugel.h"
#include "quader.h"
#include "robot.h"

class OGLWidget : public QOpenGLWidget,
                  protected QOpenGLFunctions
{
    Q_OBJECT

public:
    OGLWidget(QWidget *parent = 0);
    ~OGLWidget();

    // Used to rotate object by mouse
    void mousePressEvent(QMouseEvent *event);
    // Used to rotate object by keys (requires focus for OpenGL widget)
    void keyPressEvent(QKeyEvent *event);

signals:
    // Emitted whenever a change of rotation angles is requested (e.g. by mouse or key)
    void changeRotation( int dx, int dy, int dz );

public slots:
    // Set the rotation angles
    void setRotX( int newrx );
    void setRotY( int newry );
    void setRotZ( int newrz );
    void stepAnimation();
    void resetRotation();
    void resetZoom();
    void resetKugel();
    // Set zoom factor
    void setZoom( int newzoom );
    // Set unfolding position

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

protected:
    int rotx;       // Rotation angles (0..360)
    int roty;
    int rotz;
    int zoom;       // Zoom factor (0..200, 100 for 1:1)
    int unfold;     // Unfolding position (0..100, 0 closed)
    QPoint lastpos; // Last position of mouse pressed, used for dragging
    int frames;
    table t;
    kugel k;
    double alpha;
    double beta;
    int kreisHoehe;
    int kreisBreite;
    int breitenCounter;
    quader q;
    bool qubeTop;
    int qubeCounter;
    float s;
    float h;
    robot roboter;
    QTimer* animtimer; // Timer needed to step animation every x msec
    int animstep;      // Current animation step (used to rotate triangle
};


#endif // OGLWIDGET_H
