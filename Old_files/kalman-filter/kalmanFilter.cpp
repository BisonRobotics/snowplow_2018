
#include "kalmanFilter.h"

kFilter::_8x8Matrix::_8x8Matrix(float i) {
    uL = glm::mat4(i);
    uR = glm::mat4(0.0f);
    lL = glm::mat4(0.0f);
    lR = glm::mat4(i);
}

kFilter::_8x1Vector::_8x1Vector(float i) {

}

void kFilter::_8x8Matrix::multiply(kFilter::_8x1Vector v8) {
    glm::vec4 tempUL = uL * v8.upper;
    glm::vec4 tempLL = lL * v8.upper;
    glm::vec4 tempUR = ur * v8.lower;
    glm::vec4 tempLR = lr * v8.lower;

    upper.x = tempUL.x + tempUR.x;
    upper.y = tempUL.y + tempUR.y;
    upper.z = tempUL.z + tempUR.z;
    upper.w = tempUL.w + tempUR.w;

    lower.x = tempLL.x + tempLR.x;
    lower.y = tempLL.y + tempLR.y;
    lower.z = tempLL.z + tempLR.z;
    lower.w = tempLL.w + tempLR.w;
}

void kFilter::printMatrix(glm::mat4 m4) {
    printf("%6.2f   %6.2f   %6.2f   %6.2f\n", m4[0].x, m4[1].x, m4[2].x, m4[3].x);
    printf("%6.2f   %6.2f   %6.2f   %6.2f\n", m4[0].y, m4[1].y, m4[2].y, m4[3].y);
    printf("%6.2f   %6.2f   %6.2f   %6.2f\n", m4[0].z, m4[1].z, m4[2].z, m4[3].z);
    printf("%6.2f   %6.2f   %6.2f   %6.2f\n", m4[0].w, m4[1].w, m4[2].w, m4[3].w);
}

void kFilter::printVector(glm::vec4 v4) {
    printf("%6.2f\n%6.2f\n%6.2f\n%6.2f\n", v4.x, v4.y, v4.z, v4.w);
}

void kFilter::printMatrixVectorMult(glm::mat4 m4, glm::vec4 v4, glm::vec4 r) {
    printf("%6.2f   %6.2f   %6.2f   %6.2f       %6.2f       %6.2f\n", m4[0].x, m4[1].x, m4[2].x, m4[3].x, v4.x, r.x);
    printf("%6.2f   %6.2f   %6.2f   %6.2f   x   %6.2f   =   %6.2f\n", m4[0].y, m4[1].y, m4[2].y, m4[3].y, v4.y, r.y);
    printf("%6.2f   %6.2f   %6.2f   %6.2f       %6.2f       %6.2f\n", m4[0].z, m4[1].z, m4[2].z, m4[3].z, v4.z, r.z);
    printf("%6.2f   %6.2f   %6.2f   %6.2f       %6.2f       %6.2f\n", m4[0].w, m4[1].w, m4[2].w, m4[3].w, v4.w, r.w);
}

void kFilter::printMatrix(kFilter::_8x8Matrix m8) {
    printf("%6.2f  %6.2f  %6.2f  %6.2f  %6.2f  %6.2f  %6.2f  %6.2f\n", m8.uL[0].x, m8.uL[1].x, m8.uL[2].x, m8.uL[3].x, m8.uR[0].x, m8.uR[1].x, m8.uR[2].x, m8.uR[3].x);
    printf("%6.2f  %6.2f  %6.2f  %6.2f  %6.2f  %6.2f  %6.2f  %6.2f\n", m8.uL[0].y, m8.uL[1].y, m8.uL[2].y, m8.uL[3].y, m8.uR[0].y, m8.uR[1].y, m8.uR[2].y, m8.uR[3].y);
    printf("%6.2f  %6.2f  %6.2f  %6.2f  %6.2f  %6.2f  %6.2f  %6.2f\n", m8.uL[0].z, m8.uL[1].z, m8.uL[2].z, m8.uL[3].z, m8.uR[0].z, m8.uR[1].z, m8.uR[2].z, m8.uR[3].z);
    printf("%6.2f  %6.2f  %6.2f  %6.2f  %6.2f  %6.2f  %6.2f  %6.2f\n", m8.uL[0].w, m8.uL[1].w, m8.uL[2].w, m8.uL[3].w, m8.uR[0].w, m8.uR[1].w, m8.uR[2].w, m8.uR[3].w);
    printf("%6.2f  %6.2f  %6.2f  %6.2f  %6.2f  %6.2f  %6.2f  %6.2f\n", m8.lL[0].x, m8.lL[1].x, m8.lL[2].x, m8.lL[3].x, m8.lR[0].x, m8.lR[1].x, m8.lR[2].x, m8.lR[3].x);
    printf("%6.2f  %6.2f  %6.2f  %6.2f  %6.2f  %6.2f  %6.2f  %6.2f\n", m8.lL[0].y, m8.lL[1].y, m8.lL[2].y, m8.lL[3].y, m8.lR[0].y, m8.lR[1].y, m8.lR[2].y, m8.lR[3].y);
    printf("%6.2f  %6.2f  %6.2f  %6.2f  %6.2f  %6.2f  %6.2f  %6.2f\n", m8.lL[0].z, m8.lL[1].z, m8.lL[2].z, m8.lL[3].z, m8.lR[0].z, m8.lR[1].z, m8.lR[2].z, m8.lR[3].z);
    printf("%6.2f  %6.2f  %6.2f  %6.2f  %6.2f  %6.2f  %6.2f  %6.2f\n", m8.lL[0].w, m8.lL[1].w, m8.lL[2].w, m8.lL[3].w, m8.lR[0].w, m8.lR[1].w, m8.lR[2].w, m8.lR[3].w);
}

void kFilter::printVector(kFilter::_8x8Matrix m8) {
    printf("%6.2f\n%6.2f\n%6.2f\n%6.2f\n%6.2f\n%6.2f\n%6.2f\n%6.2f\n",
        m8.upper.x, m8.upper.y, m8.upper.z, m8.upper.w, m8.lower.x, m8.lower.y, m8.lower.z, m8.lower.w);
}

void kFilter::printMatrixVectorMult(kFilter::_8x8Matrix m8, kFilter::_8x1Vector v8) {
    printf("%6.2f  %6.2f  %6.2f  %6.2f  %6.2f  %6.2f  %6.2f  %6.2f       %6.2f       %6.2f\n", m8.uL[0].x, m8.uL[1].x, m8.uL[2].x, m8.uL[3].x, m8.uR[0].x, m8.uR[1].x, m8.uR[2].x, m8.uR[3].x, v8.upper.x, m8.upper.x);
    printf("%6.2f  %6.2f  %6.2f  %6.2f  %6.2f  %6.2f  %6.2f  %6.2f       %6.2f       %6.2f\n", m8.uL[0].y, m8.uL[1].y, m8.uL[2].y, m8.uL[3].y, m8.uR[0].y, m8.uR[1].y, m8.uR[2].y, m8.uR[3].y, v8.upper.y, m8.upper.y);
    printf("%6.2f  %6.2f  %6.2f  %6.2f  %6.2f  %6.2f  %6.2f  %6.2f       %6.2f       %6.2f\n", m8.uL[0].z, m8.uL[1].z, m8.uL[2].z, m8.uL[3].z, m8.uR[0].z, m8.uR[1].z, m8.uR[2].z, m8.uR[3].z, v8.upper.z, m8.upper.z);
    printf("%6.2f  %6.2f  %6.2f  %6.2f  %6.2f  %6.2f  %6.2f  %6.2f   X   %6.2f   =   %6.2f\n", m8.uL[0].w, m8.uL[1].w, m8.uL[2].w, m8.uL[3].w, m8.uR[0].w, m8.uR[1].w, m8.uR[2].w, m8.uR[3].w, v8.upper.w, m8.upper.w);
    printf("%6.2f  %6.2f  %6.2f  %6.2f  %6.2f  %6.2f  %6.2f  %6.2f       %6.2f       %6.2f\n", m8.lL[0].x, m8.lL[1].x, m8.lL[2].x, m8.lL[3].x, m8.lR[0].x, m8.lR[1].x, m8.lR[2].x, m8.lR[3].x, v8.lower.x, m8.lower.x);
    printf("%6.2f  %6.2f  %6.2f  %6.2f  %6.2f  %6.2f  %6.2f  %6.2f       %6.2f       %6.2f\n", m8.lL[0].y, m8.lL[1].y, m8.lL[2].y, m8.lL[3].y, m8.lR[0].y, m8.lR[1].y, m8.lR[2].y, m8.lR[3].y, v8.lower.y, m8.lower.y);
    printf("%6.2f  %6.2f  %6.2f  %6.2f  %6.2f  %6.2f  %6.2f  %6.2f       %6.2f       %6.2f\n", m8.lL[0].z, m8.lL[1].z, m8.lL[2].z, m8.lL[3].z, m8.lR[0].z, m8.lR[1].z, m8.lR[2].z, m8.lR[3].z, v8.lower.z, m8.lower.z);
    printf("%6.2f  %6.2f  %6.2f  %6.2f  %6.2f  %6.2f  %6.2f  %6.2f       %6.2f       %6.2f\n", m8.lL[0].w, m8.lL[1].w, m8.lL[2].w, m8.lL[3].w, m8.lR[0].w, m8.lR[1].w, m8.lR[2].w, m8.lR[3].w, v8.lower.w, m8.lower.w);
}
