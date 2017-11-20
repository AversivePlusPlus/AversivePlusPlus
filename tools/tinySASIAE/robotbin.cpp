#include "robotbin.hpp"

//#include <QException>
#include <stdexcept>

#include <QStringList>
#include <QDebug>
#include <stdint.h>

#include <iostream>

#include <QCoreApplication>

static const char *const binPath = "robot/robot_sasiae.elf";
static const double encCoef = 100.;
static const double timeCoef = 1000000.;
static const int mainLoopIteration = 10;
static const double leftMotCoef = 1.;
static const double rightMotCoef = 1.2;

// Device initialisation messages
static const char *const leftEncInit = "D leftEnc init";
static const char *const rightEncInit = "D rightEnc init";
static const char *const ioInit = "D io init";

// From SASIAE to robot code messages
static const char *const leftEncMsg = "D leftEnc value %1";
static const char *const rightEncMsg = "D rightEnc value %1";
static const char *const syncMsg = "T %1 %2";

// From robot code to SASIAE messages
static const char *const syncMsg2 = "T";
static const char *const deviceMsg = "D";
static const char *const leftMotName = "leftMot";
static const char *const rightMotName = "rightMot";
static const char *const ioName = "io";
static const char *const valueMsg = "value";

// Generic messages
static const char *const stopMsg = "S";

RobotBin::RobotBin(Robot& robot, const PhysicsEngine& engine, QObject *parent) :
    QObject(parent), _robot(robot), _engine(engine)
{
    QStringList args = QCoreApplication::arguments();
    QString path = "";
    bool found = false;
    for(int i = 0 ; i < args.count() ; i++) {
        if(args[i] == "-r") {
            if(i+1 < args.count()) {
                path = args[i+1];
                found = true;
            }
            else {
                qDebug() << "Error in arguments : nothing after -r";
            }
        }
    }
    if(!found) {
        qDebug() << "Robot's binary not found in application's arguments, trying default.";
        path = binPath;
    }

    _proc.start(path, QStringList());
    if(!_proc.waitForStarted()) {
        qDebug() << "Could not start robot's code with path: " << path << "\n";
        throw std::runtime_error("");
    }

    bool le = false, re = false;
    for(int i = 0; i < 3; i++)
    {
        QString line = readLineFromProc();
        if(line == leftEncInit)
        {
            le = true;
        }
        else if(line == rightEncInit)
        {
            re = true;
        }
        else if(line == ioInit)
        {
            // NOTHING TO DO
        }
        else
        {
            qDebug() << line << "\n";
            killProc();
            throw std::runtime_error("");
        }
    }

    if(!(le && re))
    {
        qDebug() << "All the devices were not initialised\n";
        killProc();
        throw std::runtime_error("");
    }
}

RobotBin::~RobotBin()
{
    if(_proc.state() != QProcess::NotRunning)
    {
        killProc();
    }
}

void RobotBin::update()
{
    _proc.write(QString(leftEncMsg).arg(static_cast<int32_t>(encCoef * _robot.left_encoder)).toLocal8Bit().append("\n"));
    _proc.write(QString(rightEncMsg).arg(static_cast<int32_t>(encCoef * _robot.right_encoder)).toLocal8Bit().append("\n"));
    _proc.write(QString(syncMsg).arg(static_cast<u_int32_t>(timeCoef * _engine.getTime())).arg(mainLoopIteration).toLocal8Bit().append("\n"));

    QString line;
    while((line = readLineFromProc()) != QString() && line != QString(syncMsg2) && line != QString(stopMsg))
    {
        QStringList words = line.split(" ");
        if(words.length() != 4)
        {
            qDebug() << line << "\n";
            killProc();
            throw std::runtime_error("");
        }

        if(words[0] == QString(deviceMsg) && words[2] == QString(valueMsg))
        {
            double speed = words[3].toDouble();
            if(words[1] == QString(leftMotName))
            {
                _robot.left_speed = leftMotCoef * speed;
            }
            else if(words[1] == QString(rightMotName))
            {
                _robot.right_speed = rightMotCoef * speed;
            }
            else if(words[1] == QString(ioName)) {
                std::cout << (char)words[3].toInt();
            }
            else
            {
                killProc();
                throw std::runtime_error("");
            }
        }
        else
        {
            killProc();
            throw std::runtime_error("");
        }
    }
}

QString RobotBin::readLineFromProc()
{
    QString line;
    char c = 0;

    if(!_proc.getChar(&c)) {
        _proc.waitForReadyRead();
    }
    else {
        line.append(QChar(c));
    }

    while(_proc.getChar(&c) && c != '\n') {
        line.append(QChar(c));
    }

    if(c == '\n') {
        return line;
    }
    else {
        // Problem
        return QString();
    }
}

void RobotBin::killProc()
{
    _proc.kill();
    _proc.waitForFinished();
}
