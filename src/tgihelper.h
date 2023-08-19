#ifndef TGIHELPER_H
#define TGIHELPER_H

#define TGI_COLOR_GET_ALPHA(color) ((unsigned char)((color) >> 24))
#define TGI_COLOR_GET_RED(color) ((unsigned char)((color) >> 16))
#define TGI_COLOR_GET_GREEN(color) ((unsigned char)((color) >> 8))
#define TGI_COLOR_GET_BLUE(color) ((unsigned char)(color))

#define TGI_POINT(x, y) (x), (y)
#define TGI_RECT(left, top, right, bottom) (left), (top), ((right) - (left)), ((bottom) - (top))
#define TGI_CIRCLE(x, y, radius) ((x) - (radius)), ((y) - (radius)), (2 * (radius)), (2 * (radius))
#define TGI_ELLIPSE(x, y, xradius, yradius) ((x) - (xradius)), ((y) - (yradius)), (2 * (xradius)), (2 * (yradius))

#endif