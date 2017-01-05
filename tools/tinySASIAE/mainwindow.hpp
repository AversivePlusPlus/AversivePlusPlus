#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "robot.hpp"
#include <QGraphicsScene>
#include <QLinkedList>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Robot& robot, QWidget *parent = 0);
    ~MainWindow();

  void renderRobot(void);
  void renderWorld(void);

public slots:
    void update();

private:
    Ui::MainWindow *ui;
    Robot& _robot;

    QGraphicsScene _scene;
    QLinkedList<QPointF> _pointList;

    static const int POINT_LIST_SIZE = 50;
    static const int ADD_POINT_EVERY = 10;
};

#endif // MAINWINDOW_H
