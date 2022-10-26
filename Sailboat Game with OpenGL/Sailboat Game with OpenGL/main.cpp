/***
   CTIS164 - Template Source Program
----------
STUDENT : Bilgehan Demirkaya
SECTION :164-2
HOMEWORK:HW-1
----------
PROBLEMS:
----------
ADDITIONAL FEATURES:
***/
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#define WINDOW_WIDTH  1200
#define WINDOW_HEIGHT 800

#define  TIMER_PERIOD  16// Period for the timer.
#define  TIMER_ON     1     // 0:disable timer, 1:enable timer

#define D2R 0.0174532

/* Global Variables for Template File */
bool up = false, down = false, right = false, left = false;
int  winWidth, winHeight; // current Window width and height

int minimumFar = 0, movement = 0;
bool inStartButton = false;
int countShape = 0;
double cloudanimationR = 0, cloudanimationL = 0;

bool mode = false;
bool isCompleted = false;


/* Programmer variables and definitions */
typedef struct {
    float x, y;
} point_t;

// mouse position
point_t mouse;

// Object place
typedef struct {
    int x1;
    int y1;
}coordinate;


coordinate charArr[10];

// this is function signature (prototype)
// this is called "function declaration"
void onTimer(int v);

//
// to draw circle, center at (x,y)
//  radius r
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

void display_background() {



    // backgound

    glColor3ub(81, 134, 252);
    glRectf(-600, 330, 600, -400);
    glColor3ub(135, 206, 235);
    glRectf(-600, 330, 600, 400);
    glColor3ub(135, 206, 235);
    glRectf(600, 330, 60, 400);

    //frame for label
    glLineWidth(3);
    glColor3ub(1, 1, 0);
    glBegin(GL_LINES);
    glVertex2f(-60, 330);
    glVertex2f(-60, 400);
    glEnd();

    glLineWidth(3);
    glColor3ub(1, 1, 0);
    glBegin(GL_LINES);
    glVertex2f(60, 330);
    glVertex2f(60, 400);
    glEnd();

    glLineWidth(3);
    glColor3ub(1, 1, 0);
    glBegin(GL_LINES);
    glVertex2f(60, 398);
    glVertex2f(-60, 398);
    glEnd();

    glLineWidth(3);
    glColor3ub(1, 1, 0);
    glBegin(GL_LINES);
    glVertex2f(60, 331);
    glVertex2f(-60, 331);
    glEnd();

    //Sand
    glColor3ub(194, 178, 128);
    glRectf(-600, -300, 600, -400);

    //life buoy left side
    glColor3ub(255, 0, 0);
    circle(-560, -365, 25);

    glLineWidth(4);
    glColor3ub(1, 1, 1);
    glBegin(GL_LINES);
    glVertex2f(-560, -370);
    glVertex2f(-585, -365);
    glEnd();

    glLineWidth(4);
    glColor3ub(1, 1, 1);
    glBegin(GL_LINES);
    glVertex2f(-560, -370);
    glVertex2f(-535, -365);
    glEnd();

    glLineWidth(4);
    glColor3ub(255, 255, 255);
    glBegin(GL_LINES);
    glVertex2f(-560, -375);
    glVertex2f(-535, -370);
    glEnd();

    glLineWidth(4);
    glColor3ub(255, 255, 255);
    glBegin(GL_LINES);
    glVertex2f(-560, -375);
    glVertex2f(-585, -370);
    glEnd();

    glColor3ub(194, 178, 128);
    circle(-560, -365, 15);

    //left side umbrella
    glLineWidth(4);
    glColor3ub(1, 1, 1);
    glBegin(GL_LINES);
    glVertex2f(-400, -340);
    glVertex2f(-400, -390);
    glEnd();

    glColor3ub(142, 98, 140);
    glBegin(GL_TRIANGLES);
    glVertex3f(-350, -340, 0);
    glVertex3f(-450, -340, 0);
    glVertex3f(-400, -300, 0);
    glEnd();

    //life buoy right side
    glColor3ub(255, 0, 0);
    circle(560, -365, 25);

    glLineWidth(4);
    glColor3ub(1, 1, 1);
    glBegin(GL_LINES);
    glVertex2f(560, -370);
    glVertex2f(585, -365);
    glEnd();

    glLineWidth(4);
    glColor3ub(1, 1, 1);
    glBegin(GL_LINES);
    glVertex2f(560, -370);
    glVertex2f(535, -365);
    glEnd();

    glLineWidth(4);
    glColor3ub(255, 255, 255);
    glBegin(GL_LINES);
    glVertex2f(560, -375);
    glVertex2f(535, -370);
    glEnd();

    glLineWidth(4);
    glColor3ub(255, 255, 255);
    glBegin(GL_LINES);
    glVertex2f(560, -375);
    glVertex2f(585, -370);
    glEnd();

    glColor3ub(194, 178, 128);
    circle(560, -365, 15);

    //right side umbrella
    glLineWidth(4);
    glColor3ub(1, 1, 1);
    glBegin(GL_LINES);
    glVertex2f(400, -340);
    glVertex2f(400, -390);
    glEnd();

    glColor3ub(142, 98, 140);
    glBegin(GL_TRIANGLES);
    glVertex2f(350, -340);
    glVertex2f(450, -340);
    glVertex2f(400, -300);
    glEnd();



    // label(name,surname,id)
    glColor3ub(0, 0, 255);
    vprint(-35, 380, GLUT_BITMAP_8_BY_13, "Bilgehan");
    vprint(-35, 360, GLUT_BITMAP_8_BY_13, "Demirkaya");
    vprint(-60, 340, GLUT_BITMAP_9_BY_15, " - 22002357 -");

    if (isCompleted)
    {
        glColor3ub(0, 0, 255);
        vprint(-130, -350, GLUT_BITMAP_8_BY_13, "Press Enter F1 to move sailboats");
    }
    else
    {
        glColor3ub(0, 0, 255);
        vprint(-250, -350, GLUT_BITMAP_8_BY_13, "For putting the sailboats, you need to left mouse click to the sea.");
    }




}


void display_Draw() {


    if (inStartButton) {

        for (int i = 0; i < countShape; i++)
        {
            if (charArr[i].y1 > -300 && charArr[i].y1 < -250)
            {
                //Draw the sailboats
                charArr[i].y1 += 5;
                glColor3ub(145, 114, 110);
                glBegin(GL_QUADS);
                glVertex2f(charArr[i].x1 + 25 + movement, charArr[i].y1 - 30);// vertex 1
                glVertex2f(charArr[i].x1 - 25 + movement, charArr[i].y1 - 30);// vertex 2
                glVertex2f(charArr[i].x1 - 70 + movement, charArr[i].y1 + 30); // vertex 3
                glVertex2f(charArr[i].x1 + 70 + movement, charArr[i].y1 + 30);  // vertex 4
                glEnd();

                glLineWidth(3);
                glColor3ub(145, 114, 110);
                glBegin(GL_LINES);
                glVertex2f(charArr[i].x1 + 70 + movement, charArr[i].y1 + 30);
                glVertex2f(charArr[i].x1 + 90 + movement, charArr[i].y1 + 35);
                glEnd();


                glLineWidth(4);
                glColor3ub(255, 255, 255);
                glBegin(GL_LINES);
                glVertex2f(charArr[i].x1 - 10 + movement, charArr[i].y1 + 30);
                glVertex2f(charArr[i].x1 - 10 + movement, charArr[i].y1 + 130);
                glEnd();

                glColor3ub(142, 98, 140);
                glBegin(GL_TRIANGLES);
                glVertex2f(charArr[i].x1 - 10 + movement, charArr[i].y1 + 40);
                glVertex2f(charArr[i].x1 - 10 + movement, charArr[i].y1 + 120);
                glVertex2f(charArr[i].x1 + 45 + movement, charArr[i].y1 + 80);
                glEnd();

                glColor3ub(142, 98, 140);
                glBegin(GL_TRIANGLES);
                glVertex2f(charArr[i].x1 - 12 + movement, charArr[i].y1 + 60);
                glVertex2f(charArr[i].x1 - 12 + movement, charArr[i].y1 + 100);
                glVertex2f(charArr[i].x1 - 45 + movement, charArr[i].y1 + 80);
                glEnd();

                glColor3ub(255, 253, 208);
                circle(charArr[i].x1 + movement, charArr[i].y1 + 10, 10);

                glLineWidth(2);
                glColor3ub(145, 114, 110);
                glBegin(GL_LINES);
                glVertex2f(charArr[i].x1 - 10 + movement, charArr[i].y1);
                glVertex2f(charArr[i].x1 + 10 + movement, charArr[i].y1 + 20);
                glEnd();

                glLineWidth(2);
                glColor3ub(145, 114, 110);
                glBegin(GL_LINES);
                glVertex2f(charArr[i].x1 - 10 + movement, charArr[i].y1 + 20);
                glVertex2f(charArr[i].x1 + 10 + movement, charArr[i].y1);
                glEnd();
            }
            else
            {
                glColor3ub(145, 114, 110);
                glBegin(GL_QUADS);
                glVertex2f(charArr[i].x1 + 25 + movement, charArr[i].y1 - 30);// vertex 1
                glVertex2f(charArr[i].x1 - 25 + movement, charArr[i].y1 - 30);// vertex 2
                glVertex2f(charArr[i].x1 - 70 + movement, charArr[i].y1 + 30); // vertex 3
                glVertex2f(charArr[i].x1 + 70 + movement, charArr[i].y1 + 30);  // vertex 4
                glEnd();

                glLineWidth(3);
                glColor3ub(145, 114, 110);
                glBegin(GL_LINES);
                glVertex2f(charArr[i].x1 + 70 + movement, charArr[i].y1 + 30);
                glVertex2f(charArr[i].x1 + 90 + movement, charArr[i].y1 + 35);
                glEnd();

                glLineWidth(4);
                glColor3ub(255, 255, 255);
                glBegin(GL_LINES);
                glVertex2f(charArr[i].x1 - 10 + movement, charArr[i].y1 + 30);
                glVertex2f(charArr[i].x1 - 10 + movement, charArr[i].y1 + 130);
                glEnd();

                glColor3ub(142, 98, 140);
                glBegin(GL_TRIANGLES);
                glVertex2f(charArr[i].x1 - 10 + movement, charArr[i].y1 + 40);
                glVertex2f(charArr[i].x1 - 10 + movement, charArr[i].y1 + 120);
                glVertex2f(charArr[i].x1 + 45 + movement, charArr[i].y1 + 80);
                glEnd();

                glColor3ub(142, 98, 140);
                glBegin(GL_TRIANGLES);
                glVertex2f(charArr[i].x1 - 12 + movement, charArr[i].y1 + 60);
                glVertex2f(charArr[i].x1 - 12 + movement, charArr[i].y1 + 100);
                glVertex2f(charArr[i].x1 - 45 + movement, charArr[i].y1 + 80);
                glEnd();

                glColor3ub(255, 253, 208);
                circle(charArr[i].x1 + movement, charArr[i].y1 + 10, 10);

                glLineWidth(2);
                glColor3ub(145, 114, 110);
                glBegin(GL_LINES);
                glVertex2f(charArr[i].x1 - 10 + movement, charArr[i].y1);
                glVertex2f(charArr[i].x1 + 10 + movement, charArr[i].y1 + 20);
                glEnd();

                glLineWidth(2);
                glColor3ub(145, 114, 110);
                glBegin(GL_LINES);
                glVertex2f(charArr[i].x1 - 10 + movement, charArr[i].y1 + 20);
                glVertex2f(charArr[i].x1 + 10 + movement, charArr[i].y1);
                glEnd();
            }

            //Wave animation for sailboats
            if (mode == true) {
                if (movement % 45 > 22) {
                    glPointSize(4);
                    glColor3ub(255, 255, 255);
                    glBegin(GL_POINTS);
                    //backside side
                    glVertex2f(charArr[i].x1 - 28 + movement, charArr[i].y1 - 28);
                    glVertex2f(charArr[i].x1 - 30 + movement, charArr[i].y1 - 26);
                    glVertex2f(charArr[i].x1 - 31 + movement, charArr[i].y1 - 25);
                    glVertex2f(charArr[i].x1 - 32 + movement, charArr[i].y1 - 24);
                    glVertex2f(charArr[i].x1 - 34 + movement, charArr[i].y1 - 22);
                    glEnd();
                }
            }

        }

    }


}

void clouds() {

    //sun 
    glColor3ub(253, 184, 19);
    circle(600, 380, 40);

    //cloud 1
    glColor3f(1, 1, 1);
    circle(420 + cloudanimationR, 375, 15);
    circle(410 + cloudanimationR, 360, 14);
    circle(425 + cloudanimationR, 367, 15);
    circle(440 + cloudanimationR, 365, 12);

    //cloud 2
    glColor3f(1, 1, 1);
    circle(220 + cloudanimationR, 375, 15);
    circle(210 + cloudanimationR, 360, 14);
    circle(225 + cloudanimationR, 367, 15);
    circle(240 + cloudanimationR, 365, 12);


    //cloud 3
    glColor3f(1, 1, 1);
    circle(-420 + cloudanimationL, 375, 15);
    circle(-410 + cloudanimationL, 360, 14);
    circle(-425 + cloudanimationL, 367, 15);
    circle(-440 + cloudanimationL, 365, 12);

    //cloud 4
    glColor3f(1, 1, 1);
    circle(-220 + cloudanimationL, 375, 15);
    circle(-210 + cloudanimationL, 360, 14);
    circle(-225 + cloudanimationL, 367, 15);
    circle(-240 + cloudanimationL, 365, 12);


}

//
// To display onto window using OpenGL commands
//
void display()
{
    glClearColor(1, 1, 1, 0);

    // common background graphics for all states.
    display_background();
    clouds();


    display_Draw();

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

    if (key == GLUT_KEY_F1)
        mode = true;

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
    if (button == GLUT_LEFT_BUTTON && stat == GLUT_DOWN) {

        inStartButton = true;
        if (countShape < 10 && y < 700 && y >70)
        {
            //take clikc coordination and put struct array
            charArr[countShape].x1 = mouse.x;
            charArr[countShape].y1 = mouse.y;
            countShape++;

            isCompleted = true; //Show screen what need o to move objects

            //Find far obejct
            if (mode == false && charArr[countShape].x1 < charArr[minimumFar].x1)
                minimumFar = countShape;
        }


    }

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




// When you move mouse pointer, this event handler is called automatically
void onMove(int x, int y) {
    // Write your codes here.

    // Convert coordinate (x,y) from GLUT to OpenGL
    mouse.x = x - winWidth / 2;
    mouse.y = winHeight / 2 - y;



    // to refresh the window it calls display() function
    glutPostRedisplay();
}

#if TIMER_ON == 1
void onTimer(int v) {
    // Write your codes here.
    glutTimerFunc(TIMER_PERIOD, onTimer, 1);

    //Cloud animation
    cloudanimationL -= 0.05;
    cloudanimationR += 0.05;

    //Move the sailboat
    if (mode == true) {
        movement += 3;
    }

    //After moving out of the screen and reset
    if (charArr[minimumFar].x1 + movement - 250 > winWidth / 2) {
        mode = false;
        countShape = -1;
        movement = 0;
        isCompleted = false;
    }


    // to refresh the window it calls display() function
    glutPostRedisplay(); // display()

}
#endif

void Init() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


void main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("CTIS 164 HW1-Sailing Boats Competition");

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