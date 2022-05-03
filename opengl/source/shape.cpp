#include "include/sample/shape.hpp"

wchar_t vvis::visualization::Cone::info_wchar() {
	return SHAPE_CONE;
}

std::wstring vvis::visualization::Cone::info_wstr() {
	return SHAPE_CONE_STR;
}

bool vvis::visualization::Cone::set_draw_configuration() {
	double sx = vrt.get_spin().get(L'x');
	double sy = vrt.get_spin().get(L'y');
	double sz = vrt.get_spin().get(L'z');

	if (sx == 0.0 && sy == 0.0 && sx == 0.0) return false;

	this->euler_phi = vvis::visualization::get_euler_phi(sx, sy, sz);
	this->euler_theta = vvis::visualization::get_euler_theta(sx, sy, sz);

	return true;
}

bool vvis::visualization::Cone::draw(double base, double height, GLint slices, GLint stacks, vvis::visualization::VvisColor_3f color) {
	glColor3f(color.red, color.green, color.blue);
	// повернули
	glRotatef(this->euler_phi, 0, 0, 1);
	glRotatef(this->euler_theta, 0, 1, 0);
	// нарисовали
	glutSolidCone(base, height, slices, stacks);
	// отвернули
	glRotatef(- this->euler_theta, 0, 1, 0);
	glRotatef(- this->euler_phi, 0, 0, 1);

	return true;
}

float vvis::visualization::get_euler_phi(const double& sx, const double& sy, const double& sz) {
	int sign = -1;
	if (COUNTERCLOCKWISE) sign = 1;
	if (sx > 0 && sy > 0) {
		return (sign * atan(abs(sy / sx)) * 180.0 / 3.1415);
	} else if (sx < 0 && sy > 0) {
		return (sign * (180 - (atan(abs(sy / sx))) * 180.0 / 3.1415));
	} else if (sx < 0 && sy < 0) {
		return (sign * (270 - (atan(abs(sx / sy))) * 180.0 / 3.1415));
	} else if (sx > 0 && sy < 0) {
		return (sign * (360 - (atan(abs(sy / sx))) * 180.0 / 3.1415));
	} else {
		if (sy == 0) return (sign * 0.0);
		if (sx == 0) return (sign * 90.0);
	} return (sign * 0.0f);
}

float vvis::visualization::get_euler_theta(const double& sx, const double& sy, const double& sz) {
	int sign = -1;
	if (COUNTERCLOCKWISE) sign = 1;
	
	if (sz == 0) return (sign * 90.0f);
	
	if (sz > 0) return (sign * (atan(abs(sqrt(pow(sx, 2) + pow(sy, 2))) / abs(sz))) * 180.0 / 3.1415);
	else return (sign * (180 - (atan(abs(sqrt(pow(sx, 2) + pow(sy, 2)) / sz))) * 180.0 / 3.1415));


	return (sign * 0.0f);
}
