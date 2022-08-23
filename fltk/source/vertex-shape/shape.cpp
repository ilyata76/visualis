#include "./shape.hpp"

bool Cone::set_draw_configuration() {
    //Assert(!(this->vrt.spin.x == 0.0 && this->vrt.spin.y == 0.0 && this->vrt.spin.z == 0.0));

	this->euler_phi = get_euler_phi(this->vrt.spin.x, this->vrt.spin.y, this->vrt.spin.z);
	this->euler_theta = get_euler_theta(this->vrt.spin.x, this->vrt.spin.y, this->vrt.spin.z);

    return true;
}

bool Cone::draw(Rgb color, double* args) {
	//Assert((args[0] != 0 && args[1] != 0), 1, L"null base or height", L"Assert, cone.draw");
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

bool Sphere::set_draw_configuration() {
	return true;
}

bool Sphere::draw(Rgb color, double* args) {
	//Assert((args[0] != 0 && args[1] != 0), 1, L"null base or height", L"Assert, cone.draw");
	glColor3f(color.red, color.green, color.blue);
	
	// нарисовали
	glutSolidSphere(args[0], args[1], args[2]);
	
	return true;
}

wchar_t Sphere::info() {
	return VVIS_SHAPE_SPHERE;
}

bool Arrow::set_draw_configuration() {
	//Assert(!(this->vrt.spin.x == 0.0 && this->vrt.spin.y == 0.0 && this->vrt.spin.z == 0.0));

	this->euler_phi = get_euler_phi(this->vrt.spin.x, this->vrt.spin.y, this->vrt.spin.z);
	this->euler_theta = get_euler_theta(this->vrt.spin.x, this->vrt.spin.y, this->vrt.spin.z);

	return true;
}

bool Arrow::draw(Rgb color, double* args) {
	//Assert((args[0] != 0 && args[1] != 0), 1, L"null base or height", L"Assert, cone.draw");
	glColor3f(color.red, color.green, color.blue);

	// повернули
	glRotatef(this->euler_phi, 0, 0, 1);
	glRotatef(this->euler_theta, 0, 1, 0);

	glutSolidSphere(args[4], args[2], args[3]);

	glTranslatef(0, 0, -args[1] / 2.0);
	
	//glutSolidCylinder(args[0] / 4.0, args[1], args[2], args[3]); // TODO:

	glTranslatef(0, 0, args[1]);

	glutSolidCone(args[0], args[1], args[2], args[3]);

	glTranslatef(0, 0, - args[1] / 2.0);

	// отвернули
	glRotatef(-this->euler_theta, 0, 1, 0);
	glRotatef(-this->euler_phi, 0, 0, 1);

	
	return false;
}

wchar_t Arrow::info() {
	return VVIS_SHAPE_ARROW;
}