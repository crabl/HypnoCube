#include "ColorTuple.h"

GLdouble ColorTuple::random_GLdouble() {
   return rand() / static_cast<GLdouble>(RAND_MAX);
}

ColorTuple::ColorTuple(GLdouble r=0.0, GLdouble g=0.0, GLdouble b=0.0) {
   r_val = std::min(r, 1.0);
   g_val = std::min(g, 1.0);
   b_val = std::min(b, 1.0);
}

void ColorTuple::random() {
   r_val = random_GLdouble();
   g_val = random_GLdouble();
   b_val = random_GLdouble();
   is_random = true;
}
   
void ColorTuple::red() {
   r_val = 1.0;
   g_val = 0.0;
   b_val = 0.0;
   is_random = false;
}

void ColorTuple::green() {
   r_val = 0.0;
   g_val = 1.0;
   b_val = 0.0;
   is_random = false;
}

void ColorTuple::blue() {
   r_val = 0.0;
   g_val = 0.0;
   b_val = 1.0;
   is_random = false;
}
