// -*- C++ -*-
#ifndef ASUNSKY_H
#define ASUNSKY_H
/* Copyright 1999 
 * Mon Apr 19 13:42:11 1999  Brian Smits  (bes@phoenix.cs.utah.edu)
 * 
 * ASunSky.H
 * 
 *	
 * 
 * $Id: ASunSky.H,v 1.1 1999/06/10 20:12:32 bes Exp $ 
 * 
 */

#ifndef ACOMMON_H
#include <ACommon.H>
#endif

#ifndef ASPECTRUM_H
#include <ASpectrum.H>
#endif

#ifndef AVECTOR3_H
#include <AVector3.H>
#endif

/***************************************************************
CLASS
    ASunSky
     <one line summary> 

DESCAPTION
     <Detailed description with any warnings>

****************************************************************/

class ASunSky {
  public:
				// GROUP: Constructors and assignment
				//// Constructs an ASunSky based on
				// [in] lat Latitude (0-360)
				// [in] long Longitude (-90,90) south to north
				// [in] sm  Standard Meridian
				// [in] jd  Julian Day (1-365)
				// [in] tod Time Of Day (0.0,23.99) 14.25 = 2:15PM
				// [in] turb  Turbidity (1.0,30+) 2-6 are most useful for clear days.
				// [in] initAtmEffects  if atm effects are not initialized, bad things will
				// happen if you try to use them....
    ASunSky(AReal lat, AReal longi, int sm, int jd, AReal tod, AReal turb,bool initAtmEffects = true);
				// GROUP: Members
				////  Position (actual Direction) of the sun
				// South = +x,  East = +y, up = +z
    AVector3  	GetSunPosition() const;
				//// [out] theta  Sun angle down? from straight above
				//   [out] phi    Sun angle around from South? 
    void 	SunThetaPhi(AReal &theta, AReal &phi) const;  
				////  Spectral radiance making it to the earth's surface
    ASpectrum 	GetSunSpectralRadiance() const;
				////  Solid angle of the sun (constant
    AReal	GetSunSolidAngle() const;
				//// Spectral radiance of the sky in the specified direction
    ASpectrum  GetSkySpectralRadiance(const AVector3 &v) const;
				//// An alternate way of getting the sky's spectral radiance
    ASpectrum  GetSkySpectralRadiance(AReal theta, AReal phi) const;

	AVector3   GetSkyxyYRadiance(const AVector3 &varg) const;
    AVector3   GetSkyxyYRadiance(AReal theta, AReal phi) const;
				////  Compute Atmospheric Perspective based on
				// [in] viewer  Position of the viewer
				// [in] source  Position of the distant point
				// [out] atmAttenuation Attenuation due to atmosphere
				// [out] atmInscatter  Amount of light scattered into the viewing direction
    void GetAtmosphericEffects(const AVector3 &viewer,
			       const AVector3 &source,
			       ASpectrum &atmAttenuation,
			       ASpectrum &atmInscatter ) const;
  private:
				//// Copy Constructor (unimplemented)
    ASunSky(const ASunSky &);
				//// Assignment (unimplemented)
    ASunSky &operator=(const ASunSky &);
				//// Compute the sun's position based on IES Sunlight Publication ????
    void 	InitSunThetaPhi();
				//// Transmittance for the sun weighted by sun's spectrum.
    ASpectrum ComputeAttenuatedSunlight(AReal theta, int turbidity);
				//// Conversion from xy to a Spectrum
    ASpectrum ChromaticityToSpectrum(AReal x, AReal y) const;
				// GROUP:  AAtmPerspective.C Functions
				////
    ASpectrum AttenuationFactor(AReal h0, AReal thetav, AReal s) const;
				////
    ASpectrum InscatteredRadiance(AReal h0, AReal thetav, AReal
				   phiv, AReal s) const;
				////
    ASpectrum GetNeta(AReal theta, AReal v) const;
				////
    void CalculateA0(AReal thetav, AReal phiv, ASpectrum& A0_1, ASpectrum& A0_2) const;
				////
    void CreateConstants();
				//// Preprocessing for calculating ambient scattered light for all
				//  directions
    void InitA0() const;
				////
    AReal PerezFunction(const AReal *lam, AReal theta, AReal phi, AReal lvz) const;
				//Group: Data
    AReal 	latitude, longitude;
    int 	julianDay;
    AReal 	timeOfDay;
    int 	standardMeridian;
    AReal 	turbidity;
				//// Sun Position Vector
    AVector3 	toSun;
				//// Sun Position
    AReal	thetaS, phiS;
				//// Spectral Radiance computed at creation time
    ASpectrum 	sunSpectralRad;
				//// Solid angle of the sun when seen from earth
    AReal 	sunSolidAngle;
				//// Perez data
    AReal zenith_Y, zenith_x, zenith_y;
				//// Perez coefficients (change to 5 when arrays become zero based)
    AReal perez_Y[6], perez_x[6], perez_y[6];
				// GROUP: Constants for Atmospheric Perspective
				////
    ASpectrum beta_m, beta_p, beta_m_ang_prefix,  beta_p_ang_prefix;
				////
    AReal	V;
				////
    bool atmInited;
};


#endif /* ASUNSKY_H */
