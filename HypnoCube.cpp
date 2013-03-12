
#include "HypnoCube.h"

HypnoCube::HypnoCube() {
   cycling = false;
   ct = new ColorTuple[64];
}

HypnoCube::HypnoCube(GLdouble x, GLdouble y, GLdouble z) {
   // TODO: Check these values for sanity
   initX = x;
   initY = y;
   initZ = z;
   cycling = false;
   ct = new ColorTuple[64];
}

// Set each light to be red
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

// Set each light to have a random color
void HypnoCube::random() {
   for(int i = 0; i < 64; i++) {
      ct[i].random();
   }
}

void HypnoCube::rotate(GLdouble deg, bool x, bool y, bool z) {
   bool is_spinning = true;
   rot += deg;
   rotx = x;
   roty = y;
   rotz = z;
}

void HypnoCube::draw() {
   // Translate to initial position
   glPushMatrix();
   glTranslatef(initX, initY, initZ);
   glRotatef(rot, rotx, roty, rotz); // TODO
   glColor3f(0.0, 0.0, 0.0);
   glScalef(0.8, 0.2, 0.8); // TODO: Should implement scaling as well...
   glutSolidCube((GLdouble) 4.4);
   glPopMatrix();

   double fudgeX = -1.5;
   double fudgeY = 0.7;
   double fudgeZ = -1.5;
   
   /* Draw wires before drawing lights */
   for(int i = 0; i < 4; i++) {
      for(int j = 0; j < 4; j++) {
	 for(int k = 0; k < 4; k++) {
	    glPushMatrix();
	    glTranslatef(initX, initY, initZ);
	    glRotatef(rot, rotx, roty, rotz); // TODO

	    glColor3f(0.2, 0.2, 0.2);
	    glTranslatef(fudgeX, fudgeY, ((GLdouble) k) + fudgeZ);
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
   //glTranslatef(0.0, 0.0, 0.0);
   for(int i = 0; i < 4; i++) {
      for(int j = 0; j < 4; j++) {
	 for(int k = 0; k < 4; k++) {
	    glPushMatrix();
	    glTranslatef(initX, initY, initZ);
	    glRotatef(rot, rotx, roty, rotz); // TODO

	    int index = i*16 + j*4 + k;

	    glColor3f(ct[index].r(), ct[index].g(), ct[index].b());
	    glTranslatef((GLdouble) i + fudgeX, (GLdouble) j + fudgeY, (GLdouble) k + fudgeZ);
	    glutSolidCube((GLdouble) 0.2);
	    glPopMatrix();
	 }
      }
   }
   
}
