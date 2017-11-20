This project is currently unstable, and does not link with the master branch of Aversive++

# project-2wheel-asserv

This project is a base code to create a controlled 2 wheeled robot.
It enables the use of several trajectory behaviours (target points, following lines, circles).

It is multiplateform, you can control any robot that has a microncontoller supported by Aversive++, and these peripherals :

 - 2 motors (left/right) : 
 A rotative actuator that can be controlled in speed (forward and backward).
 
 - 2 encoder (left/right) : 
 A sensor that can get the distance traveled by a wheel. 
 The encoders does not need to be real sensors.
 Ideed, you can directly integrate the value sent to motors to get an evaluation of the traveled distance.
 Of course, it is far to be precise, and will not detect obstacles.
 
 - 1 communication port : Generally UART, but it can be anything.
