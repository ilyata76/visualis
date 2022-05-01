#include "include/sample/point-spin.hpp"

vvis::creator::Point::Point() {
	this->x = DOUBLE_PLUG; this->y = DOUBLE_PLUG; this->z = DOUBLE_PLUG;
}

//vvis::creator::Point::Point(double x, double y, double z) {
//	this->x = x; this->y = y; this->z = z;
//}

//vvis::creator::Point::Point(double x, double y) {
//	this->x = y; this->y = y; this->z = DOUBLE_PLUG;
//}

vvis::creator::Point::Point(const double& x, const double& y, const double& z) {
	this->x = x; this->y = y; this->z = z;
}

vvis::creator::Point::Point(const double& x, const double& y) {
	this->x = y; this->y = y; this->z = DOUBLE_PLUG;
}

// use L'x' L'y' L'z'
double vvis::creator::Point::get(wchar_t what) {

	Assert((what == L'x' || what == L'y' || what == 'z'), 301, L"Íå x, íå y, íå z", L"Assert. ÔÓÍÊÖÈß: vvis::creator::Point::get");

	switch (what) {
		case L'x': { return this->x; } break;
		case L'y': { return this->y; } break;
		case L'z': { return this->z; } break;
		default:;
	}

	return DOUBLE_PLUG;
}

// use L'x' etc.
//double vvis::creator::Point::set(wchar_t what, double value) {
//
//	Assert((what == L'x' || what == L'y' || what == 'z'), 301, L"Íå x, íå y, íå z", L"Assert. ÔÓÍÊÖÈß: vvis::creator::Point::set");
//
//	switch (what) {
//		case L'x': { this->x = value; return this->x; } break;
//		case L'y': { this->y = value; return this->y; } break;
//		case L'z': { this->z = value; return this->z; } break;
//		default:;
//	}
//
//	return DOUBLE_PLUG;
//}

// use L'x' etc.
double vvis::creator::Point::set(wchar_t what, const double& value) {

	Assert((what == L'x' || what == L'y' || what == 'z'), 301, L"Íå x, íå y, íå z", L"Assert. ÔÓÍÊÖÈß: vvis::creator::Point::set");

	switch (what) {
		case L'x': { this->x = value; return this->x; } break;
		case L'y': { this->y = value; return this->y; } break;
		case L'z': { this->z = value; return this->z; } break;
		default:;
	}

	return DOUBLE_PLUG;
}


// -----
// spin
// -

vvis::creator::Spin::Spin() {
	this->sx = DOUBLE_PLUG; this->sy = DOUBLE_PLUG; this->sz = DOUBLE_PLUG;
}

//vvis::creator::Spin::Spin(double sx, double sy, double sz) {
//	this->sx = sx; this->sy = sy; this->sz = sz;
//}

//vvis::creator::Spin::Spin(double sx, double sy) {
//	this->sx = sx; this->sy = sy; this->sz = DOUBLE_PLUG;
//}

vvis::creator::Spin::Spin(const double& sx, const double& sy, const double& sz) {
	this->sx = sx; this->sy = sy; this->sz = sz;
}

vvis::creator::Spin::Spin(const double& sx, const double& sy) {
	this->sx = sx; this->sy = sy; this->sz = DOUBLE_PLUG;
}

// use L"x" etc.
double vvis::creator::Spin::get(const std::wstring& what) {

	Assert((what == L"sx" || what == L"sy" || what == L"sz"), 301, L"Íå sx, íå sy, íå sz", L"Assert. ÔÓÍÊÖÈß: vvis::creator::Spin::get");

	if (what == L"sx") { return this->sx; };
	if (what == L"sy") { return this->sy; };
	if (what == L"sz") { return this->sz; };

	return DOUBLE_PLUG;
}

// use L'x' etc.
double vvis::creator::Spin::get(wchar_t what) {

	Assert((what == L'x' || what == L'y' || what == 'z'), 301, L"Íå x, íå y, íå z", L"Assert. ÔÓÍÊÖÈß: vvis::creator::Spin::get");

	switch (what) {
		case L'x': { return this->sx; } break;
		case L'y': { return this->sy; } break;
		case L'z': { return this->sz; } break;
		default:;
	}

	return DOUBLE_PLUG;
}

// use L"x" etc.
double vvis::creator::Spin::set(const std::wstring& what, double& value) {

	Assert((what == L"sx" || what == L"sy" || what == L"sz"), 301, L"Íå sx, íå sy, íå sz", L"Assert. ÔÓÍÊÖÈß: vvis::creator::Spin::set");

	if (what == L"sx") { this->sx = value; return this->sx; };
	if (what == L"sy") { this->sy = value; return this->sy; };
	if (what == L"sz") { this->sz = value; return this->sz; };

	return DOUBLE_PLUG;
}

// use L"x" etc.
//double vvis::creator::Spin::set(const std::wstring& what, double value) {
//
//	Assert((what == L"sx" || what == L"sy" || what == L"sz"), 301, L"Íå sx, íå sy, íå sz", L"Assert. ÔÓÍÊÖÈß: vvis::creator::Spin::set");
//
//	if (what == L"sx") { this->sx = value; return this->sx; };
//	if (what == L"sy") { this->sy = value; return this->sy; };
//	if (what == L"sz") { this->sz = value; return this->sz; };
//
//	return DOUBLE_PLUG;
//}

// use L'x' etc.
double vvis::creator::Spin::set(wchar_t what, double& value) {

	Assert((what == L'x' || what == L'y' || what == 'z'), 301, L"Íå x, íå y, íå z", L"Assert. ÔÓÍÊÖÈß: vvis::creator::Spin::set");

	switch (what) {
		case L'x': { this->sx = value; return this->sx; } break;
		case L'y': { this->sy = value; return this->sy; } break;
		case L'z': { this->sz = value; return this->sz; } break;
		default:;
	}

	return DOUBLE_PLUG;
}

// use L'x' etc.
//double vvis::creator::Spin::set(wchar_t what, double value) {
//
//	Assert((what == L'x' || what == L'y' || what == 'z'), 301, L"Íå x, íå y, íå z", L"Assert. ÔÓÍÊÖÈß: vvis::creator::Spin::set");
//
//	switch (what) {
//		case L'x': { this->sx = value; return this->sx; } break;
//		case L'y': { this->sy = value; return this->sy; } break;
//		case L'z': { this->sz = value; return this->sz; } break;
//		default:;
//	}
//
//	return DOUBLE_PLUG;
//}