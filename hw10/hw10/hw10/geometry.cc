/*************************************************************************
 FILE:   geometry.cc
 Functions creating the geometry of the objects in the scene and
 drawing them.

 Author: Dana Vrajitoru, IUSB
 Class:  C481 B581 Computer Graphics
 **************************************************************************/

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;
#include "glheader.h"
#include "geometry.h"


#include <cstdlib>


bool objectFlag = false;
matrix3f points;
matrix3f fSurfaceNm;
matrix3f sTexture;
matrix3f sVectex;
matrix3f sNormal;
matrix3f faces;
vector3f vNormal;
vector3f vTexture;
vector3f vVectex;

	// Read .raw file as a triangle strip
void loadRawFile(char *filename)
{
	ifstream fin;
	float x, y, z;
	int   i = 0;
	char  txt[25];
	objectFlag = false;

	fin.open(filename);
	if(!fin){

		cerr<<"Cannot Open!"<<filename << endl;exit(1);
	}

	glNewList(MESH_ID, GL_COMPILE);
	do
		{
			//vector to store points
		vector3f fVector;
		fin >> x >> y >> z;
		glColor3f(i%2, i/(9.0f), 0);
		glBegin(GL_TRIANGLES);
		i++;
		while(fin.good()) // stop when we find a text comment
			{
				//store cordinate
			Point3f fPoint(x, y, z);
			fVector.push_back(fPoint);
			glVertex3f(x, y, z);
			fin >> x >> y >> z;

			}

		glEnd();         // and start a new triangle strip
		points.push_back(fVector);
		fin.clear();
		fin >> txt;      // the comment
		} while(fin.good());

	glEndList();
	fin.close();
}


void loadObjectFile(char *filename){
	ifstream fin;
	float x, y, z;
	int   i = 0;
	char  txt[25];
	int endCheck = 0;
	objectFlag = true;

	fin.open(filename);
	if(!fin){

		cerr<<"Cannot Open!"<<filename << endl;exit(1);
	}

	glNewList(MESH_ID, GL_COMPILE);

	string currentLine;
	while (getline(fin, currentLine))
		{
		vector3f tempVector;
		if (currentLine.substr(0, 2) == "vt") // 顶点纹理坐标数据
			{
			istringstream input(currentLine.substr(3));

			input>>x>>y;
			Point3f fPoint(x,y,0);
			vTexture.push_back(fPoint);
			
				// 解析顶点纹理数据
			}
		else if (currentLine.substr(0, 2) == "vn") // 顶点法向量数据
			{
			istringstream input(currentLine.substr(3));

			input>>x>>y>>z;
			Point3f fPoint(x,y,z);
			vNormal.push_back(fPoint);
				// 解析法向量数据
			}
		else if (currentLine.substr(0, 1) == "v") // 顶点位置数据
			{
			istringstream input(currentLine.substr(3));

			input>>x>>y>>z;
			Point3f fPoint(x,y,z);
			vVectex.push_back(fPoint);
				// 解析顶点位置数据
			}
		else if (currentLine.substr(0, 1) == "f") // 面数据
			{
				// 解析面数据
			}
		else if (currentLine[0] == '#') // 注释忽略
			{ }


		}
	do{
		char head[100];
		char lineHeader[128];
			// read the first word of the line
		int res = fscanf(fin, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

			// else : parse lineHeader

		if ( strcmp( lineHeader, "v" ) == 0 ){
			cout<<"Get v"<<endl;
			glm::vec3 vertex;
			fscanf(fin, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
			temp_vertices.push_back(vertex);
		}

	}while();
	glEndList();
	fin.close();

}

	// a version of drawing the window that uses the display list
void draw1()
{
	glCallList(MESH_ID);
}

	// a version of drawing the window that uses the matrix
void draw2()
{
		//index
	int i = 0, j;
	do{

		j= 0;
			//the part is changing color for whole piece
			//		float r =(rand()%255)/(float)255;
			//		float g =(rand()%255)/(float)255;
			//		float b = (rand()%255)/(float)255;
			//glColor3f(r, g, b);
		glBegin(GL_TRIANGLES);
		while (j<points[i].size()){
				//draw points
			points[i][j].glVertex();
				//change color for every trangle
			float r =(rand()%255)/(float)255;
			float g =(rand()%255)/(float)255;
			float b = (rand()%255)/(float)255;
			glColor3f(r, g, b);
			j++;
		}
		glEnd();
		i++;
	}while (i< points.size());

}



	// Compute the normals for a curve in the xy plane. You can use the
	// function orthogonalXy from the Point3f class. For each 2 line
	// segments in a sequence, the normal should be the average of the two
	// normals computed on each segment. If the first and last point are
	// the same, then the normal in the first and last points should be
void computeNormalsXy(vector3f &vPoints, vector3f &normals)
{
		//temporary values
	Point3f a, b,nResult;
		//check the there more than one point
	if(vPoints.size() >1)
		{
			//traversal all the points
		for(int i=0; i<vPoints.size();i++)
			{
				//vector A
			a[0] = vPoints[i+1][0]-vPoints[i][0];
			a[1] = vPoints[i+1][1]-vPoints[i][1];
			a[2] = vPoints[i+1][2]-vPoints[i][2];
				//vector B
			b[0] = vPoints[i+2][0]-vPoints[i][0];
			b[1] = vPoints[i+2][1]-vPoints[i][1];
			b[2] = vPoints[i+2][2]-vPoints[i][2];
				//cross product A*B
			nResult.normcrossprod(a, b);
			normals.push_back(nResult);
			}
		}
}


	// a version of drawing the window that uses the normalized matrix
void draw3(){
		//get normalizated maxtrix
	for(int i=0; i< points.size(); i++){
		vector3f normals;
		computeNormalsXy(points[i], normals);
		fSurfaceNm.push_back(normals);
	}

		//traversal points inside of maxtrices
	for (int i = 0; i <points.size() ; i++)
		{
		glBegin(GL_TRIANGLE_STRIP);
			//draw surface
		for (int j = 0; j < points[i].size(); j++)
			{
			fSurfaceNm[i][j].glNormal();
			points[i][j].glVertex();
				//random color will be cover by meterial
			float r =(rand()%255)/(float)255;
			float g =(rand()%255)/(float)255;
			float b = (rand()%255)/(float)255;
			glColor3f(r, g, b);
			}
		glEnd();
		
		}
}



