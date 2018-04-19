#ifndef __LPCREF_H__
#define __LPCREF_H__

/* This file includes all functions required for a transformation 
 * between LPC and reflection coefficients */

/*! Convert reflection coeffs into LPCs */
void 
ref2Lpc(const double* refCoeffs, int amountRefCoeffs,
			 double* lpcCoeffs);



/*! Convert LPCs into reflection coeffs */
void 
lpc2Ref(const double* lpcCoeffs, int amountLPCCoeffs, double* refCoeffs);

#endif
