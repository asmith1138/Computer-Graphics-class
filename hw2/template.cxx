/*********************************************************************
 *  CMPSC 457 Section 001                                            *
 *  Homework 1                                                       *
 *                                                                   *
 *  Andrew Smith                                                     *
 *  azs7014                                                          *
 *                                                                   *
 *  9/30/2021                                                        *
 *********************************************************************/  




/*********************************************************************
 *  CMPSC 457                                                        *
 *  Template code for HW 2                                           *
 *                                                                   *
 *  Sukmoon Chang                                                    *
 *  sukmoon@psu.edu                                                  *
 *                                                                   *
 *                                                                   *
 *                                                                   *
 *  Description:                                                     *
 *                                                                   *
 *  This is a template code for homework 2.                          *
 *  It takes two points from users through left button clicks.       *
 *  Then, it draws a line between the two points using               *
 *  Midpoint Algorithm (not implemented in this template).           *
 *                                                                   *
 *                                                                   *
 *  User interface:                                                  *
 *                                                                   *
 *  1. When it starts, its drawing mode is set to NONE.              *
 *     To draw a line, press 'l' to put it in LINE drawing mode.     *
 *     Then, select two points by clicking left mouse button         *
 *     The program draws a line between the two points.              *
 *  2. You can also input the points using keyboard.                 *
 *     To do this, press 'k' and type the coordinates                *
 *     on the terminal (NOTE: This feature is for grading purpose    *
 *     only and has not been tested extensively)                     *
 *  3. To quit the program, press 'q'.                               *
 *  4. Any other keys that are not used to switch drawing modes      *
 *     will put the drawing mode to NONE                             *
 *********************************************************************/  
 

#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>


using std::cin;
using std::cout;
using std::cerr;
using std::endl;


// callbacks for glut (see main() for what they do)
void reshape(int w, int h);
void display();
void mouse(int button, int state, int x, int y);
void keyboard(unsigned char key, int x, int y);


// helpers
void init();
void addPoint(int x, int y);
void keyboard_input();
void midpoint_line();
void midpoint_circle();



// Simple structure for a point
struct Point
{
    int x;
    int y;
    Point() : x(-1), y(-1) {}
    Point(int x, int y) : x(x), y(y) {}
};


// Keeps track of what I am drawing currently.
enum DrawingMode { NONE, LINE, CIRCLE };
DrawingMode drawing_mode = NONE;



// Initial window size
int win_w = 512;
int win_h = 512;


// For lines, 2 points will do.
Point points[2];

// Used to keep track of how many points I have so far
int num_points;



// OpenGL/glut programs typically have the structure shown here,
// although with different args and callbacks.
//
// You should not need to modify main().
// If you want to modify it, do it at your own risk.
//
// For complete description of each glut functions used, see
// glut manual page.
int main(int argc, char* argv[])
{
    // initialize glut
    glutInit(&argc, argv);

    // use double buffering with RGB colors
    // double buffer removes most of the flickering
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    // set window size and position
    glutInitWindowSize(win_w, win_h);
    glutInitWindowPosition(100, 100);

    // now, create window with title "Scan Conversion"
    glutCreateWindow("Scan Conversion");


    // other stuffs like background color, viewing, etc will be
    // set up in this function.
    init();

  
    // register callbacks for glut
    glutDisplayFunc(display);   // for display
    glutReshapeFunc(reshape);   // for window move/resize
    glutMouseFunc(mouse);       // for mouse buttons
    glutKeyboardFunc(keyboard); // for keyboard


    // start event processing, i.e., accept user inputs
    glutMainLoop();

    return 0;
}



void init()
{
    // set background color to black
    glClearColor(0.0, 0.0, 0.0, 0.0);

    // create viewing volume
    // -- will use orthogonal projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, win_w-1, 0.0, win_h-1, -1.0, 1.0);

}



// called when the window is resized/moved (plus some other cases)
void reshape(int w, int h)
{
    win_w = w;
    win_h = h;
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, win_w-1, 0.0, win_h-1, -1.0, 1.0);

    glViewport(0, 0, win_w, win_h);
}


// called when the window needs to be redrawn
void display()
{
    // buffer is a raster array provided by OpenGL
    // recall that we are using 2 buffers (double buffering)
    // they are called front buffer and back buffer
    // what you see on the screen is the content of front buffer
    // what you draw is drawn only on back buffer

    
    // clear back buffer with background color that is set in init()
    glClear(GL_COLOR_BUFFER_BIT);

    // now, draw on back buffer just cleared
    switch (drawing_mode) {
    case LINE:
	midpoint_line();
	break;
    case CIRCLE:
	midpoint_circle();
	break;
    default:
	break;
    }

    // swap the buffers.
    // - all the drawing is done on the back buffer
    // - once drawing is done on the back buffer, 
    //       you need to display the content of the back buffer.
    // - swapping buffers means swapping back buffer with front buffer
    //       so that front buffer becomes back buffer and
    //       back buffer becomes front buffer.
    // - once back buffer becomes front buffer, the content of it will be
    //       displayed on the screen, so you can see it.
    glutSwapBuffers();
}


// called when a mouse event (button pressed/released/moved/dragged) occurs
// in glut, 
//     mouse buttons are represented as
//           GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, and GLUT_RIGHT_BUTTON
//     state of mouse buttons are represented as
//           GLUT_UP and GLUT_DOWN
//     (x, y) is the mouse position when the event occurred
void mouse(int button, int state, int x, int y)
{
    switch (button) {
    case GLUT_LEFT_BUTTON:
	if (state == GLUT_DOWN) 
	    addPoint(x, y);
	break;
    default:
	break;
    }
}


// called when a keyboard event (key typed) occurs
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'q': // quit the program
        exit(0);
    case 'l': // draw a line
        drawing_mode = LINE;
        num_points = 0;
        break;
    case 'c': // draw a circle; not implemented
        drawing_mode = CIRCLE;
        num_points = 0;
        break;
    case 'k': // for grading purpose only--do not modify
        keyboard_input();
        num_points = 0;
        break;
    default:
        drawing_mode = NONE;
        break;
    }
}

// add the point just selected by mouse button
void addPoint(int x, int y)
{
    switch (drawing_mode)
    {
    case CIRCLE:
    case LINE: // save the points until we have 2 points
        points[num_points++] = Point(x, y);
        if (num_points == 2)
        {
            // we have 2 points now, so we can draw a line

            // reset the num_points to 0 for next line
            num_points = 0;

            // tell glut that the current window needs to be redisplayed.
            // glut will then redisplay the current window.
            // this means display() callback will be called.
            // display() in turn will draw a midpoint line on back buffer
            //   and swap the back buffer with the front buffer
            // by swapping the buffers, the back buffer becomes visible,
            //   ie, displayed on the window
            glutPostRedisplay();
        }
        break;
    default:
        break;
    }
}

// for grading purpose only
// do not modify this function
// do not use this function
//   -- it's not tested fully and does not work correctly
void keyboard_input()
{
    if (drawing_mode == NONE) {
	cerr << "Select drawing mode first...\n";
	return;
    }

    int x, y;
    num_points = 0;
    for (int i=0; i<2; i++) {
	cerr << "Enter point " << i << " => ";
	cin >> x >> y;
	cerr << endl;
	addPoint(x, y);
    }
}
  
  //Enum for slope
enum SLOPE { ZERO, ONE, ZEROTOONE, OVERONE, UNDERNEGONE, NEGONETOZERO, NEGONE, INF };

// a helper function to draw a line
// you need to modify this function for midpoint algorithm
// anything you draw here goes to back buffer
void midpoint_line()
{
    // select a line color of your choice
    glColor3f(1.0, 0.0, 0.0);

    // now, draw a line between 2 end points
    // you need to draw a line using incremental midpoint algorithm
    //     without any floating point calculations, so remove
    //     next 4 lines and implement incremental midpoint algorithm here.
    //
    // you cannot use GL_LINES for this assignment.
    // you must use GL_POINTS instead.
    //
    // To draw a pixel (x,y) with the color you set above, use
    //         glBegin(GL_POINTS);
    //            glVertex2d(x, y);
    //         glEnd();
    // Any number of glVertex2d() may appear between glBegin() and glEnd()
    // Or, even glColor3f() may appear there, if you want to change the color
    //      of each point.
    // Also, any c++ code can appear between glBegin() and glEnd()
    //
    // Note: GL provides commands for drawing.
    //       glut provides gui, including window on which you are drawing.
    //       The origin (0,0) of the coordinate system is
    //          at bottom left in GL and
    //          at top left in glut.
    //       You must compensate the difference between the coordinate
    //       systems used by GL and glut, when drawing.
    SLOPE slopeOfLine;
    //set points and swap if needed
    int y0 = win_h - points[0].y;
    int y1 = win_h - points[1].y;
    int x0 = points[0].x;
    int x1 = points[1].x;
    if (x0 > x1)
    {
        int swap = x0;
        x0 = x1;
        x1 = swap;
        swap = y0;
        y0 = y1;
        y1 = swap;
    }

    //slope stuff
    int ydiff = y1 - y0;
    int xdiff = x1 - x0;
    if (ydiff < xdiff && y1 > y0)
    {
        //0<m<1
        slopeOfLine = ZEROTOONE;
    }
    else if (ydiff > xdiff && y1 > y0)
    {
        //m>1
        slopeOfLine = OVERONE;
        int swap = x0;
        x0 = y0;
        y0 = swap;
        swap = x1;
        x1 = y1;
        y1 = swap;
        if (x0 > x1)
        {
            swap = x0;
            x0 = x1;
            x1 = swap;
            swap = y0;
            y0 = y1;
            y1 = swap;
        }
    }
    else if (ydiff > xdiff && y1 < y0)
    {
        //m<-1
        slopeOfLine = UNDERNEGONE;
        x0 = (-1 * x0);
        x1 = (-1 * x1);
        int swap = x0;
        x0 = y0;
        y0 = swap;
        swap = x1;
        x1 = y1;
        y1 = swap;
        if (x0 > x1)
        {
            swap = x0;
            x0 = x1;
            x1 = swap;
            swap = y0;
            y0 = y1;
            y1 = swap;
        }
    }
    else if (ydiff < xdiff && y1 < y0)
    {
        //-1<m<0
        slopeOfLine = NEGONETOZERO;
        y0 = (-1 * y0);
        y1 = (-1 * y1);
    }
    else if (y1 == y0)
    {
        //m=0
        slopeOfLine = ZERO;
    }
    else if (ydiff == xdiff)
    {
        //m=1
        slopeOfLine = ONE;
    }
    else if (x1 == x0)
    {
        //m=infinity striaght up
        slopeOfLine = INF;
    }
    else if (ydiff == (-1 * xdiff))
    {
        //m= -1
        slopeOfLine = NEGONE;
    }

    //setup line vars
    int dy = 2 * (y0 - y1);
    int dx = 2 * (x1 - x0);
    cout << "DX: " << dx << endl;
    cout << "DY: " << dy << endl;
    int d = ((2 * (y0 - y1) * (x0 + 1)) + ((x1 - x0) * ((2 * y0) + 1)) + (2 * x0 * y1) - (2 * x1 * y0));
    cout << "D: " << d << endl;
    int y = y0;

    glBegin(GL_POINTS);
    for (int x = x0; x <= x1; x++)
    {
        if (slopeOfLine == ZERO)
        {
            glVertex2d(x, y);
            continue;
        }
        else if (slopeOfLine == ONE)
        {
            glVertex2d(x, y);
            y++;
            continue;
        }
        else if (slopeOfLine == ZEROTOONE)
        {
            glVertex2d(x, y);
        }
        else if (slopeOfLine == OVERONE)
        {
            glVertex2d(y, x);
        }
        else if (slopeOfLine == UNDERNEGONE)
        {
            glVertex2d((-1 * y), x);
        }
        else if (slopeOfLine == NEGONETOZERO)
        {
            glVertex2d(x, (-1 * y));
        }
        else if (slopeOfLine == NEGONE)
        {
            glVertex2d((-1 * x), y);
            y++;
            continue;
        }
        else if (slopeOfLine == INF)
        {
            for (int yprime = y0; yprime <= y1; y++)
            {
                glVertex2d(x, yprime);
            }
        }

        if (d < 0)
        {
            d += dy + dx;
            y++;
        }
        else
        {
            d += dy;
        }
        cout << "D: " << d << endl;
    }
    //glVertex2d(x, y);
    glEnd();
    //glBegin(GL_LINES);
    //glVertex2d(points[0].x, win_h - points[0].y);
    //glVertex2d(points[1].x, win_h - points[1].y);
    //glEnd();
}
      
// a helper function to draw a circle
// anything you draw here goes to back buffer
void midpoint_circle()
{
    // select a line color of your choice
    glColor3f(1.0, 0.0, 0.0);

    SLOPE slopeOfLine;
    //set points and swap if needed
    int yc = win_h - points[0].y;
    int y1 = win_h - points[1].y;
    int xc = points[0].x;
    int x1 = points[1].x;

    //slope stuff
    int ydiff = y1 - yc;
    int xdiff = x1 - xc;

    //setup line vars
    

    
    double R = sqrt(((x1 - xc) ^ 2) + ((y1 - yc) ^ 2)); //???
    int R2 = ((x1 - xc) ^ 2) + ((y1 - yc) ^ 2);
    int y = yc+R;
    //WHAT IS D Initial???
    int d = (16) + (16 * y * y) + (16 * yc * yc) - (32 * y * yc) - (16 * y) + (16 * yc) + 4 + (16 * R2);
    //WHAT ARE DY AND DX???
    int dy = (32 * yc) - (32 * y) + 53;
    int dx = 48;
    cout << "DX: " << dx << endl;
    cout << "DY: " << dy << endl;
    //((2 * (yc - y1) * (xc + 1)) + ((x1 - xc) * ((2 * yc) + 1)) + (2 * xc * y1) - (2 * x1 * yc));
    cout << "D: " << d << endl;
    

    glBegin(GL_POINTS);//start at x0 WHERE TO END???
    for (int x = xc; x <= R/2; x++)
    {
        glVertex2d(x, y);
        glVertex2d(x, (-1 * y));
        glVertex2d((-1 * x), y);
        glVertex2d((-1 * x), (-1 * y));
        glVertex2d(y, x);
        glVertex2d((-1 * y), x);
        glVertex2d(y, (-1 * x));
        glVertex2d((-1 * y), (-1 * x));

        if (d < 0)
        {
            d += dy + dx;
            y++;
        }
        else
        {
            d += dy;
        }
        cout << "D: " << d << endl;
    }
    //glVertex2d(x, y);
    glEnd();
    //glBegin(GL_LINES);
    //glVertex2d(points[0].x, win_h - points[0].y);
    //glVertex2d(points[1].x, win_h - points[1].y);
    //glEnd();
}
