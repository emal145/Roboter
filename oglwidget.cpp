#include "oglwidget.h"
#include <iostream>
#include <cmath>
#include <math.h>

OGLWidget::OGLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    rotx = 0;
    roty = 0;
    rotz = 0;
    zoom = 10;
    frames = 40;
    alpha = 0.0;
    beta = 0;
    kreisHoehe = 270;
    kreisBreite = 360;
    breitenCounter = 0;
    quader = GeoQuad();
    gkugel = geokugel(1.0,0.0,0.0);
    k = kugel(1.0,0.0,0.0);
    zy = zylinder(1.0,1.0,1.0);
    s = 3;
    h = 0;
    form = 0;
    qubeCounter = 0;
    qubeTop = false;
    roboter = robot();
    startAnim = false;
    // Setup the animation timer to fire every x msec
    animtimer = new QTimer(this);

    // Everytime the timer fires, the animation is going one step forward
    connect(animtimer, SIGNAL(timeout()), this, SLOT(stepAnimation()));
    animstep = 0;
}

OGLWidget::~OGLWidget()
{
}
void OGLWidget::changeComboBox(int auswahl){
   form = auswahl;
}

void OGLWidget::setForm(){
    //Kugel
    if(form ==0){
        roboter.calculatRotations(gkugel.drawKugel(2.0, 0.0,0.0,2.0, kreisHoehe, kreisBreite));
        //Würfel
    } else if (form ==1){
        quader.drawCube(0.0,0.0,1.0,s,h,2,1,0, qubeTop);
        //Zylinder
    } else if (form ==2){
        zy.drawZylinder(zyradius,zyhoehe,1.0,1.0,1.0);
    }


}

//Hier prüfen, ob Kreis oder Würfel und dann die entsprechende Zeit
//(WEnn Kugel- Werte verändern und prüfen ob Timer zuende ist.)
void OGLWidget::stepAnimation()
{
    if (form ==0){
        if(kreisHoehe < 90){
            animtimer->stop(); //TimerStop
        }
        kreisBreite = kreisBreite - 15;
        if(kreisBreite == 0){
            kreisBreite = 360;
            kreisHoehe = kreisHoehe-2;
        }

    }else if(form ==1){
        if(qubeCounter == 300){
              qubeTop = true;
              animtimer->stop();
        }
        h = qubeCounter * (3.0f/360.0f);

    }else if(form ==2){
        if(zyhoehe == -3){
            animtimer->stop();
        }
        zyhoehe = qubeCounter *(-3.0f/360.0f);
    }
    qubeCounter++;
    update();      // Trigger redraw of scene with paintGL




}

void OGLWidget::setRotX(int newrx)
{
    rotx = newrx;
    update();
}

void OGLWidget::setRotY(int newry)
{
    roty = newry;
    update();
}

void OGLWidget::setRotZ(int newrz)
{
    rotz = newrz;
    update();
}

void OGLWidget::setArm0Rotation(int rz){
    float z = rz%360;
    this->roboter.setArmZ(0,z);
    update();
}

void OGLWidget::setArm1Rotation(int rz){
    float z = rz%360;
    this->roboter.setArmZ(1,z);
    update();
}

void OGLWidget::setArm2Rotation(int rz){
    float z = rz%360;
    this->roboter.setArmZ(2,z);
    update();
}


void OGLWidget::programmStart(){

 kreisHoehe = 270;
 kreisBreite = 360;
 qubeCounter = 0;
 qubeTop = false;
 zyradius = 1.5;
 zyhoehe = 0;
 startAnim = true;
 animtimer->start(1);//TimerStart (1= Milisekunden)
 update();
}

void OGLWidget::programmStopp(){
    startAnim = false;
    animtimer->stop();
}

void OGLWidget::resetRotation(){
    rotx = 0;
    roty = 0;
    rotz = 0;
    update();
}

void OGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0,0,0,1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHT0);
   // glEnable(GL_LIGHTING);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    glOrtho(-50,50,-50,50,2,10);
    // For wireframe replace GL_FILL with GL_LINE
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void OGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    // Apply rotation angles
    glRotatef(rotx, 1.0f, 0.0f, 0.0f); // Rotate around x axis
    glRotatef(roty, 0.0f, 1.0f, 0.0f); // Rotate around y axis
    glRotatef(rotz, 0.0f, 0.0f, 1.0f); // Rotate around z axis

    // Apply scaling
    float scale = zoom/100.0;
    glScalef( scale, scale, scale ); // Scale along all axis
    //glShadeModel(GL_FLAT);
    //k.drawKugel(0.3, roboter.endeffektorx, 0.3, roboter.endeffektorz, 90, 360);
    //if(startAnim == true){
    // setForm();
    //}
    //roboter.drawRobot();
    //ÄNDUNG Auswahl festlegen, wenn Kugel kugel zeichen usw!!!!
    roboter.drawRobot();
    roboter.calculatRotations(gkugel.drawKugel(0.3, 2, 2, 1, 90, 360));


    //X-Achse
    glBegin(GL_QUADS);
     glColor3f(0.0, 0.0, 1.0);
     glVertex3f(0.0,0.0,0.0);
     glVertex3f(0.0,0.0,0.1);
     glVertex3f(20.0,0.0,0.1);
     glVertex3f(20.0,0.0,0.0);
    glEnd();

    //Y-Achse
    glBegin(GL_QUADS);
     glColor3f(0.0, 1.0, 0.0);
     glVertex3f(0.0,0.0,0.0);
     glVertex3f(0.1,0.0,0.0);
     glVertex3f(0.1,20.0,0.0);
     glVertex3f(0.0,20.0,0.0);
    glEnd();

    //Z-Achse
    glBegin(GL_QUADS);
     glColor3f(1.0, 0.0, 0.0);
     glVertex3f(0.0,0.0,0.0);
     glVertex3f(0.1,0.0,0.0);
     glVertex3f(0.1,0.0,20.0);
     glVertex3f(0.0,0.0,20.0);
    glEnd();

}

void OGLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void OGLWidget::mousePressEvent(QMouseEvent *event)
{
    // Upon mouse pressed, we store the current position...
    lastpos = event->pos();
}

void OGLWidget::keyPressEvent(QKeyEvent *event)
{
    // This is the delta we want to use for rotating
    const int keyDelta = 10;

    switch(event->key())
    {
    // Up/Down: Rotating around x axis
    case Qt::Key_Up:
        emit changeRotation( keyDelta, 0, 0 );
        break;
    case Qt::Key_Down:
        emit changeRotation( -keyDelta, 0, 0 );
        break;

        // Left/Right: Rotating around y axis
    case Qt::Key_Left:
        emit changeRotation( 0, keyDelta, 0 );
        break;
    case Qt::Key_Right:
        emit changeRotation( 0, -keyDelta, 0 );
        break;

        // Pg up/down: Rotating around z axis
    case Qt::Key_PageUp:
        emit changeRotation( 0, 0, keyDelta );
        break;
    case Qt::Key_PageDown:
        emit changeRotation( 0, 0, -keyDelta );
        break;

        // All other will be ignored
    default:
        break;
    }
}
