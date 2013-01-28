#include <GL/glut.h>
#include <iostream>
#include <math.h>

#include "HypnoCube.h"

HypnoCube cube;

const double PI = 3.1415926535898;

void init(void)
{
   glShadeModel(GL_SMOOTH);
}

GLdouble phi = PI/4;
GLdouble theta = PI/4;
void reshape (int w, int h) {
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glFrustum (-1.0, 1.0, -1.0, 1.0, 5.0, 35.0);
   glMatrixMode (GL_MODELVIEW);
   glLoadIdentity ();
   
   GLdouble eyeX = 2 * 15.0 * cos(phi) * sin(theta);
   GLdouble eyeY = 2 * 10.0 * sin(phi) * sin(theta);
   GLdouble eyeZ = 2 * 10.5 * cos(theta);
   gluLookAt(eyeX, eyeY, eyeZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void display(void) {
   glClear(GL_COLOR_BUFFER_BIT);
   glTranslatef(0.0, 0.0, 0.0);
   cube.draw();
   glutSwapBuffers();
}


void cycle_cube() {
   cube.random();
   glutPostRedisplay();
}

/* easter egg.. */
bool spinning = false;
void spin_cube() {
   theta += 0.1;
   phi -= 0.1;
   if(theta > 2*PI) {
      theta -= 2*PI;
   }
   if(phi > -2*PI) {
      phi += 2*PI;
   }
   reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
   glutPostRedisplay();
}   

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
      default:
	 break;
   }

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
