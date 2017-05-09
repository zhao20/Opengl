#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include<time.h>
#include"particle.h"


emitter *e1;

GLuint texture[1];
	//视区
float whRatio;
int wHeight = 0;
int wWidth = 0;

	//视点
float center[] = { 0, 0, 0 };
float eye[] = { 0, 0, 5 };

particle* init_particle()
{
	float size = rand() % 100 * 0.02f;
	float color[] = { 1.0f,0.0f,0.0f };
	particle* p = new particle(size, size, float(rand() % 10 - 4) / 80, float(rand() % 10 - 4) / 40,
							   1.0 / 10000, -4.9 / 40000, rand() % 200, rand() % 360,texture[0],false);
	return p;
}

void drawScene()
{
	e1->update();

}

void updateView(int height, int width)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);//设置矩阵模式为投影
	glLoadIdentity();   //初始化矩阵为单位矩阵
	whRatio = (GLfloat)width / (GLfloat)height;  //设置显示比例
	glOrtho(-30, 30, -30, 30, -100, 100); //正投影
	glMatrixMode(GL_MODELVIEW);  //设置矩阵模式为模型
}

void reshape(int width, int height)
{
	if (height == 0)  { //如果高度为0
		height = 1;   //让高度为1（避免出现分母为0的现象）
	}
	wHeight = height;
	wWidth = width;
	updateView(wHeight, wWidth); //更新视角
}

void idle()
{
	glutPostRedisplay();
}

void init(void)
{
	srand(unsigned(time(nullptr)));
	glClearColor(1.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glColor4f(1.0, 1.0, 1.0, 1.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glEnable(GL_BLEND);
		//BuildTexture("11.jpg", texture[0]);
	GLUquadricObj *qobj = gluNewQuadric();
	gluQuadricTexture(qobj,GL_TRUE);
	glColor3f(1, 1, 1);

	e1 = new emitter(500, -30,30, 30, 30);
	e1->emit(init_particle);
}

void redraw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//清除颜色和深度缓存
	glClearColor(0, 0, 0, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();   //初始化矩阵为单位矩阵
	gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], 0, 1, 0);
	drawScene();//绘制场景
	glutSwapBuffers();//交换缓冲区
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);//对glut的初始化
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
		//初始化显示模式:RGB颜色模型，深度测试，双缓冲
	glutInitWindowSize(800, 600);//设置窗口大小
	int windowHandle = glutCreateWindow("Simple GLUT App");//设置窗口标题
	glutDisplayFunc(redraw); //注册绘制回调函数
	glutReshapeFunc(reshape);   //注册重绘回调函数
	glutIdleFunc(idle);//注册全局回调函数：空闲时调用
	init();
	glutMainLoop();  // glut事件处理循环
	return 0;
}
