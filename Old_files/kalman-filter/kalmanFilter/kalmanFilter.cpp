#include "kalmanFilter.h"


Kfilter::kalmanFilter(mat<float> A, mat<float> B,mat<float> C, mat<float> D)
{
    this.A = A;
    this.B = B;
    this.C = C;
    this.D = D;

}


Kfilter::update(vec<float> state,vec<floate> input, vec<float> measurement[])
{


    //1 Propagate State
    //x_e = A * x_p + B * u

    preState = A * state + B * input;


    //2 Propagate Covariance
    // P = A * P * A' + Q;

    P_p = A * P * A.t + Q;


    //3 Calculate State Measurement
    //y = C * x_e + D

    y = C * preState + D;


    //4 Calculate Measurement Noise
    //Sk = C * P * Ck' + R

    Sk = C * P_p * C.t + R;

    //5 Calculate Kalman Gain
    //K = P * C' * inv(Sk)

    K = P * C.t * S.i;

    //6 Update State
    //x = x_e + K * (z - y)

    newState = preState + K * (measurement - y);

    //7 Update Covariance
    //P  = (I - K * C) * P

    p = (speye(8) - K * C) * P;


    return newState;

}

