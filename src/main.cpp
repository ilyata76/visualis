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

inline int welcome();


void CALLBACK RSMAINWINDOW2() {
	glClearColor(getColorCode(0), getColorCode(0), getColorCode(255), 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


vampire5::coneSample* sample;
int code = 0;

int main(int argc, char** argv) {
	
	int code = welcome();

	if (code == 1) {
		std::cerr << "ошибка" << std::endl;
		return 1;
	}

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
	
	/*std::cout << std::endl << "PHI: " << sample[0].getCone(0).getPhiAngle() << std::endl <<
		sample[0].getCone(0).getPhiAxes().x <<
		sample[0].getCone(0).getPhiAxes().y <<
		sample[0].getCone(0).getPhiAxes().z;


	std::cout << std::endl << "THETA: " << sample[0].getCone(0).getThetaAngle() << std::endl <<
		sample[0].getCone(0).getThetaAxes().x <<
		sample[0].getCone(0).getThetaAxes().y <<
		sample[0].getCone(0).getThetaAxes().z;
	*/
	glRotatef(90, 0, 1, 0); // для того, чтобы выровнять икс???
	// если камера смотрит в пол, то поворот на 90 заставит её посмотреть в сторону икс

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

	glutSolidCone(0.05, 0.1, 10, 10);
	//glTranslated(0.1, 0.1, 0.1)

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

			if (fsMAINWINDOW) {
				glutPositionWindow(0, 0);
				fsMAINWINDOW = false;
			} else {
				glutFullScreen();
				fsMAINWINDOW = true;
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


int welcome() {

	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);

	std::ifstream file1; // for point
	std::ifstream file2; // for spin

	std::string path = "";

	std::cout << "Enter the path to folder with atoms-coords.data and spins-XXXX.data: ";
		std::cin >> path;

		for (int j = 0; j < path.size(); j++) {
			if (path[j] == '\\') path[j] = '/';
		}

	
	file1.open(path + "\\atoms-coords.data");

	if (file1.is_open() && !file1.eof()) {
		std::cout << "[] Succesfully! path = " << path << std::endl;
	} else {
		std::cerr << "ERROR: File atoms-coords.data is absent" << std::endl;
		return 1;
	}
	
	std::string number = "";
	std::string et = "00000000";
	std::string filename = "";

	std::cout << "Enter the file number (1): ";
		std::cin >> number;

		if (number.size() < et.size()) {
			for (int i = 0; i < et.size() - number.size(); i++) {
				filename.push_back('0');
			}
		}
		filename += number;

	file2.open(path + "\\spins-" + filename + ".data");

	if (file2.is_open() && !file2.eof()) {
		std::cout << "[] Succesfully! filename = spins-" << filename << std::endl;
	} else {
		std::cerr << "ERROR: File spins-" << filename <<".data is absent" << std::endl;
		return 1;
	}
	

	std::cout << "===========================================" << std::endl;

	std::cout << "Start reading data" << std::endl;
	std::cout << "___________________________________________" << std::endl;
	std::vector<vampire5::vertex> vxs = vampire5::parse(file1, file2);
	std::cout << "===========================================" << std::endl;

	for (int j = 0; j < vxs.size(); j++) {
		if (vxs[j] == INT_CHECK_VP) return 1;
	}
	
	
	std::cout << "Start data transformations" << std::endl;
	std::cout << "___________________________________________" << std::endl;
	sample = vampire5::makeSample(vxs, "cone");
	std::cout << "===========================================" << std::endl;

	for (int j = vxs.size() - 1; vxs.size() != 0; j--) {
		vxs[j].~vertex();
		vxs.pop_back();
	}

	return 0;
}