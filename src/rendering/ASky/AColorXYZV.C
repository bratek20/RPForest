#ifndef ACOMMON_H
//#include <ACommon.H>
#endif

#ifndef ASUNSKY_H
#include <ASunSky.H>
#endif

#ifndef ACOLORXYZV_H
#include <AColorXYZV.H>
#endif


#include <srgb.H>


AVector3
xyY2XYZ (AVector3 c)
{
   AReal s = c[2] / c[1];
   return AVector3 (c[0] * s, c[2], (1 - c[0] - c[1]) * s);
}

AVector3
XYZ2xyY (AVector3 c)
{
   AReal s = c[0] + c[1] + c[2];
   return AVector3 (c[0] / s, c[1] / s, c[1]);
}

AVector3
XYZ2RGB (AVector3 c)
{
   return xyY2RGB(XYZ2xyY(c));
}

AVector3
xyY2RGB (AVector3 c)
{
   float xyz[3] = { c[0], c[1], 1 - c[0] - c[1] };
   float rgb[3];
   XYZtoRGB (xyz, rgb);
   return AVector3 (rgb[0], rgb[1], rgb[2]);
}

AVector3
xyY2RGB_HDR (AVector3 c)
{
   float xyz[3] = { c[0], c[1], 1 - c[0] - c[1] };
   float rgb[3];
   XYZtoRGB (xyz, rgb);
   return AVector3 (c[2]*rgb[0], c[2]*rgb[1], c[2]*rgb[2]);
}

AReal
Lux2EV (AReal l)
{
   return log (l / 2.5) / log (2.0);
}

AReal
Lum2EV (AReal l)
{
   return log ((APi * l) / 2.5) / log (2.0);
}

// -----------------------------------------------------------------

#include <ASpectralCurve.H>

extern "C" {
#include "ciexyz.h"
}

class XYZCurves {
public:
   XYZCurves();
   ASpectrum SX,SY,SZ;
};

XYZCurves::XYZCurves(){
   // For: X=X,Y,Z
   // 1.X sensitivity -> ARegularSpectralCurve SC
   // 2.ASpectrum (operator) SC -> SP          operator should be implemented better than now!!!
   int NNN= (780-380)/5 + 1;
   AReal xdata[NNN], ydata[NNN], zdata[NNN];
#ifdef VERBOSE  
   printf("Init Spectral curves XYZ\n");
#endif
   for (int i=0; i<NNN; i++) {
      xdata[i] = CIE1931[i].x;
      ydata[i] = CIE1931[i].y;
      zdata[i] = CIE1931[i].z;
   }
   SX = ARegularSpectralCurve(xdata, 380.0, 780.0, NNN);
   SY = ARegularSpectralCurve(ydata, 380.0, 780.0, NNN);
   SZ = ARegularSpectralCurve(zdata, 380.0, 780.0, NNN);
}

// Return static object 
XYZCurves& XYZcu(){
   static XYZCurves * xyzcurves = new XYZCurves();
   return *xyzcurves;
}
// -----------------------------------------------------------------

/* TO IMPLEMENT:
 *    AColorXYZV::AColorXYZV[in-charge](ASpectrum const&)
 *    AColorXYZV::Y() const
 */

AColorXYZV::AColorXYZV(const ASpectrum &in){
   //  if (XYZcuP==NULL) XYZcuP=new XYZCurves();
   //  XYZCurves XYZcu = *XYZcuP;
   // for (int l=0; l<in.GetNumComponents(); l++)  X +=  in.data[l] * Xsensitivity[l];
   // Set: d[0-3] = X,Y,Z,V
   // LoggerStr("NOT IMPLEMENTED ColorXYZV from Spectrum !!!\n");

   // 3.SP*in   and integrate result -> X
   int k=683; // Biggs paper k=683lumens/Watt Glassner k=1 ANL???
   d[0] = k*(XYZcu().SX*in).GetArea(); ///(780-380);
   d[1] = k*(XYZcu().SY*in).GetArea(); ///(780-380);
   d[2] = k*(XYZcu().SZ*in).GetArea(); ///(780-380);
   // For V use approx. by R from Pattanaik SIg1998: A multiscale model of adaptation...
   d[3] = -0.702*d[0] + 1.039*d[1] + 0.433*d[2];
}

AReal	AColorXYZV::X() const {
   return d[0];
}
AReal	AColorXYZV::Y() const {
   return d[1];
}
AReal	AColorXYZV::Z() const {
   return d[2];
}
