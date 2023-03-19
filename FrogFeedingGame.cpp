
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>

#define WINDOW_WIDTH  666
#define WINDOW_HEIGHT 666

#define TIMER_PERIOD  16 // Period for the timer.
#define TIMER_ON         1 // 0:disable timer, 1:enable timer

#define D2R 0.0174532

/* Global Variables for Template File */
bool up = false, down = false, right = false, left = false,hit=true,turningdirection=true;
int  winWidth, winHeight,red=100,green=100,blue=100,coord1=200,coord2=150,x = 50,y=0,dy,dx; // current Window width and height
float angle;
bool move = true;
double count = 60;

//
// to draw circle, center at (x,y)
// radius r
//
void circle(int x, int y, int r)
{
#define PI 3.1415
    float angle;
    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++)
    {
        angle = 2 * PI * i / 100;
        glVertex2f(x + r * cos(angle), y + r * sin(angle));
    }
    glEnd();
}

void circle_wire(int x, int y, int r)
{
#define PI 3.1415
    float angle;

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 100; i++)
    {
        angle = 2 * PI * i / 100;
        glVertex2f(x + r * cos(angle), y + r * sin(angle));
    }
    glEnd();
}

void print(int x, int y, const char* string, void* font)
{
    int len, i;

    glRasterPos2f(x, y);
    len = (int)strlen(string);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(font, string[i]);
    }
}

// display text with variables.
// vprint(-winWidth / 2 + 10, winHeight / 2 - 20, GLUT_BITMAP_8_BY_13, "ERROR: %d", numClicks);
void vprint(int x, int y, void* font, const char* string, ...)
{
    va_list ap;
    va_start(ap, string);
    char str[1024];
    vsprintf_s(str, string, ap);
    va_end(ap);

    int len, i;
    glRasterPos2f(x, y);
    len = (int)strlen(str);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(font, str[i]);
    }
}

// vprint2(-50, 0, 0.35, "00:%02d", timeCounter);
void vprint2(int x, int y, float size, const char* string, ...) {
    va_list ap;
    va_start(ap, string);
    char str[1024];
    vsprintf_s(str, string, ap);
    va_end(ap);
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(size, size, 1);

    int len, i;
    len = (int)strlen(str);
    for (i = 0; i < len; i++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
    }
    glPopMatrix();
}
//displaying complex shapes
float tx = 0, ty = 0;
void tongue()
{
    glColor3f(1, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(0, 0);
    glVertex2f(x*cos(angle)-y*sin(angle) + tx,x*sin(angle)+y*cos(angle) + ty);
    glEnd();
}
void frog()
{
    glColor3f(96 / 255., 198 / 255., 76 / 255.);//eyes green part
    circle(+50, 10, 20);
    circle(-50, 10, 20);
    glColor3f(96 / 255., 198 / 255., 76 / 255.);//feets
    circle(-70, -60, 20);
    circle(70, -60, 20);
    glColor3f(96/ 255., 198/ 255., 76/ 255.);//body
    circle(0,-60,80);
    glColor3f(110 / 255., 236 / 255., 85 / 255.);
    circle(0, -60, 50);
    glColor3f(0, 0, 0);//black dot eyes
    circle(+50, 10, 10);
    circle(-50, 10, 10);
    glLineWidth(3);//mouth
    glBegin(GL_LINES);
    glVertex2d(10, 0);
    glVertex2d(-10, 0);
    glEnd();



}

void ladybug()
{
    glColor3d(red / 255., green / 255., blue / 255.);//body (big circle)
    circle(coord1, coord2, 55);
    glColor3d(0/ 255., 0/ 255., 0/ 255.);
    circle(coord1-15, coord2+27, 6);//little black dots on the lady bug
    circle(coord1 - 27, coord2, 6);
    circle(coord1 -25, coord2 -25, 6);
    circle(coord1 + 15, coord2 + 25, 6);
    circle(coord1 +30, coord2, 6);
    circle(coord1 + 20, coord2 - 25, 6);

    glLineWidth(3);//middle line 
    glBegin(GL_LINES);
    glVertex2d(coord1,coord2+55);
    glVertex2d(coord1, coord2-55);
    glEnd();
    glBegin(GL_TRIANGLES);// black triange
    glVertex2f(coord1, coord2);
    glVertex2f(coord1-20,coord2-55);
    glVertex2f(coord1+20, coord2-55);
    glEnd();
    glLineWidth(3);//antennas
    glBegin(GL_LINES);
    glVertex2d(coord1, coord2 + 55);
    glVertex2d(coord1+20, coord2 +80);
    glEnd();
    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex2d(coord1, coord2 + 55);
    glVertex2d(coord1-20, coord2 +80);
    glEnd();

}


//
// To display onto window using OpenGL commands
//
void display() {
    //
    // clear window to black
    //
    glClearColor(1, 0, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    ladybug();
    frog();
    tongue();
    glColor3f(0, 1, 1);
    vprint(-100, -300, GLUT_BITMAP_8_BY_13, "angle: %.1f", angle / D2R);
    vprint(100, 300, GLUT_BITMAP_8_BY_13, "Didehan Topsakal 22003293");

    if(count > 0)
        vprint(0, -300, GLUT_BITMAP_8_BY_13, "timer: %.1f", count);
    else
        vprint(0, -300, GLUT_BITMAP_8_BY_13, "GAME OVER");
    
    

    glutSwapBuffers();
}

//
// key function for ASCII charachters like ESC, a,b,c..,A,B,..Z
//
void onKeyDown(unsigned char key, int x, int y)
{
    // exit when ESC is pressed.
    if (key == 27)
        exit(0);

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

void onKeyUp(unsigned char key, int x, int y)
{
    // exit when ESC is pressed.
    if (key == 27)
        exit(0);

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyDown(int key, int x, int y)
{
    // Write your codes here.
    switch (key) {
    case GLUT_KEY_UP: up = true; break;
    case GLUT_KEY_DOWN: down = true; break;
    case GLUT_KEY_LEFT: left = true; break;
    case GLUT_KEY_RIGHT: right = true; break;
    }
    

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyUp(int key, int x, int y)
{
    // Write your codes here.
    switch (key) {
    case GLUT_KEY_UP: up = false; break;
    case GLUT_KEY_DOWN: down = false; break;
    case GLUT_KEY_LEFT: left = false; break;
    case GLUT_KEY_RIGHT: right = false; break;
    }

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// When a click occurs in the window,
// It provides which button
// buttons : GLUT_LEFT_BUTTON , GLUT_RIGHT_BUTTON
// states  : GLUT_UP , GLUT_DOWN
// x, y is the coordinate of the point that mouse clicked.
//
void onClick(int button, int stat, int x, int y)
{
    // Write your codes here.
    
    if (hit)
        move = false;
    

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// This function is called when the window size changes.
// w : is the new width of the window in pixels.
// h : is the new height of the window in pixels.
//
void onResize(int w, int h)
{
    winWidth = w;
    winHeight = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    display(); // refresh window.
}

void onMoveDown(int x, int y) {
    // Write your codes here.



    // to refresh the window it calls display() function   
    glutPostRedisplay();
}

// GLUT to OpenGL coordinate conversion:
//   x2 = x1 - winWidth / 2
//   y2 = winHeight / 2 - y1
void onMove(int x, int y) {
    // Write your codes here.



    // to refresh the window it calls display() function
    glutPostRedisplay();
}

#if TIMER_ON == 1
void onTimer(int v) {

    glutTimerFunc(TIMER_PERIOD, onTimer, 0);
    // Write your codes here.
    dy = coord2;
    dx = coord1;
 
    
    if (count > 0)
    {

        if (!move)
        {
            float distance = sqrt((x * cos(angle) - y * sin(angle) + tx - coord1) * (x * cos(angle) - y * sin(angle) + tx - coord1) + (x * sin(angle) + y * cos(angle) + ty - coord2) * (x * sin(angle) + y * cos(angle) + ty - coord2));

            if (distance <= 20)
            {
                red = rand() % 256;
                green = rand() % 256;
                blue = rand() % 256;
                coord1 = rand() % 300 + (-100);
                coord2 = rand() % 300 + (-100);
                move = true;
                tx = 0;
                ty = 0;
                if ((angle / D2R) - (atan2(coord2, coord1) / D2R) > 0)
                    turningdirection = false;
                else if ((angle / D2R) - (atan2(coord2, coord1) / D2R) < 0)
                    turningdirection = true;

            }
        }
        if (move)
        {
            if ((angle / D2R) > 360)
                angle = 0 * D2R;
            if ((angle / D2R) < 0)
                angle = 360 * D2R;
        }



        if (!move)
        {
            tx += (x * cos(angle) - y * sin(angle)) / 10;
            ty += (x * sin(angle) + y * cos(angle)) / 10;
        }

        if (x * cos(angle) - y * sin(angle) + tx > 333 || x * sin(angle) + y * cos(angle) + ty > 333 || x * cos(angle) - y * sin(angle) + tx < -333 || x * sin(angle) + y * cos(angle) + ty < -333)
        {
            move = true;
            tx = 0;
            ty = 0;
        }

        if (move)
        {
            if (turningdirection)
                angle += 0.01;
            else if (!turningdirection)
                angle -= 0.01;
        }
        if (coord2 >= 0 && coord1 >= 0)
            if ((int)(angle / D2R) == (int)(atan2(coord2, coord1) / D2R))
                move = false;
        if (coord2 < 0 && coord1>0)
            if ((int)(angle / D2R) == (int)(atan2(coord2, coord1) / D2R) + 360)
                move = false;
        if (coord2 > 0 && coord1 < 0)
            if ((int)(angle / D2R) == (int)(atan2(coord2, coord1) / D2R))
                move = false;
        if (coord2 < 0 && coord1 < 0)
            if ((int)(angle / D2R) == (int)(atan2(coord2, coord1) / D2R) + 360)
                move = false;

        count -= 0.016;
    }
    // to refresh the window it calls display() function
    glutPostRedisplay(); // display()

}
#endif

void Init() {

    // Smoothing shapes
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    //glutInitWindowPosition(100, 100);
    glutCreateWindow("hungry fat frog");

    glutDisplayFunc(display);
    glutReshapeFunc(onResize);

    //
    // keyboard registration
    //
    glutKeyboardFunc(onKeyDown);
    glutSpecialFunc(onSpecialKeyDown);

    glutKeyboardUpFunc(onKeyUp);
    glutSpecialUpFunc(onSpecialKeyUp);

    //
    // mouse registration
    //
    glutMouseFunc(onClick);
    glutMotionFunc(onMoveDown);
    glutPassiveMotionFunc(onMove);

#if  TIMER_ON == 1
    // timer event
    glutTimerFunc(TIMER_PERIOD, onTimer, 0);
#endif

    Init();

    glutMainLoop();
}