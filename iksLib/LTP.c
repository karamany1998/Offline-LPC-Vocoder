#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <float.h>

#include "LTP.h"

static int lowRange = 0;
static int uppRange = 0;
static int precision = 1;
static COMPARE_TYPE typeComparison;
static double* previousValues = NULL;
static int bufferSize = 0;

int
InitLTP(const int range_low, const int range_upp, const int prec, 
		const double* statesPrevious, const int buffer_size, COMPARE_TYPE tp)
{
	assert(range_upp > range_low);
	assert(previousValues == NULL);
	
	bufferSize = buffer_size;

	previousValues = (double*) malloc(sizeof(double) * bufferSize);
	memcpy(previousValues, statesPrevious, sizeof(double)*bufferSize);
	
	lowRange = range_low;
	uppRange = range_upp;
	precision = prec;
	typeComparison = tp;

	return(1);
}

int
ExecuteLTP(const double* current_buffer, const int amount_buffer,
		   unsigned int* val_in_range, unsigned int* steps_fraction,
		   double* max_value, double *gain_val)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int indexx = 0;
	unsigned int index_low = 0;
	unsigned int index_prec_low = 0;
	double value_max = -FLT_MAX;
	double gain_val_max = 0.0;
	
	double i_value = 0.0;
	double i_p_1_value = 0.0;

	double nom_max_val = 0.0;
	double denom_max_val = 0.0;

	assert(current_buffer);
	assert(val_in_range);
	assert(steps_fraction);
	assert(max_value);
	assert(gain_val);

	switch (typeComparison)
	{
	case WAVEFORMMATCHING:
		for(i = lowRange; i <= uppRange; i++)
		{
			for(j =0; j < precision; j++)
			{
				nom_max_val = 0.0;
				denom_max_val = 0.0;
				for(k = 0; k< amount_buffer; k++)
				{
					indexx = bufferSize-i+k;
					
					if(indexx < bufferSize)
					{
						i_value = previousValues[indexx] * (1-j/precision);
					}
					else
					{
						i_value = current_buffer[indexx-bufferSize] * (1-j/precision);
					}
					
					indexx ++;

					if(indexx < bufferSize)
					{
						i_p_1_value = previousValues[indexx] * (j/precision);
					}
					else
					{
						i_p_1_value = current_buffer[(indexx)-bufferSize] * (j/precision);
					}
					
					nom_max_val += (i_value + i_p_1_value) * current_buffer[k];
					denom_max_val += (i_value + i_p_1_value) *  (i_value + i_p_1_value);
				}
			 
				// LTP: Avoid multiples of frequency!
				if((double)(nom_max_val / sqrt(denom_max_val)) > value_max * 1.25)
				{
					index_low = i;
					index_prec_low = j;
					value_max = nom_max_val / sqrt(denom_max_val);
					gain_val_max = (nom_max_val / denom_max_val);
				}
			}
		}
		break;
	default:
		assert(0);
	}
	*val_in_range = index_low;
	*steps_fraction = index_prec_low;
	*max_value = value_max;
	*gain_val = gain_val_max;
	if(amount_buffer < bufferSize)
	{
		memcpy(previousValues, (previousValues + amount_buffer), sizeof(double)*(bufferSize - amount_buffer));
		memcpy((previousValues + (bufferSize - amount_buffer)), current_buffer, sizeof(double)* amount_buffer);
	}
	else
	{
		memcpy(previousValues, current_buffer + amount_buffer-bufferSize, sizeof(double) * bufferSize);
	}
	return(1);
}

		
int
TerminateLTP()
{
	lowRange = 0;
	uppRange = 0;
	precision = 1;
	typeComparison = WAVEFORMMATCHING;

	assert(previousValues);
	free(previousValues);
	
	previousValues = NULL;
	bufferSize = 0;
	return(1);
}

int
ReturnStatesLTP(double *states)
{
	assert(previousValues);
	assert(states);

	memcpy(states, previousValues, sizeof(double)*bufferSize);
	return(1);
}

int
SetStatesLTP(const double *states)
{
	assert(previousValues);
	assert(states);

	memcpy( previousValues, states, sizeof(double)*bufferSize);
	return(1);
}


