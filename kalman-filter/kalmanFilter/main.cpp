#include <armadillo>


float a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13;
float b1, b2, b3, b4, b5;
float

%% Constants

IT=0;       //%counter iterations
Dt=.785;    //%
Dte=.785;   //%
gam=0.1;    //%
kb=0.154;   //%EMF constant
kt=0.13;    //%Torque constant
nr=20;      //%
Iw=0.764;   //%
m=230;      //%
Nc=2014;    //%
B=0.88;     //%Robot width
Icr=127.7;  //%Mass moment of inertia
rw=0.2794;  //%
Ra=0.32;    //%Motor resistance

THk=0;
thi=0;
Dx=0;
Dy=0;
DTHk=0;
dt = 0.2;

a1 = 1 - (2*kb * kt * nr^2/(Ra * (4 * Iw + m * rw^2))) * dt;
a2 = 1 - (2*kb * kt * nr^2/(Ra * (4 * Iw + m * rw^2))) * dt;
a3 = 1 - (2*kb * kt * nr^2/(Ra * (4 * Iw + m * rw^2))) * dt;
a4 = 0;
a5 = 1 - (B^2 * kb * kt * nr^2/(2 * Icr * Ra * rw^2)) * dt;
a6 = dt;
a7 = 1;
a8 = dt*cos(thi);
a9 = 0;
a10= 1;
a11= dt*sin(thi);
a12 = 0;
a13 = 1;
