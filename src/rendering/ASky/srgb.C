#include <math.h>

#include <srgb.H>

#define power pow
#define gamma 2.2
/* float power(float x, float y)
 * {
 * return x;
 * }
 */

float M_XYZtoRGB[3][3] = {
   {  3.2406,  -1.5372,  -0.4986 },
   { -0.9689,   1.8758,   0.0415 },
   {  0.0557,  -0.2040,   1.0570 }
};

float M_RGBtoXYZ[3][3] = {
   {  0.4124,  0.3576,  0.1805 },
   {  0.2126,  0.7152,  0.0722 },
   {  0.0193,  0.1192,  0.9505 }
};

void XYZtoRGB(float *xyz, float *rgb)
   {
   rgb[0] = M_XYZtoRGB[0][0]*xyz[0] + M_XYZtoRGB[0][1]*xyz[1] +
            M_XYZtoRGB[0][2]*xyz[2];
   rgb[1] = M_XYZtoRGB[1][0]*xyz[0] + M_XYZtoRGB[1][1]*xyz[1] +
            M_XYZtoRGB[1][2]*xyz[2];
   rgb[2] = M_XYZtoRGB[2][0]*xyz[0] + M_XYZtoRGB[2][1]*xyz[1] +
            M_XYZtoRGB[2][2]*xyz[2];
   
   if (rgb[0] <= 0.0031308)
      rgb[0] *= 12.92;
   else
      rgb[0] = 1.055*power(rgb[0],1/gamma) - 0.055;
   
   if (rgb[1] <= 0.0031308)
      rgb[1] *= 12.92;
   else
      rgb[1] = 1.055*power(rgb[1],1/gamma) - 0.055;
   
   if (rgb[2] <= 0.0031308)
      rgb[2] *= 12.92;
   else
      rgb[2] = 1.055*power(rgb[2],1/gamma) - 0.055;
   }


void RGBtoXYZ(float *rgb, float *xyz)
{
   float x[3];

   if (rgb[0] <= 0.04045)
      x[0] = rgb[0]/12.92;
   else
      x[0] = power(((rgb[0]+0.055)/1.055), gamma);

   if (rgb[1] <= 0.04045)
      x[1] = rgb[1]/12.92;
   else
      x[1] = power(((rgb[1]+0.055)/1.055), gamma);

   if (rgb[2] <= 0.04045)
      x[2] = rgb[2]/12.92;
   else
      x[2] = power(((rgb[2]+0.055)/1.055), gamma);

   xyz[0] = M_RGBtoXYZ[0][0]*x[0] + M_RGBtoXYZ[0][1]*x[1] +
            M_RGBtoXYZ[0][2]*x[2];
   xyz[1] = M_RGBtoXYZ[1][0]*x[0] + M_RGBtoXYZ[1][1]*x[1] +
            M_RGBtoXYZ[1][2]*x[2];
   xyz[2] = M_RGBtoXYZ[2][0]*x[0] + M_RGBtoXYZ[2][1]*x[1] +
            M_RGBtoXYZ[2][2]*x[2];
}
