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

#ifndef __TOOLS_H__
#define __TOOLS_H__

using namespace std;

#include <valarray>

/*! Copy length elements from src, starting at position startSrc,*
 * to field dest, starting at position startDest */
bool memcopy(const valarray<double>& src, valarray<double>& dest, 
		  unsigned int startSrc, unsigned int startDest, unsigned int length);

//! Set the values of one buffer to a specific value (e.g. for initialization)
bool memset(valarray<double>& dest, unsigned int startDest, unsigned int length, double newVal);

//! Function to shift all values in a buffer to the left(shiftCoeff < 0) or right, adding zeros from one side
bool shift(valarray<double>& dest, int shiftCoeff);

#endif
