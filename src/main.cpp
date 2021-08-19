#include "./include/freeglut/glut.h"
//freeglut-3.2.1

#include "./include/visvamp.hpp"
// vampire 5

void CALLBACK RSMAINWINDOW();							// renderScene
void CALLBACK PSKMAINWINDOW(int key, int x, int y);		// processSpecialKeys
void CALLBACK KMAINWINDOW(unsigned char key, int x, int y);

void MIMAINWINDOW();									// menu initialize
void CALLBACK MPMAINWINDOW(int value);					// menu processes

float gCC(int color);									// getcolorcode. from 0 to 255, https://csscolor.ru

inline int welcome();
inline int menu();
inline int menu_1();


inline std::string getOutInstruction();

vampire5::coneSample* sample;

std::vector < vampire5::coneSample* > samples;

#define EXIT_CODE 6000
#define ERROR_CODE_1 6001
#define ERROR_CODE_2 6002
#define ERROR_CODE_3 6003
#define ERROR_CODE_4 6004

// 600X for vampire
// 500x for mumax

#define MENU_CODE_1 10000
#define MENU_CODE_11 10001
#define MENU_CODE_12 10002
#define MENU_CODE_13 10003

// TODO: организовать проверку нормального создания sample-класса
// TODO: создать формат файлов для быстрого чтения и преобразования

int main(int argc, char** argv) {
	using std::literals::string_literals::operator""s;

	int code;
	try {

		code = welcome();	

	} catch (int _CODE) {

		if (_CODE == ERROR_CODE_1) {
			std::cout << "[VISUALIS/VAMPIRE][ERROR_CODE] : The error is related to the file atoms-coords.data"s << std::endl;
			//return main(argc, argv);
		} else if (_CODE == ERROR_CODE_2) {
			std::cout << "[VISUALIS/VAMPIRE][ERROR_CODE] : The error is related to the file spins-XXX.data"s << std::endl;
			//return main(argc, argv);
		} else if (_CODE == ERROR_CODE_3) {
			std::cout << "[VISUALIS/VAMPIRE][ERROR_CODE] : The error is related to the file processing"s << std::endl;
			//return main(argc, argv);
		} else if (_CODE == ERROR_CODE_4){ 
			std::cout << "[VISUALIS/VAMPIRE][ERROR_CODE] : The error is related to transformation processing"s << std::endl;
		} else if (_CODE == EXIT_CODE) {
			std::cout << "[VISUALIS] EXIT"s << std::endl;
			return 0;
		}

		return _CODE;

		// 1 - atoms
		// 2 - spins
		// 3 - ошибка при обработке файлов
	};

	if (code == 0) {

		//FreeConsole();

		glutInit(&argc, argv);

		int screen_width = glutGet(GLUT_SCREEN_WIDTH);
		int screen_height = glutGet(GLUT_SCREEN_HEIGHT);

		// ---------------------------------------------------------------------------------------------------------------

		int width = 0.5 * screen_width;
		int height = 0.5 * screen_height;

		glutInitWindowPosition(0, 0);
		glutInitWindowSize(width, height);

		glutInitDisplayMode(GLUT_RGB);

		int MAINWINDOW = glutCreateWindow("MAINWINDOW");
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

	} else {
		return 1;
	}
}


void CALLBACK RSMAINWINDOW() {
	glClearColor(gCC(240), gCC(248), gCC(255), 1);
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
	glutAddMenuEntry("MENU", MENU_CODE_11);
	glutAddMenuEntry("menu 2", MENU_CODE_12);
	glutAddMenuEntry("menu 3", MENU_CODE_13);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

}

void CALLBACK MPMAINWINDOW(int value) {
	switch (value) {
		case MENU_CODE_11: {
			//
		} break;	
		case MENU_CODE_12: {
			glTranslated(-0.3, -0.3, -0.3);
		} break;
		case MENU_CODE_13: {
			glTranslated(0.3, 0.3, 0.3);
		} break;
	}
}
// !-------------------------------------------------------------

float gCC(int color) {
	return color/255.0;
}
// !-------------------------------------------------------------

int welcome() {
	using std::literals::string_literals::operator""s;

	int choice = menu();

	switch (choice) {

		case 1: {

			int choice_1 = menu_1();

			switch (choice_1) {

				case 1: {
					SetConsoleCP(65001);
					SetConsoleOutputCP(65001);

					std::ifstream file1; // for point
					std::ifstream file2; // for spin

					std::string path = "";

					std::cout << "[VISUALIS/VAMPIRE] Enter the path to folder with atoms-coords.data and spins-XXXX.data: "s;
						std::cin >> path;

						for (int j = 0; j < path.size(); j++) {
							if (path[j] == '\\') path[j] = '/';
						}

	
					file1.open(path + "\\atoms-coords.data");

					if (file1.is_open() && !file1.eof()) {
						std::cout << "[VISUALIS/VAMPIRE] Succesfully! path = "s << path << std::endl;
					} else {
						std::cerr << "[VISUALIS/VAMPIRE][ERROR] : File atoms-coords.data is absent"s << std::endl;
						throw ERROR_CODE_1;
					}
	
					std::string number = "";
					std::string et = "00000000";
					std::string filename = "";

					std::cout << "[VISUALIS/VAMPIRE] Enter the file number (1): "s;
						std::cin >> number;

						if (number.size() < et.size()) {
							for (int i = 0; i < et.size() - number.size(); i++) {
								filename.push_back('0');
							}
						}
						filename += number;

					file2.open(path + "\\spins-" + filename + ".data");
			
					if (file2.is_open() && !file2.eof()) {
						std::cout << "[VISUALIS/VAMPIRE] Succesfully! filename = spins-"s << filename << std::endl;
					} else {
						std::cerr << "[VISUALIS/VAMPIRE][ERROR] : File spins-"s << filename <<".data is absent"s << std::endl;
						throw ERROR_CODE_2;
					}
	
					std::string out_instruction = getOutInstruction();

					if (out_instruction == "yes") std::cout << "[VISUALIS/VAMPIRE] ==========================================="s << std::endl;

					if (out_instruction == "yes") std::cout << "[VISUALIS/VAMPIRE] Start reading data"s << std::endl;
					if (out_instruction == "yes") std::cout << "[VISUALIS/VAMPIRE] ___________________________________________"s << std::endl;
					std::vector<vampire5::vertex> vxs = vampire5::parse(file1, file2, out_instruction);
					if (out_instruction == "yes") std::cout << "[VISUALIS/VAMPIRE] ==========================================="s << std::endl;

					for (int j = 0; j < vxs.size(); j++) {
						if (!vxs[j].vertexCreated()) throw ERROR_CODE_3;
					}
	
	
					if (out_instruction == "yes") std::cout << "[VISUALIS/VAMPIRE] Start data transformations"s << std::endl;
					if (out_instruction == "yes") std::cout << "[VISUALIS/VAMPIRE] ___________________________________________"s << std::endl;
					sample = vampire5::makeSample(vxs, "cone", 0, out_instruction);
					if (out_instruction == "yes") std::cout << "[VISUALIS/VAMPIRE] ==========================================="s << std::endl;

					for (int j = 0; j < sample->size(); j++) {
						if (!sample->getCone(j).coneCreated()) throw ERROR_CODE_4;
					}

					std::cout << "[VISUALIS/VAMPIRE] Succesfully!"s << std::endl;

					for (int j = vxs.size() - 1; vxs.size() != 0; j--) {
						vxs[j].~vertex();
						vxs.pop_back();
					}

					return 0;
				} break;
			
				case 2: {
					SetConsoleCP(65001);
					SetConsoleOutputCP(65001);

					std::string path = "";
					std::vector< std::vector <vampire5::vertex> > FP;

					std::cout << "[VISUALIS/VAMPIRE] Enter the path to folder with atoms-coords.data and spins-XXXX.data: "s;
						std::cin >> path;

						for (int j = 0; j < path.size(); j++) {
							if (path[j] == '\\') path[j] = '/';
						}

					std::string out_instruction = getOutInstruction();

						FP = vampire5::fullParse(path, out_instruction);

						if (!FP[0][0].vertexCreated()) throw ERROR_CODE_3;

						samples = vampire5::makeVSample(FP, "cone", out_instruction);

						if (!samples[0]->getCone(0).coneCreated()) throw ERROR_CODE_4;

						return 0;
				} break;

				case 0: {
					throw EXIT_CODE;
				} break;
					  
				default: {
					throw EXIT_CODE;
				} break;

			}

		} break;
		
		case 0: {
			throw EXIT_CODE;
		} break;

		default: {
			throw EXIT_CODE;
		} break;
	}
}

// STRUCTURE welcome:
// |choice for vampire or mumax
// |--1: vampire
	// |--1: 1 file parse
	// |--2: all files parse
	// |--0: exit
// |--2: mumax
	// |--1: 1 file parse
	// |--2: all files parse
	// |--0: exit
// |--0: exit


int menu() {
	using std::literals::string_literals::operator""s;
	int choice = 0;
	std::cout << "[VISUALIS] *********************************"s << std::endl;
	std::cout << "[VISUALIS] 1. VAMPIRE 5"s << std::endl;
	std::cout << "[VISUALIS] 0. EXIT"s << std::endl;
	std::cout << "[VISUALIS] *********************************"s << std::endl;
	std::cout << "[VISUALIS] Choice? : "s; std::cin >> choice;
	return choice;
}

int menu_1() {
	using std::literals::string_literals::operator""s;
	int choice = 0;
	std::cout << "[VISUALIS/VAMPIRE] *********************************"s << std::endl;
	std::cout << "[VISUALIS/VAMPIRE] 1. 1 file"s << std::endl;
	std::cout << "[VISUALIS/VAMPIRE] 2. all files"s << std::endl;
	std::cout << "[VISUALIS/VAMPIRE] 0. EXIT"s << std::endl;
	std::cout << "[VISUALIS/VAMPIRE] *********************************"s << std::endl;
	std::cout << "[VISUALIS/VAMPIRE] Choice? : "s; std::cin >> choice;
	return choice;
}


std::string getOutInstruction() {
	using std::literals::string_literals::operator""s;
	std::string choice = "";
	
	whille:

	std::cout << "[VISUALIS/VAMPIRE] *********************************"s << std::endl;
	std::cout << "[VISUALIS] нужен ли вывод? (yes/no) "s; std::cin >> choice;

	if (choice == "yes"s || choice == "y"s) return "yes"s;
	else if (choice == "no"s || choice == "n"s) return "no"s;
	else {
		goto whille;
	}

}