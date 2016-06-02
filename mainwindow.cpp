#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QComboBox"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Handle slider usage
    connect(ui->xRot, SIGNAL(valueChanged(int)), ui->glwidget, SLOT(setRotX(int)));
    connect(ui->yRot, SIGNAL(valueChanged(int)), ui->glwidget, SLOT(setRotY(int)));
    connect(ui->zRot, SIGNAL(valueChanged(int)), ui->glwidget, SLOT(setRotZ(int)));

    connect(ui->zoom, SIGNAL(valueChanged(int)), ui->glwidget, SLOT(setZoom(int)));
    connect(ui->arm0Rotatez, SIGNAL(valueChanged(int)), ui->glwidget, SLOT(setArm0Rotation(int)));
    connect(ui->arm1Rotatez, SIGNAL(valueChanged(int)), ui->glwidget, SLOT(setArm1Rotation(int)));
    connect(ui->arm2Rotatez, SIGNAL(valueChanged(int)), ui->glwidget, SLOT(setArm2Rotation(int)));

    connect(ui->resetK, SIGNAL(clicked(bool)), ui->glwidget, SLOT(resetKugel()));
    connect(ui->resetR, SIGNAL(clicked(bool)), ui->glwidget, SLOT(resetRotation()));
    connect(ui->resetZ, SIGNAL(clicked(bool)), ui->glwidget, SLOT(resetZoom()));
    //Start + Stopp Button
    connect(ui->start, SIGNAL(clicked(bool)), ui->glwidget, SLOT(programmStart(auswahl)));
    connect(ui->stopp, SIGNAL(clicked(bool)), ui->glwidget, SLOT(programmStopp()));

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
    int newx = ui->xRot->value() + dx;
    int newy = ui->yRot->value() + dy;
    int newz = ui->zRot->value() + dz;

    // ... and set the sliders to the new angles mod 360 (to ensure 0..359)
    ui->xRot->setValue( newx % 360 );
    ui->yRot->setValue( newy % 360 );
    ui->zRot->setValue( newz % 360 );

    // NB: SetValue will emit valueChanged signal, so the scene gets updated
}

int MainWindow::changeComboBox(){

    if(ui->comboBox->currentText() == "Kugel"){
        auswahl = 1;
        return auswahl;
    } else if (ui->comboBox->currentText() == "Würfel"){
        auswahl = 2;
        return auswahl;
    } else if (ui->comboBox->currentText() == "Zylinder"){
        auswahl = 3;
        return auswahl;
    }

}
