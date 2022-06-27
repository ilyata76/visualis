﻿#include "./shape.hpp"

bool Cone::set_draw_configuration() {
    Assert(!(this->vrt.spin.x == 0.0 && this->vrt.spin.y == 0.0 && this->vrt.spin.z == 0.0));

	this->euler_phi = get_euler_phi(this->vrt.spin.x, this->vrt.spin.y, this->vrt.spin.z);
	this->euler_theta = get_euler_theta(this->vrt.spin.x, this->vrt.spin.y, this->vrt.spin.z);

    return true;
}

bool Cone::draw(Rgb color, double* args) {
	glColor3f(color.red, color.green, color.blue);
	// повернули
	glRotatef(this->euler_phi, 0, 0, 1);
	glRotatef(this->euler_theta, 0, 1, 0);
	// нарисовали
	glutSolidCone(args[0], args[1], args[2], args[3]);
	// отвернули
	glRotatef(-this->euler_theta, 0, 1, 0);
	glRotatef(-this->euler_phi, 0, 0, 1);

	return true;
}

wchar_t Cone::info() {
    return VVIS_SHAPE_CONE;
}
