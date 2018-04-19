#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "IIR.h"

static double *stateBuffer = NULL;
static double *nominatorBuffer = NULL;
static double *denomBuffer = NULL;
static int amountTaps = 0;

int 
InitIIR(const double* stateTaps, const double* nomTaps, 
		const double*denomTaps, int amount_taps)
{
	int i=0;
	double norm = denomTaps[0];

	assert(stateBuffer == 0);
	assert(nominatorBuffer == 0);
	assert(denomBuffer == 0);

	assert(stateTaps);
	assert(nomTaps);
	assert(denomTaps);

	amountTaps = amount_taps;
	stateBuffer = (double*) malloc(sizeof(double)*amountTaps);
	nominatorBuffer = (double*) malloc(sizeof(double)*amountTaps);
	denomBuffer = (double*) malloc(sizeof(double)*amountTaps);

	for (i=0; i< amountTaps; i++)
	{
		stateBuffer[i] = stateTaps[i];
		nominatorBuffer[i] = nomTaps[i];
		denomBuffer[i] = denomTaps[i]/norm;
	}
	return(1);
}

int
TerminateIIR()
{
	assert(stateBuffer);
	assert(nominatorBuffer);
	assert(denomBuffer);

	free(stateBuffer);
	free(nominatorBuffer);
	free(denomBuffer);

	stateBuffer = NULL;
	nominatorBuffer = NULL;
	denomBuffer = NULL;

	amountTaps = 0;
	return(1);
}

int 
ExecuteIIRDF1(const double *frame_in, double *frame_out, int amount_values)
{
	int i,j;

  	for(i=0; i< amount_values; i++)
  	{
		frame_out[i] = nominatorBuffer[0] * frame_in[i] +stateBuffer[0];
  		for(j =1; j < amountTaps; j++)
		{
			stateBuffer[j-1] = stateBuffer[j] + frame_in[i] * nominatorBuffer[j] - 
				frame_out[i] * denomBuffer[j];
		}
	}
	return(1);
}


int 
ExecuteIIRDF2(const double *frame_in, double *frame_out, int amount_values)
{
	double temp;
	int i = 0;
	int j = 0;
	for(i=0; i< amount_values; i++)
	{
		temp =0;
		stateBuffer[0] = frame_in[i];
		for(j=amountTaps-1; j> 0; j--)
		{
			temp += stateBuffer[j] * nominatorBuffer[j];
			stateBuffer[0] += -(stateBuffer[j] * denomBuffer[j]);
			stateBuffer[j] = stateBuffer[j-1];
		}
		temp += nominatorBuffer[0] * stateBuffer[0];
		frame_out[i] = temp;
	}
	return(1);
}

int 
SetStatesIIR(const double* states)
{
	assert(states);
	memcpy(stateBuffer, states, sizeof(double) * amountTaps);
	return(1);
}

int 
ReturnStatesIIR(double* stateReturn)
{
	assert(stateReturn);
	assert(stateBuffer);
	memcpy(stateReturn, stateBuffer, sizeof(double) * amountTaps);
	return(1);
}


