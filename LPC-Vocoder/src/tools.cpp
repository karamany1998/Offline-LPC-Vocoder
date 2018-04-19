/* ============================================================	*
 * LABORATORY COURSES FOR OBJECT ORIENTED PROGRAMMING,			*
 * INSTITUTE OF COMMUNICATION SYSTEMS AND DATA PROCESSING,		*
 * IND, RWTH-AACHEN												*/

/* DESCRIPTION:													*
 * These are functions that simplify the usage of the valarray	*
 * datatype. Those who have been working with C previously will	*
 * consider the implemented function as missing with valarray	*
 * datatype.
 *																*/

/* CLASS/FUNCTION:												*
 *	memcopy, memset, shift										*
 *============================================================	*/

#include <cassert>

#include "tools.h"

/*============================================================*/
/* Copy length elements from src, starting at position startSrc,*
 * to field dest, starting at position startDest */
bool
memcopy(const valarray<double>& src, valarray<double>& dest, 
	 unsigned int startSrc, unsigned int startDest, unsigned int length)
{
	assert(startSrc+length <= src.size());
	assert(startDest+length <= dest.size());
	
	for(unsigned int i = 0; i < length; i++)
		dest[startDest+i] = src[startSrc+i];
	return(true);
}

/*============================================================*/
/* Set the length elements in dest, starting from position 	*
 *	startDest, to newVal*/
bool 
memset(valarray<double>& dest, unsigned int startDest, unsigned int length, double newVal)
{
	assert(startDest+length <= dest.size());
	for(unsigned int i = 0; i < length; i++)
		dest[startDest+i] = newVal;
	return(true);
}

/*============================================================*/
/* 	Shift the values in buffer dest to left or right.				*
 * 	If shiftCoeff > 0, shift into the right direction, otherwhise 	*
 * 	into the left direction. The new values will be set to zero 	*
 *	when inserting.*/
bool
shift(valarray<double>& dest, int shiftCoeff)
{
	unsigned int i;

	if((int)dest.size() < shiftCoeff)
		return(false);

	// Shift to right
	if(shiftCoeff > 0)
	{
		for(i =0; i <(dest.size()-shiftCoeff);i++)
		{
			dest[(dest.size()-1-i)] = dest[(dest.size()-1-i-shiftCoeff)];
		}
		for(i =0; i < (unsigned)shiftCoeff;i++)
		{
			dest[(i)] = 0;
		}
		
	}
	else
	{	
		// Shift to left
		for(i =0; i < (unsigned)(dest.size()+shiftCoeff);i++)
		{
			dest[(i)] = dest[(i-shiftCoeff)];
		}
		for(i =0; i < (unsigned) (-shiftCoeff);i++)
		{
			dest[(dest.size()+shiftCoeff+i)] = 0;
		}
	}
	return(true);
}
		
