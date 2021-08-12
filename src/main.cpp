#include "./include/freeglut/glut.h"
//freeglut-3.2.1

#include "./include/visvamp.hpp"
// vampire 5

void CALLBACK RSMAINWINDOW();							// renderScene
void CALLBACK PSKMAINWINDOW(int key, int x, int y);		// processSpecialKeys
void CALLBACK KMAINWINDOW(unsigned char key, int x, int y);

void MIMAINWINDOW();									// menu initialize
void CALLBACK MPMAINWINDOW(int value);					// menu processes

float getColorCode(int color);							// from 0 to 255, https://csscolor.ru

void CALLBACK IFMAINWINDOW();							// IdleFun for MAIN WINDOW




void CALLBACK RSMAINWINDOW2() {
	glClearColor(getColorCode(0), getColorCode(0), getColorCode(255), 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


vampire5::coneSample* sample;

int main(int argc, char** argv) {
	
	std::vector<vampire5::vertex> vxs = vampire5::parse();
	
	if (vxs[0] != INT_CHECK_VP);
	else return 1;


	sample = vampire5::makeSample(vxs, "cone");


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

	glutSpecialFunc(PSKMAINWINDOW);
	glutKeyboardFunc(KMAINWINDOW);

	glutDisplayFunc(RSMAINWINDOW);

	glutSetCursor(GLUT_CURSOR_CROSSHAIR);

	MIMAINWINDOW();

	//glutIdleFunc(RSMAINWINDOW);


// !---------------------------------------------------------------------------------------------------------------
	
	glutMainLoop();
	return 0;

}


void CALLBACK RSMAINWINDOW() {
	glClearColor(getColorCode(240), getColorCode(248), getColorCode(255), 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glPushMatrix();
	
	glColor3f(0.0, 1.0, 0.0);
	
	std::cout << sample[0].getCone(0).getPhiAngle() <<
		sample[0].getCone(0).getPhiAxes().x <<
		sample[0].getCone(0).getPhiAxes().y <<
		sample[0].getCone(0).getPhiAxes().z;
	
	glRotatef(90, 0, 1, 0); // для того, чтобы выровнять икс???

	glRotatef(
		sample[0].getCone(0).getPhiAngle(), 
		sample[0].getCone(0).getPhiAxes().x, 
		sample[0].getCone(0).getPhiAxes().y, 
		sample[0].getCone(0).getPhiAxes().z
	);

	glRotatef(
		sample[0].getCone(0).getThetaAngle(),
		sample[0].getCone(0).getThetaAxes().x,
		sample[0].getCone(0).getThetaAxes().y,
		sample[0].getCone(0).getThetaAxes().z
	);

	glutSolidCone(0.05, 0.05, 10, 10);
	//glTranslated(0.1, 0.1, 0.1)

	glPopMatrix();
	glutSwapBuffers();

	// здесь выбор цвета	
	
	//glColor3f(0.0, 1.0, 0.0);
	//glutSolidCone(0.1, 0.5, 100, 100);
	//glTranslated(0.3, 0.3, 0.3);
	//glRotated(90, 1, 1, 1);
	////glRotatef(10, 1, 1, 1);
	//glutSolidCone(0.1, 0.5, 100, 100);
	
		/*for (int i = 0; i < 10; i++) {
			glPushMatrix();
			glColor3f(0.0, 1.0, 0.0);
			glutSolidCone(0.05, 0.05, 10, 10);
			glTranslated(0.1, 0.1, 0.1);
			glRotated(30, 0, 1, 0);
			glPopMatrix();
		}*/


	//if (GetKeyState(VK_UP) < 0) glTranslated(0.3, 0.3, 0.3);


	
	
	
	
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


void CALLBACK KMAINWINDOW(unsigned char key, int x, int y) {

	switch (key) {
	case 'w':
		glTranslated(0, 0.3, 0);
		break;
	case 's':
		glTranslated(-0.3, -0.3, -0.3);
		break;
	}; 

}


// -------------------------------------------------------------
void MIMAINWINDOW() {

	int menu = glutCreateMenu(MPMAINWINDOW);
	glutSetMenu(menu);
	glutAddMenuEntry("MENU", 1);
	glutAddMenuEntry("menu 2", 2);
	glutAddMenuEntry("menu 3", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

}

void CALLBACK MPMAINWINDOW(int value) {
	switch (value) {
		case 1: {
			std::cout << "EEEEEE\n";
		} break;	
		case 2: {
			glTranslated(-0.3, -0.3, -0.3);
		} break;
	}
}
// !-------------------------------------------------------------



float getColorCode(int color) {
	return color/255.0;
}