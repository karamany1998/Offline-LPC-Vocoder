/* ============================================================	*
 * LABORATORY COURSES FOR OBJECT ORIENTED PROGRAMMING,			*
 * INSTITUTE OF COMMUNICATION SYSTEMS AND DATA PROCESSING,		*
 * IND, RWTH-AACHEN												*/

/* DESCRIPTION:													*
 *	Class for an openloop pitch estimation. This class receives *
 *  frames of input speech and finds the best matching pitch 	*
 * 	in a specific range of possible pitch-related delays.		*
 *  The passed samples for the pitch analysis are stored 		*
 * 	internally. Pitch doubling can be avoided by the module		*
 *																*/

/* CLASS/FUNCTION:												*
 *	openLoopPitchEstimation										*
 *============================================================	*/

#include "openLoopPitchEstimation.h"
#include <vector>
#include <float.h>
#include "tools.h"
#include <cassert>

#ifndef HUGE
#define HUGE FLT_MAX
#endif

/*===========================================================*/
/* 	Constructor: Create a buffer that is sufficiently large to*
 * 	store as many values from the past as required to search  *
 *	for the maximum pitch period delay*/
openLoopPitchEstimation::openLoopPitchEstimation(int maxInter, 
												 int minInter, int lengthFrame,
												 double weight, int delta)
{
	int i =0;
	maxTimeIntervall = maxInter;
	minTimeIntervall = minInter;

	frameLengthMax = lengthFrame;

	weightPitchDoubling = weight;
	deltaPitchDoubling = delta;

	// set length of buffer and set to zero
	buffer.resize((maxTimeIntervall+frameLengthMax));
	for(i = 0; i < (maxTimeIntervall+frameLengthMax); i++)
		buffer[i] = 0;
}


/*============================================================*/
/* 	Add the input to the buffer, therefore copy values from the*
 * 	past as a leftshift and then the values from the current   *
 *	buffer.*/
bool 
openLoopPitchEstimation::setInput(const valarray<double>& subframe)
{
	assert((int)subframe.size() == frameLengthMax);
	// Copy as leftshift
	memcopy(buffer, buffer, (unsigned int) subframe.size(), 0, (unsigned int) (buffer.size() - subframe.size()));

	// Copy the new values
	memcopy(subframe, buffer, 0, (unsigned int) (buffer.size() - subframe.size()), (unsigned int) subframe.size());

	return(true);
}

/*============================================================*/
/* 	Determine the open loop pitch period based on the 			*
 *	correlation between the original signal and the shifted one.*
 *	Another output of this routine is the criterion for the 	*
 *	voiced/unvoiced characteristic of the current speech segment*/
int 
openLoopPitchEstimation::determineOpenLoopPitch(double& excitationCrit)
{
	int i = 0;
	unsigned int j =0;

	valarray<double> correlation(0.0, (maxTimeIntervall-minTimeIntervall+1));
	int p = 0;
	int delta = deltaPitchDoubling;
	
	double nom;
	double denom1, denom2;
	double doubleWeight = weightPitchDoubling;

	// Copy buffer and shift to determine the first 
	// possible pitch autocorrelation 
	valarray<double> tempBuffer = buffer;
	shift(tempBuffer,-minTimeIntervall);

	int max_index = 0;
	double maxValue = -HUGE;
	
	// Find the maximum autocorrelation in the integer delay range
	for(i = minTimeIntervall ; i <=maxTimeIntervall; i ++)
	{
		// Determine autocorrelation
		correlation[i-minTimeIntervall] = 0;

		for(j =0; j < buffer.size(); j++)
			correlation[i-minTimeIntervall] += buffer[j] * tempBuffer[j];
		
		// Find a way to avoid pitch doubling
		if(i<2*max_index-2)
		{
			if(correlation[i-minTimeIntervall] > maxValue)
			{
				max_index = i;
				maxValue = correlation[i-minTimeIntervall];
			}
		}
		else
		{
			// If pitch double may be possible, consider a weighting coefficient
			if(correlation[i-minTimeIntervall]*doubleWeight > maxValue)
			{
				max_index = i;
				maxValue = correlation[i-minTimeIntervall];
			}
		}
		// Get the next autocorrelation coeff by simply shifting the buffer

		shift(tempBuffer,-1);
	}

	doubleWeight = doubleWeight*doubleWeight;
	
	// Avoid pitch triples
	p = max_index/3;
	
	if(p>= minTimeIntervall+delta)
	{
		for( i = p-delta; i < p+delta; i++)
		{
			if(maxValue * doubleWeight < correlation[i-minTimeIntervall])
				max_index = i;
		}
	}

	// Determine criterion for voiced/unvoiced
	tempBuffer = buffer;
	shift(tempBuffer, -max_index);

	nom =0;
	denom1 = 0;
	denom2 = 0;
	for(unsigned int i = 0; i < buffer.size(); i++)
	{
		nom += buffer[i] * tempBuffer[i];
		denom1 += buffer[i] * buffer[i];
		denom2 += tempBuffer[i] * tempBuffer[i];
	}
	
	excitationCrit = nom/(sqrt(denom1*denom2)+0.01);
	return(max_index);
}

//============================================================	
		
	
		
		
		
		
	
