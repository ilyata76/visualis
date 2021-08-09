#include "./include/freeglut/glut.h"
//freeglut-3.2.1

#include <iostream>

void CALLBACK RSMAINWINDOW();							// renderScene
void CALLBACK PSKMAINWINDOW(int key, int x, int y);		// processSpecialKeys

void MIMAINWINDOW();									// menu initialize
void CALLBACK MPMAINWINDOW(int value);					// menu processes

float getColorCode(int color);							// from 0 to 255, https://csscolor.ru

void CALLBACK IFMAINWINDOW();							// IdleFun for MAIN WINDOW




void CALLBACK RSMAINWINDOW2() {
	glClearColor(getColorCode(0), getColorCode(0), getColorCode(255), 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

int main(int argc, char** argv) {
	



	// здесь ввод файлов, потом подтверждение и скрытие консоли если ответить на вопрос YES
	// повторить всё это на окошках
	// сделать модульно: VAMPIRE модулем подключать, обработку его тоже
	// отрисовку и просчёты тоже отдельными модулями???







	//FreeConsole();										// спрятать консоль
	
	glutInit(&argc, argv);								// инициализация GLUT

	int screen_width = glutGet(GLUT_SCREEN_WIDTH);
	int screen_height = glutGet(GLUT_SCREEN_HEIGHT);

// ---------------------------------------------------------------------------------------------------------------
	
	int width = 0.5 * screen_width;
	int height = 0.5 * screen_height;

	glutInitWindowPosition(0, 0);						// позиция окошка
	glutInitWindowSize(width, height);					// его размер

	glutInitDisplayMode(GLUT_RGB);						// режимы отображения окошка
	
	int MAINWINDOW = glutCreateWindow("MAINWINDOW");	// создаётся окошко	
	glutSetWindowTitle("TTITLE");


	glutDisplayFunc(RSMAINWINDOW);
	glutSpecialFunc(PSKMAINWINDOW);

	glutSetCursor(GLUT_CURSOR_CROSSHAIR);

	MIMAINWINDOW();

	//glutIdleFunc(IFMAINWINDOW);


// !---------------------------------------------------------------------------------------------------------------
	
	glutMainLoop();
	return 0;

}


void CALLBACK RSMAINWINDOW() {
	glClearColor(getColorCode(240), getColorCode(248), getColorCode(255), 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	
	glPushMatrix();
	// здесь выбор цвета	
	
	
	for (int i = 0; i < 3; i++) {
		glColor3f(0.0, 1.0, 0.0);
		glutSolidCone(0.1, 0.5, 100, 100);
		glTranslated(0.3, 0.3, 0.3);
	}
	glPopMatrix();

	glutSwapBuffers();
}


void CALLBACK IFMAINWINDOW() {
	//
}

void CALLBACK PSKMAINWINDOW(int key, int x, int y) {

	switch (key) {

		case GLUT_KEY_F11: {
			static bool fsMAINWINDOW = false;

			if (!fsMAINWINDOW) {
				glutPositionWindow(0, 0);
				fsMAINWINDOW = true;
			} else {
				glutFullScreen();
				fsMAINWINDOW = false;
			}
		} break;

		case GLUT_KEY_F12: {
			exit(0);
		} break;

	}
}

// -------------------------------------------------------------
void MIMAINWINDOW() {

	int menu = glutCreateMenu(MPMAINWINDOW);
	glutSetMenu(menu);
	glutAddMenuEntry("MENU", 1);
	glutAddMenuEntry("CHTO", 2);
	glutAddMenuEntry("YEP", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

}

void CALLBACK MPMAINWINDOW(int value) {
	switch (value) {
		case 1: {
			std::cout << "EEEEEE\n";
		} break;	
	}
}
// !-------------------------------------------------------------



float getColorCode(int color) {
	return color/255.0;
}