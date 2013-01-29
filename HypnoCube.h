#ifndef __HYPNOCUBE_H__
#define __HYPNOCUBE_H__

#include <GL/glut.h>
#include "ColorTuple.h"

class HypnoCube {
  public:
   HypnoCube();
   HypnoCube(GLdouble x, GLdouble y, GLdouble z);
   ~HypnoCube() { delete[] ct; }
   void red();
   void green();
   void blue();
   void random();
   void rotate(GLdouble deg, bool x, bool y, bool z);
   void toggle_cycle() { cycling = !cycling; }
   bool is_cycling() { return cycling; }
   void draw();
  private:
   GLdouble initX;
   GLdouble initY;
   GLdouble initZ;
   bool cycling;
   ColorTuple* ct;
   bool spinning;
   GLdouble rot;
   bool rotx;
   bool roty;
   bool rotz;
};


#endif
