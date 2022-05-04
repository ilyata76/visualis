#include "include\sample\color_class.hpp"

#include <iostream>

using vvis::visualization::VvisColor_3f;
using vvis::visualization::rgb;
using vvis::visualization::hsv;

VvisColor_3f vvis::visualization::get_color_by_direction(double x, double y, double z) {

	return VvisColor_3f(1, 1, 1);
}

// TODO: напиши сам функцию HSL -> RGV это вообще не сложно абсолюно https://en.wikipedia.org/wiki/HSL_and_HSV
// потом уже придумаем как это делать всё
// вообще сначала надо бы построить хотя бы один образец полный а потом уже с цветом мучаться


// готовое решение из https://stackoverflow.com/questions/3018313/algorithm-to-convert-rgb-to-hsv-and-hsv-to-rgb-in-range-0-255-for-both
//rgb vvis::visualization::hsv2rgb(hsv in) {
//    double      hh, p, q, t, ff;
//    long        i;
//    rgb         out;
//
//    if (in.s <= 0.0) {     
//        out.r = in.v;
//        out.g = in.v;
//        out.b = in.v;
//        return out;
//    }
//
//    hh = in.h;
//
//    if (hh >= 360.0) hh = 0.0;
//
//    hh /= 60.0;
//
//    i = (long)hh;
//
//    ff = hh - i;
//
//    p = in.v * (1.0 - in.s);
//    q = in.v * (1.0 - (in.s * ff));
//    t = in.v * (1.0 - (in.s * (1.0 - ff)));
//
//    switch (i) {
//        case 0:
//            out.r = in.v;
//            out.g = t;
//            out.b = p;
//            break;
//
//        case 1:
//            out.r = q;
//            out.g = in.v;
//            out.b = p;
//            break;
//
//        case 2:
//            out.r = p;
//            out.g = in.v;
//            out.b = t;
//            break;
//
//        case 3:
//            out.r = p;
//            out.g = q;
//            out.b = in.v;
//            break;
//
//        case 4:
//            out.r = t;
//            out.g = p;
//            out.b = in.v;
//            break;
//
//        default:
//            out.r = in.v;
//            out.g = p;
//            out.b = q;
//            break;
//    }
//    return out;
//}