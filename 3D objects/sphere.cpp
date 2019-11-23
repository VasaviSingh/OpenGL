#include <iostream>
#include<GL/gl.h>
#include<glut.h> 
#include<stdio.h>
#include<stdlib.h>

GLfloat xRotated, yRotated, zRotated;
GLdouble radius=1;
void display(void);
void reshape(int x, int y); 

int main (int argc, char **argv)
{
    glutInit(&argc, argv); 
    glutInitWindowSize(350,350);
    glutCreateWindow("Solid Sphere");
    xRotated = yRotated = zRotated = 30.0;
    xRotated=43;
    yRotated=50;
 
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
void display(void)
{
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0,0.0,-5.0);
    glColor3f(0.9, 0.3, 0.2);
    glRotatef(xRotated,1.0,0.0,0.0);
    glRotatef(yRotated,0.0,1.0,0.0);
    glRotatef(zRotated,0.0,0.0,1.0); 
    glScalef(1.0,1.0,1.0);
    glutSolidSphere(radius,20,20);    
    glFlush();        
}
void reshape(int x, int y)
{
    if (y == 0 || x == 0) return;   
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity(); 
    gluPerspective(39.0,(GLdouble)x/(GLdouble)y,0.6,21.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0,0,x,y); 
}
 
