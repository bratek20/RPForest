// -*- C++ -*-
/* Copyright 1999 
 * Wed Apr 14 10:07:50 1999  Brian Smits  (bes@phoenix.cs.utah.edu)
 * 
 * ASunSky.C
 * 
 *	
 * 
 * $Id: ASunSky.C,v 1.2 1999/07/15 00:07:34 bes Exp $ 
 * 
 */

/**********************************************************
//  TODO							   
// Fix Indexing (make it zero based, not 1 based...)
// ********************************************************/

#ifndef ACOMMON_H
#include <ACommon.H>
#endif

#ifndef ASUNSKY_H
#include <ASunSky.H>
#endif

#ifndef ACOLORXYZV_H
#include <AColorXYZV.H>
#endif

#ifndef ASPECTRALCURVE_H
#include <ASpectralCurve.H>
#endif


#include <stdio.h>
//#include <iostream.h>


/**********************************************************
// Atmospheric Perspective Constants
// 
// ********************************************************/


// density decreses as exp(-alpha*h) alpha in m^-1.
// _1 refers to Haze, _2 referes to molecules.

static AReal const Alpha_1 = 0.83331810215394e-3;
static AReal const Alpha_2 = 0.11360016092149e-3;

#define Nt 20 // Number of bins for theta
#define Np 20 // Number of bins for phi

#define radians(x) ((x)/180.0*APi)

static ASpectrum AT0_1[Nt+1][Np+1];
static ASpectrum AT0_2[Nt+1][Np+1];

/* inline ASpectrum exp(const ASpectrum &in)
 * {
 *     ASpectrum out;
 *     for(int i = 0; i < ASpectrum::GetNumComponents(); i++)
 *       out[i] = exp(in[i]);
 *     return out;
 * }
 */

/* All angles in radians, theta angles measured from normal */
inline AReal AAngleBetween(AReal thetav, AReal phiv, AReal theta, AReal phi)
{
  AReal cospsi = sin(thetav) * sin(theta) * cos(phi-phiv) + cos(thetav) * cos(theta);
  if (cospsi > 1) return 0;
  if (cospsi < -1) return M_PI;
  return  acos(cospsi);
}




ASunSky::ASunSky(AReal lat,
		   AReal longi,
		   int sm,       // standardMeridian
		   int jd,       // julianDay
		   AReal tOfDay,   // timeOfDay
		   AReal turb,
		   bool initAtmEffects) // turbidity
{
    latitude = lat;
    longitude = longi;
    julianDay = jd;
    timeOfDay = tOfDay;
    standardMeridian = sm * 15;  // sm is actually timezone number (east to west, zero based...)
    turbidity = turb;

    V = 4.0; // Junge's exponent.

    InitSunThetaPhi();
    toSun = AVector3(cos(phiS)*sin(thetaS), sin(phiS)*sin(thetaS), cos(thetaS));

    sunSpectralRad =  ComputeAttenuatedSunlight(thetaS, int(turbidity));
    sunSolidAngle =  0.25*APi*1.39*1.39/(150*150);  // = 6.7443e-05

    AReal theta2 = thetaS*thetaS;
    AReal theta3 = theta2*thetaS;
    AReal T = turb;
    AReal T2 = turb*turb;

    AReal chi = (4.0/9.0 - T / 120.0) * (APi - 2 * thetaS);
    zenith_Y = (4.0453 * T - 4.9710) * tan(chi) - .2155 * T + 2.4192;
    //zenith_Y *= 1000;  // conversion from kcd/m^2 to cd/m^2
    zenith_Y *= 0.1;

    zenith_x =
	(+0.00165*theta3 - 0.00374*theta2 + 0.00208*thetaS + 0)          * T2 +
	(-0.02902*theta3 + 0.06377*theta2 - 0.03202*thetaS + 0.00394) * T +
	(+0.11693*theta3 - 0.21196*theta2 + 0.06052*thetaS + 0.25885);

    zenith_y =
	(+0.00275*theta3 - 0.00610*theta2 + 0.00316*thetaS  + 0)          * T2 +
	(-0.04214*theta3 + 0.08970*theta2 - 0.04153*thetaS  + 0.00515) * T +
	(+0.15346*theta3 - 0.26756*theta2 + 0.06669*thetaS  + 0.26688);
      
    perez_Y[1] =    0.17872 *T  - 1.46303;
    perez_Y[2] =   -0.35540 *T  + 0.42749;
    perez_Y[3] =   -0.02266 *T  + 5.32505;
    perez_Y[4] =    0.12064 *T  - 2.57705;
    perez_Y[5] =   -0.06696 *T  + 0.37027;
      
    perez_x[1] =   -0.01925 *T  - 0.25922;
    perez_x[2] =   -0.06651 *T  + 0.00081;
    perez_x[3] =   -0.00041 *T  + 0.21247;
    perez_x[4] =   -0.06409 *T  - 0.89887;
    perez_x[5] =   -0.00325 *T  + 0.04517;
      
    perez_y[1] =   -0.01669 *T  - 0.26078;
    perez_y[2] =   -0.09495 *T  + 0.00921;
    perez_y[3] =   -0.00792 *T  + 0.21023;
    perez_y[4] =   -0.04405 *T  - 1.65369;
    perez_y[5] =   -0.01092 *T  + 0.05291;

    if(initAtmEffects) {
				// Atmospheric Perspective initialization
	CreateConstants();	
	InitA0();
    }
    atmInited = initAtmEffects;
    
}

/**********************************************************
// South = x,  East = y, up = z
// All times in decimal form (6.25 = 6:15 AM)
// All angles in Radians
// ********************************************************/

void ASunSky::SunThetaPhi(AReal &stheta, AReal &sphi) const
{
    sphi = phiS;
    stheta = thetaS;
}

/**********************************************************
// South = x,  East = y, up = z
// All times in decimal form (6.25 = 6:15 AM)
// All angles in Radians
// From IES Lighting Handbook pg 361
// ********************************************************/

void ASunSky::InitSunThetaPhi()
{
    AReal solarTime = timeOfDay +
	(0.170*sin(4*APi*(julianDay - 80)/373) - 0.129*sin(2*APi*(julianDay - 8)/355)) +
	(standardMeridian - longitude)/15.0;

    AReal solarDeclination = (0.4093*sin(2*APi*(julianDay - 81)/368));

    AReal solarAltitude= asin(sin(radians(latitude)) * sin(solarDeclination) -
			       cos(radians(latitude)) * cos(solarDeclination) * cos(APi*solarTime/12));

    AReal opp, adj;
    opp = -cos(solarDeclination) * sin(APi*solarTime/12);
    adj = -(cos(radians(latitude)) * sin(solarDeclination) +
	    sin(radians(latitude)) * cos(solarDeclination) *  cos(APi*solarTime/12));
    AReal solarAzimuth=atan2(opp,adj);

    phiS = -solarAzimuth;
    thetaS = APi / 2.0 - solarAltitude;

}

AVector3 ASunSky::GetSunPosition() const
{
    return toSun;
}

/**********************************************************
// Solar Radiance
// 
// ********************************************************/

ASpectrum ASunSky::GetSunSpectralRadiance() const
{
    return sunSpectralRad;
}

AReal ASunSky::GetSunSolidAngle() const
{
    return sunSolidAngle;
}

/**********************************************************
// Sky Radiance
// 
// ********************************************************/

ASpectrum ASunSky::GetSkySpectralRadiance(const AVector3 &varg) const
{
    AReal theta, phi;
    AUnitVector3 v = varg;
    if (v.Z() < 0) return ASpectrum(0.000000);
    if (v.Z() < 0.001) 
      v = AUnitVector3(v.X(),v.Y(), 0.001f );
    
    theta = acos(v.Z());
    if (fabs(theta)< 1e-5) phi = 0;
    else  phi = atan2(v.Y(),v.X());
    return GetSkySpectralRadiance(theta,phi);
}

inline AReal ASunSky::PerezFunction(const AReal *lam, AReal theta, AReal gamma, AReal lvz) const
{
   AReal den = ((1 + lam[1]*exp(lam[2])) *
		 (1 + lam[3]*exp(lam[4]*thetaS) + lam[5]*cos(thetaS)*cos(thetaS)));
                
   AReal num = ((1 + lam[1]*exp(lam[2]/cos(theta))) *
		 (1 + lam[3]*exp(lam[4]*gamma)  + lam[5]*cos(gamma)*cos(gamma)));

   return lvz* num/den;
}

ASpectrum ASunSky::GetSkySpectralRadiance(AReal theta, AReal phi) const
{
    AReal gamma = AAngleBetween(theta,phi,thetaS,phiS);
				// Compute xyY values
    AReal x = PerezFunction(perez_x, theta, gamma, zenith_x);
    AReal y = PerezFunction(perez_y, theta, gamma, zenith_y);
    AReal Y = PerezFunction(perez_Y, theta, gamma, zenith_Y);

    ASpectrum spect = ChromaticityToSpectrum(x,y);

				// A simple luminance function would be more efficient.
    return Y * spect / AColorXYZV(spect).Y();
}


AVector3 ASunSky::GetSkyxyYRadiance(AReal theta, AReal phi) const  // ANL!!! added, code as ^^ 
{
    AReal gamma = AAngleBetween(theta,phi,thetaS,phiS);
				// Compute xyY values
    AReal x = PerezFunction(perez_x, theta, gamma, zenith_x);
    AReal y = PerezFunction(perez_y, theta, gamma, zenith_y);
    AReal Y = PerezFunction(perez_Y, theta, gamma, zenith_Y);

    return  AVector3(x,y,Y);
}

AVector3 ASunSky::GetSkyxyYRadiance(const AVector3 &varg) const
{
    AReal theta, phi;
    AUnitVector3 v = varg;
    if (v.Z() < 0) return AVector3(0, 0, 0);
    if (v.Z() < 0.001) 
      v = AUnitVector3(v.X(),v.Y(), 0.001f );
    
    theta = acos(v.Z());
    if (fabs(theta)< 1e-5) phi = 0;
    else  phi = atan2(v.Y(),v.X());
    return GetSkyxyYRadiance(theta,phi);
}

/**********************************************************
// Atmospheric perspective functions
// 
// ********************************************************/


/**********************************************************
// Initialization
// 
// ********************************************************/





void ASunSky::CalculateA0(AReal thetav, AReal phiv, ASpectrum &A0_1, ASpectrum &A0_2) const
{
    AReal psi;
    ASpectrum skyRad;
    ASpectrum beta_ang_1, beta_ang_2;
    AReal theta, phi, phiDelta = M_PI/20;
    AReal thetaDelta = M_PI/2/20;
    AReal thetaUpper;
  
    ASpectrum skyAmb_1 = 0;
    ASpectrum skyAmb_2 = 0;
  
    thetaUpper = M_PI / 2;

    for (theta = 0; theta < thetaUpper; theta += thetaDelta)
      for (phi = 0; phi < 2 * M_PI; phi += phiDelta)  {
	  skyRad = GetSkySpectralRadiance(theta, phi);
	  psi = AAngleBetween(thetav, phiv, theta, phi);
	  
	  beta_ang_1 = beta_p_ang_prefix * GetNeta(psi, V);
	  beta_ang_2 = beta_m_ang_prefix * (1+0.9324*cos(psi)*cos(psi));
	  
	  skyAmb_1 += skyRad * beta_ang_1 * sin(theta) * thetaDelta * phiDelta;
	  skyAmb_2 += skyRad * beta_ang_2 * sin(theta) * thetaDelta * phiDelta;
      }
  
    /* Sun's ambience term*/
  
    psi = AAngleBetween(thetav, phiv, thetaS, phiS);

    beta_ang_1 = beta_p_ang_prefix * GetNeta(psi, V);
    beta_ang_2 = beta_m_ang_prefix * (1+0.9324*cos(psi)*cos(psi));
  
    ASpectrum sunAmb_1 = sunSpectralRad * beta_ang_1 * sunSolidAngle;
    ASpectrum sunAmb_2 = sunSpectralRad * beta_ang_2 * sunSolidAngle;
    
				// Sum of sun and sky  (should probably add a ground ambient)
    A0_1 =  (sunAmb_1 + skyAmb_1);
    A0_2 =  (sunAmb_2 + skyAmb_2);
}

void  ASunSky::InitA0() const
{
    int i, j;
    AReal theta, phi;
  
    AReal delTheta = M_PI/Nt;
    AReal delPhi = 2*M_PI/Np;
#ifdef VERBOSE  
    LoggerStr("ggSunSky::Preprocessing: 0%\r");
#endif
    for (i=0,theta = 0; theta<=  M_PI; theta+= delTheta,i++) {
	for (j=0,phi=0; phi <= 2*M_PI; phi+= delPhi,j++)
	  CalculateA0(theta, phi,  AT0_1[i][j], AT0_2[i][j]);
#ifdef VERBOSE	  
    LoggerStr( "ggSunSky::Preprocessing: ");
    LoggerNum( 100*(i*Np+j)/((Nt+1)*Np)   );
    LoggerStr( "%  \r"                    );
#endif
    }
#ifdef VERBOSE    
    LoggerStr("ggSunSky::Preprocessing:  100% \n  ");
#endif    
}      



/**********************************************************
// Evaluation
// 
// ********************************************************/


void ASunSky::GetAtmosphericEffects(const AVector3 &viewer, const AVector3 &source,
				     ASpectrum &attenuation, ASpectrum &inscatter ) const
{
    assert(atmInited);
				// Clean up the 1000 problem
    AReal h0 = viewer.z+1000;//1000 added to make sure ray doesnt
				//go below zero. 
    AUnitVector3 direction = source - viewer;
    AReal thetav = acos(direction.Z());
    AReal phiv = atan2(direction.Y(),direction.X());
    AReal s = glm::length(viewer - source);


    // This should be changed so that we don't need to worry about it.
    if(h0+s*cos(thetav) <= 0)
    {
	attenuation = 1;
	inscatter = 0;
#ifdef VERBOSE	
	LoggerStr("\nWarning: Ray going below earth's surface \n");
#endif 
	return;
    }

    attenuation = AttenuationFactor(h0, thetav, s);
    inscatter   = InscatteredRadiance(h0, thetav, phiv, s);
}


inline AReal EvalFunc(AReal B, AReal x)
{
    if (fabs(B*x)< 0.01) return x;
    return (1-exp(-B*x))/B;
}


ASpectrum ASunSky::AttenuationFactor(AReal h0, AReal theta, AReal s) const
{
    AReal costheta = cos(theta);
    AReal B_1 = Alpha_1 * costheta;
    AReal B_2 = Alpha_2 * costheta;
    AReal constTerm_1 = exp(-Alpha_1*h0) * EvalFunc(B_1, s);
    AReal constTerm_2 = exp(-Alpha_2*h0) * EvalFunc(B_2, s);
  
    return (exp(-beta_p * constTerm_1) *
	    exp(-beta_m * constTerm_2));
}




static void GetA0fromTable(AReal theta, AReal phi, ASpectrum &A0_1, ASpectrum &A0_2)
{
  AReal eps = 1e-4;
  if (phi < 0) phi += 2*M_PI; // convert phi from -pi..pi to 0..2pi
  theta = theta*Nt/M_PI - eps;
  phi = phi*Np/(2*M_PI) - eps;
  if (theta < 0) theta = 0;
  if (phi < 0) phi = 0;
  int i = (int) theta;
  AReal u = theta - i;
  int j = (int)phi;
  AReal v = phi - j;

  A0_1 = (1-u)*(1-v)*AT0_1[i][j] + u*(1-v)*AT0_1[i+1][j]
    + (1-u)*v*AT0_1[i][j+1] + u*v*AT0_1[i+1][j+1];
  A0_2 = (1-u)*(1-v)*AT0_2[i][j] + u*(1-v)*AT0_2[i+1][j]
    + (1-u)*v*AT0_2[i][j+1] + u*v*AT0_2[i+1][j+1];
}

inline AReal AHelper1(AReal A, AReal B, AReal C, AReal D,
			AReal H, AReal K, AReal u)
{
    AReal t = exp(-K*(H-u));
    return (t/K)*((A*u*u*u + B*u*u + C*u +D) -
		  (3*A*u*u + 2*B*u + C)/K +
		  (6*A*u + 2*B)/(K*K) -
		  (6*A)/(K*K*K));
}

inline void ACalculateABCD(AReal a, AReal b, AReal c, AReal d, AReal e,
			    AReal den, AReal &A, AReal &B, AReal &C, AReal &D)
{
    A = (-b*d -2 + 2*c + a*e - b*e + a*d)/den;
    B = -(2*a*a*e + a*a*d - 3*a - a*b*e +
	  3*a*c + a*b*d - 2*b*b*d - 3*b - b*b*e + 3*b*c)/den;
    C =( -b*b*b*d - 2*b*b*a*e -   b*b*a*d + a*a*b*e +
	2*a*a*b*d - 6*a*b     + 6*b*a*c   + a*a*a*e)/den;
    D = -(   b*b*b - b*b*b*a*d - b*b*a*a*e + b*b*a*a*d
	  -3*a*b*b + b*e*a*a*a - c*a*a*a + 3*c*b*a*a)/den;
}

ASpectrum ASunSky::InscatteredRadiance(AReal h0, AReal theta, AReal phi, AReal s) const
{
    AReal costheta = cos(theta);
    AReal B_1 = Alpha_1*costheta;
    AReal B_2 = Alpha_2*costheta;
    ASpectrum A0_1; 
    ASpectrum A0_2;
    ASpectrum result;
    int i;
    ASpectrum I_1, I_2;
  
    GetA0fromTable(theta, phi, A0_1, A0_2);

    // approximation (< 0.3 for 1% accuracy)
    if (fabs(B_1*s) < 0.3) {
	AReal constTerm1 =  exp(-Alpha_1*h0);
	AReal constTerm2 =  exp(-Alpha_2*h0);

	ASpectrum C_1 = beta_p * constTerm1;
	ASpectrum C_2 = beta_m * constTerm2;
	    
	for(int i = 0; i < ASpectrum::GetNumComponents(); i++) {
	    I_1[i] =  (1-exp(-(B_1 + C_1[i] + C_2[i]) * s)) / (B_1 + C_1[i] + C_2[i]);
	    I_2[i] =  (1-exp(-(B_2 + C_1[i] + C_2[i]) * s)) / (B_2 + C_1[i] + C_2[i]);
	}

	return A0_1 * constTerm1 * I_1 + A0_2 * constTerm2 * I_2;
    }

    // Analytical approximation
    AReal A,B,C,D,H1,H2,K;
    AReal u_f1, u_i1,u_f2, u_i2, int_f, int_i, fs, fdashs, fdash0;
    AReal a1,b1,a2,b2;
    AReal den1, den2;

    b1 = u_f1 = exp(-Alpha_1*(h0+s*costheta));
    H1 = a1 = u_i1 = exp(-Alpha_1*h0);
    b2 = u_f2 = exp(-Alpha_2*(h0+s*costheta));
    H2 = a2 = u_i2 = exp(-Alpha_2*h0);
    den1 = (a1-b1)*(a1-b1)*(a1-b1);
    den2 = (a2-b2)*(a2-b2)*(a2-b2);
    
    for (i = 0; i < ASpectrum::GetNumComponents(); i++) {
	// for integral 1
	K = beta_p[i]/(Alpha_1*costheta);
	fdash0 = -beta_m[i]*H2;
	fs = exp(-beta_m[i]/(Alpha_2*costheta)*(u_i2 - u_f2));
	fdashs = -fs*beta_m[i]*u_f2;

	ACalculateABCD(a1,b1,fs,fdash0,fdashs,den1,A,B,C,D);
	int_f = AHelper1(A,B,C,D,H1,K, u_f1);
	int_i = AHelper1(A,B,C,D,H1,K, u_i1);
	I_1[i] = (int_f - int_i)/(-Alpha_1*costheta);

	// for integral 2
	K = beta_m[i]/(Alpha_2*costheta);
	fdash0 = -beta_p[i]*H1;
	fs = exp(-beta_p[i]/(Alpha_1*costheta)*(u_i1 - u_f1));
	fdashs = -fs*beta_p[i]*u_f1;

	ACalculateABCD(a2,b2,fs,fdash0, fdashs, den2, A,B,C,D);
	int_f = AHelper1(A,B,C,D,H2,K, u_f2);
	int_i = AHelper1(A,B,C,D,H2,K, u_i2);
	I_2[i] = (int_f - int_i)/(-Alpha_2*costheta);

    }
    return A0_1 * I_1 + A0_2 * I_2;
}


