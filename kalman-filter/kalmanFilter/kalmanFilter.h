#include <armadillo>


namespace Kfilter:

class kalmanFilter{

    public:
        kalmanFilter(mat<float> A, mat<float> B,mat<float> C, mat<float> D);

        vec<float> update(vec<float> state, vec<float> measurement);
//        systemMatrix(mat<float> AMat);
//        inputMatrix(mat<float> BMat);
//        measurementMatrix(mat<float> CMat);
//        measurementNoise(mat<float> DMat);

    private:
        mat<float> A;
        mat<float> B;
        mat<float> C;
        mat<float> P;
        mat<float> Q;
        vec<float> pre_state;
}
