#include<stdio.h>
#include<conio.h>
#include<GL/gl.h>
#include<glut.h>
int x1,y2,r;
void eightWaySymmetricPlot(int xc,int yc,int x,int y)
{
	glBegin(GL_POINTS);
    glVertex2i(x+xc,y+yc); 
    glVertex2i(x+xc,-y+yc); 
    glVertex2i(-x+xc,-y+yc);
    glVertex2i(-x+xc,y+yc);
    glVertex2i(y+xc,x+yc);
    glVertex2i(y+xc,-x+yc); 
    glVertex2i(-y+xc,-x+yc);
    glVertex2i(-y+xc,x+yc);
    glEnd();
}
void init(void)
{
	glClearColor(0.7,0.7,0.7,0.7);
	glColor3f(0.0f,0.0f,1.0f);
	glPointSize(2.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-100.0,100.0,-100.0,100.0);
}
void PolarCircle(int xc,int yc,int r)  
{  
    int x,y,d;  
    x=0;  
    y=r;  
    d=3-2*r;  
    eightWaySymmetricPlot(xc,yc,x,y);  
    while(x<=y)  
    {  
        if(d<=0)  
        {  
            d=d+4*x+6;  
        }  
        else  
        {  
            d=d+4*x-4*y+10;  
            y=y-1;  
        }  
        x=x+1;  
        eightWaySymmetricPlot(xc,yc,x,y);  
    }  
}  
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0,0.0,0.0);
	glPointSize(1.0);
	PolarCircle(x1,y2,r);
	glFlush();
}
int main(int argc,char** argv)
{
	printf("Enter the coordinates of the center\n");
	printf("X- Coordinate\t");
	scanf("%d",&x1);
	printf("Y-Coordinate\t");
	scanf("%d",&y2);
	printf("Enter radius:\t");
	scanf("%d",&r);
	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(100,150);
	glutCreateWindow("Circle drawing using Polar Coordinate\n");
	glutDisplayFunc(display);
	init();
	glutMainLoop();
	
	return 0;
}
