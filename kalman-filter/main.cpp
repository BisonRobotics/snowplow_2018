#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "kalmanFilter.h"
#include <stdio.h>

float a[16] =  {
                5.0f, 5.0f, 5.0f, 5.0f, // first column
                0.0f, 5.0f, 0.0f, 0.0f, // second column
                0.0f, 0.0f, 6.0f, 0.0f, // third column
                0.0f, 0.0f, 0.0f, 7.0f  // fourth column
            };

int main(int argc, char* argv[]) {
    glm::vec4 v4(1.0f, 2.0f, 3.0f, 4.0f);
    glm::mat4 m4 = glm::make_mat4(a);
    glm::vec4 result = m4 * v4;

    // print matrix
    //kFilter::printMatrix(m4);
    //kFilter::printVector(v4);
    //kFilter::printMatrixVectorMult(m4, v4, result);
    printf("\n\n");
    kFilter::_8x8Matrix A_(2.0);
    A_.uL = glm::mat4(4.0);
    A_.lR = glm::mat4(2.0);
    kFilter::printMatrix(A_);
    A_.multiply()

    kFilter::printMatrixVectorMult(A_, )

    return 0;

}
