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
    //int form;

private slots:
    void onChangeRotation( int dx, int dy, int dz );

    //void changeComboBox();
    void checkForm();


private:
    Ui::MainWindow *ui;




};

#endif // MAINWINDOW_H
