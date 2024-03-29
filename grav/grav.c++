#include <iostream>
#include <string>
#include <time.h>

// Unit is meter.  Scale is 1 m = 1 char.
int const SpaceLength = 100;            // m
// TODO:  double const SpaceScale = 0.1           // meters per character
double const InitialSpeed = 50;         // m/s
double const GravityAccel = -9.80665;   // m/s2
double const TickSimTime  =  0.01;      // s
double const TickRealTime =  0.01;      // s

void visualize(int accel, int speed, int pos, int time)
{
     std::string space(SpaceLength, ' ');
     space+= '|';

     if (pos >= 0 && pos < SpaceLength)
          space[SpaceLength-pos] = 'O';

     std::cout << "\r" << space << ' ' << accel << ' ' << speed << ' ' << pos << ' ' << time << "      ";
     std::cout.flush();
}

void tick(double& accel, double& speed, double& pos, double& time)
{
     pos+=   (speed * TickSimTime);
     speed+= (accel * TickSimTime);
     time+= TickSimTime;

     if (pos <= 0 && speed < 0) {
          speed*= -0.8;  // bounce;
          pos = 0;
     }

     timespec sleep_time;
     sleep_time.tv_sec = int(TickRealTime);
     sleep_time.tv_nsec = long((TickRealTime - int(TickRealTime)) * long(1E9));

     while(nanosleep(&sleep_time, 0));
}

int main()
{
     double time = 0;
     double pos = 0;
     double speed = InitialSpeed;
     double accel = GravityAccel;

     while(true) {
          tick(accel, speed, pos, time);
          visualize(int(accel), int(speed), int(pos), int(time));
     }

     std::cout << std::endl;

     return 0;
}
