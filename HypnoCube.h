#ifndef __HYPNOCUBE_H__
#define __HYPNOCUBE_H__

#include <GL/glut.h>
#include "ColorTuple.h"

class HypnoCube {
  public:
   HypnoCube();
   HypnoCube(double x, double y, double z, double initRot = 0.0);
   ~HypnoCube() { delete[] ct; }
   void red();
   void green();
   void blue();
   void random();
   void rotate(GLdouble deg, bool x, bool y, bool z);
   void draw();
   GLdouble get_x() { return initX; }
   GLdouble get_y() { return initY; }
   GLdouble get_z() { return initZ; }
  private:
   GLdouble initX;
   GLdouble initY;
   GLdouble initZ;
   ColorTuple* ct;
   bool spinning;
   GLdouble rot;
   bool rotx;
   bool roty;
   bool rotz;
};


#endif
