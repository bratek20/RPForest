#include <string.h>

#ifndef ACOMMON_H
//#include <ACommon.H>
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
                                                                                
/* TO IMPLEMENT (EMPTY):
 * v   AIrregularSpectralCurve::~AIrregularSpectralCurve [in-charge]()
 * v   AIrregularSpectralCurve::AIrregularSpectralCurve[in-charge](float const*, float const*, int)
 * v   ARegularSpectralCurve::~ARegularSpectralCurve [in-charge]()
 * v   ARegularSpectralCurve::ARegularSpectralCurve[in-charge](float const*, float, float, int)
 * TODO
 * v   ASpectrum::operator-() const
 * v   ASpectrum::operator/(float) const
 * v   ASpectrum::operator*(float) const
 * v   ASpectrum::operator=(ASpectrum const&)
 * v   ASpectrum::operator+=(ASpectrum const&)
 * v   ASpectrum::operator*(ASpectrum const&) const
 * v   ASpectrum::operator+(ASpectrum const&) const
 */

AIrregularSpectralCurve::AIrregularSpectralCurve(const AReal *data, 
				      const AReal *lambda, int numSamples){
   this->data   = new AReal[numSamples];
   memcpy(this->data,   data,   numSamples * sizeof(AReal) );
   this->lambda = new AReal[numSamples];
   memcpy(this->lambda, lambda, numSamples * sizeof(AReal) );
   this->numSamples = numSamples;
}

AIrregularSpectralCurve::~AIrregularSpectralCurve(){
   delete[] data;
   delete[] lambda;
}

ARegularSpectralCurve::ARegularSpectralCurve(const float  *data, 
			AReal minLambda, AReal maxLambda, int numSamples){
   this->data   = new AReal[numSamples];
   memcpy(this->data,   data,   numSamples * sizeof(AReal) );
   this->minLambda  = minLambda;
   this->maxLambda  = maxLambda;
   this->numSamples = numSamples;
}

ARegularSpectralCurve::ARegularSpectralCurve(const double *data, 
			AReal minLambda, AReal maxLambda, int numSamples){
   this->data   = new AReal[numSamples];
   memcpy(this->data,   data,   numSamples * sizeof(AReal) );
   this->minLambda  = minLambda;
   this->maxLambda  = maxLambda;
   this->numSamples = numSamples;
}

ARegularSpectralCurve::~ARegularSpectralCurve(){
   delete[] data;
}

AReal AIrregularSpectralCurve::GetValue(AReal lambda) const {  // ANL!!!: not effective search
   int l=0;
   while (lambda>this->lambda[l] && l<numSamples) l++;
   if (l>=numSamples)    return this->data[l-1];
   return this->data[l];
}

AReal ARegularSpectralCurve::GetValue(AReal lambda) const {
   int l = int(((numSamples-1)*(lambda - minLambda)) / (maxLambda - minLambda));
   return this->data[l];
}



ASpectralCurve::operator ASpectrum() const {
  ASpectrum S;
  AReal Jump=(S.GetMaxLambda()-S.GetMinLambda())/S.GetNumComponents();

  for (int l=0; l<S.GetNumComponents(); l++ ) {
     S[l] = 0; 
     AReal Shift=0;
     while (Shift<Jump) {   // Sample at 1nm
        S[l] += this->GetValue(S.GetMinLambda() + l*Jump + Shift );
        Shift ++;
     }
     S[l] /= Jump;
  }
  return S;
}



ASpectrum ASpectrum::operator-() const {
  ASpectrum S;
  for (int l=0; l<this->GetNumComponents(); l++)  S.data[l] = - this->data[l];
  return S;
}

ASpectrum ASpectrum::operator*( AReal r) const {
  ASpectrum S;
  for (int l=0; l<this->GetNumComponents(); l++)  S.data[l] = this->data[l] * r;
  return S;
}

ASpectrum ASpectrum::operator/( AReal r) const {
  ASpectrum S;
  for (int l=0; l<this->GetNumComponents(); l++)  S.data[l] = this->data[l] / r;
  return S;
}

const ASpectrum& ASpectrum::operator=(  const ASpectrum& s ) {
  for (int l=0; l<s.GetNumComponents(); l++)  data[l]  = s.data[l];
  return (*this);
}

const ASpectrum& ASpectrum::operator+=( const ASpectrum& s ) {
  for (int l=0; l<s.GetNumComponents(); l++)  data[l] += s.data[l];
  return (*this);
}

ASpectrum ASpectrum::operator*( const ASpectrum& s) const {
  ASpectrum S;
  for (int l=0; l<this->GetNumComponents(); l++)  S.data[l] = this->data[l] * s.data[l];
  return S;
}

ASpectrum ASpectrum::operator+( const ASpectrum& s) const {
  ASpectrum S;
  for (int l=0; l<this->GetNumComponents(); l++)  S.data[l] = this->data[l] + s.data[l];
  return S;
}



AReal ASpectrum::GetArea() const {
  AReal A=0;
  for (int l=0; l<GetNumComponents(); l++)  
     A += data[l] * GetBinWidth(l);
  return A;
}

// ----------___END ------------------------------------------------------------------------------------------------


/* inline ASpectrum ASpectrum::operator-() const {
 * //    return AVector3(-V[0], -V[1], -V[2]);
 *     return ASpectrum(*this);
 * }
 * 
 * inline const ASpectrum &ASpectrum::operator=(const ASpectrum &v) {
 * //    V[0] = v.V[0];
 * //    V[1] = v.V[1];
 * //    V[2] = v.V[2];
 *     return *this;
 * }
 * 
 * //inline ASpectrum ASpectrum::operator+=(const ASpectrum &v) {
 * inline const ASpectrum& ASpectrum::operator+=(const ASpectrum &v) {
 * //    V[0] += v.V[0];
 * //    V[1] += v.V[1];
 * //    V[2] += v.V[2];
 *     return *this;
 * }
 * ////////////////////////
 * inline ASpectrum ASpectrum::operator/(AReal v) const {
 *     return *this;
 * }
 * inline ASpectrum ASpectrum::operator*(AReal v) const {
 *     return *this;
 * }
 * inline ASpectrum ASpectrum::operator*(ASpectrum const &v) const {
 *     return *this;
 * }
 * inline ASpectrum ASpectrum::operator+(const ASpectrum &v) const {
 *     return *this;
 * }
 * 
 * 
 * 
 * ////////////////////////
 * inline ASpectrum operator/(const ASpectrum &lhs, const AReal &rhs) {
 * //    return AVector3(lhs.V[0]+rhs.V[0], lhs.V[1]+rhs.V[1], lhs.V[2]+rhs.V[2]);
 *   return ASpectrum(lhs);
 * }
 * 
 * inline ASpectrum operator*(const ASpectrum &lhs, const AReal &rhs) {
 * //    return AVector3(lhs.V[0]+rhs.V[0], lhs.V[1]+rhs.V[1], lhs.V[2]+rhs.V[2]);
 *   return ASpectrum(lhs);
 * }
 * 
 * 
 * inline ASpectrum operator*(const ASpectrum &lhs, const ASpectrum &rhs) {
 * //    return AVector3(lhs.V[0]+rhs.V[0], lhs.V[1]+rhs.V[1], lhs.V[2]+rhs.V[2]);
 *   return ASpectrum(lhs);
 * }
 * 
 * inline ASpectrum operator+(const ASpectrum &lhs, const ASpectrum &rhs) {
 * //    return AVector3(lhs.V[0]+rhs.V[0], lhs.V[1]+rhs.V[1], lhs.V[2]+rhs.V[2]);
 *   return ASpectrum(lhs);
 * }
 * 
 */

#undef inline
