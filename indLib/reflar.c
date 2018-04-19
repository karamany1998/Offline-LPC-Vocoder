#include "reflar.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void
ref2Lar(const double* refCoeffs, double* larCoeffs, int amount)
{
	int i =0;
	for(i=0; i< amount; i++)
	{
		larCoeffs[i] = log((1+refCoeffs[i])/(1-refCoeffs[i]));
	}
}

void
lar2Ref(const double* larCoeffs, double* refCoeffs, int amount)
{
	int i = 0;
	for(i=0; i< amount; i++)
	{
		refCoeffs[i] = -( (1-exp(larCoeffs[i])))/(1+exp(larCoeffs[i]));
	}
}
