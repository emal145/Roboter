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
    int changeComboBox();

private:
    Ui::MainWindow *ui;
    int auswahl;



};

#endif // MAINWINDOW_H
