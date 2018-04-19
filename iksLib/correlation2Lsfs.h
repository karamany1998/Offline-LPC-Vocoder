#ifndef CORRELATION2LSFS_H__
#define CORRELATION2LSFS_H__

/*! 
 * Function to determine the (amountCorrelation-1) reflection (PARCOR) 
 * coefficients based on the amountCorrelation correlation coefficients */
int correlation2Lsfs( const double *correlation, double *lsps, 
					   double *reflectionCoeffs, 
					   int amountCorrelation);

#endif
