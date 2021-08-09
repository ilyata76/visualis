//#pragma comment (lib, "D:/CPP_2020/opengl/freeglut-3.2.1/build/lib/Debug/freeglutd.lib")
#include "./include/freeglut/glut.h"

// freeglut-3.2.1
#include <iostream>

void CALLBACK renderScene() ;

int main(int argc, char** argv) {
	glutInit(&argc, argv);								// инициализация GLUT

	int screen_width = glutGet(GLUT_SCREEN_WIDTH);
	int screen_height = glutGet(GLUT_SCREEN_HEIGHT);

	int width = 0.5 * screen_width;
	int height = 0.5 * screen_height;

	glutInitWindowPosition(200, 200);					// позиция окошка
	glutInitWindowSize(width, height);					// его размер
	

	glutInitDisplayMode(GLUT_RGB);						// режимы отображения окошка
	
	int MAINWINDOW = glutCreateWindow("ИМЯ ОКОШКА");	// создаётся окошко	
	glutDisplayFunc(renderScene);

	glutMainLoop();

	// "невидимая" область

	return 0;

}


void CALLBACK renderScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_TRIANGLES);
	glVertex3f(-0.3, -0.3, 0.0);
	glVertex3f(0.0, 0.3, 0.0);
	glVertex3f(0.3, -0.3, 0.0);
	glEnd();
	
	glBegin(GL_TRIANGLES);
	glVertex3f(-0.7, -0.7, 0.0);
	glVertex3f(-0.4, 0.5, 0.0);
	glVertex3f(-0.3, -0.3, 0.0);
	glEnd();

	glutSwapBuffers();
}