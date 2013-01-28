#ifndef __COLORTUPLE_H__
#define __COLORTUPLE_H__

#include <GL/glut.h>
#include <algorithm>
#include <stdlib.h>

class ColorTuple {
public:
   ColorTuple() { r_val = 0.0; g_val = 0.0; b_val = 0.0; }
   ColorTuple(GLdouble r, GLdouble g, GLdouble b);
   void random();
   void red();
   void green();
   void blue();
   GLdouble random_GLdouble();
   bool randColor() const { return is_random; }
   GLdouble r() const { return r_val; }
   GLdouble g() const { return g_val; }
   GLdouble b() const { return b_val; }
private:
   GLdouble r_val;
   GLdouble g_val;
   GLdouble b_val;
   bool is_random;
};

#endif
