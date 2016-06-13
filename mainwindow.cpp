#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QComboBox"
#include "QSpinBox"
#include "iostream"
#include "QGroupBox"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Handle slider usage
    connect(ui->sliderX, SIGNAL(valueChanged(int)), ui->glwidget, SLOT(setRotX(int)));
    connect(ui->sliderY, SIGNAL(valueChanged(int)), ui->glwidget, SLOT(setRotY(int)));
    connect(ui->sliderZ, SIGNAL(valueChanged(int)), ui->glwidget, SLOT(setRotZ(int)));

    //connect(ui->zoom, SIGNAL(valueChanged(int)), ui->glwidget, SLOT(setZoom(int)));
    connect(ui->sliderArm0, SIGNAL(valueChanged(int)), ui->glwidget, SLOT(setArm0Rotation(int)));
    connect(ui->sliderArm1, SIGNAL(valueChanged(int)), ui->glwidget, SLOT(setArm1Rotation(int)));
    connect(ui->sliderArm2, SIGNAL(valueChanged(int)), ui->glwidget, SLOT(setArm2Rotation(int)));

    connect(ui->resetR, SIGNAL(clicked(bool)), ui->glwidget, SLOT(resetRotation()));
    //Start + Stopp Button
    connect(ui->start, SIGNAL(clicked(bool)), ui->glwidget, SLOT(programmStart()));
    connect(ui->stopp, SIGNAL(clicked(bool)), ui->glwidget, SLOT(programmStopp()));
    //Formauswahl Kugel, Würfel, Zylinder
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), ui->glwidget, SLOT(changeComboBox(int)));

    // Handle any rotation change requests from mouse dragging and key presses
    connect( ui->glwidget, SIGNAL(changeRotation(int,int,int)), this, SLOT(onChangeRotation(int,int,int)));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onChangeRotation(int dx, int dy, int dz)
{
    // To apply the requested rotation deltas, we increment...
    int newx = ui->sliderX->value() + dx;
    int newy = ui->sliderY->value() + dy;
    int newz = ui->sliderZ->value() + dz;

    // ... and set the sliders to the new angles mod 360 (to ensure 0..359)
    ui->xRot->setValue( newx % 360 );
    ui->yRot->setValue( newy % 360 );
    ui->zRot->setValue( newz % 360 );

    ui->sliderX->setValue( newx % 360 );
    ui->sliderY->setValue( newy % 360 );
    ui->sliderZ->setValue( newz % 360 );
>>>>>>> origin/newRoboterarms
    // NB: SetValue will emit valueChanged signal, so the scene gets updated
}

