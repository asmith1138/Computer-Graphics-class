/*********************************************************************
 *  CMPSC 457 Section 001                                            *
 *  Homework 3                                                       *
 *                                                                   *
 *  Andrew Smith                                                     *
 *  azs7014                                                          *
 *                                                                   *
 *  10/13/2021                                                       *
 *********************************************************************/  




/*********************************************************************
 *  CMPSC 457                                                        *
 *  Template code for HW 3                                           *
 *                                                                   *
 *  Sukmoon Chang                                                    *
 *  sukmoon@psu.edu                                                  *
 *                                                                   *
 *                                                                   *
 *                                                                   *
 *  Description:                                                     *
 *                                                                   *
 *  This is a template code for homework 3.                          *
 *  It takes three points from users through left button click.      *
 *  Then, it draws a triangle with the three points as its vertices. *
 *                                                                   *
 *                                                                   *
 *  User interface:                                                  *
 *                                                                   *
 *  1. When it starts, its shading mode is set to WIREFRAME.         *
 *     WIREFRAME mode is already implemented for your reference.     *        
 *  2. For flat shading, press 'f' to put it in FLAT shading mode.   *
 *     Then, select 3 points by clicking left mouse button.          *
 *     The program draws a triangle with the selected points         *
 *     as its vertices using the color of your choice.               *
 *  3. For Gouraud shading, press 'g' to put it in Gouraud           *
 *     shading mode. Then, select 3 points by clicking left mouse    *
 *     button. The program draws a triangle with the selected points *
 *     as its vertices, interpolating the vertex colors (red, green, *
 *     blue for the first, second, third points in that order)       *
 *  4. Press 'w' to go back to WIREFRAME mode.                       *
 *  5. To quit the program, press 'q'.                               *
 *  6. Any other keys that are not used to switch shading modes      *
 *     will put the shading mode to WIREFRAME.                       *
 *********************************************************************/  
 

#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#define PI 3.14159265

using std::cin;
using std::cerr;
using std::endl;


// callbacks for glut (see main() for what they do)
void reshape(int w, int h);
void display();
void mouse(int button, int state, int x, int y);
void keyboard(unsigned char key, int x, int y);




// Simple structure for a point
struct Point
{
    int x;
    int y;
    Point() : x(-1), y(-1) {}
    Point(int x, int y) : x(x), y(y) {}
};

struct Color
{
    float r;
    float g;
    float b;

    Color() : r(0), g(0), b(0) {}
    Color(float r, float g, float b) : r(r), g(g), b(b) {}
};


// helpers
void init();
void addPoint(int x, int y);
void keyboard_input();
void draw_point(int x, int y, Color c);
void draw_line(int x0, int y0, int x1, int y1, Color c);


void draw_triangle();
void triangle_wireframe(Color color);
void triangle_flat(Color color);
void triangle_gourand(Color c0, Color c1, Color c2);


// Keeps track of current shading mode.
enum ShadingMode { WIREFRAME, FLAT, GOURAUD };
ShadingMode shading_mode = WIREFRAME;



// Initial window size
int win_w = 512;
int win_h = 512;


// For triangles, 3 points will do.
Point points[3];

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




/*****************
 *   callbacks   *
 *****************/


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
    draw_triangle();

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
//     status of mouse buttons are represented as
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
    switch (key) {
    case 'q':  // quit the program
	exit(0);
    case 'f':  // flat shading
	shading_mode = FLAT;
	break;
    case 'g':  // gouraud shading
	shading_mode = GOURAUD;
	break;
    case 'k':  // for grading purpose only--do not modify
	keyboard_input();
	num_points = 0;
	break;
    default:
	shading_mode = WIREFRAME;
	break;
    }
}




/**************
 *   helpers  *
 **************/


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



// add the point just selected by mouse button
void addPoint(int x, int y)
{
    points[num_points++] = Point(x, y);
    if (num_points == 3) {
	// we have 3 points now, so we can draw a triangle
	    
	// reset the num_points to 0 for next line
	num_points = 0;

	// tell glut that the current window needs to be redisplayed.
	// glut will then redisplay the current window.
	// this means display() callback will be called.
	// display() in turn will draw a triangle on back buffer
	//   and swap the back buffer with the front buffer
	// by swapping the buffers, the back buffer becomes visible,
	//   ie, displayed on the window
	glutPostRedisplay();
    }
}



// for grading purpose only
// do not modify this function
// do not use this function
//   -- it's not tested fully and does not work correctly
void keyboard_input()
{
    int x, y;
    num_points = 0;
    for (int i=0; i<3; i++) {
	cerr << "Enter point " << i << " => ";
	cin >> x >> y;
	cerr << endl;
	addPoint(x, y);
    }
}
 

void draw_point(int x, int y, Color c)
{
    glBegin(GL_POINTS);
    {
	glColor3f(c.r, c.g, c.b);
	glVertex2d(x, win_h-y);
    }
    glEnd();
}


void draw_line(int x0, int y0, int x1, int y1, Color c)
{
    glBegin(GL_LINES);
    glColor3f(c.r, c.g, c.b);
    glVertex2d(x0, win_h - y0);
    glVertex2d(x1, win_h - y1);
    glEnd();
}
 


// a helper function to draw a triangle
// WIREFRAME mode is implemented for your reference
// you need to modify this function for other drawing modes
// anything you draw here goes to back buffer
void draw_triangle()
{
    switch (shading_mode) {
    case WIREFRAME:
    {
	// choose the color for wireframe
	Color color(1.0, 0.0, 0.0);
	// draw a triangle as wireframe
	// using draw_line()
	triangle_wireframe(color);
	break;
    }
    case FLAT:
    {
	// choose the color for flat shading
	Color color(1.0, 1.0, 1.0);
	// HERE, draw a triangle with flat shading
	//       using draw_point()
    triangle_flat(color);
	break;
    }
    case GOURAUD:
    {
	// choose the vertex colors for gouraud shading
	Color c0(1.0, 0.0, 0.0);
	Color c1(0.0, 1.0, 0.0);
	Color c2(0.0, 0.0, 1.0);
	// HERE, draw a triangle with gouraud shading
	//       using draw_point()
    triangle_gourand(c0,c1,c2);
	break;
    }
    }
}


void triangle_wireframe(Color color)
{
    // not much to do.
    // just draw 3 lines using the 3 points
    for (int i=0; i<3; i++) {
	int x0 = points[i].x, y0 = points[i].y;
	int x1 = points[(i+1)%3].x, y1 = points[(i+1)%3].y;
	draw_line(x0, y0, x1, y1, color);
    }
}

void triangle_flat(Color color)
{
    int maxY = std::max(std::max(points[0].y,points[1].y),points[2].y);
    int maxX = std::max(std::max(points[0].x,points[1].x),points[2].x);
    int minY = std::min(std::min(points[0].y,points[1].y),points[2].y);
    int minX = std::min(std::min(points[0].x,points[1].x),points[2].x);
    
    int x01 = points[1].x-points[0].x;
    int x02 = points[2].x-points[0].x;
    int y01 = points[1].y-points[0].y;
    int y02 = points[2].y-points[0].y;
    std::cout<<"x01: "<<x01<<std::endl;
    std::cout<<"x02: "<<x02<<std::endl;
    std::cout<<"y01: "<<y01<<std::endl;
    std::cout<<"y02: "<<y02<<std::endl;
    
    Point p0p1(x01,y01);
    Point p0p2(x02,y02);

    double magnitudes = sqrt((p0p1.x*p0p1.x)+(p0p1.y*p0p1.y))*sqrt((p0p2.x*p0p2.x)+(p0p2.y*p0p2.y));
    double costhetaA = ((p0p1.x*p0p2.x)+(p0p1.y*p0p2.y))/magnitudes;
    double A = (magnitudes*sin(acos(costhetaA)))/2;
    double altA = ((p0p1.x*p0p2.y)-(p0p2.x*p0p1.y))/2;
    //std::cout<<"magnitudes: "<<magnitudes<<std::endl;
    //std::cout<<"costhetaA: "<<costhetaA<<std::endl;
    //std::cout<<"A: "<<A<<std::endl;
    //std::cout<<"Alt-A: "<<altA<<std::endl;
    
    for(int r=minY;r<=maxY;r++){
        for(int c=minX;c<=maxX;c++){
            Point p(c,r);
            int xp1 = points[1].x-p.x;
            int xp2 = points[2].x-p.x;
            int xp0 = points[0].x-p.x;
            int yp1 = points[1].y-p.y;
            int yp2 = points[2].y-p.y;
            int yp0 = points[0].y-p.y;
            //std::cout<<"xp1: "<<xp1<<std::endl;
            //std::cout<<"xp2: "<<xp2<<std::endl;
            //std::cout<<"xp0: "<<xp0<<std::endl;
            //std::cout<<"yp1: "<<yp1<<std::endl;
            //std::cout<<"yp2: "<<yp2<<std::endl;
            //std::cout<<"yp0: "<<yp0<<std::endl;
            Point pp1(xp1,yp1);
            Point pp2(xp2,yp2);
            Point pp0(xp0,yp0);
            // double magnitudesA0 = sqrt((pp1.x*pp1.x)+(pp1.y*pp1.y))*sqrt((pp2.x*pp2.x)+(pp2.y*pp2.y));
            // double magnitudesA1 = sqrt((pp0.x*pp0.x)+(pp0.y*pp0.y))*sqrt((pp2.x*pp2.x)+(pp2.y*pp2.y));
            // double magnitudesA2 = sqrt((pp0.x*pp0.x)+(pp0.y*pp0.y))*sqrt((pp1.x*pp1.x)+(pp1.y*pp1.y));
            // std::cout<<"magnitudesA0: "<<magnitudesA0<<std::endl;
            // std::cout<<"magnitudesA1: "<<magnitudesA1<<std::endl;
            // std::cout<<"magnitudesA2: "<<magnitudesA2<<std::endl;
            // double costhetaA0 = ((pp1.x*pp2.x)+(pp1.y*pp2.y))/magnitudesA0;
            // double costhetaA1 = ((pp0.x*pp2.x)+(pp0.y*pp2.y))/magnitudesA1;
            // double costhetaA2 = ((pp0.x*pp1.x)+(pp0.y*pp1.y))/magnitudesA2;
            // double thetaA0 = acos(costhetaA0);
            // double thetaA1 = acos(costhetaA1);
            // double thetaA2 = acos(costhetaA2);
            // std::cout<<"costhetaA0: "<<costhetaA0<<std::endl;
            // std::cout<<"costhetaA1: "<<costhetaA1<<std::endl;
            // std::cout<<"costhetaA2: "<<costhetaA2<<std::endl;
            // std::cout<<"thetaA0: "<<thetaA0<<std::endl;
            // std::cout<<"thetaA1: "<<thetaA1<<std::endl;
            // std::cout<<"thetaA2: "<<thetaA2<<std::endl;
            // double A0 = (magnitudesA0*sin(thetaA0))/2;
            // double A1 = (magnitudesA1*sin(thetaA1))/2;
            // double A2 = (magnitudesA2*sin(thetaA2))/2;
            double altA0 = ((pp1.x*pp2.y)-(pp2.x*pp1.y))/2;
            double altA1 = ((pp0.x*pp2.y)-(pp2.x*pp0.y))/2;
            double altA2 = ((pp0.x*pp1.y)-(pp1.x*pp0.y))/2;
            // std::cout<<"A0: "<<A0<<std::endl;
            // std::cout<<"A1: "<<A1<<std::endl;
            // std::cout<<"A2: "<<A2<<std::endl;
            //std::cout<<"altA0: "<<altA0<<std::endl;
            //std::cout<<"altA1: "<<altA1<<std::endl;
            //std::cout<<"altA2: "<<altA2<<std::endl;
            double alpha = altA0/altA;
            double beta = altA1/altA;
            double gamma = altA2/altA;
            //std::cout<<"alpha: "<<alpha<<std::endl;
            //std::cout<<"beta: "<<beta<<std::endl;
            //std::cout<<"gamma: "<<gamma<<std::endl;
            if(alpha>=0 && beta<=0 && gamma>=0){
                if(/*alpha<1 && beta<1 && gamma<1*/(gamma+beta<1)){
                    draw_point(p.x, p.y, color);
                }
            }
        }
    }
    std::cout<<"x01: "<<x01<<std::endl;
    std::cout<<"x02: "<<x02<<std::endl;
    std::cout<<"y01: "<<y01<<std::endl;
    std::cout<<"y02: "<<y02<<std::endl;
    std::cout<<"magnitudes: "<<magnitudes<<std::endl;
    std::cout<<"costhetaA: "<<costhetaA<<std::endl;
    std::cout<<"A: "<<A<<std::endl;
    std::cout<<"Alt-A: "<<altA<<std::endl;
    // draw_point(int x, int y, Color c)
    // for (int i=0; i<3; i++) {
	// int x0 = points[i].x, y0 = points[i].y;
	// int x1 = points[(i+1)%3].x, y1 = points[(i+1)%3].y;
	// draw_line(x0, y0, x1, y1, color);
    //}
}

void triangle_gourand(Color c0,Color c1,Color c2)
{
    int maxY = std::max(std::max(points[0].y,points[1].y),points[2].y);
    int maxX = std::max(std::max(points[0].x,points[1].x),points[2].x);
    int minY = std::min(std::min(points[0].y,points[1].y),points[2].y);
    int minX = std::min(std::min(points[0].x,points[1].x),points[2].x);
    
    int x01 = points[1].x-points[0].x;
    int x02 = points[2].x-points[0].x;
    int y01 = points[1].y-points[0].y;
    int y02 = points[2].y-points[0].y;
    
    Point p0p1(x01,y01);
    Point p0p2(x02,y02);

    double magnitudes = sqrt((p0p1.x*p0p1.x)+(p0p1.y*p0p1.y))*sqrt((p0p2.x*p0p2.x)+(p0p2.y*p0p2.y));
    double costhetaA = ((p0p1.x*p0p2.x)+(p0p1.y*p0p2.y))/magnitudes;
    double A = (magnitudes*sin(acos(costhetaA)))/2;
    double altA = ((p0p1.x*p0p2.y)-(p0p2.x*p0p1.y))/2;
    
    for(int r=minY;r<=maxY;r++){
        for(int c=minX;c<=maxX;c++){
            Point p(c,r);
            int xp1 = points[1].x-p.x;
            int xp2 = points[2].x-p.x;
            int xp0 = points[0].x-p.x;
            int yp1 = points[1].y-p.y;
            int yp2 = points[2].y-p.y;
            int yp0 = points[0].y-p.y;

            Point pp1(xp1,yp1);
            Point pp2(xp2,yp2);
            Point pp0(xp0,yp0);

            double altA0 = ((pp1.x*pp2.y)-(pp2.x*pp1.y))/2;
            double altA1 = ((pp0.x*pp2.y)-(pp2.x*pp0.y))/2;
            double altA2 = ((pp0.x*pp1.y)-(pp1.x*pp0.y))/2;

            double alpha = altA0/altA;
            double beta = altA1/altA;
            double gamma = altA2/altA;
            if(alpha>=0 && beta<=0 && gamma>=0){
                if((gamma+beta<1)){
                    Color color(c0.r*alpha,c1.g*beta*-1,c2.b*gamma);
                    draw_point(p.x, p.y, color);
                }
            }
        }
    }
    std::cout<<"x01: "<<x01<<std::endl;
    std::cout<<"x02: "<<x02<<std::endl;
    std::cout<<"y01: "<<y01<<std::endl;
    std::cout<<"y02: "<<y02<<std::endl;
    std::cout<<"magnitudes: "<<magnitudes<<std::endl;
    std::cout<<"costhetaA: "<<costhetaA<<std::endl;
    std::cout<<"A: "<<A<<std::endl;
    std::cout<<"Alt-A: "<<altA<<std::endl;
}
