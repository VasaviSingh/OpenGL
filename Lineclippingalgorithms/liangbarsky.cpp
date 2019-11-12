#include<GL/gl.h>
#include<glut.h> 
#include<stdlib.h>
#include<stdio.h>

double y_max = 100, y_min = 50, x_max = 100, x_min = 50;   
double ny_max = 300, ny_min = 200, nx_max = 300, nx_min = 200; 
double t1 = 0.0, t2 = 1.0; 

double x1 = 10, y1 = 20;   
double x2 = 120, y2 = 80;  

void myDisplay();
void draw_lineAndPort(double x1, double y1, double x2, double y2, double y_max, double y_min, double x_max, double x_min);
void liangBarsky(double x1, double y1, double x2, double y2);
bool cliptest(double p, double q);

void myInit()
{
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 500, 0, 500);
    glMatrixMode(GL_MODELVIEW);
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    
    glutCreateWindow("Liang Barsky");
    
    glutDisplayFunc(myDisplay);
    myInit();
    glutMainLoop();
    return 0;
}



void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    draw_lineAndPort(x1, y1, x2, y2, y_max, y_min, x_max, x_min);
    liangBarsky(x1, y1, x2, y2);
    
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

bool cliptest(double p, double q)
{
    double t = q / p;
    
    if (p == 0 && q < 0)    // Line is parallel to viewport and outside
    {
        return false;
    }
    else if (p < 0)
    {
        if (t > t1)
            t1 = t;
        if (t > t2)
            return false;
    }
    else if (p > 0)
    {
        if (t < t2)
            t2 = t;
        if (t < t1)
            return false;
    }
    return true;
}

void liangBarsky(double x1, double y1, double x2, double y2)
{
    double dx = x2 - x1;
    double dy = y2 - y1;
   
    if (cliptest(-dx, x1 - x_min) && cliptest(dx, x_max - x1) && cliptest(-dy, y1 - y_min) && cliptest(dy, y_max - y1))
    {
        if (t2 < 1)
        {
            x2 = x1 + t2 * dx;
            y2 = y1 + t2 * dy;
        }
        if (t1 > 0)
        {
            x1 = x1 + t1 * dx;
            y1 = y1 + t1 * dy;
        }
        double scale_x = (nx_max - nx_min) / (x_max - x_min);
        double scale_y = (ny_max - ny_min) / (y_max - y_min);
        
        double nx1 = nx_min + (x1 - x_min) * scale_x;
        double ny1 = ny_min + (y1 - y_min) * scale_y;
        
        double nx2 = nx_min + (x2 - x_min) * scale_x;
        double ny2 = ny_min + (y2 - y_min) * scale_y;
        
        draw_lineAndPort(nx1, ny1, nx2, ny2, ny_max, ny_min, nx_max, nx_min);
    }
}

