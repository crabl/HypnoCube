#include "HypnoCube.h"

HypnoCube::HypnoCube() {
   cycling = false;
   ct = new ColorTuple[64];
}

HypnoCube::HypnoCube(GLdouble x, GLdouble y, GLdouble z) {
   initX = x;
   initY = y;
   initZ = z;
   cycling = false;
   ct = new ColorTuple[64];
}

void HypnoCube::red() {
   for(int i = 0; i < 64; i++) {
      ct[i].red();
   }
}

void HypnoCube::green() {
   for(int i = 0; i < 64; i++) {
      ct[i].green();
   }
}

void HypnoCube::blue() {
   for(int i = 0; i < 64; i++) {
      ct[i].blue();
   }
}

void HypnoCube::random() {
   for(int i = 0; i < 64; i++) {
      ct[i].random();
   }
}

void HypnoCube::draw() {
   glTranslatef(initX, initY, initZ);

   glPushMatrix();
   glColor3f(0.0, 0.0, 0.0);
   glScalef(0.8, 0.2, 0.8);
   glTranslatef(1.8, -4.0, 1.9);
   glutSolidCube((GLdouble) 4.4);
   glPopMatrix();

   /* Draw wires before drawing lights */
   glTranslatef(0.0, 0.0, 0.0);
   for(int i = 0; i < 4; i++) {
      for(int j = 0; j < 4; j++) {
	 for(int k = 0; k < 4; k++) {
	    glPushMatrix();
	    glColor3f(0.2, 0.2, 0.2);
	    glTranslatef(0.0, 0.0, (GLdouble) k);
	    glBegin(GL_LINES);
	    glVertex2d((GLdouble) j, (GLdouble) i);
	    glVertex2d((GLdouble) k, (GLdouble) i);
	    glEnd();

	    glBegin(GL_LINES);
	    glVertex2d((GLdouble) i, (GLdouble) j);
	    glVertex2d((GLdouble) i, (GLdouble) k);
	    glEnd();
	    glPopMatrix();
	 }
      }
   }

   /* Draw lights */
   glTranslatef(0.0, 0.0, 0.0);
   for(int i = 0; i < 4; i++) {
      for(int j = 0; j < 4; j++) {
	 for(int k = 0; k < 4; k++) {
	    glPushMatrix();
	    int index = i*16 + j*4 + k;
	    glColor3f(ct[index].r(), ct[index].g(), ct[index].b());
	    glTranslatef((GLdouble) i, (GLdouble) j, (GLdouble) k);
	    glutSolidCube((GLdouble) 0.2);
	    glPopMatrix();
	 }
      }
   }
   
}
