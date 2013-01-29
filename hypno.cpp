#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "HypnoCube.h"

const double PI = 3.1415926535898; // Mmmm... pi.

HypnoCube cube; // ALL GLORY TO HYPNOCUBE.

void init(void)
{
   srand(time(NULL)); // Seed PRNG
   glShadeModel(GL_SMOOTH); // Because we fancy.
}

void reshape (int w, int h) {
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glFrustum (-1.0, 1.0, -1.0, 1.0, 5.0, 35.0);
   glMatrixMode (GL_MODELVIEW);
   glLoadIdentity ();

   // added vars so we can adjustthe camera later
   GLdouble eyeX = 15.0;
   GLdouble eyeY = 10.0;
   GLdouble eyeZ = 10.5;
   gluLookAt(eyeX, eyeY, eyeZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void display(void) {
   glClear(GL_COLOR_BUFFER_BIT);
   glTranslatef(0.0, 0.0, 0.0);
   cube.draw();
   glutSwapBuffers();
}

/* Cycle through the colors of the cube. Need this because we can't pass
   member functions to glutIdleFunc */
void cycle_cube() {
   cube.random();
   glutPostRedisplay();
}

/* Easter egg... please disregard :) */
bool spinning = false;
void spin_cube() {
   cube.rotate(1, 0, 1, 0);
   glutPostRedisplay();
}   

/* Ditto */
void spin_and_flash() {
   spin_cube();
   cycle_cube();
}

/* Handle keyboard events from the user */
void keyboard(unsigned char key, int x, int y)
{
   switch(key) {
      case 'r':
	 cube.red();
	 break;
      case 'g':
	 cube.green();
	 break;
      case 'b':
	 cube.blue();
	 break;
      case 'm':
	 cube.random();
	 break;
      case 27:
	 exit(0);
	 break;
      case 'o':
	 if(!cube.is_cycling()) {
	    cube.toggle_cycle();
	    glutIdleFunc(cycle_cube);
	 } else {
	    cube.toggle_cycle();
	    glutIdleFunc(NULL);
	 }
	 break;
      case 's':
	 if(!spinning) {
	    spinning = true;
	    glutIdleFunc(spin_cube);
	 } else {
	    spinning = false;
	    glutIdleFunc(NULL);
	 }
	 break;
      case 'q':
	 if(!spinning) {
	    spinning = true;
	    cube.toggle_cycle();
	    glutIdleFunc(spin_and_flash);
	 } else {
	    spinning = false;
	    cube.toggle_cycle();
	    glutIdleFunc(NULL);
	 }
	 break;
      default:
	 break;
   }
   
   /* Easter eggs: S (spin), Q (spin cycle) */
   glutPostRedisplay();
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (500, 500);
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   glClearColor(1.0, 1.0, 1.0, 1.0);
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);

   glutMainLoop();
   return 0;
}
