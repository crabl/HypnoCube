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

const size_t NUM_HYPNOCUBES = 10; // Well, you said more than 5...
const int VIEW_HEIGHT = 20;
const int VIEW_WIDTH = 20;
const int VIEW_DEPTH = 20;

const GLdouble PITCH_YAW_INCREMENT = 0.25;

const double PI = 3.1415926535898; // Mmmm... pi.
const double ROOT_2_INV = 0.7071; // 1/sqrt(2)... not so delicious.

GLdouble eyeX = 0.0;
GLdouble eyeY = 0.0;
GLdouble eyeZ = 20.0;

GLdouble centerX = 0.0;
GLdouble centerY = 0.0;
GLdouble centerZ = 0.0;

GLdouble vupX = 0.0;
GLdouble vupY = 1.0;
GLdouble vupZ = 0.0;

std::vector<HypnoCube*> cubes;

void init(void) {
   srand(time(NULL)); // Seed PRNG
   glShadeModel(GL_SMOOTH); // Because we fancy.
}

void reshape (int w, int h) {
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 50.0);
}

void display(void) {
   glClear(GL_COLOR_BUFFER_BIT);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, vupX, vupY, vupZ);
   
   glTranslatef(0.0, 0.0, 0.0);

   // DRAW THE TETRAHEDRON! (...drawing the tetrahedron.)
   glPushMatrix();
   glFrontFace(GL_CCW);

   // BDA - 1 - PURPLE
   glColor3f(0.5, 0.0, 0.5);
   glBegin(GL_TRIANGLES);
   glVertex3d(-1.0, 0.0, -ROOT_2_INV); // b
   glVertex3d(1.0, 0.0, -ROOT_2_INV); // a
   glVertex3d(0.0, -1.0, ROOT_2_INV); // d
   glEnd();
      
   // DBC - 2 - RED
   glColor3f(1.0, 0.0, 0.0);
   glBegin(GL_TRIANGLES);
   glVertex3d(-1.0, 0.0, -ROOT_2_INV); // b 
   glVertex3d(0.0, -1.0, ROOT_2_INV); // d
   glVertex3d(0.0, 1.0, ROOT_2_INV); // c
   glEnd();
      
   // BCA - 3 - GREEN
   glColor3f(0.0, 1.0, 0.0);
   glBegin(GL_TRIANGLES);
   glVertex3d(1.0, 0.0, -ROOT_2_INV); // a
   glVertex3d(-1.0, 0.0, -ROOT_2_INV); // b 
   glVertex3d(0.0, 1.0, ROOT_2_INV); // c  
   glEnd();

   // DAC - 4 - BLUE
   glColor3f(0.0, 0.0, 1.0);
   glBegin(GL_TRIANGLES);
   glVertex3d(0.0, -1.0, ROOT_2_INV); // d
   glVertex3d(1.0, 0.0, -ROOT_2_INV); // a 
   glVertex3d(0.0, 1.0, ROOT_2_INV); // c
   glEnd();
   
   glPopMatrix();
   
   // DRAW THE CUBES! (...drawing the cubes.)
   for(cube_in_cubes) {
      (*cube)->draw();
   }
   
   glutSwapBuffers();
}

/* Cycle through the colors of the cube. Need this because we can't pass
   member functions to glutIdleFunc */
bool cycling = false;
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
      (*cube)->rotate(3, 0, 1, 0);
   }

   glutPostRedisplay();
}   

/* Ditto */
void spin_and_flash() {
   spin_cube();
   cycle_cube();
}


/*************** MOVEMENT FUNCTIONS *********************/
void move_forward() {
   eyeZ -= 0.45;
   glutPostRedisplay();
}

void move_backward() {
   eyeZ += 0.45;
   glutPostRedisplay();
}

void roll_left() {
  vupX += 0.05;
  glutPostRedisplay();
}

void roll_right() {
  vupX -= 0.05;
  glutPostRedisplay();
}

void pitch_up() {
  centerY += PITCH_YAW_INCREMENT;
  glutPostRedisplay();
}

void pitch_down() {
  centerY -= PITCH_YAW_INCREMENT;
  glutPostRedisplay();
}

void yaw_left() {
  centerX -= PITCH_YAW_INCREMENT;
  glutPostRedisplay();
}

void yaw_right() {
  centerX += PITCH_YAW_INCREMENT;
  glutPostRedisplay();
}

/****************************************************/

/*********** FPS FUNCTIONS **************************/

bool looking_at(HypnoCube* h) {
  GLdouble tol = 5;
  GLdouble hx = h->get_x();
  GLdouble hy = h->get_y();

  GLdouble x = centerX;
  GLdouble y = centerY;
  if(x > hx - tol && x < hx + tol) {
    if(y > hy - tol && y < hy + tol) {
      return true;
    }
  }

  return false;

}

void shoot_hypnocube() {
  for(cube_in_cubes) {
    if(looking_at(*cube)) {
      cubes.erase(cube);
      break;
    }
  }
}

void create_hypnocube() {
  HypnoCube* hc = new HypnoCube(centerX, centerY, centerZ, 0);
  cubes.push_back(hc);

  glutPostRedisplay();
}

/* Handle keyboard events from the user */
void keyboard(unsigned char key, int x, int y) {
  switch(key) {
  case 'c':
    create_hypnocube();
    break;
  case 'q':
    shoot_hypnocube();
    break;
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
  case 'z': 
    roll_left();
    break; 
  case 'x': 
    roll_right();
    break; 
  case 'o':
    if(!cycling) {
      cycling = true;
      if(!spinning) {
	glutIdleFunc(cycle_cube);
      } else {
	glutIdleFunc(spin_and_flash);
      }
    } else {
      cycling = false;
      if(!spinning) {
	glutIdleFunc(NULL);
      } else {
	glutIdleFunc(spin_cube);
      }
    }
    break;
  case 's':
    // S IS FOR SWAGGER
    if(!spinning) {
      spinning = true;
      if(!cycling) {
	glutIdleFunc(spin_cube);
      } else {
	glutIdleFunc(spin_and_flash);
      }
    } else {
      spinning = false;
      if(!cycling) {
	glutIdleFunc(NULL);
      } else {
	glutIdleFunc(cycle_cube);
      }
    }
    break;
  case 'f':
    move_forward();
    break;
  case 32:
    move_backward();
    break;
  default:
    break;
  }
  
  glutPostRedisplay();
}

void specialKeyboard(int key, int x, int y) {
  switch(key) {
  case GLUT_KEY_UP:
    pitch_up();
    break;
  case GLUT_KEY_DOWN:
    pitch_down();
    break;
  case GLUT_KEY_LEFT:
    yaw_left();
    break;
  case GLUT_KEY_RIGHT:
    yaw_right();
    break;
  default:
    break;
  }

  glutPostRedisplay();
}


int main(int argc, char** argv) {

   /* Generate HypnoCubes in random places in our world */
   for(int i = 0; i < NUM_HYPNOCUBES; ++i) {
      int sign_x = (rand() % 2) * 2 - 1;
      int sign_y = (rand() % 2) * 2 - 1;
      int sign_z = (rand() % 2) * 2 - 1;
      
      GLdouble x = sign_x * rand() / static_cast<GLdouble>(RAND_MAX) * VIEW_WIDTH;
      GLdouble y = sign_y * rand() / static_cast<GLdouble>(RAND_MAX) * VIEW_HEIGHT;
      GLdouble z = sign_z * rand() / static_cast<GLdouble>(RAND_MAX) * VIEW_DEPTH;
      GLdouble theta = rand() / static_cast<GLdouble>(RAND_MAX) * 360;

      HypnoCube* hc = new HypnoCube(x,y,z,theta);
      cubes.push_back(hc);
   }
   
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize(500, 500);
   glutInitWindowPosition(100, 100);
   glutCreateWindow(argv[0]);
   init();
   glEnable(GL_CULL_FACE); 
   glClearColor(1.0, 1.0, 1.0, 1.0);
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutSpecialFunc(specialKeyboard);
   glutMainLoop();
   return 0;
}
