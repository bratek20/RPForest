#ifndef ASPECTRUM_H
#define ASPECTRUM_H
/********************************************************************
 * BaseGLIB   Andrzej Lukaszewski
 *
 * Spectrum
 *
 * CLASSES:
 *            ASpectrum 
 *            function const on maybe unequal intervals, 
 ********************************************************************/

#ifndef AMATH_H
#include <ABase.H>
#endif

#define A_SPECTRUM_MIN_LAMBDA 380
#define A_SPECTRUM_MAX_LAMBDA 720
#define A_SPECTRUM_N_LAMBDA 10


class ASpectrum { // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
public:
   ASpectrum();
   ASpectrum(AReal v);  // const spectrum
   
   static int 	GetNumComponents();
   static AReal GetMinLambda();
   static AReal GetMaxLambda();
   static AReal GetBinWidth(int i);
   static ASpectrum FromRGB(AReal red, AReal blue, AReal green);
   AReal& operator[] (int i);
   AReal operator[] (int i) const;
   AReal GetValue( AReal wavelength ) const;

   int  GetIndexAtWavelength( AReal lambda ) const;
   void GetIndexAtWavelength(AReal lambda, int& i, AReal& t) const;
   AReal GetArea() const;
   AReal GetArea(AReal l1, AReal l2) const;
   AReal GetMinValue() const;
   AReal GetMaxValue() const;
   AReal GetAvgValue() const;

   const ASpectrum &operator=( const ASpectrum & ) ;
   const ASpectrum &operator-=( const ASpectrum& ) ;
   const ASpectrum &operator+=( const ASpectrum& ) ;
   const ASpectrum &operator*=( const ASpectrum& ) ;
   const ASpectrum &operator/=( const ASpectrum& ) ;
   const ASpectrum &operator*=( AReal) ;
   const ASpectrum &operator/=( AReal) ;
   ASpectrum operator-() const;
   ASpectrum operator+() const;
   ASpectrum operator+( const ASpectrum& ) const;
   ASpectrum operator-( const ASpectrum& ) const;
   ASpectrum operator*( const ASpectrum& ) const;
   ASpectrum operator/( const ASpectrum& ) const;
   ASpectrum operator*( AReal d ) const;
   ASpectrum operator/( AReal d ) const;
   bool operator==( const ASpectrum& ) const;
   bool operator!=( const ASpectrum& ) const;

private:
   static AReal GetBinWidth();
   AReal data[A_SPECTRUM_N_LAMBDA];
};


/********************************************************************
 * Implementations 
 ********************************************************************/ 
inline ASpectrum operator*( AReal lhs,  const ASpectrum& rhs)
{
   return rhs * lhs;
}

inline ASpectrum::ASpectrum() {
}


inline ASpectrum::ASpectrum(AReal v) {
   for (int i = 0; i < A_SPECTRUM_N_LAMBDA; i++)
      data[i] = v;
}

inline int ASpectrum::GetNumComponents() {
   return A_SPECTRUM_N_LAMBDA;
}

inline AReal ASpectrum::GetMinLambda(){ 
   return A_SPECTRUM_MIN_LAMBDA; 
}

inline AReal ASpectrum::GetMaxLambda(){ 
   return A_SPECTRUM_MAX_LAMBDA; 
}

inline AReal ASpectrum::GetBinWidth(int i){
   return (A_SPECTRUM_MAX_LAMBDA-A_SPECTRUM_MIN_LAMBDA)/A_SPECTRUM_N_LAMBDA ;
}

inline AReal& ASpectrum::operator[] (int i) {
   assert( i >= 0 );
   assert( i < A_SPECTRUM_N_LAMBDA );
   return data[i];
}

inline AReal ASpectrum::operator[] (int i) const {
   assert( i >= 0 );
   assert( i < A_SPECTRUM_N_LAMBDA );
   return data[i];
}

inline ASpectrum exp(const ASpectrum &in)
{
   ASpectrum out;
   //  for(int i = 0; i < A_SPECTRUM_N_LAMBDA; i++)
   for(int i = 0; i < ASpectrum::GetNumComponents(); i++)
      out[i] = exp(in[i]);
   return out;
}

#endif /* ASPECTRUM_H */
