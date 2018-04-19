#ifndef __REFLAR_H__
#define __REFLAR_H__

/*! Function to convert reflection coefficients into Log Area Ratios */
void
ref2Lar(const double* refCoeffs, double* larCoeffs, int amount);

/*! Function to convert Log Area Ratios into Log Area Ratios */
void
lar2Ref(const double* larCoeffs, double* refCoeffs, int amount);

#endif
