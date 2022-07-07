#include "./freeglut_drawer.hpp"

Settings glob_settings;
std::vector<Vertex> glob_vct;

std::vector<std::string> vct_log;
std::vector<Rgb> vct_log_colorful;

bool have_additional_sub_windows = false;

std::map<std::wstring, Rgb> colors = {
	{L"white", Rgb(255.0 / 255.0, 255.0 / 255.0, 255.0 / 255.0)},
	{L"red", Rgb(195.0 / 255.0, 21.0 / 255.0, 21.0 / 255.0)},
	{L"green", Rgb(0.0, 154.0 / 255.0, 99.0 / 255.0)},
	{L"blue", Rgb(19.0 / 255.0, 86.0 / 255.0, 201.0 / 255.0)},
	{L"lightblue", Rgb(108.0 / 255.0, 146.0 / 255.0, 175.0 / 255.0)},
	{L"black", Rgb(0.0 / 255.0, 0.0 / 255.0, 0.0 / 255.0)},
	{L"lightgrey", Rgb(230.0 / 255.0, 230.0 / 255.0, 230.0 / 255.0)},
	{L"main", Rgb(255.0 / 255.0, 255.0 / 255.0, 255.0 / 255.0)},
	{L"sub0", Rgb(255.0 / 255.0, 255.0 / 255.0, 255.0 / 255.0)},
	{L"sub1", Rgb(230.0 / 255.0, 230.0 / 255.0, 230.0 / 255.0)},
	{L"sub2", Rgb(230.0 / 255.0, 230.0 / 255.0, 230.0 / 255.0)},
	{L"sbu3", Rgb(230.0 / 255.0, 230.0 / 255.0, 230.0 / 255.0)},
};

Rgb RGB_RED = colors[L"red"];
Rgb RGB_GREEN = colors[L"green"];
Rgb RGB_BLACK = colors[L"black"];
Rgb RGB_WHITE = colors[L"white"];
Rgb RGB_BLUE = colors[L"blue"];

void print_text_3f(double _x, double _y, double _z, std::wstring text, void* FONT) {
	glRasterPos3i(_x, _y, _z);
	int len = text.length(); 

	for (int i = 0; i < len; ++i) 
		glutBitmapCharacter(FONT, text[i]);
}

void print_text_2f(double _x, double _y, std::wstring text, void* FONT) {
	glRasterPos2i(_x, _y);
	int len = text.length(); 

	for (int i = 0; i < len; ++i) 
		glutBitmapCharacter(FONT, text[i]);
}

void print_text_3f(double _x, double _y, double _z, std::string text, void* FONT) {
	glRasterPos3i(_x, _y, _z);
	int len = text.length();

	for (int i = 0; i < len; ++i)
		glutBitmapCharacter(FONT, text[i]);
}

void print_text_2f(double _x, double _y, std::string text, void* FONT) {
	glRasterPos2i(_x, _y);
	int len = text.length(); 

	for (int i = 0; i < len; ++i) 
		glutBitmapCharacter(FONT, text[i]);
}

double distance_between_fonts(void* _font) {
	
	if (_font == GLUT_BITMAP_HELVETICA_10) return 10.0;
	if (_font == GLUT_BITMAP_HELVETICA_12) return 12.0;
	if (_font == GLUT_BITMAP_HELVETICA_18) return 18.0;

	if (_font == GLUT_BITMAP_8_BY_13) return 13.0;
	if (_font == GLUT_BITMAP_9_BY_15) return 15.0;

	if (_font == GLUT_BITMAP_TIMES_ROMAN_10) return 10.0;
	if (_font == GLUT_BITMAP_TIMES_ROMAN_24) return 24.0;

	return 10.0;

}

void log(std::string _str, Rgb _color) {
	
	char buffer[256];
	time_t rawtime; time(&rawtime);
	struct tm *timeinfo = localtime(&rawtime);
	strftime(buffer, 256, "%H:%M:%S", timeinfo);

	vct_log.push_back(std::string(buffer) + " - " + _str);
	vct_log_colorful.push_back(_color);

}

void draw_sample(Settings& _settings, std::vector<Vertex>& _vct, int argc, char** argv) {

	glob_settings = _settings;
	glob_vct = _vct;

	have_additional_sub_windows = false;

	colors[L"main"] = glob_settings.main_window.backgroundcolor;
	colors[L"sub0"] = glob_settings.subwindows[0].backgroundcolor;
	colors[L"sub1"] = glob_settings.subwindows[1].backgroundcolor;
	colors[L"sub2"] = glob_settings.subwindows[2].backgroundcolor;
	colors[L"sub3"] = glob_settings.subwindows[3].backgroundcolor;

	glob_settings.other_settings.font_stats = GLUT_BITMAP_9_BY_15;
	glob_settings.other_settings.font_log = GLUT_BITMAP_9_BY_15;

	vct_log = {};
	vct_log_colorful = {};

	log("System initialized", RGB_GREEN);

	// настройки будут переходить из окна к окну только в случае сохранения их здесь и восстановления из файла в консоли

	glutInit(&argc, argv);

	glutInitWindowSize(glob_settings.main_window.wh.width,
						glob_settings.main_window.wh.height);

	glutInitWindowPosition(glob_settings.main_window.window_position.x, glob_settings.main_window.window_position.y);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

	glob_settings.main_window.descriptor = glutCreateWindow("main_window"); glutSetWindowTitle("VISUALIS");
		glutDisplayFunc(display_mainwindow);
		glutReshapeFunc(reshape_mainwindow);
		main_menu_init();

	recalculation_subwindows_wh();

	glob_settings.subwindows[0].descriptor = glutCreateSubWindow(
		glob_settings.main_window.descriptor,
		glob_settings.subwindows[0].window_position.x, glob_settings.subwindows[0].window_position.y,
		glob_settings.subwindows[0].wh.width, glob_settings.subwindows[0].wh.height
	);
		glutDisplayFunc(display_subwindow_0);
		glutReshapeFunc(reshape_subwindow_0);
		glutKeyboardFunc(normal_keys);
		glutSpecialFunc(special_keys);
		glutPassiveMotionFunc(passive_mouse_motion);
		glutMotionFunc(pressed_mouse_motion);
		glutMouseFunc(mouse_pressed);
		subwindow_0_menu_init();

	log("Drawer area was built", RGB_BLACK);

	if (glob_settings.freeglut_settings.use_additional_subwindows) {

		create_additional_subwindows();
		have_additional_sub_windows = true;

	}
	
	if (glob_settings.freeglut_settings.fullscreen) { glutFullScreen(); log("Fullscreen mode was enabled", RGB_BLUE); }

	// continue
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
	
	glutMainLoop();

}

void display_mainwindow() {
	glClearColor(glob_settings.main_window.backgroundcolor.red, glob_settings.main_window.backgroundcolor.green, glob_settings.main_window.backgroundcolor.blue, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glutSwapBuffers();
}

void reshape_mainwindow(int w, int h) {
	if (h == 0) h = 1;
	if (w == 0) w = 1;

	glViewport(0, 0, w, h);
	
	glob_settings.main_window.wh.width = w;
	glob_settings.main_window.wh.height= h;

	// reshape subwindows
	recalculation_subwindows_wh();

	if (w < 500 || h < 300 || double(h)/double(w) > 1.1) {
		
		destroy_additional_subwindows();

	} else {
	
		if (!have_additional_sub_windows) {
			recalculation_subwindows_wh();
			if (glob_settings.freeglut_settings.use_additional_subwindows) create_additional_subwindows();
		}

		if (glob_settings.freeglut_settings.use_additional_subwindows) have_additional_sub_windows = true;

	}

	log("Main window was reshaped", RGB_BLACK);

	reshape_reposition_subwindows();

}



void main_menu_init() {
	int _main_menu = glutCreateMenu(main_menu);
	int _menu_main = glutCreateMenu(menu_background_main);
	int _menu_gap = glutCreateMenu(main_menu_gap);
	int _menu_subwindows = glutCreateMenu(main_menu_subwindows);

	char buff[256]; 

	glutSetMenu(_menu_main);
		sprintf(buff, "White: (%g/255, %g/255, %g/255)", colors[L"white"].red * 255.0, colors[L"white"].green * 255.0, colors[L"white"].blue * 255.0);
		glutAddMenuEntry(buff, MENU_COLORING_BACKGROUND_WHITE);
		sprintf(buff, "Red: (%g/255, %g/255, %g/255)", colors[L"red"].red * 255.0, colors[L"red"].green * 255.0, colors[L"red"].blue * 255.0);
		glutAddMenuEntry(buff, MENU_COLORING_BACKGROUND_RED);
		sprintf(buff, "Green: (%g/255, %g/255, %g/255)", colors[L"green"].red * 255.0, colors[L"green"].green * 255.0, colors[L"green"].blue * 255.0);
		glutAddMenuEntry(buff, MENU_COLORING_BACKGROUND_GREEN);
		sprintf(buff, "Blue: (%g/255, %g/255, %g/255)", colors[L"blue"].red * 255.0, colors[L"blue"].green * 255.0, colors[L"blue"].blue * 255.0);
		glutAddMenuEntry(buff, MENU_COLORING_BACKGROUND_BLUE);
		sprintf(buff, "Light blue: (%g/255, %g/255, %g/255)", colors[L"lightblue"].red * 255.0, colors[L"lightblue"].green * 255.0, colors[L"lightblue"].blue * 255.0);
		glutAddMenuEntry(buff, MENU_COLORING_BACKGROUND_LIGHTBLUE);
		sprintf(buff, "Black: (%g/255, %g/255, %g/255)", colors[L"black"].red * 255.0, colors[L"black"].green * 255.0, colors[L"black"].blue * 255.0);
		glutAddMenuEntry(buff, MENU_COLORING_BACKGROUND_BLACK);
		sprintf(buff, "Light grey: (%g/255, %g/255, %g/255)", colors[L"lightgrey"].red * 255.0, colors[L"lightgrey"].green * 255.0, colors[L"lightgrey"].blue * 255.0);
		glutAddMenuEntry(buff, MENU_COLORING_BACKGROUND_LIGHTGREY);
		sprintf(buff, "As main was: (%g/255, %g/255, %g/255)", colors[L"main"].red * 255.0, colors[L"main"].green * 255.0, colors[L"main"].blue * 255.0);
		glutAddMenuEntry(buff, MENU_COLORING_BACKGROUND_MAIN);
		sprintf(buff, "As drawer area was: (%g/255, %g/255, %g/255)", colors[L"sub0"].red * 255.0, colors[L"sub0"].green * 255.0, colors[L"sub0"].blue * 255.0);
		glutAddMenuEntry(buff, MENU_COLORING_BACKGROUND_SUB0);
		sprintf(buff, "As axis area was: (%g/255, %g/255, %g/255)", colors[L"sub1"].red * 255.0, colors[L"sub1"].green * 255.0, colors[L"sub1"].blue * 255.0);
		glutAddMenuEntry(buff, MENU_COLORING_BACKGROUND_SUB1);
		sprintf(buff, "As stats area was: (%g/255, %g/255, %g/255)", colors[L"sub2"].red * 255.0, colors[L"sub2"].green * 255.0, colors[L"sub2"].blue * 255.0);
		glutAddMenuEntry(buff, MENU_COLORING_BACKGROUND_SUB2);
		sprintf(buff, "As log area was: (%g/255, %g/255, %g/255)", colors[L"sub3"].red * 255.0, colors[L"sub3"].green * 255.0, colors[L"sub3"].blue * 255.0);
		glutAddMenuEntry(buff, MENU_COLORING_BACKGROUND_SUB3);

	glutSetMenu(_menu_gap);
		glutAddMenuEntry("Increase by 1", MAIN_MENU_GAP_INCREASE_BY_1);
		glutAddMenuEntry("Decrease by 1", MAIN_MENU_GAP_DECREASE_BY_1);
		glutAddMenuEntry("Set gap = 5", MAIN_MENU_GAP_SET_5);
		glutAddMenuEntry("Set gap = 6", MAIN_MENU_GAP_SET_6);
		glutAddMenuEntry("Set gap = 7", MAIN_MENU_GAP_SET_7);
		glutAddMenuEntry("Set gap = 8", MAIN_MENU_GAP_SET_8);
		glutAddMenuEntry("Set gap = 9", MAIN_MENU_GAP_SET_9);

	glutSetMenu(_menu_subwindows);
		glutAddMenuEntry("Destroy additional subwindows", MAIN_MENU_SUBWINDOWS_DESTROY);
		glutAddMenuEntry("Build additional subwindows", MAIN_MENU_SUBWINDOWS_BUILD);

	glutSetMenu(_main_menu);
		glutAddSubMenu("Background", _menu_main);
		glutAddSubMenu("Gap", _menu_gap);
		glutAddSubMenu("Subwindows", _menu_subwindows);

	log("Main menu was initialized", RGB_BLACK);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutDetachMenu(GLUT_LEFT_BUTTON);

}

void main_menu(int code) {

	switch (code) {
		default: break;
	}

}

void main_menu_gap(int code) {

	switch (code) {

		case MAIN_MENU_GAP_INCREASE_BY_1:	glob_settings.freeglut_settings.gap += 1;
											log("GAP has been changed to " + std::to_string(glob_settings.freeglut_settings.gap), RGB_BLUE);
											recalculation_subwindows_wh();
											reshape_reposition_subwindows();
											postRedisplay(); 
											break;

		case MAIN_MENU_GAP_DECREASE_BY_1:	glob_settings.freeglut_settings.gap = glob_settings.freeglut_settings.gap == 1 ? 1 : glob_settings.freeglut_settings.gap - 1;
											log("GAP has been changed to " + std::to_string(glob_settings.freeglut_settings.gap), RGB_BLUE);
											recalculation_subwindows_wh();
											reshape_reposition_subwindows();
											postRedisplay(); 
											break;
		
		case MAIN_MENU_GAP_SET_5:	glob_settings.freeglut_settings.gap = 5;
									log("GAP has been changed to " + std::to_string(glob_settings.freeglut_settings.gap), RGB_BLUE);
									recalculation_subwindows_wh();
									reshape_reposition_subwindows();
									postRedisplay(); 
									break;

		case MAIN_MENU_GAP_SET_6:	glob_settings.freeglut_settings.gap = 6;
									log("GAP has been changed to " + std::to_string(glob_settings.freeglut_settings.gap), RGB_BLUE);
									recalculation_subwindows_wh();
									reshape_reposition_subwindows();
									postRedisplay(); 
									break;

		case MAIN_MENU_GAP_SET_7:	glob_settings.freeglut_settings.gap = 7;
									log("GAP has been changed to " + std::to_string(glob_settings.freeglut_settings.gap), RGB_BLUE);
									recalculation_subwindows_wh();
									reshape_reposition_subwindows();
									postRedisplay(); 
									break;

		case MAIN_MENU_GAP_SET_8:	glob_settings.freeglut_settings.gap = 8;
									log("GAP has been changed to " + std::to_string(glob_settings.freeglut_settings.gap), RGB_BLUE);
									recalculation_subwindows_wh();
									reshape_reposition_subwindows();
									postRedisplay(); 
									break;

		case MAIN_MENU_GAP_SET_9:	glob_settings.freeglut_settings.gap = 9;
									log("GAP has been changed to " + std::to_string(glob_settings.freeglut_settings.gap), RGB_BLUE);
									recalculation_subwindows_wh();
									reshape_reposition_subwindows();
									postRedisplay(); 
									break;

		default: break;
	}

}

void menu_background_main(int code) {

	switch (code) {

		case MENU_COLORING_BACKGROUND_WHITE: glob_settings.main_window.backgroundcolor = colors[L"white"]; log("Main background color changed", RGB_BLUE); postRedisplay(); break;
		case MENU_COLORING_BACKGROUND_RED: glob_settings.main_window.backgroundcolor = colors[L"red"]; log("Main background color changed", RGB_BLUE);  postRedisplay(); break;
		case MENU_COLORING_BACKGROUND_GREEN: glob_settings.main_window.backgroundcolor = colors[L"green"]; log("Main background color changed", RGB_BLUE);  postRedisplay(); break;
		case MENU_COLORING_BACKGROUND_BLUE: glob_settings.main_window.backgroundcolor = colors[L"blue"]; log("Main background color changed", RGB_BLUE);  postRedisplay(); break;
		case MENU_COLORING_BACKGROUND_LIGHTBLUE: glob_settings.main_window.backgroundcolor = colors[L"lightblue"]; log("Main background color changed", RGB_BLUE);  postRedisplay(); break;
		case MENU_COLORING_BACKGROUND_BLACK: glob_settings.main_window.backgroundcolor = colors[L"black"]; log("Main background color changed", RGB_BLUE);  postRedisplay(); break;
		case MENU_COLORING_BACKGROUND_LIGHTGREY: glob_settings.main_window.backgroundcolor = colors[L"lightgrey"]; log("Main background color changed", RGB_BLUE);  postRedisplay(); break;
		case MENU_COLORING_BACKGROUND_MAIN: glob_settings.main_window.backgroundcolor = colors[L"main"]; log("Main background color changed", RGB_BLUE);  postRedisplay(); break;
		case MENU_COLORING_BACKGROUND_SUB0: glob_settings.main_window.backgroundcolor = colors[L"sub0"]; log("Main background color changed", RGB_BLUE);  postRedisplay(); break;
		case MENU_COLORING_BACKGROUND_SUB1: glob_settings.main_window.backgroundcolor = colors[L"sub1"]; log("Main background color changed", RGB_BLUE);  postRedisplay(); break;
		case MENU_COLORING_BACKGROUND_SUB2: glob_settings.main_window.backgroundcolor = colors[L"sub2"]; log("Main background color changed", RGB_BLUE);  postRedisplay(); break;
		case MENU_COLORING_BACKGROUND_SUB3: glob_settings.main_window.backgroundcolor = colors[L"sub3"]; log("Main background color changed", RGB_BLUE);  postRedisplay(); break;
		
		default: break;

	}

}

void main_menu_subwindows(int code) {

	switch (code) {
	
		case MAIN_MENU_SUBWINDOWS_DESTROY: 
				glob_settings.freeglut_settings.use_additional_subwindows = false;
				log("Subwindows will be destroyed", RGB_BLUE);
				recalculation_subwindows_wh();
				reshape_reposition_subwindows();
				destroy_additional_subwindows();
				postRedisplay();
				break;
		case MAIN_MENU_SUBWINDOWS_BUILD: 
				glob_settings.freeglut_settings.use_additional_subwindows = true;
				log("Subwindows will be built", RGB_BLUE);
				create_additional_subwindows();
				recalculation_subwindows_wh();
				reshape_reposition_subwindows();
				postRedisplay();
				break;

		default: break;
	
	}

}

void create_additional_subwindows() {
	if (have_additional_sub_windows == false) {
		if (glob_settings.freeglut_settings.use_additional_subwindows) {
			glob_settings.subwindows[1].descriptor = glutCreateSubWindow(
				glob_settings.main_window.descriptor,
				glob_settings.subwindows[1].window_position.x, glob_settings.subwindows[1].window_position.y,
				glob_settings.subwindows[1].wh.width, glob_settings.subwindows[1].wh.height
			);
				glutDisplayFunc(display_subwindow_1);
				glutReshapeFunc(reshape_subwindow_1);
				subwindow_1_menu_init();

			glob_settings.subwindows[2].descriptor = glutCreateSubWindow(
				glob_settings.main_window.descriptor,
				glob_settings.subwindows[2].window_position.x, glob_settings.subwindows[2].window_position.y,
				glob_settings.subwindows[2].wh.width, glob_settings.subwindows[2].wh.height
			);
				glutDisplayFunc(display_subwindow_2);
				glutReshapeFunc(reshape_subwindow_2);
				glutSpecialFunc(subwindow_2_special_keys);
				glutMouseFunc(subwindow_2_mouse_pressed);
				subwindow_2_menu_init();

			glob_settings.subwindows[3].descriptor = glutCreateSubWindow(
				glob_settings.main_window.descriptor,
				glob_settings.subwindows[3].window_position.x, glob_settings.subwindows[3].window_position.y,
				glob_settings.subwindows[3].wh.width, glob_settings.subwindows[3].wh.height
			);
				glutDisplayFunc(display_subwindow_3);
				glutReshapeFunc(reshape_subwindow_3);
				glutSpecialFunc(subwindow_3_special_keys);
				glutMouseFunc(subwindow_3_mouse_pressed);
				subwindow_3_menu_init();
		}

		have_additional_sub_windows = true;

		log("Additional subwindows were built", RGB_BLACK);
	} else log("Additional subwindows were NOT built", RGB_BLACK);
}

void destroy_additional_subwindows() {

	if (have_additional_sub_windows == true && glob_settings.freeglut_settings.use_additional_subwindows == false) {

		if (have_additional_sub_windows) {
			glutDestroyWindow(glob_settings.subwindows[1].descriptor);
			glutDestroyWindow(glob_settings.subwindows[2].descriptor);
			glutDestroyWindow(glob_settings.subwindows[3].descriptor);
		}

		have_additional_sub_windows = false;

	}

}

void recalculation_subwindows_wh() {
	int x = glob_settings.main_window.wh.width;
	int y = glob_settings.main_window.wh.height;
	int gap = glob_settings.freeglut_settings.gap;

	if (have_additional_sub_windows && glob_settings.freeglut_settings.use_additional_subwindows) {

		glob_settings.subwindows[0].wh.width = x - 2 * gap;
		glob_settings.subwindows[0].wh.height = int((y - 3 * gap) * 0.75);

		glob_settings.subwindows[1].wh.width = int((y - 3 * gap) * 0.25);
		glob_settings.subwindows[1].wh.height = int((y - 3 * gap) * 0.25);


		//int temp = x - glob_settings.subwindows[1].wh.width - gap - gap - gap - gap;
		int temp = x - int((y - 3 * gap) * 0.25) - gap - gap - gap - gap;

		glob_settings.subwindows[2].wh.width = int(temp * 0.5);
		glob_settings.subwindows[2].wh.height = int((y - 3 * gap) * 0.25);

		glob_settings.subwindows[3].wh.width = int(temp * 0.5);
		glob_settings.subwindows[3].wh.height = int((y - 3 * gap) * 0.25);

		glob_settings.subwindows[0].window_position.x = gap;
		glob_settings.subwindows[0].window_position.y = gap;

		glob_settings.subwindows[1].window_position.x = gap;
		glob_settings.subwindows[1].window_position.y = gap + glob_settings.subwindows[0].wh.height + gap;

		glob_settings.subwindows[2].window_position.x = gap + glob_settings.subwindows[1].wh.width + gap;
		glob_settings.subwindows[2].window_position.y = gap + glob_settings.subwindows[0].wh.height + gap;

		glob_settings.subwindows[3].window_position.x = gap + glob_settings.subwindows[1].wh.width + gap + glob_settings.subwindows[2].wh.width + gap;
		glob_settings.subwindows[3].window_position.y = gap + glob_settings.subwindows[0].wh.height + gap;
	} else {
		glob_settings.subwindows[0].wh.width = x - 2 * gap;
		glob_settings.subwindows[0].wh.height = y - 2 * gap;

		glob_settings.subwindows[0].window_position.x = gap;
		glob_settings.subwindows[0].window_position.y = gap;
	}

	log("Subwindows were recalculated", RGB_BLACK);
}

void reshape_reposition_subwindows() {

	if (have_additional_sub_windows) {
		for (const auto& subw : glob_settings.subwindows) {
			glutSetWindow(subw.descriptor);
				glutPositionWindow(subw.window_position.x, subw.window_position.y);
				glutReshapeWindow(subw.wh.width, subw.wh.height);
		}
	} else {
		glutSetWindow(glob_settings.subwindows[0].descriptor);
			glutPositionWindow(glob_settings.subwindows[0].window_position.x, glob_settings.subwindows[0].window_position.y);
			glutReshapeWindow(glob_settings.subwindows[0].wh.width, glob_settings.subwindows[0].wh.height);
	}

	glutSetWindow(glob_settings.main_window.descriptor);

	log("Subwindows were reshaped and relocated", RGB_BLACK);
}

void postRedisplay() {
	glutSetWindow(glob_settings.main_window.descriptor);
		glutPostRedisplay();
	
	if (have_additional_sub_windows) {
		for (const auto& x : glob_settings.subwindows) {
			glutSetWindow(x.descriptor);
				glutPostRedisplay();
		}
	} else {
		glutSetWindow(glob_settings.subwindows[0].descriptor);
			glutPostRedisplay();
	}

	glutSetWindow(glob_settings.main_window.descriptor);
}

void display_subwindow_0() {

	glClearColor(glob_settings.subwindows[0].backgroundcolor.red, glob_settings.subwindows[0].backgroundcolor.green, glob_settings.subwindows[0].backgroundcolor.blue, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (glob_settings.freeglut_settings.shape == VVIS_SHAPE_NOTHING || glob_vct.size() == 0) {
	
		glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluOrtho2D(0.0, glob_settings.subwindows[0].wh.width, 0.0, glob_settings.subwindows[0].wh.height);
			glColor3f(0.0, 0.0, 0.0);

		glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glColor3f(0.0, 0.0, 0.0);
			glLoadIdentity();
			glRasterPos2i(0.0, glob_settings.subwindows[0].wh.height / 2);
				[](std::string text) {int len = text.length(); for (int i = 0; i < len; ++i) glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]); }("NOTHING TO DISPLAY");
		glPopMatrix();

		glFlush();
		glutSwapBuffers();

	} else {
	
		glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			gluLookAt(
				glob_settings.freeglut_settings.position_of_camera.x, glob_settings.freeglut_settings.position_of_camera.y, glob_settings.freeglut_settings.position_of_camera.z,		//
				glob_settings.freeglut_settings.position_of_element.x, glob_settings.freeglut_settings.position_of_element.y, glob_settings.freeglut_settings.position_of_element.z,		//
				0., 1., 0.
			);

		glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
		
			glOrtho(
				-(double(glob_settings.subwindows[0].wh.width) / 2.) * double(glob_settings.freeglut_settings.estrangement), (double(glob_settings.subwindows[0].wh.width) / 2.) * double(glob_settings.freeglut_settings.estrangement),
				-(double(glob_settings.subwindows[0].wh.height) / 2.) * abs(double(glob_settings.freeglut_settings.estrangement)), (double(glob_settings.subwindows[0].wh.height) / 2.) * abs(double(glob_settings.freeglut_settings.estrangement)),
				-100000.0, 100000.0
			);
		
		glMatrixMode(GL_MODELVIEW);

		if (glob_settings.freeglut_settings.beta_light && !glob_settings.freeglut_settings.coloring_sample) {

			glEnable(GL_LIGHTING); //рассчёт освещения
			glEnable(GL_LIGHT0); // источник

			glEnable(GL_NORMALIZE);
			glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
			//float direction[] = { 0.0, 0.0, -1.0, 0.0 };
			GLfloat direction[] = { 0.0, 0.0, 1.0, 0.0 };
			GLfloat params1[] = { 1.0, 0.0, 0.0, 0.0 };
			GLfloat params2[] = { 0.0, 1.0, 0.0, 0.0 };
			GLenum position = (0.0, 0.0, 0.0, 0.0);
			GLfloat s1[] = { 0.0 };
			GLfloat s2[] = { 0.0 };

			glMaterialfv(GL_FRONT, GL_SPECULAR, params1);
			glMaterialfv(GL_FRONT, GL_SHININESS, s1);
			glMaterialfv(GL_BACK, GL_SPECULAR, params2);
			glMaterialfv(GL_BACK, GL_SHININESS, s2);
			glLightfv(GL_LIGHT0, position, direction);

			
		} else {
			glDisable(GL_LIGHTING);
		}


		if (glob_settings.global_settings.index_of_spin == VVIS_DRAW_ALL) {
				
			size_t size_of_vector = glob_vct.size();
				
			for (unsigned int i = 0; i < size_of_vector; ++i) {
				if (i % glob_settings.freeglut_settings.spinrate == 0) draw_shape(i);
			}

			//log(std::string("Drawed " + std::to_string(size_of_vector/glob_settings.spinrate) + " spins"), RGB_BLACK);

		} else {
			draw_shape(glob_settings.global_settings.index_of_spin);

			//log(std::string("Drawed " + std::to_string(glob_settings.global_settings.index_of_spin) + " spin"), RGB_BLACK);
		}

		

		glFlush();
		glutSwapBuffers();

	}
}

void draw_shape(int index) {
	Shape* shape = NULL; double args_for_draw[5]; // 5 - max

	Vertex current_vertex = glob_vct[index];

	switch (glob_settings.freeglut_settings.shape) {

		case VVIS_SHAPE_CONE:
			shape = new Cone(current_vertex);

			args_for_draw[0] = 0.005 * glob_settings.freeglut_settings.scaling_parameters.x;		//
			args_for_draw[1] = 0.05 * glob_settings.freeglut_settings.scaling_parameters.y;		//
			args_for_draw[2] = glob_settings.freeglut_settings.polygonrate;
			args_for_draw[3] = glob_settings.freeglut_settings.polygonrate;
			break;


		case VVIS_SHAPE_SPHERE :
			shape = new Sphere(current_vertex);

			args_for_draw[0] = 0.009 * glob_settings.freeglut_settings.scaling_parameters.x;
			args_for_draw[1] = glob_settings.freeglut_settings.polygonrate;
			args_for_draw[2] = glob_settings.freeglut_settings.polygonrate;

			break;

		case VVIS_SHAPE_ARROW :
			shape = new Arrow(current_vertex);

			args_for_draw[0] = 0.004 * glob_settings.freeglut_settings.scaling_parameters.x;		//
			args_for_draw[1] = 0.025 * glob_settings.freeglut_settings.scaling_parameters.y;		//
			args_for_draw[2] = glob_settings.freeglut_settings.polygonrate;
			args_for_draw[3] = glob_settings.freeglut_settings.polygonrate;
			args_for_draw[4] = 0.003 * glob_settings.freeglut_settings.scaling_parameters.x; // sphere

			break;
		
		default: 

			shape = new Cone(current_vertex);

			args_for_draw[0] = 0.005 * glob_settings.freeglut_settings.scaling_parameters.x;		//
			args_for_draw[1] = 0.05 * glob_settings.freeglut_settings.scaling_parameters.y;		//
			args_for_draw[2] = glob_settings.freeglut_settings.polygonrate;
			args_for_draw[3] = glob_settings.freeglut_settings.polygonrate;

			break;

	}

	glPushMatrix();

	glTranslated(0, 0, glob_settings.freeglut_settings.position_of_element.z);

	glTranslated(glob_settings.freeglut_settings.global_translation.x, glob_settings.freeglut_settings.global_translation.y, glob_settings.freeglut_settings.global_translation.z); 
	glTranslated(-glob_settings.freeglut_settings.position_of_camera.x, -glob_settings.freeglut_settings.position_of_camera.y, -glob_settings.freeglut_settings.position_of_camera.z);


	shape->set_draw_configuration(); 

	glRotated(glob_settings.freeglut_settings.additional_rotation.phi, 0, 1, 0); 
	glRotatef(glob_settings.freeglut_settings.additional_rotation.theta, 1, 0, 0);

	glTranslated(
		current_vertex.point.x * glob_settings.freeglut_settings.scaling_translation.x,
		current_vertex.point.y * glob_settings.freeglut_settings.scaling_translation.y,
		current_vertex.point.z * glob_settings.freeglut_settings.scaling_translation.z);

	Rgb color_config(0.0, 0.0, 0.0);

	if (glob_settings.freeglut_settings.coloring_sample) {
		color_config = get_color_by_direction(current_vertex.spin.x, current_vertex.spin.y, current_vertex.spin.z);
	}

	shape->draw(color_config, args_for_draw);

	glPopMatrix();

	delete shape;

}

void subwindow_0_menu_init() {
	int _main_menu_render = glutCreateMenu(subwindow_0_menu);

	int _menu_movements_by_arrows = glutCreateMenu(menu_movements_by_arrows);
	int _menu_movements_by_wasd = glutCreateMenu(menu_movements_by_wasd);
	int _menu_movements_by_ijkl = glutCreateMenu(menu_movements_by_ijkl);
	int _menu_movements_by_shiftspace = glutCreateMenu(menu_movements_by_shiftspace);
	int _menu_scaling = glutCreateMenu(menu_scaling);
	int _menu_color = glutCreateMenu(menu_color);
	int _menu_settings = glutCreateMenu(menu_settings);
	int _menu_spinrate = glutCreateMenu(menu_spinrate);
	int _menu_spinrate_set = glutCreateMenu(menu_spinrate_set);
	int _menu_spinrate_set_1_10 = glutCreateMenu(menu_spinrate_set_1_10);
	int _menu_spinrate_set_11_20 = glutCreateMenu(menu_spinrate_set_11_20);
	int _menu_spinrate_set_21_30 = glutCreateMenu(menu_spinrate_set_21_30);
	int _menu_background = glutCreateMenu(menu_background_sub0);
	int _menu_shape = glutCreateMenu(menu_shape);
	int _menu_polygon = glutCreateMenu(menu_polygon);

	char buff[256];

	glutSetMenu(_menu_movements_by_arrows);
		glutAddMenuEntry("Inrease sensivity", MENU_RENDER_MOVEMENTS_BY_ARROWS_INCREASE_SENSIVITY);
		glutAddMenuEntry("Decrease sensivity", MENU_RENDER_MOVEMENTS_BY_ARROWS_DECREASE_SENSIVITY);
		glutAddMenuEntry("Press UP", MENU_RENDER_MOVEMENTS_BY_ARROWS_PRESS_UP);
		glutAddMenuEntry("Press DOWN", MENU_RENDER_MOVEMENTS_BY_ARROWS_PRESS_DOWN);
		glutAddMenuEntry("Press LEFT", MENU_RENDER_MOVEMENTS_BY_ARROWS_PRESS_LEFT);
		glutAddMenuEntry("Press RIGHT", MENU_RENDER_MOVEMENTS_BY_ARROWS_PRESS_RIGHT);

	glutSetMenu(_menu_movements_by_wasd);
		glutAddMenuEntry("Inrease sensivity", MENU_RENDER_MOVEMENTS_BY_WASD_INCREASE_SENSIVITY);
		glutAddMenuEntry("Decrease sensivity", MENU_RENDER_MOVEMENTS_BY_WASD_DECREASE_SENSIVITY);
		glutAddMenuEntry("Press W", MENU_RENDER_MOVEMENTS_BY_WASD_PRESS_W);
		glutAddMenuEntry("Press A", MENU_RENDER_MOVEMENTS_BY_WASD_PRESS_A);
		glutAddMenuEntry("Press S", MENU_RENDER_MOVEMENTS_BY_WASD_PRESS_S);
		glutAddMenuEntry("Press D", MENU_RENDER_MOVEMENTS_BY_WASD_PRESS_D);

	glutSetMenu(_menu_movements_by_ijkl);
		glutAddMenuEntry("Inrease sensivity", MENU_RENDER_MOVEMENTS_BY_IJKL_INCREASE_SENSIVITY);
		glutAddMenuEntry("Decrease sensivity", MENU_RENDER_MOVEMENTS_BY_IJKL_DECREASE_SENSIVITY);
		glutAddMenuEntry("Press I", MENU_RENDER_MOVEMENTS_BY_IJKL_PRESS_I);
		glutAddMenuEntry("Press J", MENU_RENDER_MOVEMENTS_BY_IJKL_PRESS_J);
		glutAddMenuEntry("Press K", MENU_RENDER_MOVEMENTS_BY_IJKL_PRESS_K);
		glutAddMenuEntry("Press L", MENU_RENDER_MOVEMENTS_BY_IJKL_PRESS_L);

	glutSetMenu(_menu_movements_by_shiftspace);
		glutAddMenuEntry("Inrease sensivity", MENU_RENDER_MOVEMENTS_BY_SHIFTSPACE_INCREASE_SENSIVITY);
		glutAddMenuEntry("Decrease sensivity", MENU_RENDER_MOVEMENTS_BY_SHIFTSPACE_DECREASE_SENSIVITY);
		glutAddMenuEntry("Press SHIFT", MENU_RENDER_MOVEMENTS_BY_SHIFTSPACE_PRESS_SHIFT);
		glutAddMenuEntry("Press SPACE", MENU_RENDER_MOVEMENTS_BY_SHIFTSPACE_PRESS_SPACE);

	glutSetMenu(_menu_scaling);
		glutAddMenuEntry("Inrease sensivity", MENU_RENDER_SCALING_INCREASE_SENSIVITY);
		glutAddMenuEntry("Decrease sensivity", MENU_RENDER_SCALING_DECREASE_SENSIVITY);
		glutAddMenuEntry("Press PAGE UP", MENU_RENDER_SCALING_PRESS_PAGE_UP);
		glutAddMenuEntry("Press PAGE DOWN", MENU_RENDER_SCALING_PRESS_PAGE_DOWN);

	glutSetMenu(_menu_color);
		glutAddMenuEntry("ON", MENU_COLOR_OO_ON);
		glutAddMenuEntry("OFF", MENU_COLOR_OO_OFF);

	glutSetMenu(_menu_settings);
		glutAddMenuEntry("Save", MENU_SETTINGS_GS_SAVE);
		glutAddMenuEntry("Get", MENU_SETTINGS_GS_GET);
		glutAddMenuEntry("Reset", MENU_SETTINGS_GS_RESET);
		glutAddMenuEntry("Reset file", MENU_SETTINGS_GS_RESET_FILE);

	glutSetMenu(_menu_spinrate_set_1_10);
		glutAddMenuEntry("1", MENU_RENDER_SPINRATE_1);
		glutAddMenuEntry("2", MENU_RENDER_SPINRATE_2);
		glutAddMenuEntry("3", MENU_RENDER_SPINRATE_3);
		glutAddMenuEntry("4", MENU_RENDER_SPINRATE_4);
		glutAddMenuEntry("5", MENU_RENDER_SPINRATE_5);
		glutAddMenuEntry("6", MENU_RENDER_SPINRATE_6);
		glutAddMenuEntry("7", MENU_RENDER_SPINRATE_7);
		glutAddMenuEntry("8", MENU_RENDER_SPINRATE_8);
		glutAddMenuEntry("9", MENU_RENDER_SPINRATE_9);
		glutAddMenuEntry("10", MENU_RENDER_SPINRATE_10);

	glutSetMenu(_menu_spinrate_set_11_20);
		glutAddMenuEntry("11", MENU_RENDER_SPINRATE_11);
		glutAddMenuEntry("12", MENU_RENDER_SPINRATE_12);
		glutAddMenuEntry("13", MENU_RENDER_SPINRATE_13);
		glutAddMenuEntry("14", MENU_RENDER_SPINRATE_14);
		glutAddMenuEntry("15", MENU_RENDER_SPINRATE_15);
		glutAddMenuEntry("16", MENU_RENDER_SPINRATE_16);
		glutAddMenuEntry("17", MENU_RENDER_SPINRATE_17);
		glutAddMenuEntry("18", MENU_RENDER_SPINRATE_18);
		glutAddMenuEntry("19", MENU_RENDER_SPINRATE_19);
		glutAddMenuEntry("20", MENU_RENDER_SPINRATE_20);

	glutSetMenu(_menu_spinrate_set_21_30);
		glutAddMenuEntry("21", MENU_RENDER_SPINRATE_21);
		glutAddMenuEntry("22", MENU_RENDER_SPINRATE_22);
		glutAddMenuEntry("23", MENU_RENDER_SPINRATE_23);
		glutAddMenuEntry("24", MENU_RENDER_SPINRATE_24);
		glutAddMenuEntry("25", MENU_RENDER_SPINRATE_25);
		glutAddMenuEntry("26", MENU_RENDER_SPINRATE_26);
		glutAddMenuEntry("27", MENU_RENDER_SPINRATE_27);
		glutAddMenuEntry("28", MENU_RENDER_SPINRATE_28);
		glutAddMenuEntry("29", MENU_RENDER_SPINRATE_29);
		glutAddMenuEntry("30", MENU_RENDER_SPINRATE_30);

	glutSetMenu(_menu_spinrate_set);
		glutAddSubMenu("1-10", _menu_spinrate_set_1_10);
		glutAddSubMenu("11-20", _menu_spinrate_set_11_20);
		glutAddSubMenu("21-30", _menu_spinrate_set_21_30);
		glutAddMenuEntry("I want count of spins < 10 000", MENU_RENDER_SPINRATE);

	glutSetMenu(_menu_spinrate);
		glutAddMenuEntry("Increase by 1", MENU_RENDER_INCREASE_SPINRATE_BY_1);
		glutAddMenuEntry("Decreasy by 1", MENU_RENDER_DECREASE_SPINRATE_BY_1);
		glutAddSubMenu("SET", _menu_spinrate_set);

	glutSetMenu(_menu_background);
		sprintf(buff, "White: (%g/255, %g/255, %g/255)", colors[L"white"].red * 255.0, colors[L"white"].green * 255.0, colors[L"white"].blue * 255.0);
		glutAddMenuEntry(buff, MENU_COLORING_BACKGROUND_WHITE);
		sprintf(buff, "Red: (%g/255, %g/255, %g/255)", colors[L"red"].red * 255.0, colors[L"red"].green * 255.0, colors[L"red"].blue * 255.0);
		glutAddMenuEntry(buff, MENU_COLORING_BACKGROUND_RED);
		sprintf(buff, "Green: (%g/255, %g/255, %g/255)", colors[L"green"].red * 255.0, colors[L"green"].green * 255.0, colors[L"green"].blue * 255.0);
		glutAddMenuEntry(buff, MENU_COLORING_BACKGROUND_GREEN);
		sprintf(buff, "Blue: (%g/255, %g/255, %g/255)", colors[L"blue"].red * 255.0, colors[L"blue"].green * 255.0, colors[L"blue"].blue * 255.0);
		glutAddMenuEntry(buff, MENU_COLORING_BACKGROUND_BLUE);
		sprintf(buff, "Light blue: (%g/255, %g/255, %g/255)", colors[L"lightblue"].red * 255.0, colors[L"lightblue"].green * 255.0, colors[L"lightblue"].blue * 255.0);
		glutAddMenuEntry(buff, MENU_COLORING_BACKGROUND_LIGHTBLUE);
		sprintf(buff, "Black: (%g/255, %g/255, %g/255)", colors[L"black"].red * 255.0, colors[L"black"].green * 255.0, colors[L"black"].blue * 255.0);
		glutAddMenuEntry(buff, MENU_COLORING_BACKGROUND_BLACK);
		sprintf(buff, "Light grey: (%g/255, %g/255, %g/255)", colors[L"lightgrey"].red * 255.0, colors[L"lightgrey"].green * 255.0, colors[L"lightgrey"].blue * 255.0);
		glutAddMenuEntry(buff, MENU_COLORING_BACKGROUND_LIGHTGREY);
		sprintf(buff, "As main was: (%g/255, %g/255, %g/255)", colors[L"main"].red * 255.0, colors[L"main"].green * 255.0, colors[L"main"].blue * 255.0);
		glutAddMenuEntry(buff, MENU_COLORING_BACKGROUND_MAIN);
		sprintf(buff, "As drawer area was: (%g/255, %g/255, %g/255)", colors[L"sub0"].red * 255.0, colors[L"sub0"].green * 255.0, colors[L"sub0"].blue * 255.0);
		glutAddMenuEntry(buff, MENU_COLORING_BACKGROUND_SUB0);
		sprintf(buff, "As axis area was: (%g/255, %g/255, %g/255)", colors[L"sub1"].red * 255.0, colors[L"sub1"].green * 255.0, colors[L"sub1"].blue * 255.0);
		glutAddMenuEntry(buff, MENU_COLORING_BACKGROUND_SUB1);
		sprintf(buff, "As stats area was: (%g/255, %g/255, %g/255)", colors[L"sub2"].red * 255.0, colors[L"sub2"].green * 255.0, colors[L"sub2"].blue * 255.0);
		glutAddMenuEntry(buff, MENU_COLORING_BACKGROUND_SUB2);
		sprintf(buff, "As log area was: (%g/255, %g/255, %g/255)", colors[L"sub3"].red * 255.0, colors[L"sub3"].green * 255.0, colors[L"sub3"].blue * 255.0);
		glutAddMenuEntry(buff, MENU_COLORING_BACKGROUND_SUB3);


	glutSetMenu(_menu_shape);
		glutAddMenuEntry("Nothing", VVIS_SHAPE_NOTHING);
		glutAddMenuEntry("Cone", VVIS_SHAPE_CONE);
		glutAddMenuEntry("Sphere", VVIS_SHAPE_SPHERE);
		glutAddMenuEntry("Arrow", VVIS_SHAPE_ARROW);


	glutSetMenu(_menu_polygon);
		glutAddMenuEntry("Increase by 1", MENU_INCREASE_POLYGON_BY_1);
		glutAddMenuEntry("Decrease by 1", MENU_DECREASE_POLYGON_BY_1);
		glutAddMenuEntry("Set 5", MENU_SET_POLYGON_5);
		glutAddMenuEntry("Set 10", MENU_SET_POLYGON_10);
		glutAddMenuEntry("Set 15", MENU_SET_POLYGON_15);
		glutAddMenuEntry("Set 20", MENU_SET_POLYGON_20);


	glutSetMenu(_main_menu_render);
		glutAddSubMenu("Movements by arrows", _menu_movements_by_arrows);
		glutAddSubMenu("Movements by wasd", _menu_movements_by_wasd);
		glutAddSubMenu("Movements by ijkl", _menu_movements_by_ijkl);
		glutAddSubMenu("Movements by shift(lctrl)/space", _menu_movements_by_shiftspace);
		glutAddSubMenu("Scaling parameters by pageup/pagedown", _menu_scaling);
		glutAddSubMenu("Coloring", _menu_color);
		glutAddSubMenu("Settings", _menu_settings);
		glutAddSubMenu("Spin rate", _menu_spinrate);
		glutAddSubMenu("Background color", _menu_background);
		glutAddSubMenu("Shape", _menu_shape);
		glutAddSubMenu("Polygon rate", _menu_polygon);
		glutAddMenuEntry("Invert control", MENU_RENDER_INVERT_CONTROL);
		glutAddMenuEntry("Restore gap=7", MENU_RENDER_RESTORE_GAP);
		glutAddMenuEntry("Lighting on/off (beta)", MENU_RENDER_LIGHTING);


	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutDetachMenu(GLUT_LEFT_BUTTON);

	log("Sub0 menu was initialized", RGB_BLACK);

}

void subwindow_0_menu(int code) {
	
	switch (code) {

		case MENU_RENDER_INVERT_CONTROL: glob_settings.freeglut_settings.translation_by_element *= -1; 
			log("Control inverted", RGB_BLUE);
			postRedisplay();
			break;

		case MENU_RENDER_RESTORE_GAP: glob_settings.freeglut_settings.gap = 7;
			log("GAP has been restored to 7", RGB_BLUE);
			recalculation_subwindows_wh();
			reshape_reposition_subwindows();
			postRedisplay();
			
			break;

		case MENU_RENDER_LIGHTING: glob_settings.freeglut_settings.beta_light = !glob_settings.freeglut_settings.beta_light;
			if (glob_settings.freeglut_settings.beta_light) log("Beta lighting was enabled", RGB_RED);
			else log("Beta lighting was disabled", RGB_GREEN);
			postRedisplay();

		default:
			break;
	}

}

void menu_movements_by_arrows(int code) {
	
	switch (code) {

		case MENU_RENDER_MOVEMENTS_BY_ARROWS_INCREASE_SENSIVITY: 
			glob_settings.freeglut_settings.translation_changes.x *= MOVEMENTS_BY_ARROWS_MULTIPLY_SENSIVITY;
			glob_settings.freeglut_settings.translation_changes.y *= MOVEMENTS_BY_ARROWS_MULTIPLY_SENSIVITY;
			glob_settings.freeglut_settings.translation_changes.z *= MOVEMENTS_BY_ARROWS_MULTIPLY_SENSIVITY;
			log("Sensivity of movements by arrow was increased", RGB_BLUE);
			postRedisplay();
			break;

		case MENU_RENDER_MOVEMENTS_BY_ARROWS_DECREASE_SENSIVITY:
			glob_settings.freeglut_settings.translation_changes.x /= MOVEMENTS_BY_ARROWS_MULTIPLY_SENSIVITY;
			glob_settings.freeglut_settings.translation_changes.y /= MOVEMENTS_BY_ARROWS_MULTIPLY_SENSIVITY;
			glob_settings.freeglut_settings.translation_changes.z /= MOVEMENTS_BY_ARROWS_MULTIPLY_SENSIVITY;
			log("Sensivity of movements by arrow was decreased", RGB_BLUE);
			postRedisplay();
			break;

		case MENU_RENDER_MOVEMENTS_BY_ARROWS_PRESS_UP: 
			special_keys(GLUT_KEY_UP, 0, 0);
			break;

		case MENU_RENDER_MOVEMENTS_BY_ARROWS_PRESS_DOWN: 
			special_keys(GLUT_KEY_DOWN, 0, 0);
			break;

		case MENU_RENDER_MOVEMENTS_BY_ARROWS_PRESS_LEFT: 
			special_keys(GLUT_KEY_LEFT, 0, 0);
			break;

		case MENU_RENDER_MOVEMENTS_BY_ARROWS_PRESS_RIGHT: 
			special_keys(GLUT_KEY_RIGHT, 0, 0);
			break;

		default:
			break;
	}

}

void menu_movements_by_wasd(int code) {

	switch (code) {

		case MENU_RENDER_MOVEMENTS_BY_WASD_INCREASE_SENSIVITY: 
			glob_settings.freeglut_settings.camera_changes.x *= MOVEMENTS_BY_WASD_MULTIPLY_SENSIVITY;
			glob_settings.freeglut_settings.camera_changes.y *= MOVEMENTS_BY_WASD_MULTIPLY_SENSIVITY;
			glob_settings.freeglut_settings.camera_changes.z *= MOVEMENTS_BY_WASD_MULTIPLY_SENSIVITY;
			log("Sensivity of movements by WASD was increased", RGB_BLUE);
			postRedisplay();
			break;

		case MENU_RENDER_MOVEMENTS_BY_WASD_DECREASE_SENSIVITY: 
			glob_settings.freeglut_settings.camera_changes.x /= MOVEMENTS_BY_WASD_MULTIPLY_SENSIVITY;
			glob_settings.freeglut_settings.camera_changes.y /= MOVEMENTS_BY_WASD_MULTIPLY_SENSIVITY;
			glob_settings.freeglut_settings.camera_changes.z /= MOVEMENTS_BY_WASD_MULTIPLY_SENSIVITY;
			log("Sensivity of movements by WASD was decreased", RGB_BLUE);
			postRedisplay();
			break;

		case MENU_RENDER_MOVEMENTS_BY_WASD_PRESS_W:
			normal_keys('w', 0, 0);
			break;

		case MENU_RENDER_MOVEMENTS_BY_WASD_PRESS_A:
			normal_keys('a', 0, 0);
			break;

		case MENU_RENDER_MOVEMENTS_BY_WASD_PRESS_S:
			normal_keys('s', 0, 0);
			break;

		case MENU_RENDER_MOVEMENTS_BY_WASD_PRESS_D:
			normal_keys('d', 0, 0);
			break;

		default:
			break;

	}
}

void menu_movements_by_ijkl(int code) {

	switch (code) {

		case MENU_RENDER_MOVEMENTS_BY_IJKL_INCREASE_SENSIVITY: 
			glob_settings.freeglut_settings.camera_changes.x *= MOVEMENTS_BY_WASD_MULTIPLY_SENSIVITY;
			glob_settings.freeglut_settings.camera_changes.y *= MOVEMENTS_BY_WASD_MULTIPLY_SENSIVITY;
			glob_settings.freeglut_settings.camera_changes.z *= MOVEMENTS_BY_WASD_MULTIPLY_SENSIVITY;
			log("Sensivity of movements by IJKL was increased", RGB_BLUE);
			postRedisplay();
			break;

		case MENU_RENDER_MOVEMENTS_BY_IJKL_DECREASE_SENSIVITY: 
			glob_settings.freeglut_settings.camera_changes.x /= MOVEMENTS_BY_WASD_MULTIPLY_SENSIVITY;
			glob_settings.freeglut_settings.camera_changes.y /= MOVEMENTS_BY_WASD_MULTIPLY_SENSIVITY;
			glob_settings.freeglut_settings.camera_changes.z /= MOVEMENTS_BY_WASD_MULTIPLY_SENSIVITY;
			postRedisplay();
			log("Sensivity of movements by IJKL was decreased", RGB_BLUE);
			break;

		case MENU_RENDER_MOVEMENTS_BY_IJKL_PRESS_I: 
			normal_keys('i', 0, 0);
			break;

		case MENU_RENDER_MOVEMENTS_BY_IJKL_PRESS_J: 
			normal_keys('j', 0, 0);
			break;

		case MENU_RENDER_MOVEMENTS_BY_IJKL_PRESS_K: 
			normal_keys('k', 0, 0);
			break;

		case MENU_RENDER_MOVEMENTS_BY_IJKL_PRESS_L: 
			normal_keys('l', 0, 0);
			break;


		default:
			break;

	}

}

void menu_movements_by_shiftspace(int code) {

	switch (code) {

		case MENU_RENDER_MOVEMENTS_BY_SHIFTSPACE_INCREASE_SENSIVITY: 
			glob_settings.freeglut_settings.estrangement_changes *= MOVEMENTS_BY_SHIFTSPACE_MULTIPLY_SENSIVITY;
			log("Sensivity of movements by shift/space was increased", RGB_BLUE);
			postRedisplay();
			break;

		case MENU_RENDER_MOVEMENTS_BY_SHIFTSPACE_DECREASE_SENSIVITY: 
			glob_settings.freeglut_settings.estrangement_changes /= MOVEMENTS_BY_SHIFTSPACE_MULTIPLY_SENSIVITY;
			log("Sensivity of movements by shift/space was decreased", RGB_BLUE);
			postRedisplay();
			break;

		case MENU_RENDER_MOVEMENTS_BY_SHIFTSPACE_PRESS_SHIFT: 
			special_keys(GLUT_KEY_SHIFT_L, 0, 0);
			break;

		case MENU_RENDER_MOVEMENTS_BY_SHIFTSPACE_PRESS_SPACE: 
			normal_keys(' ', 0, 0);
			break;

		default:
			break;

	}

}

void menu_scaling(int code) {

	switch (code) {

		case MENU_RENDER_SCALING_INCREASE_SENSIVITY:
			glob_settings.freeglut_settings.scaling_parameters_changes.x *= SCALING_MULTIPLY_SENSIVITY_X;
			glob_settings.freeglut_settings.scaling_parameters_changes.y *= SCALING_MULTIPLY_SENSIVITY_Y;
			glob_settings.freeglut_settings.scaling_parameters_changes.z *= SCALING_MULTIPLY_SENSIVITY_Z;
			log("Sensivity of movements by page up/down was increased", RGB_BLUE);
			postRedisplay();
			break;

		case MENU_RENDER_SCALING_DECREASE_SENSIVITY:
			glob_settings.freeglut_settings.scaling_parameters_changes.x /= SCALING_MULTIPLY_SENSIVITY_X;
			glob_settings.freeglut_settings.scaling_parameters_changes.y /= SCALING_MULTIPLY_SENSIVITY_Y;
			glob_settings.freeglut_settings.scaling_parameters_changes.z /= SCALING_MULTIPLY_SENSIVITY_Z;
			log("Sensivity of movements by page up/down was decreased", RGB_BLUE);
			postRedisplay();
			break;

		case MENU_RENDER_SCALING_PRESS_PAGE_UP: 
			special_keys(GLUT_KEY_PAGE_UP, 0, 0);
			break;
			

		case MENU_RENDER_SCALING_PRESS_PAGE_DOWN: 
			special_keys(GLUT_KEY_PAGE_DOWN, 0, 0);
			break;

		default:
			break;

	}

}

void menu_color(int code) {

	switch (code) {

		case MENU_COLOR_OO_OFF:
			glob_settings.freeglut_settings.coloring_sample = false;
			log("Coloring mode: OFF", RGB_BLUE);
			postRedisplay();
			break;

		case MENU_COLOR_OO_ON:
			glob_settings.freeglut_settings.coloring_sample = true;
			log("Coloring mode: ON", RGB_BLUE);
			postRedisplay();
			break;

		default:
			break;
	}

}

void menu_settings(int code) {

	switch (code) {

		case MENU_SETTINGS_GS_SAVE:
			if (glob_settings.save(L'a')) log("Settings has been saved", RGB_GREEN); else log("Settings has NOT been saved", RGB_RED);
			postRedisplay();
			break;

		case MENU_SETTINGS_GS_GET: {
				int width = glob_settings.main_window.wh.width, height = glob_settings.main_window.wh.height;
				if (glob_settings.get(L'a')) log("Settings has been loaded", RGB_GREEN); else log("Settings has NOT been loaded", RGB_RED);
				glob_settings.main_window.wh.width = width; glob_settings.main_window.wh.height = height;
				
				recalculation_subwindows_wh(); 
				reshape_reposition_subwindows();
				postRedisplay();
		} break;

		case MENU_SETTINGS_GS_RESET: {
			glob_settings = Settings(glob_settings.global_settings, Freeglut_settings(), glob_settings.main_window, glob_settings.subwindows);

			glob_settings.main_window.backgroundcolor = colors[L"main"];
			glob_settings.subwindows[0].backgroundcolor = colors[L"sub0"];
			glob_settings.subwindows[1].backgroundcolor = colors[L"sub1"];
			glob_settings.subwindows[2].backgroundcolor = colors[L"sub2"];
			glob_settings.subwindows[3].backgroundcolor = colors[L"sub3"];

			log("Settings has been reseted", RGB_GREEN);
			recalculation_subwindows_wh();
			reshape_reposition_subwindows();
			postRedisplay();
		} break;

		case MENU_SETTINGS_GS_RESET_FILE: {
			Settings reseted_settings = Settings(glob_settings.global_settings, Freeglut_settings(), glob_settings.main_window, glob_settings.subwindows);
			reseted_settings.save(L'a');
			log("Settings has been reseted in file", RGB_BLUE);
			postRedisplay();
		} break;
	}

}

void menu_spinrate(int code) {

	switch(code) {
	
		case MENU_RENDER_INCREASE_SPINRATE_BY_1: glob_settings.freeglut_settings.spinrate += 1; log("Spinrate was increased by 1", RGB_BLUE); postRedisplay(); break;
		case MENU_RENDER_DECREASE_SPINRATE_BY_1: glob_settings.freeglut_settings.spinrate = glob_settings.freeglut_settings.spinrate == 1 ? 1 : glob_settings.freeglut_settings.spinrate -= 1; log("Spinrate was decreased by 1", RGB_BLUE); postRedisplay(); break;
	
		default: break;
	}

}

void menu_spinrate_set(int code) {

	switch (code) {

		case MENU_RENDER_SPINRATE: {

			int len = glob_vct.size(); int spinrate = 1;

			while (len / spinrate > 10000) {
				spinrate += 1;
			}

			glob_settings.freeglut_settings.spinrate = spinrate;

			log("AUTO Spinrate = " + std::to_string(glob_settings.freeglut_settings.spinrate), RGB_GREEN); postRedisplay();

		} break;

		default: break;

	}
}

void menu_spinrate_set_1_10(int code) {
	
	switch (code) {

		case MENU_RENDER_SPINRATE_1: glob_settings.freeglut_settings.spinrate = 1; log("Spinrate = " + std::to_string(glob_settings.freeglut_settings.spinrate), RGB_GREEN); postRedisplay(); break;
		case MENU_RENDER_SPINRATE_2: glob_settings.freeglut_settings.spinrate = 2; log("Spinrate = " + std::to_string(glob_settings.freeglut_settings.spinrate), RGB_GREEN); postRedisplay(); break;
		case MENU_RENDER_SPINRATE_3: glob_settings.freeglut_settings.spinrate = 3; log("Spinrate = " + std::to_string(glob_settings.freeglut_settings.spinrate), RGB_GREEN); postRedisplay(); break;
		case MENU_RENDER_SPINRATE_4: glob_settings.freeglut_settings.spinrate = 4; log("Spinrate = " + std::to_string(glob_settings.freeglut_settings.spinrate), RGB_GREEN); postRedisplay(); break;
		case MENU_RENDER_SPINRATE_5: glob_settings.freeglut_settings.spinrate = 5; log("Spinrate = " + std::to_string(glob_settings.freeglut_settings.spinrate), RGB_GREEN); postRedisplay(); break;
		case MENU_RENDER_SPINRATE_6: glob_settings.freeglut_settings.spinrate = 6; log("Spinrate = " + std::to_string(glob_settings.freeglut_settings.spinrate), RGB_GREEN); postRedisplay(); break;
		case MENU_RENDER_SPINRATE_7: glob_settings.freeglut_settings.spinrate = 7; log("Spinrate = " + std::to_string(glob_settings.freeglut_settings.spinrate), RGB_GREEN); postRedisplay(); break;
		case MENU_RENDER_SPINRATE_8: glob_settings.freeglut_settings.spinrate = 8; log("Spinrate = " + std::to_string(glob_settings.freeglut_settings.spinrate), RGB_GREEN); postRedisplay(); break;
		case MENU_RENDER_SPINRATE_9: glob_settings.freeglut_settings.spinrate = 9; log("Spinrate = " + std::to_string(glob_settings.freeglut_settings.spinrate), RGB_GREEN); postRedisplay(); break;
		case MENU_RENDER_SPINRATE_10: glob_settings.freeglut_settings.spinrate = 10; log("Spinrate = " + std::to_string(glob_settings.freeglut_settings.spinrate), RGB_GREEN); postRedisplay(); break;

		default: break;

	}
}

void menu_spinrate_set_11_20(int code) {
	
	switch (code) {

		case MENU_RENDER_SPINRATE_11: glob_settings.freeglut_settings.spinrate = 11; log("Spinrate = " + std::to_string(glob_settings.freeglut_settings.spinrate), RGB_GREEN); postRedisplay(); break;
		case MENU_RENDER_SPINRATE_12: glob_settings.freeglut_settings.spinrate = 12; log("Spinrate = " + std::to_string(glob_settings.freeglut_settings.spinrate), RGB_GREEN); postRedisplay(); break;
		case MENU_RENDER_SPINRATE_13: glob_settings.freeglut_settings.spinrate = 13; log("Spinrate = " + std::to_string(glob_settings.freeglut_settings.spinrate), RGB_GREEN); postRedisplay(); break;
		case MENU_RENDER_SPINRATE_14: glob_settings.freeglut_settings.spinrate = 14; log("Spinrate = " + std::to_string(glob_settings.freeglut_settings.spinrate), RGB_GREEN); postRedisplay(); break;
		case MENU_RENDER_SPINRATE_15: glob_settings.freeglut_settings.spinrate = 15; log("Spinrate = " + std::to_string(glob_settings.freeglut_settings.spinrate), RGB_GREEN); postRedisplay(); break;
		case MENU_RENDER_SPINRATE_16: glob_settings.freeglut_settings.spinrate = 16; log("Spinrate = " + std::to_string(glob_settings.freeglut_settings.spinrate), RGB_GREEN); postRedisplay(); break;
		case MENU_RENDER_SPINRATE_17: glob_settings.freeglut_settings.spinrate = 17; log("Spinrate = " + std::to_string(glob_settings.freeglut_settings.spinrate), RGB_GREEN); postRedisplay(); break;
		case MENU_RENDER_SPINRATE_18: glob_settings.freeglut_settings.spinrate = 18; log("Spinrate = " + std::to_string(glob_settings.freeglut_settings.spinrate), RGB_GREEN); postRedisplay(); break;
		case MENU_RENDER_SPINRATE_19: glob_settings.freeglut_settings.spinrate = 19; log("Spinrate = " + std::to_string(glob_settings.freeglut_settings.spinrate), RGB_GREEN); postRedisplay(); break;
		case MENU_RENDER_SPINRATE_20: glob_settings.freeglut_settings.spinrate = 20; log("Spinrate = " + std::to_string(glob_settings.freeglut_settings.spinrate), RGB_GREEN); postRedisplay(); break;

		default: break;

	}
}

void menu_spinrate_set_21_30(int code) {
		
	switch (code) {

		case MENU_RENDER_SPINRATE_21: glob_settings.freeglut_settings.spinrate = 21; log("Spinrate = " + std::to_string(glob_settings.freeglut_settings.spinrate), RGB_GREEN); postRedisplay(); break;
		case MENU_RENDER_SPINRATE_22: glob_settings.freeglut_settings.spinrate = 22; log("Spinrate = " + std::to_string(glob_settings.freeglut_settings.spinrate), RGB_GREEN); postRedisplay(); break;
		case MENU_RENDER_SPINRATE_23: glob_settings.freeglut_settings.spinrate = 23; log("Spinrate = " + std::to_string(glob_settings.freeglut_settings.spinrate), RGB_GREEN); postRedisplay(); break;
		case MENU_RENDER_SPINRATE_24: glob_settings.freeglut_settings.spinrate = 24; log("Spinrate = " + std::to_string(glob_settings.freeglut_settings.spinrate), RGB_GREEN); postRedisplay(); break;
		case MENU_RENDER_SPINRATE_25: glob_settings.freeglut_settings.spinrate = 25; log("Spinrate = " + std::to_string(glob_settings.freeglut_settings.spinrate), RGB_GREEN); postRedisplay(); break;
		case MENU_RENDER_SPINRATE_26: glob_settings.freeglut_settings.spinrate = 26; log("Spinrate = " + std::to_string(glob_settings.freeglut_settings.spinrate), RGB_GREEN); postRedisplay(); break;
		case MENU_RENDER_SPINRATE_27: glob_settings.freeglut_settings.spinrate = 27; log("Spinrate = " + std::to_string(glob_settings.freeglut_settings.spinrate), RGB_GREEN); postRedisplay(); break;
		case MENU_RENDER_SPINRATE_28: glob_settings.freeglut_settings.spinrate = 28; log("Spinrate = " + std::to_string(glob_settings.freeglut_settings.spinrate), RGB_GREEN); postRedisplay(); break;
		case MENU_RENDER_SPINRATE_29: glob_settings.freeglut_settings.spinrate = 29; log("Spinrate = " + std::to_string(glob_settings.freeglut_settings.spinrate), RGB_GREEN); postRedisplay(); break;
		case MENU_RENDER_SPINRATE_30: glob_settings.freeglut_settings.spinrate = 30; log("Spinrate = " + std::to_string(glob_settings.freeglut_settings.spinrate), RGB_GREEN); postRedisplay(); break;

		default: break;

	}
}

void menu_background_sub0(int code) {

	switch (code) {

		case MENU_COLORING_BACKGROUND_WHITE: glob_settings.subwindows[0].backgroundcolor = colors[L"white"]; log("Sub0 background color changed", RGB_BLUE); postRedisplay(); break;
		case MENU_COLORING_BACKGROUND_RED: glob_settings.subwindows[0].backgroundcolor = colors[L"red"]; log("Sub0 background color changed", RGB_BLUE); postRedisplay(); break;
		case MENU_COLORING_BACKGROUND_GREEN: glob_settings.subwindows[0].backgroundcolor = colors[L"green"]; log("Sub0 background color changed", RGB_BLUE); postRedisplay(); break;
		case MENU_COLORING_BACKGROUND_BLUE: glob_settings.subwindows[0].backgroundcolor = colors[L"blue"]; log("Sub0 background color changed", RGB_BLUE); postRedisplay(); break;
		case MENU_COLORING_BACKGROUND_LIGHTBLUE: glob_settings.subwindows[0].backgroundcolor = colors[L"lightblue"]; log("Sub0 background color changed", RGB_BLUE);  postRedisplay(); break;
		case MENU_COLORING_BACKGROUND_BLACK: glob_settings.subwindows[0].backgroundcolor = colors[L"black"]; log("Sub0 background color changed", RGB_BLUE);  postRedisplay(); break;
		case MENU_COLORING_BACKGROUND_LIGHTGREY: glob_settings.subwindows[0].backgroundcolor = colors[L"lightgrey"]; log("Sub0 background color changed", RGB_BLUE);  postRedisplay(); break;
		case MENU_COLORING_BACKGROUND_MAIN: glob_settings.subwindows[0].backgroundcolor = colors[L"main"]; log("Sub0 background color changed", RGB_BLUE);  postRedisplay(); break;
		case MENU_COLORING_BACKGROUND_SUB0: glob_settings.subwindows[0].backgroundcolor = colors[L"sub0"]; log("Sub0 background color changed", RGB_BLUE);  postRedisplay(); break;
		case MENU_COLORING_BACKGROUND_SUB1: glob_settings.subwindows[0].backgroundcolor = colors[L"sub1"]; log("Sub0 background color changed", RGB_BLUE);  postRedisplay(); break;
		case MENU_COLORING_BACKGROUND_SUB2: glob_settings.subwindows[0].backgroundcolor = colors[L"sub2"]; log("Sub0 background color changed", RGB_BLUE);  postRedisplay(); break;
		case MENU_COLORING_BACKGROUND_SUB3: glob_settings.subwindows[0].backgroundcolor = colors[L"sub3"]; log("Sub0 background color changed", RGB_BLUE);  postRedisplay(); break;
		
		default: break;

	}

}


void menu_shape(int code) {

	switch (code) {
	
		case VVIS_SHAPE_NOTHING: 
			glob_settings.freeglut_settings.shape = VVIS_SHAPE_NOTHING;
			glob_settings.freeglut_settings.shape_wstr = VVIS_SHAPE_NOTHING_WSTR;
			log("Shape was changed to nothing", RGB_GREEN);
			postRedisplay();
			break; 

		case VVIS_SHAPE_CONE:
			glob_settings.freeglut_settings.shape = VVIS_SHAPE_CONE;
			glob_settings.freeglut_settings.shape_wstr = VVIS_SHAPE_CONE_WSTR;
			log("Shape was changed to cone", RGB_GREEN);
			postRedisplay();
			break;

		case VVIS_SHAPE_SPHERE:
			glob_settings.freeglut_settings.shape = VVIS_SHAPE_SPHERE;
			glob_settings.freeglut_settings.shape_wstr = VVIS_SHAPE_SPHERE_WSTR;
			log("Shape was changed to sphere", RGB_GREEN);
			postRedisplay();
			break;

		case VVIS_SHAPE_ARROW:
			glob_settings.freeglut_settings.shape = VVIS_SHAPE_ARROW;
			glob_settings.freeglut_settings.shape_wstr = VVIS_SHAPE_ARROW_WSTR;
			log("Shape was changed to arrow", RGB_GREEN);
			postRedisplay();
			break;
	
		default: break;

	}


}


void menu_polygon(int code) {

	switch (code) {

		case MENU_INCREASE_POLYGON_BY_1:
			glob_settings.freeglut_settings.polygonrate += 1;
			log("Polygonrate was changed and now: " + std::to_string(glob_settings.freeglut_settings.polygonrate), RGB_GREEN);
			postRedisplay();
			break;

		case MENU_DECREASE_POLYGON_BY_1:
			glob_settings.freeglut_settings.polygonrate = glob_settings.freeglut_settings.polygonrate == 1 ? 1 : glob_settings.freeglut_settings.polygonrate - 1;
			log("Polygonrate was changed and now: " + std::to_string(glob_settings.freeglut_settings.polygonrate), RGB_GREEN);
			postRedisplay();
			break;
			
		case MENU_SET_POLYGON_5:
			glob_settings.freeglut_settings.polygonrate = 5;
			log("Polygonrate was changed and now: " + std::to_string(glob_settings.freeglut_settings.polygonrate), RGB_GREEN);
			postRedisplay();
			break;

		case MENU_SET_POLYGON_10:
			glob_settings.freeglut_settings.polygonrate = 10;
			log("Polygonrate was changed and now: " + std::to_string(glob_settings.freeglut_settings.polygonrate), RGB_GREEN);
			postRedisplay();
			break;
			
		case MENU_SET_POLYGON_15:
			glob_settings.freeglut_settings.polygonrate = 15;
			log("Polygonrate was changed and now: " + std::to_string(glob_settings.freeglut_settings.polygonrate), RGB_GREEN);
			postRedisplay();
			break;

		case MENU_SET_POLYGON_20:
			glob_settings.freeglut_settings.polygonrate = 20;
			log("Polygonrate was changed and now: " + std::to_string(glob_settings.freeglut_settings.polygonrate), RGB_GREEN);
			postRedisplay();
			break;



		default: break;

	}

}


void normal_keys(unsigned char key, int x, int y) {

	double t_b_e = glob_settings.freeglut_settings.translation_by_element;

	switch (key) {
	
		case 'w':	glob_settings.freeglut_settings.position_of_camera.y -= t_b_e * glob_settings.freeglut_settings.camera_changes.y; 
					glob_settings.freeglut_settings.position_of_element.y += t_b_e * glob_settings.freeglut_settings.camera_changes.y;
					postRedisplay();
					break;

		case 's':	glob_settings.freeglut_settings.position_of_camera.y += t_b_e * glob_settings.freeglut_settings.camera_changes.y;
					glob_settings.freeglut_settings.position_of_element.y -= t_b_e * glob_settings.freeglut_settings.camera_changes.y;
					postRedisplay();
					break;

		case 'a':	glob_settings.freeglut_settings.position_of_camera.x += t_b_e * glob_settings.freeglut_settings.camera_changes.x;
					glob_settings.freeglut_settings.position_of_element.x -= t_b_e * glob_settings.freeglut_settings.camera_changes.x;
					postRedisplay();
					break;

		case 'd':	glob_settings.freeglut_settings.position_of_camera.x -= t_b_e * glob_settings.freeglut_settings.camera_changes.x;
					glob_settings.freeglut_settings.position_of_element.x += t_b_e * glob_settings.freeglut_settings.camera_changes.x;
					postRedisplay();
					break;

		case 'i':	glob_settings.freeglut_settings.additional_rotation.theta -= t_b_e * glob_settings.freeglut_settings.camera_changes.y;
					postRedisplay();
					break;

		case 'k':	glob_settings.freeglut_settings.additional_rotation.theta += t_b_e * glob_settings.freeglut_settings.camera_changes.y;
					postRedisplay();
					break;
		
		case 'j':	glob_settings.freeglut_settings.additional_rotation.phi -= t_b_e * glob_settings.freeglut_settings.camera_changes.x;
					postRedisplay();
					break;
		
		case 'l':	glob_settings.freeglut_settings.additional_rotation.phi += t_b_e * glob_settings.freeglut_settings.camera_changes.x;
					postRedisplay();
					break;
		
		case ' ':	glob_settings.freeglut_settings.estrangement += glob_settings.freeglut_settings.estrangement_changes;
					postRedisplay();
					break;
		
		case 27:	glutLeaveMainLoop(); 
					break;

		default: 
					break;
	
	}


}

void special_keys(int key, int x, int y) {
	
	double t_b_e = glob_settings.freeglut_settings.translation_by_element;

	switch (key) {

		case GLUT_KEY_PAGE_UP:		glob_settings.freeglut_settings.scaling_parameters.x += glob_settings.freeglut_settings.scaling_parameters_changes.x;
									glob_settings.freeglut_settings.scaling_parameters.y += glob_settings.freeglut_settings.scaling_parameters_changes.y;
									glob_settings.freeglut_settings.scaling_parameters.z += glob_settings.freeglut_settings.scaling_parameters_changes.z;
									postRedisplay();
									break;

		case GLUT_KEY_PAGE_DOWN:	glob_settings.freeglut_settings.scaling_parameters.x -= glob_settings.freeglut_settings.scaling_parameters_changes.x;
									glob_settings.freeglut_settings.scaling_parameters.y -= glob_settings.freeglut_settings.scaling_parameters_changes.y;
									glob_settings.freeglut_settings.scaling_parameters.z -= glob_settings.freeglut_settings.scaling_parameters_changes.z;
									postRedisplay();
									break;
									
		case GLUT_KEY_LEFT:			glob_settings.freeglut_settings.global_translation.x -= t_b_e * glob_settings.freeglut_settings.translation_changes.x;
									postRedisplay();
									break;									

		case GLUT_KEY_RIGHT:		glob_settings.freeglut_settings.global_translation.x += t_b_e * glob_settings.freeglut_settings.translation_changes.x;
									postRedisplay();
									break;							

		case GLUT_KEY_UP:			glob_settings.freeglut_settings.global_translation.y += t_b_e * glob_settings.freeglut_settings.translation_changes.y;
									postRedisplay();
									break;		

		case GLUT_KEY_DOWN:			glob_settings.freeglut_settings.global_translation.y -= t_b_e * glob_settings.freeglut_settings.translation_changes.y;
									postRedisplay();
									break;

		case GLUT_KEY_CTRL_L:
		case GLUT_KEY_SHIFT_L:		glob_settings.freeglut_settings.estrangement -= glob_settings.freeglut_settings.estrangement_changes;
									postRedisplay();
									break;

		case GLUT_KEY_F11:			if (!glob_settings.freeglut_settings.fullscreen) { glutSetWindow(glob_settings.main_window.descriptor); glutFullScreen(); glob_settings.freeglut_settings.fullscreen = true;  glutSetWindow(glob_settings.subwindows[0].descriptor);
									log("Fullmode screen was enabled", RGB_BLUE);
									}
									else { glutSetWindow(glob_settings.main_window.descriptor); glutPositionWindow(0, 0); glob_settings.freeglut_settings.fullscreen = false; glutSetWindow(glob_settings.subwindows[0].descriptor); log("Fullmode screen was disabled", RGB_BLUE);
									};
									break;

		default:					
									break;

	}

}

void mouse_pressed(int button, int state, int x, int y) {

	// scroll up
	if (button == 3 && glutGetModifiers() == GLUT_ACTIVE_ALT) {
		glob_settings.freeglut_settings.scaling_parameters.x += glob_settings.freeglut_settings.scaling_parameters_changes.x;
		glob_settings.freeglut_settings.scaling_parameters.y += glob_settings.freeglut_settings.scaling_parameters_changes.y;
		glob_settings.freeglut_settings.scaling_parameters.z += glob_settings.freeglut_settings.scaling_parameters_changes.z;
		postRedisplay();
	} else if (button == 3) {
		glob_settings.freeglut_settings.estrangement -= 0.5 * glob_settings.freeglut_settings.estrangement_changes;
		postRedisplay();
	}
	
	// scroll down
	if (button == 4 && glutGetModifiers() == GLUT_ACTIVE_ALT) { 
		glob_settings.freeglut_settings.scaling_parameters.x -= glob_settings.freeglut_settings.scaling_parameters_changes.x;
		glob_settings.freeglut_settings.scaling_parameters.y -= glob_settings.freeglut_settings.scaling_parameters_changes.y;
		glob_settings.freeglut_settings.scaling_parameters.z -= glob_settings.freeglut_settings.scaling_parameters_changes.z;
		postRedisplay();
	} else if (button == 4) {
		glob_settings.freeglut_settings.estrangement += 0.5 * glob_settings.freeglut_settings.estrangement_changes;
		postRedisplay();
	}

	glob_settings.main_window.arrow.pressed_position_x = x;
	glob_settings.main_window.arrow.pressed_position_y = y;
}

void passive_mouse_motion(int x, int y) {
	glob_settings.main_window.arrow.x = x;
	glob_settings.main_window.arrow.y = y;
}

void pressed_mouse_motion(int x, int y) {

	double t_b_e = glob_settings.freeglut_settings.translation_by_element;

	if (x > glob_settings.main_window.arrow.x && glutGetModifiers() == GLUT_ACTIVE_ALT) {
		glob_settings.freeglut_settings.additional_rotation.phi -= t_b_e * 2.0 * glob_settings.freeglut_settings.camera_changes.x;
		postRedisplay();
	} else if (x > glob_settings.main_window.arrow.x) {
		glob_settings.freeglut_settings.global_translation.x -= t_b_e * 2.0 * glob_settings.freeglut_settings.translation_changes.x;
		postRedisplay();
	}

	if (x < glob_settings.main_window.arrow.x && glutGetModifiers() == GLUT_ACTIVE_ALT) {
		glob_settings.freeglut_settings.additional_rotation.phi += t_b_e * 2.0 * glob_settings.freeglut_settings.camera_changes.x;
		postRedisplay();
	} else if (x < glob_settings.main_window.arrow.x) {
		glob_settings.freeglut_settings.global_translation.x += t_b_e * 2.0 * glob_settings.freeglut_settings.translation_changes.x;
		postRedisplay();
	}

	if (y > glob_settings.main_window.arrow.y && glutGetModifiers() == GLUT_ACTIVE_ALT) {
		glob_settings.freeglut_settings.additional_rotation.theta -= t_b_e * 2.0 * glob_settings.freeglut_settings.camera_changes.y;
		postRedisplay();
	} else if (y > glob_settings.main_window.arrow.y) {
		glob_settings.freeglut_settings.global_translation.y += t_b_e * 2.0 * glob_settings.freeglut_settings.translation_changes.y;
		postRedisplay();
	}

	if (y < glob_settings.main_window.arrow.y && glutGetModifiers() == GLUT_ACTIVE_ALT) {
		glob_settings.freeglut_settings.additional_rotation.theta += t_b_e * 2.0 * glob_settings.freeglut_settings.camera_changes.y;
		postRedisplay();
	} else if (y < glob_settings.main_window.arrow.y) {
		glob_settings.freeglut_settings.global_translation.y -= t_b_e * 2.0 * glob_settings.freeglut_settings.translation_changes.y;
		postRedisplay();
	}



	glob_settings.main_window.arrow.x = x;
	glob_settings.main_window.arrow.y = y;
}

void display_subwindow_1() {
	glClearColor(glob_settings.subwindows[1].backgroundcolor.red, glob_settings.subwindows[1].backgroundcolor.green, glob_settings.subwindows[1].backgroundcolor.blue, 1.0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		gluLookAt(
			glob_settings.freeglut_settings.position_of_camera.x, glob_settings.freeglut_settings.position_of_camera.y, glob_settings.freeglut_settings.position_of_camera.z,		//
			0., 0., -100.0,		//
			0., 1., 0.
		);

	glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		double estrangement = 0.7;
		if (glob_settings.freeglut_settings.estrangement < 0) estrangement = -estrangement;

		//glOrtho(
		//	-(double(glob_settings.subwindows[1].wh.width) / 2.) * estrangement, (double(glob_settings.subwindows[1].wh.width) / 2.) * estrangement,
		//	-(double(glob_settings.subwindows[1].wh.height) / 2.) * abs(estrangement), (double(glob_settings.subwindows[1].wh.height) / 2.) * abs(estrangement),
		//	-100000.0, 100000.0
		//);

		glFrustum(
			-1.0 * estrangement, 1.0 * estrangement,
			-1.0 * abs(estrangement), 1.0 * abs(estrangement),
			1.0, 1000.0
		);

	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();

	glTranslated(0., 0., -100.0);
	glRotated(glob_settings.freeglut_settings.additional_rotation.phi, 0, 1, 0);
	glRotatef(glob_settings.freeglut_settings.additional_rotation.theta, 1, 0, 0);

	if (glob_settings.other_settings.axis_by_cones) {
		draw_axis_by_cones();
	} else {
		draw_axis_by_lines();
	}

	glutSwapBuffers();

}

void draw_axis_by_cones() {
	double estrangement = glob_settings.subwindows[1].wh.width / 100.0;
	
	glColor3f(1.0, 0.0, 0.0);
	
	glRotated(90.0, 0, 1, 0);
		glutSolidCylinder(3.0 * estrangement, 6.0 * estrangement, 10.0, 10.0);
		glTranslated(0.0, 0.0, 6.0 * estrangement);
		glutSolidCone(3.0 * estrangement, 17.0 * estrangement, 10.0, 10.0);
		glTranslated(0.0, 0.0, -5.0 * estrangement);
	glRotated(-90.0, 0, 1, 0);
	
	if (glob_settings.other_settings.show_axis_names) {
		if (glob_settings.other_settings.inverted_black_text_axis) glColor3f(1.0, 1.0, 1.0);
		else glColor3f(0.0, 0.0, 0.0);
		print_text_3f(35.0, 10.0, 5.0, L"X", GLUT_BITMAP_HELVETICA_18);
	}
	
	
	
	glColor3f(0.0, 154.0 / 255.0, 99.0 / 255.0);
	
	glRotated(-90.0, 1, 0, 0);
		glutSolidCylinder(3.0 * estrangement, 6.0 * estrangement, 10.0, 10.0);
		glTranslated(0.0, 0.0, 6.0 * estrangement);
		glutSolidCone(3.0 * estrangement, 17.0 * estrangement, 10.0, 10.0);
		glTranslated(0.0, 0.0, -5.0 * estrangement);
	glRotated(90.0, 1, 0, 0);
	
	
	if (glob_settings.other_settings.show_axis_names) {
		if (glob_settings.other_settings.inverted_black_text_axis) glColor3f(1.0, 1.0, 1.0);
		else glColor3f(0.0, 0.0, 0.0);
		print_text_3f(5.0, 35.0, 5.0, L"Y", GLUT_BITMAP_HELVETICA_18);
	}
	
	
	glColor3f(0.0, 0.0, 1.0);
		
		glutSolidCylinder(3.0 * estrangement, 6.0 * estrangement, 10.0, 10.0);
		glTranslated(0.0, 0.0, 6.0 * estrangement);
		glutSolidCone(3.0 * estrangement, 17.0 * estrangement, 10.0, 10.0);
		glTranslated(0.0, 0.0, -5.0 * estrangement);
	
	if (glob_settings.other_settings.show_axis_names) {
		if (glob_settings.other_settings.inverted_black_text_axis) glColor3f(1.0, 1.0, 1.0);
		else glColor3f(0.0, 0.0, 0.0);
		print_text_3f(5.0, 10.0, 35.0, L"Z", GLUT_BITMAP_HELVETICA_18);
	}
	
	glPopMatrix();
}

void draw_axis_by_lines() {

	glLineWidth(4);

	glColor3f(1.0, 0.0, 0.0);

	glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(30.0, 0.0, 0.0);
	glEnd();	
	
	if (glob_settings.other_settings.show_axis_names) {
		if (glob_settings.other_settings.inverted_black_text_axis) glColor3f(1.0, 1.0, 1.0);
		else glColor3f(0.0, 0.0, 0.0);
		print_text_3f(35.0, 10.0, 5.0, L"X", GLUT_BITMAP_HELVETICA_18);
	}

	glColor3f(0.0, 154.0 / 255.0, 99.0 / 255.0);
	

	glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 30.0, 0.0);
	glEnd();
	
	if (glob_settings.other_settings.show_axis_names) {
		if (glob_settings.other_settings.inverted_black_text_axis) glColor3f(1.0, 1.0, 1.0);
		else glColor3f(0.0, 0.0, 0.0);
		print_text_3f(5.0, 35.0, 5.0, L"Y", GLUT_BITMAP_HELVETICA_18);
	}

	glColor3f(0.0, 0.0, 1.0);

	glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 30.0);
	glEnd();

	if (glob_settings.other_settings.show_axis_names) {
		if (glob_settings.other_settings.inverted_black_text_axis) glColor3f(1.0, 1.0, 1.0);
		else glColor3f(0.0, 0.0, 0.0);
		print_text_3f(5.0, 10.0, 35.0, L"Z", GLUT_BITMAP_HELVETICA_18);
	}

}

void subwindow_1_menu_init() {
	int _subwindow1_menu = glutCreateMenu(subwindow_1_menu);
	int _menu_background = glutCreateMenu(menu_background_sub1);
	
	char buff[256];

	glutSetMenu(_menu_background);
		sprintf(buff, "White: (%g/255, %g/255, %g/255)", colors[L"white"].red * 255.0, colors[L"white"].green * 255.0, colors[L"white"].blue * 255.0);
		glutAddMenuEntry(buff, MENU_COLORING_BACKGROUND_WHITE);
		sprintf(buff, "Red: (%g/255, %g/255, %g/255)", colors[L"red"].red * 255.0, colors[L"red"].green * 255.0, colors[L"red"].blue * 255.0);
		glutAddMenuEntry(buff, MENU_COLORING_BACKGROUND_RED);
		sprintf(buff, "Green: (%g/255, %g/255, %g/255)", colors[L"green"].red * 255.0, colors[L"green"].green * 255.0, colors[L"green"].blue * 255.0);
		glutAddMenuEntry(buff, MENU_COLORING_BACKGROUND_GREEN);
		sprintf(buff, "Blue: (%g/255, %g/255, %g/255)", colors[L"blue"].red * 255.0, colors[L"blue"].green * 255.0, colors[L"blue"].blue * 255.0);
		glutAddMenuEntry(buff, MENU_COLORING_BACKGROUND_BLUE);
		sprintf(buff, "Light blue: (%g/255, %g/255, %g/255)", colors[L"lightblue"].red * 255.0, colors[L"lightblue"].green * 255.0, colors[L"lightblue"].blue * 255.0);
		glutAddMenuEntry(buff, MENU_COLORING_BACKGROUND_LIGHTBLUE);
		sprintf(buff, "Black: (%g/255, %g/255, %g/255)", colors[L"black"].red * 255.0, colors[L"black"].green * 255.0, colors[L"black"].blue * 255.0);
		glutAddMenuEntry(buff, MENU_COLORING_BACKGROUND_BLACK);
		sprintf(buff, "Light grey: (%g/255, %g/255, %g/255)", colors[L"lightgrey"].red * 255.0, colors[L"lightgrey"].green * 255.0, colors[L"lightgrey"].blue * 255.0);
		glutAddMenuEntry(buff, MENU_COLORING_BACKGROUND_LIGHTGREY);
		sprintf(buff, "As main was: (%g/255, %g/255, %g/255)", colors[L"main"].red * 255.0, colors[L"main"].green * 255.0, colors[L"main"].blue * 255.0);
		glutAddMenuEntry(buff, MENU_COLORING_BACKGROUND_MAIN);
		sprintf(buff, "As drawer area was: (%g/255, %g/255, %g/255)", colors[L"sub0"].red * 255.0, colors[L"sub0"].green * 255.0, colors[L"sub0"].blue * 255.0);
		glutAddMenuEntry(buff, MENU_COLORING_BACKGROUND_SUB0);
		sprintf(buff, "As axis area was: (%g/255, %g/255, %g/255)", colors[L"sub1"].red * 255.0, colors[L"sub1"].green * 255.0, colors[L"sub1"].blue * 255.0);
		glutAddMenuEntry(buff, MENU_COLORING_BACKGROUND_SUB1);
		sprintf(buff, "As stats area was: (%g/255, %g/255, %g/255)", colors[L"sub2"].red * 255.0, colors[L"sub2"].green * 255.0, colors[L"sub2"].blue * 255.0);
		glutAddMenuEntry(buff, MENU_COLORING_BACKGROUND_SUB2);
		sprintf(buff, "As log area was: (%g/255, %g/255, %g/255)", colors[L"sub3"].red * 255.0, colors[L"sub3"].green * 255.0, colors[L"sub3"].blue * 255.0);
		glutAddMenuEntry(buff, MENU_COLORING_BACKGROUND_SUB3);
	
	glutSetMenu(_subwindow1_menu);
		glutAddMenuEntry("Use lines", SUBWINDOW_AXIS_MENU_USE_LINES);
		glutAddMenuEntry("Use cones", SUBWINDOW_AXIS_MENU_USE_CONES);
		glutAddMenuEntry("Show axis names", SUBWINDOW_AXIS_MENU_SHOW_NAMES);
		glutAddMenuEntry("Hide axis names", SUBWINDOW_AXIS_MENU_HIDE_NAMES);
		glutAddSubMenu("Background color", _menu_background);
		glutAddMenuEntry("Invert black text to white or conversely", MENU_INVERT_BLACK_TEXT_COLOR);

	log("Sub1 menu was initialized", RGB_BLACK);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutDetachMenu(GLUT_LEFT_BUTTON);
}

void subwindow_1_menu(int code) {
	
	switch (code) {
		case SUBWINDOW_AXIS_MENU_USE_CONES: glob_settings.other_settings.axis_by_cones = true; log("Cone mode to axis", RGB_BLUE); postRedisplay();break;
		case SUBWINDOW_AXIS_MENU_USE_LINES: glob_settings.other_settings.axis_by_cones = false; log("Line mode to axis", RGB_BLUE); postRedisplay(); break;
		case SUBWINDOW_AXIS_MENU_SHOW_NAMES: glob_settings.other_settings.show_axis_names = true; log("Showed names of axis", RGB_BLUE); postRedisplay(); break;
		case SUBWINDOW_AXIS_MENU_HIDE_NAMES: glob_settings.other_settings.show_axis_names = false; log("Hided names of axis", RGB_BLUE); postRedisplay(); break;
		case MENU_INVERT_BLACK_TEXT_COLOR: glob_settings.other_settings.inverted_black_text_axis = !glob_settings.other_settings.inverted_black_text_axis; log("Black color of sub1 has been inverted", RGB_BLUE); postRedisplay(); break;
		default: break;
	}

}

void menu_background_sub1(int code) {

	switch (code) {
		  
		case MENU_COLORING_BACKGROUND_WHITE: glob_settings.subwindows[1].backgroundcolor = colors[L"white"]; log("Sub1 background color changed", RGB_BLUE); postRedisplay(); break;
		case MENU_COLORING_BACKGROUND_RED: glob_settings.subwindows[1].backgroundcolor = colors[L"red"]; log("Sub1 background color changed", RGB_BLUE); postRedisplay(); break;
		case MENU_COLORING_BACKGROUND_GREEN: glob_settings.subwindows[1].backgroundcolor = colors[L"green"]; log("Sub1 background color changed", RGB_BLUE); postRedisplay(); break;
		case MENU_COLORING_BACKGROUND_BLUE: glob_settings.subwindows[1].backgroundcolor = colors[L"blue"]; log("Sub1 background color changed", RGB_BLUE); postRedisplay(); break;
		case MENU_COLORING_BACKGROUND_LIGHTBLUE: glob_settings.subwindows[1].backgroundcolor = colors[L"lightblue"]; log("Sub1 background color changed", RGB_BLUE); postRedisplay(); break;
		case MENU_COLORING_BACKGROUND_BLACK: glob_settings.subwindows[1].backgroundcolor = colors[L"black"]; log("Sub1 background color changed", RGB_BLUE); postRedisplay(); break;
		case MENU_COLORING_BACKGROUND_LIGHTGREY: glob_settings.subwindows[1].backgroundcolor = colors[L"lightgrey"]; log("Sub1 background color changed", RGB_BLUE); postRedisplay(); break;
		case MENU_COLORING_BACKGROUND_MAIN: glob_settings.subwindows[1].backgroundcolor = colors[L"main"]; log("Sub1 background color changed", RGB_BLUE); postRedisplay(); break;
		case MENU_COLORING_BACKGROUND_SUB0: glob_settings.subwindows[1].backgroundcolor = colors[L"sub0"]; log("Sub1 background color changed", RGB_BLUE); postRedisplay(); break;
		case MENU_COLORING_BACKGROUND_SUB1: glob_settings.subwindows[1].backgroundcolor = colors[L"sub1"]; log("Sub1 background color changed", RGB_BLUE); postRedisplay(); break;
		case MENU_COLORING_BACKGROUND_SUB2: glob_settings.subwindows[1].backgroundcolor = colors[L"sub2"]; log("Sub1 background color changed", RGB_BLUE); postRedisplay(); break;
		case MENU_COLORING_BACKGROUND_SUB3: glob_settings.subwindows[1].backgroundcolor = colors[L"sub3"]; log("Sub1 background color changed", RGB_BLUE); postRedisplay(); break;

		default: break;

	}

}

void display_subwindow_2() {
	int gap = glob_settings.freeglut_settings.gap;
	glClearColor(glob_settings.subwindows[2].backgroundcolor.red, glob_settings.subwindows[2].backgroundcolor.green, glob_settings.subwindows[2].backgroundcolor.blue, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	double x = 0.0 - double(glob_settings.subwindows[2].wh.width) + double(gap);
	double y = 0.0 - double(glob_settings.subwindows[2].wh.height) + double(gap);

	glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0.0, glob_settings.subwindows[2].wh.width, 0.0, glob_settings.subwindows[2].wh.height);
		glColor3f(0.0, 0.0, 0.0);

	glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		if (glob_settings.other_settings.inverted_black_text_stats) glColor3f(1.0, 1.0, 1.0);
		else glColor3f(0.0, 0.0, 0.0);
		glLoadIdentity();

		glTranslatef(glob_settings.other_settings.transl_stats.x, glob_settings.other_settings.transl_stats.y, glob_settings.other_settings.transl_stats.z);

		char buff[256];
		sprintf(buff, "x, y: %g, %g", x, y);

		std::vector <std::wstring> vct_temp = {
			(std::wstring(L"Count of all spins - ") + std::to_wstring(glob_vct.size())),
			(std::wstring(L"Count of drawed spins - ") + (glob_settings.global_settings.index_of_spin == VVIS_DRAW_ALL ? (std::to_wstring(glob_vct.size() / glob_settings.freeglut_settings.spinrate)) : L"1")),
			(std::wstring(L"Spinrate - ") + std::to_wstring(glob_settings.freeglut_settings.spinrate)),
			(std::wstring(L"Additional rotation (phi, theta) - ") + std::to_wstring(glob_settings.freeglut_settings.additional_rotation.phi) + std::wstring(L", ") + std::to_wstring(glob_settings.freeglut_settings.additional_rotation.theta)),
			(std::wstring(L"Estrangement - ") + std::to_wstring(glob_settings.freeglut_settings.estrangement)),
			(std::wstring(L"Global translation - (") + std::to_wstring(glob_settings.freeglut_settings.global_translation.x) + std::wstring(L", ") + std::to_wstring(glob_settings.freeglut_settings.global_translation.y) + std::wstring(L", ") + std::to_wstring(glob_settings.freeglut_settings.global_translation.z) + std::wstring(L")")),
			(std::wstring(L"Scaling parameters - (") + std::to_wstring(glob_settings.freeglut_settings.scaling_parameters.x) + std::wstring(L", ") + std::to_wstring(glob_settings.freeglut_settings.scaling_parameters.y) + std::wstring(L", ") + std::to_wstring(glob_settings.freeglut_settings.scaling_parameters.z) + std::wstring(L")")),			
			(std::wstring(L"Scaling translation - (") + std::to_wstring(glob_settings.freeglut_settings.scaling_translation.x) + std::wstring(L", ") + std::to_wstring(glob_settings.freeglut_settings.scaling_translation.y) + std::wstring(L", ") + std::to_wstring(glob_settings.freeglut_settings.scaling_translation.z) + std::wstring(L")")),			
			(std::wstring(L"Position of camera - (") + std::to_wstring(glob_settings.freeglut_settings.position_of_camera.x) + std::wstring(L", ") + std::to_wstring(glob_settings.freeglut_settings.position_of_camera.y) + std::wstring(L", ") + std::to_wstring(glob_settings.freeglut_settings.position_of_camera.z) + std::wstring(L")")),
			(std::wstring(L"Position of element - (") + std::to_wstring(glob_settings.freeglut_settings.position_of_element.x) + std::wstring(L", ") + std::to_wstring(glob_settings.freeglut_settings.position_of_element.y) + std::wstring(L", ") + std::to_wstring(glob_settings.freeglut_settings.position_of_element.z) + std::wstring(L")")),
			(std::wstring(L"Camera changes - (") + std::to_wstring(glob_settings.freeglut_settings.camera_changes.x) + std::wstring(L", ") + std::to_wstring(glob_settings.freeglut_settings.camera_changes.y) + std::wstring(L", ") + std::to_wstring(glob_settings.freeglut_settings.camera_changes.z) + std::wstring(L")")),
			(std::wstring(L"Estrangement changes - ") + std::to_wstring(glob_settings.freeglut_settings.estrangement_changes)),
			(std::wstring(L"Translation changes - (") + std::to_wstring(glob_settings.freeglut_settings.translation_changes.x) + std::wstring(L", ") + std::to_wstring(glob_settings.freeglut_settings.translation_changes.y) + std::wstring(L", ") + std::to_wstring(glob_settings.freeglut_settings.translation_changes.z) + std::wstring(L")")),
			(std::wstring(L"Scaling parameters changes - (") + std::to_wstring(glob_settings.freeglut_settings.scaling_parameters_changes.x) + std::wstring(L", ") + std::to_wstring(glob_settings.freeglut_settings.scaling_parameters_changes.y) + std::wstring(L", ") + std::to_wstring(glob_settings.freeglut_settings.scaling_parameters_changes.z) + std::wstring(L")")),
			(std::wstring(L"Translation by element - ") + (glob_settings.freeglut_settings.translation_by_element == -1 ? L"false" : L"true")),
			(std::wstring(L"Polygon rate - ") + std::to_wstring(glob_settings.freeglut_settings.polygonrate)),
			(std::wstring(L"Shape - ") + glob_settings.freeglut_settings.shape_wstr),
			(std::wstring(L"Gap - ") + std::to_wstring(glob_settings.freeglut_settings.gap)),
			(std::wstring(L"Coloring sample - ") + (glob_settings.freeglut_settings.coloring_sample ? L"true" : L"false")),
			(std::wstring(L"Index of spin - ") + (glob_settings.global_settings.index_of_spin == VVIS_DRAW_ALL ? L"DRAW ALL" : std::to_wstring(glob_settings.global_settings.index_of_spin))),
			(std::wstring(L"Path to folder - ") + str2wstr(glob_settings.global_settings.path_to_folder)),
			(std::wstring(L"Path to sconf file - ") + str2wstr(glob_settings.global_settings.path_to_sconfiguration_file)),
			(std::wstring(L"Path to settings folder - ") + str2wstr(glob_settings.global_settings.path_to_settings_file_folder)),
			(std::wstring(L"Path to settings file - ") + str2wstr(glob_settings.global_settings.path_to_settings_file)),
			(std::wstring(L"Number of file - ") + std::to_wstring(glob_settings.global_settings.number_of_file)),			
		};

		for (int j = 0; j < vct_temp.size(); ++j) {
			print_text_2f(3.0, glob_settings.subwindows[2].wh.height - (double(j) + 1.0) * distance_between_fonts(glob_settings.other_settings.font_stats), vct_temp[j], glob_settings.other_settings.font_stats);
		}


	glPopMatrix();
	glutSwapBuffers();
}

void subwindow_2_menu_init() {
	int _subwindow2_menu = glutCreateMenu(subwindow_2_menu);
	int _menu_background = glutCreateMenu(menu_background_sub2);
	int _menu_font = glutCreateMenu(menu_font_sub2);

	char buff[256];

	glutSetMenu(_menu_background);
		sprintf(buff, "White: (%g/255, %g/255, %g/255)", colors[L"white"].red * 255.0, colors[L"white"].green * 255.0, colors[L"white"].blue * 255.0);
		glutAddMenuEntry(buff, MENU_COLORING_BACKGROUND_WHITE);
		sprintf(buff, "Red: (%g/255, %g/255, %g/255)", colors[L"red"].red * 255.0, colors[L"red"].green * 255.0, colors[L"red"].blue * 255.0);
		glutAddMenuEntry(buff, MENU_COLORING_BACKGROUND_RED);
		sprintf(buff, "Green: (%g/255, %g/255, %g/255)", colors[L"green"].red * 255.0, colors[L"green"].green * 255.0, colors[L"green"].blue * 255.0);
		glutAddMenuEntry(buff, MENU_COLORING_BACKGROUND_GREEN);
		sprintf(buff, "Blue: (%g/255, %g/255, %g/255)", colors[L"blue"].red * 255.0, colors[L"blue"].green * 255.0, colors[L"blue"].blue * 255.0);
		glutAddMenuEntry(buff, MENU_COLORING_BACKGROUND_BLUE);
		sprintf(buff, "Light blue: (%g/255, %g/255, %g/255)", colors[L"lightblue"].red * 255.0, colors[L"lightblue"].green * 255.0, colors[L"lightblue"].blue * 255.0);
		glutAddMenuEntry(buff, MENU_COLORING_BACKGROUND_LIGHTBLUE);
		sprintf(buff, "Black: (%g/255, %g/255, %g/255)", colors[L"black"].red * 255.0, colors[L"black"].green * 255.0, colors[L"black"].blue * 255.0);
		glutAddMenuEntry(buff, MENU_COLORING_BACKGROUND_BLACK);
		sprintf(buff, "Light grey: (%g/255, %g/255, %g/255)", colors[L"lightgrey"].red * 255.0, colors[L"lightgrey"].green * 255.0, colors[L"lightgrey"].blue * 255.0);
		glutAddMenuEntry(buff, MENU_COLORING_BACKGROUND_LIGHTGREY);
		sprintf(buff, "As main was: (%g/255, %g/255, %g/255)", colors[L"main"].red * 255.0, colors[L"main"].green * 255.0, colors[L"main"].blue * 255.0);
		glutAddMenuEntry(buff, MENU_COLORING_BACKGROUND_MAIN);
		sprintf(buff, "As drawer area was: (%g/255, %g/255, %g/255)", colors[L"sub0"].red * 255.0, colors[L"sub0"].green * 255.0, colors[L"sub0"].blue * 255.0);
		glutAddMenuEntry(buff, MENU_COLORING_BACKGROUND_SUB0);
		sprintf(buff, "As axis area was: (%g/255, %g/255, %g/255)", colors[L"sub1"].red * 255.0, colors[L"sub1"].green * 255.0, colors[L"sub1"].blue * 255.0);
		glutAddMenuEntry(buff, MENU_COLORING_BACKGROUND_SUB1);
		sprintf(buff, "As stats area was: (%g/255, %g/255, %g/255)", colors[L"sub2"].red * 255.0, colors[L"sub2"].green * 255.0, colors[L"sub2"].blue * 255.0);
		glutAddMenuEntry(buff, MENU_COLORING_BACKGROUND_SUB2);
		sprintf(buff, "As log area was: (%g/255, %g/255, %g/255)", colors[L"sub3"].red * 255.0, colors[L"sub3"].green * 255.0, colors[L"sub3"].blue * 255.0);
		glutAddMenuEntry(buff, MENU_COLORING_BACKGROUND_SUB3);

	glutSetMenu(_menu_font);
		glutAddMenuEntry("HELVETICA 10", FONT_HELVETICA_10);
		glutAddMenuEntry("HELVETICA 12", FONT_HELVETICA_12);
		glutAddMenuEntry("HELVETICA 18", FONT_HELVETICA_18);
		glutAddMenuEntry("8 BY 13", FONT_8_BY_13);
		glutAddMenuEntry("9 BY 15", FONT_8_BY_15);
		glutAddMenuEntry("TIMES NEW ROMAN 10", FONT_TIMES_ROMAN_10);
		glutAddMenuEntry("TIMES NEW ROMAN 24", FONT_TIMES_ROMAN_24);

	glutSetMenu(_subwindow2_menu);
		glutAddSubMenu("Background color", _menu_background);
		glutAddSubMenu("Font", _menu_font);
		glutAddMenuEntry("Invert black text to white or conversely", MENU_INVERT_BLACK_TEXT_COLOR);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutDetachMenu(GLUT_LEFT_BUTTON);

	log("Sub2 menu was initialized", RGB_BLACK);
}

void subwindow_2_menu(int code) {

	switch (code) {
		case MENU_INVERT_BLACK_TEXT_COLOR: glob_settings.other_settings.inverted_black_text_stats = !glob_settings.other_settings.inverted_black_text_stats; log("Black color of sub2 has been inverted", RGB_BLUE); postRedisplay(); break;

		default: break;

	}

}

void menu_background_sub2(int code) {

	switch (code) {

		case MENU_COLORING_BACKGROUND_WHITE: glob_settings.subwindows[2].backgroundcolor = colors[L"white"]; log("Sub2 background color changed", RGB_BLUE); postRedisplay(); break;
		case MENU_COLORING_BACKGROUND_RED: glob_settings.subwindows[2].backgroundcolor = colors[L"red"]; log("Sub2 background color changed", RGB_BLUE); postRedisplay(); break;
		case MENU_COLORING_BACKGROUND_GREEN: glob_settings.subwindows[2].backgroundcolor = colors[L"green"]; log("Sub2 background color changed", RGB_BLUE); postRedisplay(); break;
		case MENU_COLORING_BACKGROUND_BLUE: glob_settings.subwindows[2].backgroundcolor = colors[L"blue"]; log("Sub2 background color changed", RGB_BLUE); postRedisplay(); break;
		case MENU_COLORING_BACKGROUND_LIGHTBLUE: glob_settings.subwindows[2].backgroundcolor = colors[L"lightblue"]; log("Sub2 background color changed", RGB_BLUE); postRedisplay(); break;
		case MENU_COLORING_BACKGROUND_BLACK: glob_settings.subwindows[2].backgroundcolor = colors[L"black"]; log("Sub2 background color changed", RGB_BLUE); postRedisplay(); break;
		case MENU_COLORING_BACKGROUND_LIGHTGREY: glob_settings.subwindows[2].backgroundcolor = colors[L"lightgrey"]; log("Sub2 background color changed", RGB_BLUE); postRedisplay(); break;
		case MENU_COLORING_BACKGROUND_MAIN: glob_settings.subwindows[2].backgroundcolor = colors[L"main"]; log("Sub2 background color changed", RGB_BLUE); postRedisplay(); break;
		case MENU_COLORING_BACKGROUND_SUB0: glob_settings.subwindows[2].backgroundcolor = colors[L"sub0"]; log("Sub2 background color changed", RGB_BLUE); postRedisplay(); break;
		case MENU_COLORING_BACKGROUND_SUB1: glob_settings.subwindows[2].backgroundcolor = colors[L"sub1"]; log("Sub2 background color changed", RGB_BLUE); postRedisplay(); break;
		case MENU_COLORING_BACKGROUND_SUB2: glob_settings.subwindows[2].backgroundcolor = colors[L"sub2"]; log("Sub2 background color changed", RGB_BLUE); postRedisplay(); break;
		case MENU_COLORING_BACKGROUND_SUB3: glob_settings.subwindows[2].backgroundcolor = colors[L"sub3"]; log("Sub2 background color changed", RGB_BLUE); postRedisplay(); break;

		default: break;

	}

}

void menu_font_sub2(int code) {

	switch (code) {

		case FONT_HELVETICA_10: glob_settings.other_settings.font_stats = GLUT_BITMAP_HELVETICA_10; log("Sub2 font was changed", RGB_BLUE); postRedisplay(); break;
		case FONT_HELVETICA_12: glob_settings.other_settings.font_stats = GLUT_BITMAP_HELVETICA_12; log("Sub2 font was changed", RGB_BLUE); postRedisplay(); break;
		case FONT_HELVETICA_18: glob_settings.other_settings.font_stats = GLUT_BITMAP_HELVETICA_18; log("Sub2 font was changed", RGB_BLUE); postRedisplay(); break;
		case FONT_8_BY_13: glob_settings.other_settings.font_stats = GLUT_BITMAP_8_BY_13; log("Sub2 font was changed", RGB_BLUE); postRedisplay(); break;
		case FONT_8_BY_15: glob_settings.other_settings.font_stats = GLUT_BITMAP_9_BY_15; log("Sub2 font was changed", RGB_BLUE); postRedisplay(); break;
		case FONT_TIMES_ROMAN_10: glob_settings.other_settings.font_stats = GLUT_BITMAP_TIMES_ROMAN_10; log("Sub2 font was changed", RGB_BLUE); postRedisplay(); break;
		case FONT_TIMES_ROMAN_24: glob_settings.other_settings.font_stats = GLUT_BITMAP_TIMES_ROMAN_24; log("Sub2 font was changed", RGB_BLUE); postRedisplay(); break;

		default: break;

	}

}

void subwindow_2_special_keys(int key, int x, int y) {
	double t_b_e = glob_settings.freeglut_settings.translation_by_element;

	switch (key) {							

		case GLUT_KEY_UP:			glob_settings.other_settings.transl_stats.y += t_b_e * 3.0;
									glutPostRedisplay();
									break;		

		case GLUT_KEY_DOWN:			glob_settings.other_settings.transl_stats.y -= t_b_e * 3.0;
									glutPostRedisplay();
									break;

		default:					
									break;

	}
}


void subwindow_2_mouse_pressed(int button, int state, int x, int y) {

	// scroll up
	if (button == 3) {
		subwindow_2_special_keys(GLUT_KEY_UP, 0, 0);
	}	
	// scroll up
	if (button == 4) {
		subwindow_2_special_keys(GLUT_KEY_DOWN, 0, 0);
	}


}



void display_subwindow_3() {
	int gap = glob_settings.freeglut_settings.gap;
	glClearColor(glob_settings.subwindows[3].backgroundcolor.red, glob_settings.subwindows[3].backgroundcolor.green, glob_settings.subwindows[3].backgroundcolor.blue, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	double x = 0.0 - double(glob_settings.subwindows[3].wh.width) + double(gap);
	double y = 0.0 - double(glob_settings.subwindows[3].wh.height) + double(gap);

	glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0.0, glob_settings.subwindows[3].wh.width, 0.0, glob_settings.subwindows[3].wh.height);
		glColor3f(0.0, 0.0, 0.0);

	glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glColor3f(0.0, 0.0, 0.0);
		glLoadIdentity();

		glTranslatef(glob_settings.other_settings.transl_log.x, glob_settings.other_settings.transl_log.y, glob_settings.other_settings.transl_log.z);

		if (vct_log.size() == vct_log_colorful.size()) {
			for (int j = vct_log.size() - 1, i = 0; j >= 0; --j, ++i) {
				if (vct_log_colorful[j] == RGB_BLACK && glob_settings.other_settings.inverted_black_text_log) vct_log_colorful[j] = RGB_WHITE;
				if (vct_log_colorful[j] == RGB_WHITE && !glob_settings.other_settings.inverted_black_text_log) vct_log_colorful[j] = RGB_BLACK;
				glColor3f(vct_log_colorful[j].red, vct_log_colorful[j].green, vct_log_colorful[j].blue);
				print_text_2f(3.0, glob_settings.subwindows[3].wh.height - (double(i) + 1.0) * distance_between_fonts(glob_settings.other_settings.font_log), vct_log[j], glob_settings.other_settings.font_log);
			}
		} else {
			print_text_2f(3.0, glob_settings.subwindows[3].wh.height - (0.0 + 1.0) * distance_between_fonts(glob_settings.other_settings.font_log), "Something wrong", glob_settings.other_settings.font_log);
		}

	glPopMatrix();
	glutSwapBuffers();
}

void subwindow_3_special_keys(int key, int x, int y) {
	double t_b_e = glob_settings.freeglut_settings.translation_by_element;

	switch (key) {							

		case GLUT_KEY_UP:			glob_settings.other_settings.transl_log.y += t_b_e * 3.0;
									glutPostRedisplay();
									break;		

		case GLUT_KEY_DOWN:			glob_settings.other_settings.transl_log.y -= t_b_e * 3.0;
									glutPostRedisplay();
									break;

		default:					
									break;

	}
}

void subwindow_3_mouse_pressed(int button, int state, int x, int y) {
	// scroll up
	if (button == 3) {
		subwindow_3_special_keys(GLUT_KEY_UP, 0, 0);
	}	
	// scroll up
	if (button == 4) {
		subwindow_3_special_keys(GLUT_KEY_DOWN, 0, 0);
	}
}

void subwindow_3_menu_init() {
	int _subwindow3_menu = glutCreateMenu(subwindow_3_menu);
	int _menu_background = glutCreateMenu(menu_background_sub3);
	int _menu_font = glutCreateMenu(menu_font_sub3);

	char buff[256];

	glutSetMenu(_menu_background);
		sprintf(buff, "White: (%g/255, %g/255, %g/255)", colors[L"white"].red * 255.0, colors[L"white"].green * 255.0, colors[L"white"].blue * 255.0);
		glutAddMenuEntry(buff, MENU_COLORING_BACKGROUND_WHITE);
		sprintf(buff, "Red: (%g/255, %g/255, %g/255)", colors[L"red"].red * 255.0, colors[L"red"].green * 255.0, colors[L"red"].blue * 255.0);
		glutAddMenuEntry(buff, MENU_COLORING_BACKGROUND_RED);
		sprintf(buff, "Green: (%g/255, %g/255, %g/255)", colors[L"green"].red * 255.0, colors[L"green"].green * 255.0, colors[L"green"].blue * 255.0);
		glutAddMenuEntry(buff, MENU_COLORING_BACKGROUND_GREEN);
		sprintf(buff, "Blue: (%g/255, %g/255, %g/255)", colors[L"blue"].red * 255.0, colors[L"blue"].green * 255.0, colors[L"blue"].blue * 255.0);
		glutAddMenuEntry(buff, MENU_COLORING_BACKGROUND_BLUE);
		sprintf(buff, "Light blue: (%g/255, %g/255, %g/255)", colors[L"lightblue"].red * 255.0, colors[L"lightblue"].green * 255.0, colors[L"lightblue"].blue * 255.0);
		glutAddMenuEntry(buff, MENU_COLORING_BACKGROUND_LIGHTBLUE);
		sprintf(buff, "Black: (%g/255, %g/255, %g/255)", colors[L"black"].red * 255.0, colors[L"black"].green * 255.0, colors[L"black"].blue * 255.0);
		glutAddMenuEntry(buff, MENU_COLORING_BACKGROUND_BLACK);
		sprintf(buff, "Light grey: (%g/255, %g/255, %g/255)", colors[L"lightgrey"].red * 255.0, colors[L"lightgrey"].green * 255.0, colors[L"lightgrey"].blue * 255.0);
		glutAddMenuEntry(buff, MENU_COLORING_BACKGROUND_LIGHTGREY);
		sprintf(buff, "As main was: (%g/255, %g/255, %g/255)", colors[L"main"].red * 255.0, colors[L"main"].green * 255.0, colors[L"main"].blue * 255.0);
		glutAddMenuEntry(buff, MENU_COLORING_BACKGROUND_MAIN);
		sprintf(buff, "As drawer area was: (%g/255, %g/255, %g/255)", colors[L"sub0"].red * 255.0, colors[L"sub0"].green * 255.0, colors[L"sub0"].blue * 255.0);
		glutAddMenuEntry(buff, MENU_COLORING_BACKGROUND_SUB0);
		sprintf(buff, "As axis area was: (%g/255, %g/255, %g/255)", colors[L"sub1"].red * 255.0, colors[L"sub1"].green * 255.0, colors[L"sub1"].blue * 255.0);
		glutAddMenuEntry(buff, MENU_COLORING_BACKGROUND_SUB1);
		sprintf(buff, "As stats area was: (%g/255, %g/255, %g/255)", colors[L"sub2"].red * 255.0, colors[L"sub2"].green * 255.0, colors[L"sub2"].blue * 255.0);
		glutAddMenuEntry(buff, MENU_COLORING_BACKGROUND_SUB2);
		sprintf(buff, "As log area was: (%g/255, %g/255, %g/255)", colors[L"sub3"].red * 255.0, colors[L"sub3"].green * 255.0, colors[L"sub3"].blue * 255.0);
		glutAddMenuEntry(buff, MENU_COLORING_BACKGROUND_SUB3);

	glutSetMenu(_menu_font);
		glutAddMenuEntry("HELVETICA 10", FONT_HELVETICA_10);
		glutAddMenuEntry("HELVETICA 12", FONT_HELVETICA_12);
		glutAddMenuEntry("HELVETICA 18", FONT_HELVETICA_18);
		glutAddMenuEntry("8 BY 13", FONT_8_BY_13);
		glutAddMenuEntry("9 BY 15", FONT_8_BY_15);
		glutAddMenuEntry("TIMES NEW ROMAN 10", FONT_TIMES_ROMAN_10);
		glutAddMenuEntry("TIMES NEW ROMAN 24", FONT_TIMES_ROMAN_24);

	glutSetMenu(_subwindow3_menu);
		glutAddSubMenu("Background color", _menu_background);
		glutAddSubMenu("Font", _menu_font);
		glutAddMenuEntry("Invert black text to white or conversely", MENU_INVERT_BLACK_TEXT_COLOR);
		glutAddMenuEntry("Clear log", CLEAR_LOG);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutDetachMenu(GLUT_LEFT_BUTTON);

	log("Sub3 menu was initialized", RGB_BLACK);
}

void subwindow_3_menu(int code) {

	switch (code) {
		
		case MENU_INVERT_BLACK_TEXT_COLOR: glob_settings.other_settings.inverted_black_text_log = !glob_settings.other_settings.inverted_black_text_log; log("Black color of sub3 has been inverted", RGB_BLUE); postRedisplay(); break;
		case CLEAR_LOG: vct_log = {}; vct_log_colorful = {}; log("Log has been cleared", RGB_RED); postRedisplay(); break;


		default: break;

	}

}

void menu_background_sub3(int code) {
	
	switch (code) {

		case MENU_COLORING_BACKGROUND_WHITE: glob_settings.subwindows[3].backgroundcolor = colors[L"white"]; log("Sub3 background color changed", RGB_BLUE); postRedisplay(); break;
		case MENU_COLORING_BACKGROUND_RED: glob_settings.subwindows[3].backgroundcolor = colors[L"red"]; log("Sub3 background color changed", RGB_BLUE); postRedisplay(); break;
		case MENU_COLORING_BACKGROUND_GREEN: glob_settings.subwindows[3].backgroundcolor = colors[L"green"]; log("Sub3 background color changed", RGB_BLUE); postRedisplay(); break;
		case MENU_COLORING_BACKGROUND_BLUE: glob_settings.subwindows[3].backgroundcolor = colors[L"blue"]; log("Sub3 background color changed", RGB_BLUE); postRedisplay(); break;
		case MENU_COLORING_BACKGROUND_LIGHTBLUE: glob_settings.subwindows[3].backgroundcolor = colors[L"lightblue"]; log("Sub3 background color changed", RGB_BLUE); postRedisplay(); break;
		case MENU_COLORING_BACKGROUND_BLACK: glob_settings.subwindows[3].backgroundcolor = colors[L"black"]; log("Sub3 background color changed", RGB_BLUE); postRedisplay(); break;
		case MENU_COLORING_BACKGROUND_LIGHTGREY: glob_settings.subwindows[3].backgroundcolor = colors[L"lightgrey"]; log("Sub3 background color changed", RGB_BLUE); postRedisplay(); break;
		case MENU_COLORING_BACKGROUND_MAIN: glob_settings.subwindows[3].backgroundcolor = colors[L"main"]; log("Sub3 background color changed", RGB_BLUE); postRedisplay(); break;
		case MENU_COLORING_BACKGROUND_SUB0: glob_settings.subwindows[3].backgroundcolor = colors[L"sub0"]; log("Sub3 background color changed", RGB_BLUE); postRedisplay(); break;
		case MENU_COLORING_BACKGROUND_SUB1: glob_settings.subwindows[3].backgroundcolor = colors[L"sub1"]; log("Sub3 background color changed", RGB_BLUE); postRedisplay(); break;
		case MENU_COLORING_BACKGROUND_SUB2: glob_settings.subwindows[3].backgroundcolor = colors[L"sub2"]; log("Sub3 background color changed", RGB_BLUE); postRedisplay(); break;
		case MENU_COLORING_BACKGROUND_SUB3: glob_settings.subwindows[3].backgroundcolor = colors[L"sub3"]; log("Sub3 background color changed", RGB_BLUE); postRedisplay(); break;

		default: break;

	}
}

void menu_font_sub3(int code) {

	switch (code) {

		case FONT_HELVETICA_10: glob_settings.other_settings.font_log = GLUT_BITMAP_HELVETICA_10; log("Sub3 font was changed", RGB_BLUE); postRedisplay(); break;
		case FONT_HELVETICA_12: glob_settings.other_settings.font_log = GLUT_BITMAP_HELVETICA_12; log("Sub3 font was changed", RGB_BLUE); postRedisplay(); break;
		case FONT_HELVETICA_18: glob_settings.other_settings.font_log = GLUT_BITMAP_HELVETICA_18; log("Sub3 font was changed", RGB_BLUE); postRedisplay(); break;
		case FONT_8_BY_13: glob_settings.other_settings.font_log = GLUT_BITMAP_8_BY_13; log("Sub3 font was changed", RGB_BLUE); postRedisplay(); break;
		case FONT_8_BY_15: glob_settings.other_settings.font_log = GLUT_BITMAP_9_BY_15; log("Sub3 font was changed", RGB_BLUE); postRedisplay(); break;
		case FONT_TIMES_ROMAN_10: glob_settings.other_settings.font_log = GLUT_BITMAP_TIMES_ROMAN_10; log("Sub3 font was changed", RGB_BLUE); postRedisplay(); break;
		case FONT_TIMES_ROMAN_24: glob_settings.other_settings.font_log = GLUT_BITMAP_TIMES_ROMAN_24; log("Sub3 font was changed", RGB_BLUE); postRedisplay(); break;

		default: break;

	}
}

void reshape_subwindow_0(int w, int h) {
	if (h == 0) h = 1;
	if (w == 0) w = 1;

	glViewport(0, 0, w, h);
	
	glob_settings.subwindows[0].wh.width = w;
	glob_settings.subwindows[0].wh.height = h;
}

void reshape_subwindow_1(int w, int h) {
	if (h == 0) h = 1;
	if (w == 0) w = 1;

	glViewport(0, 0, w, h);

	glob_settings.subwindows[1].wh.width = w;
	glob_settings.subwindows[1].wh.height = h;

}

void reshape_subwindow_2(int w, int h) {
	if (h == 0) h = 1;
	if (w == 0) w = 1;

	glViewport(0, 0, w, h);

	glob_settings.subwindows[2].wh.width = w;
	glob_settings.subwindows[2].wh.height = h;
}

void reshape_subwindow_3(int w, int h) {
	if (h == 0) h = 1;
	if (w == 0) w = 1;

	glViewport(0, 0, w, h);

	glob_settings.subwindows[3].wh.width = w;
	glob_settings.subwindows[3].wh.height = h;
}


