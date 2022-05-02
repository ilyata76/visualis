#include "include/sample/shape.hpp"

wchar_t vvis::visualization::Cone::info_wchar() {
	return SHAPE_CONE;
}

std::wstring vvis::visualization::Cone::info_wstr() {
	return SHAPE_CONE_STR;
}




bool vvis::visualization::Cone::set_draw_configuration() {



	return true;
}

bool vvis::visualization::Cone::draw(double base, double height, GLint slices, GLint stacks, vvis::visualization::VvisColor_3f color) {
	glColor3f(0, 0, 0); // test drawing
	glRotatef(90, 0, 1, 0);
	glRotatef(90, 0, 0, 1);
	glRotatef(90, 0, 1, 0);
	glutSolidCone(base, height, slices, stacks);
	return false;
}


