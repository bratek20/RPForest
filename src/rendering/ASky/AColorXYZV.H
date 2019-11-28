#ifndef ACOLORXYZS_H
#define ACOLORXYZS_H
/********************************************************************
 * BaseGLIB   Andrzej Lukaszewski
 *
 * Color model XYZ+V
 *
 * CLASSES:
 *    AColorXYZV
 *    XYZ + scotopic V  
 ********************************************************************/

#ifndef ASPECTRUM_H
#include <ASpectrum.H>
#endif

#include <srgb.H>

AVector3 xyY2XYZ (AVector3 c);
AVector3 XYZ2xyY (AVector3 c);
AVector3 XYZ2RGB (AVector3 c);
AVector3 xyY2RGB     (AVector3 c);
AVector3 xyY2RGB_HDR (AVector3 c);
AReal    Lux2EV (AReal l);
AReal    Lum2EV (AReal l);


/***************************************************************
CLASS
  
****************************************************************/
class AColorXYZV {
public:
   AColorXYZV();
   AColorXYZV(AReal x, AReal y, AReal z, AReal v = 0);
   AColorXYZV(const ASpectrum &s);
   
   AReal	X() const;
   AReal	Y() const;
   AReal	Z() const;
   AReal	V() const;
   
   AColorXYZV operator+(const AColorXYZV &rside) const;
   AColorXYZV operator-(const AColorXYZV &rside) const;
   AColorXYZV operator*(AReal rside) const;
   AColorXYZV operator/(AReal rside) const;
   const AColorXYZV &operator+=(const AColorXYZV &rside);
   const AColorXYZV &operator-=(const AColorXYZV &rside);
   const AColorXYZV &operator*=(AReal rside);
   const AColorXYZV &operator/=(AReal rside);
   
private:
   AReal d[4];
};

#endif /* ACOLORXYZS_H */
