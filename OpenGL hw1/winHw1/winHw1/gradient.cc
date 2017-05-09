/********************************************************************
  File: gradient.cc 
  Author:       Dana Vrajitoru
  Project:      Simple gradient program
  Last updated: January 9, 2017.

  Drawing several gradients using simple lines.

********************************************************************/

#include <GL/glut.h>
//#include <GLUT/glut.h>
#include "gradient.h"

// display a vertical gradient going from the bg color on the left to
// the fg color on the right
void verticalGrad(float bg[], float fg[], 
                  float start[], float end[])
{
    glBegin(GL_POLYGON);
    glColor3f(bg[0], bg[1], bg[2]);
    glVertex2f(start[0], start[1]); // bottom left
    glColor3f(fg[0], fg[1], fg[2]);
    glVertex2f(end[0], start[1]);   // bottom right
    glVertex2f(end[0], end[1]);     // top right
    glColor3f(bg[0], bg[1], bg[2]);
    glVertex2f(start[0], end[1]);   // top left

    glEnd();
}




// display a vertical gradient made of horizontal lines of varying color
void verticalGrad1(float bg[], float fg[], 
                   float start[], float end[])
{
    int i;
    float y, color[3], alpha;
    for (y=start[1]; y<end[1]; y += 1) 
    {
        //draw a horizontal line from the bg color to the fg color
        glBegin(GL_LINES);
        glColor3f(bg[0], bg[1], bg[2]);
        glVertex2f(start[0], y);
        glColor3f(fg[0], fg[1], fg[2]);
        glVertex2f(end[0], y);
        glEnd();
    }
}


// display a horizontal gradient going from the bg color on the bottom to
// the fg color on the top
void horizontalGrad(float bg[], float fg[], 
                    float start[], float end[])
{
  
glBegin(GL_POLYGON);
  glColor3f(fg[0], fg[1], fg[2]);
   glVertex2f(end[0], end[1]);     // top right
  glColor3f(fg[0], fg[1], fg[2]);
  glVertex2f(start[0], end[1]);   // top left
  glColor3f(bg[0], bg[1], bg[2]);
  glVertex2f(start[0], start[1]); // bottom left
  glColor3f(bg[0], bg[1], bg[2]);
  glVertex2f(end[0], start[1]);   // bottom right
   
  glEnd();
    // To be completed by the student.
}

// display a square gradient going from the bg color in the center to
// the fg color on the outside
void squareGrad(float bg[], float fg[], 
                float start[], float end[])
{
    // To be completed by the student.
    
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(bg[0], bg[1], bg[2]);
    glVertex2f((end[0]/2), end[1]/2);
    
    
    glColor3f(fg[0], fg[1], fg[2]);
     glVertex2f(start[0], start[1]); // bottom left
    
     glVertex2f(start[0], end[1]);   // top left
    
    glVertex2f(end[0], end[1]);     // top right
    
    glVertex2f(end[0], start[1]);   // bottom right
    
    glVertex2f(start[0], start[1]); // bottom left
    
    glEnd();
}

// display a main diagonal gradient going from the bg color in the
// bottom left corner to the fg color in the top right corner
void diagonalGrad(float bg[], float fg[], 
                  float start[], float end[])
{
  
  glBegin(GL_POLYGON);
    glColor3f(bg[0], bg[1], bg[2]);
    glVertex2f(start[0], start[1]);     //left button
    glColor3f((bg[0]+fg[0])/2, (bg[1]+fg[1])/2, (bg[2]+fg[2])/2);
    glVertex2f(start[0], end[1]);       //left top
     glColor3f(fg[0], fg[1], fg[2]);
    glVertex2f(end[0], end[1]);         //right top
     glColor3f((bg[0]+fg[0])/2, (bg[1]+fg[1])/2, (bg[2]+fg[2])/2);
    glVertex2f(end[0], start[1]);       //left button
  glEnd();
    // To be completed by the student.
}

// display a custom gradient
void customGrad(float bg[], float fg[], 
                 float start[], float end[])
{
   // int i;
    
    glBegin(GL_LINE_STRIP);
    
    
    glColor3f(bg[0], bg[1], bg[2]);
    glVertex2f((end[0]/2), end[1]/2);
    glColor3f(fg[0], fg[1], fg[2]);
    for(int i = 0; i <= (int)end[0]/2; i++) {
        
        if(i%4 ==0){
            glColor3f(bg[0], bg[1], bg[2]);
            glVertex2f(end[0]/2-i,end[1]/2-i);
        }else if(i%4 ==1 ){
            glVertex2f(end[0]/2+i,end[1]/2-i);
        }else if(i%4 ==2 ){
            //glColor3f(bg[0], bg[1], bg[2]);
            
            glColor3f(fg[0], fg[1], fg[2]);
            glVertex2f(end[0]/2+i,end[1]/2+i);
        }
        else if(i%4 ==3){
            glVertex2f(end[0]/2-i,end[1]/2+i);
        }
       // glVertex2f(i,i);
    }
    glEnd();
    // To be implemented by the student.
}
