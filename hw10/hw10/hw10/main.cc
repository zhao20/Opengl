/*************************************************************************
  FILE:   main.cc
          Main function.

  Author: Dana Vrajitoru, IUSB
  Class:  C481 B581 Computer Graphics
**************************************************************************/

#include "interface.h"
#include "geometry.h"
#include "glheader.h"
#include <fstream>
#include <iostream>
#include <ctime>
#include <cstring>

using namespace std;

int main(int argc, char **argv)
{
	char objectfile[] = ".obj";
	srand (time(NULL));

    char filename[50];
    glutInit(&argc, argv);
    cout << "Enter the file name" << endl;
    cin >> filename;
    // need both double buffering and z buffer 
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("object");

	if(strstr(filename, objectfile) != NULL){

		printf("I am here reading object file\n");
		loadObjectFile(filename);

	}else{
		loadRawFile(filename);
	}


    myinit();
    glutMainLoop();
    return 0;
}
