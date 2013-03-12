#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <vector>

#include "HypnoCube.h"

/* BECAUSE I HATE HOW C++ WORKS WITH VECTORS AND ITERATORS. IT IS ANNOYING */
#define cube_in_cubes std::vector<HypnoCube*>::iterator cube = cubes.begin(); cube != cubes.end(); ++cube
/* woot python */

const double PI = 3.1415926535898; // Mmmm... pi.

HypnoCube cube0(0, 5, -5); // ALL GLORY TO HYPNOCUBE.
HypnoCube cube1(0, 5, 5);
HypnoCube cube2(0, -5, 5);
HypnoCube cube3(0, -5, -5);
HypnoCube cube4(0, 3, 3);

std::vector<HypnoCube*> cubes;

void init(void)
{
   srand(time(NULL)); // Seed PRNG
   glShadeModel(GL_SMOOTH); // Because we fancy.
}

void reshape (int w, int h) {
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glFrustum (-1.0, 1.0, -1.0, 1.0, 5.0, 40.0);
   glMatrixMode (GL_MODELVIEW);
   glLoadIdentity ();

   // added vars so we can adjust the camera later
   GLdouble eyeX = 35.0;
   GLdouble eyeY = 0.0;
   GLdouble eyeZ = 0.0;
   gluLookAt(eyeX, eyeY, eyeZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void display(void) {
   glClear(GL_COLOR_BUFFER_BIT);
   glTranslatef(0.0, 0.0, 0.0);

   /* do some shit here */
   
   for(cube_in_cubes) {
      (*cube)->draw();
   }
   
   glutSwapBuffers();
}

/* Cycle through the colors of the cube. Need this because we can't pass
   member functions to glutIdleFunc */
void cycle_cube() {
   for(cube_in_cubes) {
      (*cube)->random();
   }
   
   glutPostRedisplay();
}

/* No longer an Easter egg... please do not disregard :) */
bool spinning = false;
void spin_cube() {
   for(cube_in_cubes) {
      (*cube)->rotate(1, 0, 0.5, 0);
   }

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
	 for(cube_in_cubes) {
	    (*cube)->red();
	 }
	 break;
      case 'g':
	 for(cube_in_cubes) {
	    (*cube)->green();
	 }
	 break;
      case 'b':
	 for(cube_in_cubes) {
	    (*cube)->blue();
	 }
	 break;
      case 'm':
	 for(cube_in_cubes) {
	    (*cube)->random();
	 }
	 break;
      case 27:
	 exit(0);
	 break;
      case 'o':
	 for(cube_in_cubes) {
	    if(!(*cube)->is_cycling()) {
	       (*cube)->toggle_cycle();
	       glutIdleFunc(cycle_cube);
	    } else {
	       (*cube)->toggle_cycle();
	       glutIdleFunc(NULL);
	    }
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

	    for(cube_in_cubes) {
	       (*cube)->toggle_cycle();
	    }

	    glutIdleFunc(spin_and_flash);
	 } else {
	    spinning = false;

            for(cube_in_cubes) {
	       (*cube)->toggle_cycle();
	    }
	    
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
   cubes.push_back(&cube0); // You
   cubes.push_back(&cube1); // Only
   cubes.push_back(&cube2); // Live
   cubes.push_back(&cube3); // Once
   cubes.push_back(&cube4); // ! <- exclamation point

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
