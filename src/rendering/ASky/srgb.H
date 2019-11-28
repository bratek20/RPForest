/* Konwersja z przestrzeni XYZ do przestrzeni sRGB
 * i z powrotem
 */
#ifndef  __SRGB_HEADER
#define  __SRGB_HEADER

void XYZtoRGB(float *xyz, float *rgb);
void RGBtoXYZ(float *rgb, float *xyz);

#endif  // #ifndef __SRGB_HEADER
