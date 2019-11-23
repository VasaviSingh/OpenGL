#include <iostream>
#include<GL/gl.h>
#include<glut.h> 
#include<stdio.h>
#include<stdlib.h>
#define PI 3.1415926535898 

GLfloat xRotated, yRotated, zRotated;
GLdouble base=1;
GLdouble height=1.5;
GLint slices =30;
GLint stacks =30;

void displayCone(void)
{
			glMatrixMode(GL_MODELVIEW);
            glClear(GL_COLOR_BUFFER_BIT);
            glLoadIdentity();
            glTranslatef(0.0,0.0,-3.5);
            glColor3f(0.5, 0., 0.1);   

            glRotatef(xRotated,1.0,0.0,0.0);
            glRotatef(yRotated,0.0,1.0,0.0);
            glRotatef(zRotated,0.0,0.0,1.0);
            glScalef(1.0,1.0,1.0);
            glutSolidCone(base,height,slices,stacks);
            glFlush();       
}
void reshapeCone(int x, int y)
{
            if (y == 0 || x == 0) return;     
            glMatrixMode(GL_PROJECTION); 
            glLoadIdentity();  
            gluPerspective(40.0,(GLdouble)x/(GLdouble)y,0.5,20.0);
            glViewport(0,0,x,y); 
}
int main (int argc, char **argv)
{   
            glutInit(&argc, argv);
            glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
            glutInitWindowSize(400,350);
            glutCreateWindow("Cone");
            glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
            zRotated = 30.0;
            xRotated=30;
            yRotated=40;
            glClearColor(0.0,0.0,0.0,0.0);
            glutDisplayFunc(displayCone);
            glutReshapeFunc(reshapeCone);
            glutMainLoop();
            return 0;

}
