#ifndef ROBOTBIN_HPP
#define ROBOTBIN_HPP

#include <QObject>
#include <QString>
#include <QProcess>

#include "robot.hpp"
#include "physicsengine.hpp"

class RobotBin : public QObject
{
    Q_OBJECT
public:
    explicit RobotBin(Robot& robot, const PhysicsEngine& engine, QObject *parent = 0);
    virtual ~RobotBin();

signals:

public slots:
    void update();

protected:
    QString readLineFromProc();
    void killProc();

private:
    Robot& _robot;
    const PhysicsEngine& _engine;
    QProcess _proc;
};

#endif // ROBOTBIN_HPP
