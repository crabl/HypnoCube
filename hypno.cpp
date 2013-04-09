#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <cmath>
#include "HypnoCube.h"

/* BECAUSE I HATE HOW C++ WORKS WITH VECTORS AND ITERATORS. IT IS ANNOYING */
#define cube_in_cubes std::vector<HypnoCube*>::iterator cube = cubes.begin(); cube != cubes.end(); ++cube
/* woot python */

const bool DEBUG = false;

const size_t NUM_HYPNOCUBES = 10; // Well, you said more than 5...
const int VIEW_HEIGHT = 20;
const int VIEW_WIDTH = 20;
const int VIEW_DEPTH = 20;

const double PI = 3.1415926535898; // Mmmm... pi.
const double ROOT_2_INV = 0.7071; // 1/sqrt(2)... not so delicious.

const GLdouble ROTATE_INCREMENT = PI/40;
const GLdouble MOVE_FACTOR = 0.45;

const GLdouble ANGLE_THRESHOLD = 0.2;
const GLdouble CUBE_CREATE_DISTANCE = 10;

struct vect3d {
  GLdouble x;
  GLdouble y;
  GLdouble z;
} cam, vpn, vup, vrp, x_axis, y_axis, z_axis;


std::vector<HypnoCube*> cubes;

void init(void) {
   srand(time(NULL)); // Seed PRNG
   glShadeModel(GL_SMOOTH); // Because we fancy.

   cam.x = 0.0;
   cam.y = 0.0;
   cam.z = 20.0;

   vpn.x = 0.0;
   vpn.y = 0.0;
   vpn.z = -1.0;

   vup.x = 0.0;
   vup.y = 1.0;
   vup.z = 0.0;

   vrp.x = 1.0;
   vrp.y = 0.0;
   vrp.z = 0.0;

   /* Some axes in case we need them */
   x_axis.x = 1.0;
   x_axis.y = 0.0;
   x_axis.z = 0.0;

   y_axis.x = 0.0;
   y_axis.y = 1.0;
   y_axis.z = 0.0;

   z_axis.x = 0.0;
   z_axis.y = 0.0;
   z_axis.z = 1.0;

}

void reshape (int w, int h) {
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 100.0);
}

void display(void) {
  if(DEBUG) {
    std::cout << "CAM: " << cam.x << " " << cam.y << " " << cam.z << std::endl;
    std::cout << "VPN: " << vpn.x << " " << vpn.y << " " << vpn.z << std::endl;
    std::cout << "VUP: " << vup.x << " " << vup.y << " " << vup.z << std::endl;
    std::cout << "VRP: " << vrp.x << " " << vrp.y << " " << vrp.z << std::endl;
  }

   glClear(GL_COLOR_BUFFER_BIT);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt(cam.x, cam.y, cam.z, cam.x+vpn.x, cam.y+vpn.y, cam.z+vpn.z, vup.x, vup.y, vup.z);
   
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

/*************** VECTOR FUNCTIONS ************************/

/* Steve's code... wow this is ugly. Modified to use my vect3d struct */
void rotate_about(vect3d& v, const vect3d& u, float Theta)
{   
  GLdouble uX, uY, uZ;
  uX = u.x;
  uY = u.y;
  uZ = u.z;
  float ct,st,lv0,lv1,lv2;
  ct= cos(Theta);
  st= sin(Theta);

  lv0=v.x;
  lv1=v.y;
  lv2=v.z;

  v.x = lv0*(uX*uX +  ct * (1.0-uX*uX))  +
    lv1*(uX*uY * (1.0-ct) - uZ*st)+
    lv2*(uZ*uX * (1.0-ct) + uY*st);

  v.y = lv0*(uX*uY * (1.0-ct) + uZ*st)+
    lv1*(uY*uY +  ct      * (1.0-uY*uY))  +
    lv2*(uY*uZ * (1.0-ct) - uX*st);

  v.z = lv0*(uZ*uX * (1.0-ct) - uY*st)+
    lv1*(uY*uZ * (1.0-ct) + uX*st)+
    lv2*(uZ*uZ +  ct      * (1.0-uZ*uZ));
}

/*
  Computes the determinant:
  
  | a  b |
  | c  d | = det(a,b,c,d)
  
 */
GLdouble det(GLdouble a, GLdouble b, GLdouble c, GLdouble d) {
  return a*d - b*c;
}


/* Computes the cross product of two vectors using determinants */
void cross_product(vect3d& result, const vect3d& u, const vect3d& v) {
  result.x = det(u.y, u.z, v.y, v.z);
  result.y = (-1.0) * det(u.x, u.z, v.x, v.z);
  result.z = det(u.x, u.y, v.x, v.y);
}

/* Computes the dot product */
GLdouble dot_product(const vect3d& u, const vect3d& v) {
  GLdouble dot = u.x * v.x + u.y * v.y + u.z * v.z;
  return dot;
}

/* Magnitude of a vector */
GLdouble mag(const vect3d& v) {
  return std::sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

void recompute_vrp() {
  cross_product(vrp, vpn, vup);
}

/*********************************************************/


/*************** MOVEMENT FUNCTIONS *********************/
void move_forward() {
  cam.x += MOVE_FACTOR * vpn.x;
  cam.y += MOVE_FACTOR * vpn.y;
  cam.z += MOVE_FACTOR * vpn.z;

  glutPostRedisplay();
}

void move_backward() {
  cam.x -= MOVE_FACTOR * vpn.x;
  cam.y -= MOVE_FACTOR * vpn.y;
  cam.z -= MOVE_FACTOR * vpn.z;
  glutPostRedisplay();
}

void roll_left() {
  rotate_about(vup, vpn, -ROTATE_INCREMENT);
  glutPostRedisplay();
}

void roll_right() {
  rotate_about(vup, vpn, ROTATE_INCREMENT);
  glutPostRedisplay();
}

void pitch_up() {
  recompute_vrp();
  rotate_about(vup, vrp, ROTATE_INCREMENT);
  rotate_about(vpn, vrp, ROTATE_INCREMENT);
  glutPostRedisplay();
}

void pitch_down() {
  recompute_vrp();
  rotate_about(vup, vrp, -ROTATE_INCREMENT);
  rotate_about(vpn, vrp, -ROTATE_INCREMENT);
  glutPostRedisplay();
}

void yaw_left() {
  recompute_vrp();
  /* rotate about y-axis, NOT VUP!!!! */
  rotate_about(vpn, y_axis, ROTATE_INCREMENT);
  rotate_about(vup, y_axis, ROTATE_INCREMENT);
  glutPostRedisplay();
}

void yaw_right() {
  recompute_vrp();
  /* we want to rotate about the y-axis, not VUP! */
  rotate_about(vpn, y_axis, -ROTATE_INCREMENT);
  rotate_about(vup, y_axis, -ROTATE_INCREMENT);
  glutPostRedisplay();
}

/****************************************************/

/*********** FPS FUNCTIONS **************************/

bool looking_at(HypnoCube* h) {
  vect3d hc;
  hc.x = h->get_x() - cam.x;
  hc.y = h->get_y() - cam.y;
  hc.z = h->get_z() - cam.z;

  /* calculate the angle difference between vrp and hypnocube */
  GLdouble dp = dot_product(hc, vpn);
  GLdouble magnitudes = mag(hc) * mag(vpn);
  GLdouble theta = std::acos(dp / magnitudes);
  
  // std::cout << "Theta: " << theta << std::endl;
  /* If it's within a certain threshold, kill the cube */
  if(theta < ANGLE_THRESHOLD) {
    return true;
  }

  return false;

}

void shoot_hypnocube() {
  for(cube_in_cubes) {
    if(looking_at(*cube)) {
      // std::cout << "KILLED HYPNOCUBE!" << std::endl;
      cubes.erase(cube);
      break; // only kill one at a time!
    }
  }
}

void create_hypnocube() {
  HypnoCube* hc = new HypnoCube(cam.x + vpn.x * CUBE_CREATE_DISTANCE, 
				cam.y + vpn.y * CUBE_CREATE_DISTANCE, 
				cam.z + vpn.z * CUBE_CREATE_DISTANCE, 0);
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
