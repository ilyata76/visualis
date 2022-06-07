#include "include\sample\color_class.hpp"

using vvis::visualization::VvisColor_3f;

VvisColor_3f vvis::visualization::get_color_by_direction(const double& x, const double& y, const double& z) {
	// https://en.wikipedia.org/wiki/HSL_and_HSV

	// HSL
	//https://galactic.ink/sphere/
	// HUE 0-360 - будет нашем углом arctg 0-360
	// Luminance 0-100 - от оси Z 0-180

	double hue = get_euler_phi(x, y, z); //Given a color with hue H ∈ [0°, 360°], saturation SL ∈ [0, 1], and lightness L ∈ [0, 1], we first find chroma:
	double lightness = (get_euler_theta(x, y, z) * 1 / 180);
	double saturation = 1;

	double chroma = ( 1 - fabs(2.0 * lightness - 1.0) * saturation );
	double h = ( hue / 60 );
	double intermediate_X = ( chroma * (1 - fabs(fmod(h, 2.0) - 1)) );
	
	double R1 = 0, G1 = 0, B1 = 0;;

	if		(h >= 0 && h < 1)	{ R1 = chroma; G1 = intermediate_X; B1 = 0; }
	else if (h >= 1 && h < 2)	{ R1 = intermediate_X; G1 = chroma; B1 = 0; }
	else if (h >= 2 && h < 3)	{ R1 = 0; G1 = chroma; B1 = intermediate_X; }
	else if (h >= 3 && h < 4)	{ R1 = 0; G1 = intermediate_X; B1 = chroma; }
	else if (h >= 4 && h < 5)	{ R1 = intermediate_X; G1 = 0; B1 = chroma; }
	else						{ R1 = chroma; G1 = 0; B1 = intermediate_X; }
	
	double m = lightness - chroma / 2;

	return VvisColor_3f(R1 + m, G1 + m, B1 + m);
}

VvisColor_3f vvis::visualization::get_color_by_direction(vvis::creator::Spin& spin) {
	return get_color_by_direction(spin.get(L'x'), spin.get(L'y'), spin.get(L'z'));
}

float vvis::visualization::get_euler_phi(const double& sx, const double& sy, const double& sz) {
	int sign = -1;
	if (COUNTERCLOCKWISE) sign = 1;
	if (sx > 0 && sy > 0) {
		return (sign * atan(fabs(sy / sx)) * 180.0 / 3.1415);
	} else if (sx < 0 && sy > 0) {
		return (sign * (180 - (atan(fabs(sy / sx))) * 180.0 / 3.1415));
	} else if (sx < 0 && sy < 0) {
		return (sign * (270 - (atan(fabs(sx / sy))) * 180.0 / 3.1415));
	} else if (sx > 0 && sy < 0) {
		return (sign * (360 - (atan(fabs(sy / sx))) * 180.0 / 3.1415));
	} else {
		if (sy == 0) if (sx < 0) return (sign * 180.0); else return (sign * 0.0);
		if (sx == 0) if (sy > 0) return (sign * 90.0); else return (sign * (-90.0));
	} return (sign * 0.0f);
}

float vvis::visualization::get_euler_theta(const double& sx, const double& sy, const double& sz) {
	int sign = -1;
	if (COUNTERCLOCKWISE) sign = 1;
	
	if (sz == 0) return (sign * 90.0f);
	
	if (sz > 0) return (sign * (atan(fabs(sqrt(pow(sx, 2) + pow(sy, 2))) / fabs(sz))) * 180.0 / 3.1415);
	else return (sign * (180 - (atan(fabs(sqrt(pow(sx, 2) + pow(sy, 2)) / sz))) * 180.0 / 3.1415));


	return (sign * 0.0f);
}

// TODO: напиши сам функцию HSL -> RGV это вообще не сложно абсолюно https://en.wikipedia.org/wiki/HSL_and_HSV
// потом уже придумаем как это делать всё
// вообще сначала надо бы построить хотя бы один образец полный а потом уже с цветом мучаться

