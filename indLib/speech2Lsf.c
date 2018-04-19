#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include "speech2Lsf.h"
#include "autocorrelation.h"
#include "correlation2Lsfs.h"

/* Main function: Determine the LSFs, pass windowing functions as functionpointers.
 * This function is for using multiple windows (quick attempts) only. 
 * To evaluate the complete windowing function in each step is very complex */
int
speech2lsp_functions( double  *xin, double  *lsfs, 
					  int amountSpeechSamples, int amountLsfs, 
					  int middleFromLeft,
					  double(*f_windowSpeech)(int index, int middleFromLeft, 
											  int length), 
					  double(*f_windowCorr)(int index, int length))
{
	double *correlation;
	double *correlationWindow;
	double *speechWindow;
	double *reflect;
	int result = 1;
	int i;
	
	correlation = (double*) malloc(sizeof(double)*(amountLsfs+1));
	correlationWindow = (double*) malloc(sizeof(double)*(amountLsfs+1));
	speechWindow = (double*) malloc(sizeof(double)*(amountSpeechSamples));
	reflect = (double*) malloc(sizeof(double)*(amountLsfs));

	for(i =0; i< amountSpeechSamples; i++)
	{
		speechWindow[i] = f_windowSpeech(i, middleFromLeft, amountSpeechSamples);
	}
	for(i =0; i< (amountLsfs+1); i++)
	{
		correlationWindow[i] = f_windowCorr(i, (amountLsfs+1));
	}

	/* Determine autocorrelation function */
	autoCorrelation(correlation, correlationWindow, (amountLsfs+1),
					xin, speechWindow, amountSpeechSamples);
					
	/* Determine the LSPS */
	result = correlation2Lsfs( correlation, lsfs, reflect, amountLsfs);

	free(correlation);
	free(correlationWindow);
	free(speechWindow);
	free(reflect);
	return(result);
}

/* Main function: Determine the LSFs, pass windowing functions as array.
 * This function should be used for the final version of the coder as
 * the windowing function must only be once evaluated. */
int 
speech2lsp_array( double  *xin, double  *lsfs, 
				  int amountSpeechSamples, int amountLsfs, 
				  double *arrayWindowSpeech, 
				  double *arrayWindowCorrelation)
{
	double *correlation;
	double *reflect;
	int result = 1;

	correlation = (double*) malloc(sizeof(double)*(amountLsfs+1));
	reflect = (double*) malloc(sizeof(double)*(amountLsfs));

	/* Determine the autocorrelation coefficients */
	autoCorrelation(correlation, arrayWindowCorrelation, (amountLsfs+1),
					xin, arrayWindowSpeech, amountSpeechSamples);
					
	/* Based on the CORRS determine the LSFs */
	result = correlation2Lsfs( correlation, lsfs, reflect, amountLsfs);

	free(correlation);
	free(reflect);
	return(result);
}
	



