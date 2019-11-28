#ifndef ASPECTRALCURVE_H
#define ASPECTRALCURVE_H

#ifndef ASPECTRUM_H
#include <ASpectrum.H>
#endif


/***************************************************************
CLASS
    ASpectralCurve
    An abstract class that represents a function over the visible
    spectrum. A_SPECTRUM_MIN_LAMBDA to A_SPECTRUM_MAX_LAMBDA

DESCRIPTION
    This class allows us to represent any spectral data.  ASpectrum
    can then use this interface to convert any arbitrary spectral data
    to an ASpectrum.  There are minimal restrictions on this class.
    It will be used to represent energy, sensitivity curves, and
    possibly reflectances.

PATTERN
    abstract function

WARNING
    The conversion operator to ASpectrum samples the spectral function
    at 1nm increments.  If you have data that contains higher frequencies,
    (sodium vapor lamp maybe, lazer) either smooth it a little or
    write your own conversion operator if you want to get an ASpectrum out of it.
    Obviously, an ASpectrum is a really bad represenation of the original
    data.
****************************************************************/

class ASpectralCurve {
public:
   //// Virtual destructor so everything works fine for derived classes
   virtual ~ASpectralCurve() {}
   //// Conversion operator to ASpectrum
   virtual operator ASpectrum() const;
   //// Return the value of the function at lambda
   virtual AReal GetValue(AReal lambda) const = 0;
   //// overload the function call operator for convenience
   AReal operator()(AReal lambda) const {return GetValue(lambda);}
protected:
   //// allow a little efficiency into the conversion to Spectrum
   ASpectrum Integrate(AReal stepSize) const;
};


/***************************************************************
CLASS
    ARegularSpectralCurve
    A spectral curve from regularly spaced samples

DESCAPTION
     This class takes a set of numSamples regularly spaced samples from a
     minLambda to a maxLambda represented as an array of AReals.  

WARNINGS
     The user is responsible for deleting the array passed in.  ARegularSpectralCurve
     makes it's own internal copy.
****************************************************************/

class ARegularSpectralCurve : public ASpectralCurve {
public:
   // GROUP: Constructors and assignment
   //// Constructor [in] data Array of values
   //               [in] minLambda  starting lambda for the data
   //               [in] maxLambda  ending lambda for the data
   //               [in] numSamples total number of samples
   ARegularSpectralCurve(const float  *data, AReal minLambda, AReal maxLambda,
                         int numSamples);
   ARegularSpectralCurve(const double *data, AReal minLambda, AReal maxLambda,
                         int numSamples);
   //// Destructor deletes the internal data array
   ~ARegularSpectralCurve();
   // GROUP: Members
   //// returns the linearly interpolated value of the function at lambda
   virtual AReal GetValue(AReal lambda) const;
private:
   //// Copy constructor
   ARegularSpectralCurve(const ARegularSpectralCurve &);
   //// Assignment
   ARegularSpectralCurve& operator=( const ARegularSpectralCurve &);
   AReal 	*data;
   AReal 	 minLambda, maxLambda;
   int	 	 numSamples;
   AReal	 width;
};


/***************************************************************
CLASS
    AIrregularSpectralCurve
     A ASpectralCurve represented by irregular data points

DESCAPTION
     A ASpectralCurve represented by irregular data points.  The user passes in two arrays,
     one representing the values of the spectral curve, the other representing the wavelengths
     corresponding to those values.

WARNINGS
     The user is responsible for deleting the array passed in.  ARegularSpectralCurve
     makes it's own internal copy.
     The wavelength samples (lambda) must be strictly increasing.
****************************************************************/

class AIrregularSpectralCurve : public ASpectralCurve {
public:
   // GROUP: Constructors and assignment
   //// Default Constructor
   AIrregularSpectralCurve(const AReal *data, const AReal *lambda, int numSamples);
   //// Constructor for incremental creation
   AIrregularSpectralCurve(int numSamples);
   //// Destructor
   ~AIrregularSpectralCurve();
   //// Build the data incrementally (useful for reading)
   void SetSample(int sample, AReal value, AReal lambda);
   // GROUP: Members
   //// returns the linearly interpolated value of the function at lambda
   virtual AReal GetValue(AReal lambda) const;
private:
   //// Copy constructor makes sure adoptData isn't passed along
   AIrregularSpectralCurve(const AIrregularSpectralCurve &);
   //// Assignment  makes sure adoptData isn't passed along.
   AIrregularSpectralCurve& operator=( const AIrregularSpectralCurve &);
   AReal 	*data;
   AReal	*lambda;
   int	 	 numSamples;
};



/***************************************************************
CLASS
    ACombinedSpectralCurve
     Create a ASpectralCurve that is the linear combination of some other
     set of ASpectralCurve.

DESCAPTION
     Takes 2,3, or 4 ASpectralCurve and weights, and returns the weighted
     sum of the curves at each lambda.  

WARNINGS
      The user is responsible for deleting the ASpectralCurves when done with
      the ACombinedSpectralCurve.  The user must not delete them before then.
****************************************************************/

class ACombinedSpectralCurve : public ASpectralCurve {
public:
   // GROUP: Constructors and assignment
   //// Default Constructor
   ACombinedSpectralCurve();
   //// Linearly combine 2 curves
   ACombinedSpectralCurve(const ASpectralCurve *c0, AReal w0, const ASpectralCurve *c1, AReal w1);
   //// Linearly combine 3 curves
   ACombinedSpectralCurve(const ASpectralCurve *c0, AReal w0, const ASpectralCurve *c1, AReal w1,
                          const ASpectralCurve *c2, AReal w2);
   //// Linearly combine 4 curves
   ACombinedSpectralCurve(const ASpectralCurve *c0, AReal w0, const ASpectralCurve *c1, AReal w1,
                          const ASpectralCurve *c2, AReal w2, const ASpectralCurve *c3, AReal w3);
   ////Copy Constructor
   ACombinedSpectralCurve(const ACombinedSpectralCurve &);
   //// Assignment
   ACombinedSpectralCurve &operator=(const ACombinedSpectralCurve &);
   // GROUP: Members
   //// Return the weighted sum of the curves
   virtual AReal GetValue(AReal lambda) const;
private:
   const ASpectralCurve  	*curve[4];
   AReal		 	 weight[4];
   int			 	 numCurves;
};



#endif /* ASPECTRALCURVE_H */
