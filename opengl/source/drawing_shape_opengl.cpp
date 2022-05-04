#include "./include/sample/drawing_shape_opengl.hpp"

int glob_index = 0;
int glob_color = false;

std::vector<vvis::creator::Vertex> vrt_vctr;

void vvis::visualization::display_nothing() {
	//
}

void vvis::visualization::draw_cone_spin(int& index, bool color) {
	double x = vrt_vctr[glob_index].get_point().get(L'x');
	double y = vrt_vctr[glob_index].get_point().get(L'y');
	double z = vrt_vctr[glob_index].get_point().get(L'z');
	vvis::visualization::Cone my_cone(vrt_vctr[glob_index]);

	glPushMatrix();
	
	if (ROTATE_Z_FO_SECOND_REPRESENTATION) glRotatef(-90, 1, 0, 0);
	
	my_cone.set_draw_configuration();
	
	glTranslated(x / 32, y / 32, z / 32); // TODO: параметры скейлинга трансляции

	if (color == true) 
		my_cone.draw(0.005, 0.05, 10, 10, vvis::visualization::get_color_by_direction(vrt_vctr[glob_index].get_spin())); // TODO: параметры конуса
	else 
		my_cone.draw(0.005, 0.05, 10, 10, vvis::visualization::VvisColor_3f(0, 0, 0)); // TODO: параметры конуса

	glPopMatrix();
}

void vvis::visualization::display_cone() {
	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	if (glob_index == DRAW_ALL) {
		glob_index = 0;
		size_t size = vrt_vctr.size();
		for (glob_index; glob_index != size; ++glob_index) {
			draw_cone_spin(glob_index, glob_color);
		}
	}
	
	glutSwapBuffers();
}

void vvis::visualization::main_glut(int argc, char** argv, std::vector<vvis::creator::Vertex>& vect, 
									wchar_t shape, bool color, int index) {
	
	vrt_vctr = vect;
	glob_index = index;
	glob_color = color;

	glutInitWindowSize(1600, 1000);
	glutInitWindowPosition(10, 10);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInit(&argc, argv);
	int MAINWINDOW = glutCreateWindow("mainwindow");
	glutSetWindowTitle("TTITLE");

	switch (shape) {
		case SHAPE_CONE: {
			glutDisplayFunc(vvis::visualization::display_cone);
		} break;
	}

	
	//glutIdleFunc(display);
	glutMainLoop();
}


//void draw_spin(int& index) {
//	glPushMatrix();
//	glRotatef(-90, 1, 0, 0);
//	vvis::creator::Point p = vect[index].get_point();
//	
//	vvis::visualization::Cone B(vect[index]);
//	
//	
//	
//	B.set_draw_configuration();
//
//	B.draw(0.005, 0.05, 10, 10, vvis::visualization::VvisColor_3f(0, 0, 0));
//	glPopMatrix();
//}