#include<stdio.h>
#include<conio.h>
#include<GL/gl.h>
#include<glut.h>
int x1,y1,r;
void plot(int x,int y)
{
	glBegin(GL_POINTS);
	glVertex2i(x+x1,y+y1);
	glEnd();
}
void init(void)
{
	glClearColor(1.0,1.0,1.0,0.0);
	glColor3f(0.0f,0.0f,1.0f);
	glPointSize(4.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,500.0,0.0,500.0);
}
void midpoint()
{
	int x=0,y=r;
	float dec=1;
	plot(x,y);
	while(y>x)
	{
		if(dec<8)
		{
			x++;
			dec+=2*x+1;
		}
		else
		{
			y--;
			x++;
			dec+=2*(x-y)+1;
		}
		plot(x,y);
		plot(x,-y);
		plot(-x,y);
		plot(-x,-y);
		plot(y,x);
		plot(-y,x);
		plot(y,-x);
		plot(-y,-x);
	}
}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0,0.0,0.0);
	glPointSize(1.0);
	midpoint();
	glFlush();
}
int main(int argc,char** argv)
{
	printf("Enter the coordinates of the center\n");
	printf("X- Coordinate\t");
	scanf("%d",&x1);
	printf("Y-Coordinate\t");
	scanf("%d",&y1);
	printf("Enter radius:\t");
	scanf("%d",&r);
	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(100,150);
	glutCreateWindow("Circle drawing using midpoint algorithm");
	glutDisplayFunc(display);
	init();
	glutMainLoop();
	
	return 0;
}
