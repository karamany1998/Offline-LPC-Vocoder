#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "FIR.h"

static double* stateBuffer = NULL;
static double* multBuffer = NULL;
static int amountTaps = 0;

int 
InitFIR(const double* initial_states, const double* taps, int amount_taps)
{
	int i = 0;

	assert(stateBuffer == NULL);
	assert(multBuffer == NULL);
	assert(taps);
	assert(initial_states);

	amountTaps = amount_taps;

	stateBuffer = (double*) malloc(sizeof(double) * amount_taps);
	multBuffer = (double*) malloc(sizeof(double) * amount_taps);


	for(i = 0; i < amountTaps; i ++)
	{
		stateBuffer[i] = initial_states[i];
		multBuffer[i] = taps[i];
	}
	return(1);
}

int 
TerminateFIR()
{
	assert(stateBuffer);
	free(stateBuffer);
	stateBuffer = NULL;

	assert(multBuffer);
	free(multBuffer);
	multBuffer = NULL;
	amountTaps = 0;
	return(1);
}

int 
ExecuteFIRDF1(const double* inputBuffer, double* outputBuffer, int amount_values)
{
	int i = 0;
	int j = 0;

	assert(amount_values > amountTaps);

	for(i = 0; i< amount_values; i++)
	{
		outputBuffer[i] = inputBuffer[i] * multBuffer[0] +stateBuffer[0];
		for(j = 1; j < amountTaps; j++)
		{
			stateBuffer[j-1] = stateBuffer[j] + inputBuffer[i] * multBuffer[j];
		}
	}
	return(1);
}

int 
ExecuteFIRDF2(const double* inputBuffer, double* outputBuffer, int amount_values)
{
	int i = 0;
	int j = 0;

	assert(amount_values > amountTaps);

	for(i=0; i<amount_values;i++)
	{
		stateBuffer[0] = inputBuffer[i];
		outputBuffer[i] = 0;
		for(j = amountTaps-1; j>0; j--)
		{
			outputBuffer[i] += stateBuffer[j] * multBuffer[j];
			stateBuffer[j] = stateBuffer[j-1];
		}
		outputBuffer[i] += stateBuffer[0] * multBuffer[0];
	}
	return(1);
}

int 
ExecuteFIRDF1Long(const double* inputBuffer, double* outputBuffer, int amount_values)
{
	int i = 0;
	int j = 0;

/*	assert(amount_values > amountTaps);*/

	for(i = 0; i< amount_values; i++)
	{
		outputBuffer[i] = inputBuffer[i] * multBuffer[0] +stateBuffer[0];
		for(j = 1; j < amountTaps; j++)
		{
			stateBuffer[j-1] = stateBuffer[j] + inputBuffer[i] * multBuffer[j];
		}
	}
	return(1);
}

int 
ExecuteFIRDF2Long(const double* inputBuffer, double* outputBuffer, int amount_values)
{
	int i = 0;
	int j = 0;

/*	assert(amount_values > amountTaps);*/

	for(i=0; i<amount_values;i++)
	{
		stateBuffer[0] = inputBuffer[i];
		outputBuffer[i] = 0;
		for(j = amountTaps-1; j>0; j--)
		{
			outputBuffer[i] += stateBuffer[j] * multBuffer[j];
			stateBuffer[j] = stateBuffer[j-1];
		}
		outputBuffer[i] += stateBuffer[0] * multBuffer[0];
	}
	return(1);
}


int 
SetStatesFIR(const double* states)
{
	assert(states);
	memcpy(stateBuffer, states, sizeof(double)*amountTaps);
	return(1);
}

int
ReturnStatesFIR(double* states)
{
	assert(states);
	memcpy(states, stateBuffer, sizeof(double)*amountTaps);
	return(1);
}
