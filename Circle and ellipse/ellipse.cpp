#include<stdio.h>
#include<GL/gl.h>
#include<glut.h>

void init(void)
{
	glClearColor(1.0,1.0,1.0,0.0);
	glColor3f(1.0,1.0,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,640.0,0.0,480.0);
}
float xc,yc,rx,ry;
void drawellipse(float xc,float yc,float x,float y)
{
	int p1[]={(int)xc+x,(int)yc+y};
	int p2[]={(int)xc-x,(int)yc+y};
	int p3[]={(int)xc+x,(int)yc-y};
	int p4[]={(int)xc-x,(int)yc-y};
	glBegin(GL_POINTS);
	glColor3f(1.0,1.0,0.0);
	glVertex2iv(p1);
	glVertex2iv(p2);
	glVertex2iv(p3);
	glVertex2iv(p4);
	glEnd();
	glFlush();
}
void display()
{
	float rxsq=rx*rx;
	float rysq=ry*ry;
	float x=0,y=ry,p;
	float px=0,py=2*rxsq*y;
	drawellipse(xc,yc,x,y);
	
	p=rysq-(rxsq*ry)+(0.25*rxsq);
	while(px<py)
	{
		x++;
		px+=2*rysq;
		if(p<0)
		{
			p=p+rysq+px;
		}
		else
		{
			y--;
			py=py-2*rxsq;
			p=p+rysq+px-py;
		}
		drawellipse(xc,yc,x,y);
	}
	p=rysq*(x+0.5)*(x+0.50)+rxsq*(y-1)*(y-1)-rxsq*rysq;
	while(y>0)
	{
		y--;
		py=py-2*rxsq;
		if(p>0)
		{
			p=p+rxsq-py;
		}
		else
		{
			x++;
			px=px+2*rysq;
			p=p+rxsq-py+px;
		}
		drawellipse(xc,yc,x,y);
	}
}
int main(int argc,char **argv)
{
	printf("Enter the centre coordinate: ");
	scanf("%f\t%f",&xc,&yc);
	printf("\nEnter major axis radius");
	scanf("%f",&rx);
	printf("\nEnter minor axis radius");
	scanf("%f",&ry);
	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Ellipse");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}

