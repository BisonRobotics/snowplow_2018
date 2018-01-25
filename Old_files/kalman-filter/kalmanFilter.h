#ifndef __KFILTER__H__
#define __KFILTER__H__

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>

namespace kFilter {

class _8x1Vector {
public:
    _8x1Vector(float i = 0.0f);
    glm::vec4 upper;
    glm::vec4 lower;
};

class _8x8Matrix : public _8x1Vector { // results from multiplication will always fit in the _8x8Matrix you are multiplying by
public:
    _8x8Matrix(float i = 0.0f);
    void multiply(_8x1Vector v8);
    void multiply(_8x1Vector v8);
    glm::mat4 uL;
    glm::mat4 uR;
    glm::mat4 lL;
    glm::mat4 lR;
};

void printMatrix(glm::mat4 m4);
void printMatrix(_8x8Matrix m8);

void printVector(glm::vec4 v4);
void printVector(_8x8Matrix m8);

void printMatrixVectorMult(glm::mat4 m4, glm::vec4 v4, glm::vec4 r);
void printMatrixVectorMult(_8x8Matrix m8. _8x1Vector v8);

} // end of namespace

#endif // __KFILTER__H__





