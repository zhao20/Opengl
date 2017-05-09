#include <cstdlib>
#include <GLUT/glut.h>
#include    <stdlib.h>
#include    <stdio.h>
#include    <iostream>
#include <GLUT/glut.h>



typedef struct _AUX_RGBImageRec {
	GLint sizeX, sizeY;
	unsigned char *data;
}AUX_RGBImageRec;

AUX_RGBImageRec *LoadBMP(char *Filename)	// Loads A Bitmap Image
{
	FILE *File=NULL;	// File Handle

	if (!Filename)	// Make Sure A Filename Was Given
		{

		return NULL;	// If Not Return NULL
		}

	File=fopen(Filename,"r");	// Check To See If The File Exists

	if (File)	// Does The File Exist?
		{
		fclose(File);	// Close The Handle
		return auxDIBImageLoad(Filename);	// Load The Bitmap And Return A Pointer
		}


	return NULL;	// If Load Failed Return NULL
}




GLfloat  corner = 0.0;
GLuint texName;
GLuint flag = 1;
GLUquadricObj* qobj;
void draw_tellurion()
{
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 glLoadIdentity();
		//GLUquadricObj* qobj;// 创建一个二次曲面(二次曲面的创建GLUquadricObj* qobj;qobj = gluNewQuadric();)
 qobj = gluNewQuadric();
		//画球体
 glPushMatrix();
 glTranslatef(0.0, 0.0, 0.0);//屏幕上的位移
 glBindTexture(GL_TEXTURE_2D, texName);
 glEnable(GL_TEXTURE_2D);
 gluQuadricTexture(qobj, GL_TRUE);//纹理函数
 glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
 glRotatef(66.3f, 0.0f, 0.0f, 1.0f);
 glRotatef(-corner, 0.0, -0.261, 0.595);
 gluSphere(qobj, 0.45, 60, 60);//二次曲面qobj

 glDisable(GL_TEXTURE_2D);
 glPopMatrix();
 glutSwapBuffers();//实现双缓冲(解决了频繁刷新导致的画面闪烁问题)双缓冲glutSwapBuffers()很重要的函数
}
void init()
{
 AUX_RGBImageRec *TextureImage[1];
 glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //多边形的显示方式,模式将适用于物体的所有面采用填充形式

 glGenTextures(1, &texName);
 glBindTexture(GL_TEXTURE_2D, texName);
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
 memset(TextureImage, 0, sizeof(void *) * 1);
 if (TextureImage[0] = auxDIBImageLoadA("13.bmp"))   //地球仪
	 {
  glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
	 }


 glClearDepth(1.0f);
 glEnable(GL_DEPTH_TEST);
 glDepthFunc(GL_LEQUAL);//深度缓冲比较值,通过传入的z值是否小于或等于存储z值
 glClearColor(0, 0, 0, 0);     //设置背景色
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);//正射投影函数
}
void Moving()      //地球旋转
{
 if (flag == 1)
	 {
  corner += 0.25f;
  glutPostRedisplay();
	 }
}
int main(int argc, char** argv)
{
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
 glutInitWindowSize(600, 600);
 glutInitWindowPosition(100, 100);
 glutCreateWindow("OpenGL地球——LEILEI");
 glutDisplayFunc(draw_tellurion);
 glutIdleFunc(Moving);
 init();
 glutMainLoop();
 return 0;
}
