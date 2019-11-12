#include<GL/gl.h>
#include<glut.h> 
#include<stdlib.h>
#include<stdio.h>

double y_max = 100, y_min = 50, x_max = 100, x_min = 50;   
double ny_max = 300, ny_min = 200, nx_max = 300, nx_min = 200;
int TOP = 8, BOTTOM = 4, RIGHT = 2, LEFT = 1;

double x1 = 10, y1 = 120;    
double x2 = 120, y2 = 50; 

void myInit();
void myDisplay();
void draw_lineAndPort(double x1, double y1, double x2, double y2, double y_max, double y_min, double x_max, double x_min);
void cohenSutherland(double x1, double y1, double x2, double y2);
int outcode(double x, double y);

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    
    glutCreateWindow("Cohen Sutherland");
    
    glutDisplayFunc(myDisplay);
    myInit();
    glutMainLoop();
    
    return 0;
}

void myInit()
{
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 500, 0, 500);
    glMatrixMode(GL_MODELVIEW);
}

void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    draw_lineAndPort(x1, y1, x2, y2, y_max, y_min, x_max, x_min);
    cohenSutherland(x1, y1, x2, y2);
    glFlush();
}

void draw_lineAndPort(double x1, double y1, double x2, double y2, double y_max, double y_min, double x_max, double x_min)
{
    glColor3d(1, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2d(x_min, y_min);
    glVertex2d(x_max, y_min);
    glVertex2d(x_max, y_max);
    glVertex2d(x_min, y_max);
    glEnd();
    
    glColor3d(1, 1, 1);
    glBegin(GL_LINES);
    glVertex2d(x1, y1);
    glVertex2d(x2, y2);
    glEnd();
}

int outcode(double x, double y)
{
    int out=0;
    if (y > y_max)
        out|= TOP;
    else if (y < y_min)
        out|= BOTTOM;
    
    if (x > x_max)
        out|= RIGHT;
    else if (x < x_min)
        out|= LEFT;
    return out;
}

void cohenSutherland(double x1, double y1, double x2, double y2)
{
    int c1 = outcode(x1, y1);
    int c2 = outcode(x2, y2);
    int outcodeOut;
    bool accept = false, done = false;
    
    do
    {
        if ((c1 | c2) == 0)   
        {
            accept = true;
            done = true;
        }
        else if ((c1 & c2) != 0)
        {
            done = true;
        }
        else
        {
            outcodeOut = (c1 != 0)? c1:c2;
            double x, y;
            double slope = (y2 - y1) / (x2 - x1);
            
            if (outcodeOut & TOP)
            {
                y = y_max;
                x = x1 + (y - y1) / slope;
            }
            else if (outcodeOut & BOTTOM)
            {
                y = y_min;
                x = x1 + (y - y1) / slope;
            }
            else if (outcodeOut & RIGHT)
            {
                x = x_max;
                y = y1 + (x - x1) * slope;
            }
            else
            {
                x = x_min;
                y = y1 + (x - x1) * slope;
            }
            
            if (outcodeOut ==c1)
            {
                x1 = x;
                y1 = y;
                c1 = outcode(x1, y1);
            }
            else
            {
                x2 = x;
                y2 = y;
                c2 = outcode(x2, y2);
            }
        }
    } while (!done);
    
    
    if(accept)
    {
        double scale_x = (nx_max - nx_min) / (x_max - x_min);
        double scale_y = (ny_max - ny_min) / (y_max - y_min);
        
        double nx1 = nx_min + (x1 - x_min) * scale_x;
        double ny1 = ny_min + (y1 - y_min) * scale_y;
        
        double nx2 = nx_min + (x2 - x_min) * scale_x;
        double ny2 = ny_min + (y2 - y_min) * scale_y;
        
        draw_lineAndPort(nx1, ny1, nx2, ny2, ny_max, ny_min, nx_max, nx_min);
    }
}

