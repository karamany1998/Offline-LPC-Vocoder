#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include "autocorrelation.h"

/* Determine the windowed correlation function */
void
autoCorrelation(double* correlation, const double* correlationWindow, int amountCorr,
				const double* xin, const double* speechWindow, int amountSpeechSamples)
{
	int i,j;

	for(i=0; i< amountCorr; i++)
	{
		correlation[i] =0;
		for(j=0; j<(amountSpeechSamples-i);j++)
		{
			correlation[i] += xin[j]*speechWindow[j] * xin[i+j]*speechWindow[i+j];

		}
		correlation[i] = correlation[i]*correlationWindow[i];
	}
	if(correlation[0]<1.0)
		correlation[0] = 1.0;
}
