#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onChangeRotation( int dx, int dy, int dz );

private:
    Ui::MainWindow *ui;
    int form;



};

#endif // MAINWINDOW_H
