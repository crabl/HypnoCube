#include "ColorTuple.h"

// PRNG method, seeded in init() because seeding is expensive
GLdouble ColorTuple::random_GLdouble() {
   return rand() / static_cast<GLdouble>(RAND_MAX);
}

ColorTuple::ColorTuple(GLdouble r=0.0, GLdouble g=0.0, GLdouble b=0.0) {
   /* Color values should be between 0 and 1 only... not checking at the moment */
   r_val = r;
   g_val = g;
   b_val = b;
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
   is_random = false; // make sure flag is false in non-random cases
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
