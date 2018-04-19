/*============================================================
 * FUNCTION TO IMPLEMENT FIR_FILTER IN FLOATING POINT
 * This version is critical for timevariant filters! Use FIR2 instead!
 *============================================================*/
#ifndef __FIR__H
#define __FIR__H

/*! Init: Set taps, states and length of FIR. TAPS include the leading 1 and
 * thus the lengthes for both arrays match:
 * Definitions:
 * \f[ a_i = taps[i] \f]
 * \f[ L_{FIR} = amount\_taps \f]
 */
int InitFIR(const double* initial_states, const double* taps, int amount_taps);

/*! Deallocate used memory after FIR-filtering. The filter must be 
 * terminated before using it again */
int TerminateFIR();

/*! Execute one filter-iteration for one frame, amount_values must be bigger 
 * than amount_taps during initialization
 * Functionality:
 * \f[ H(z) = \sum_{i=0}^{L_{FIR}-1} a_i \cdot z^{-i} \f]
 * This implementation of the FIR filter is not suited for time variant 
 * FIR filters as the coefficients are multiplied to the internal
 * states:
 * For all states: \f[ 1) state[i] = x(k) \cdot a_i + state[i-j] \f] and 
 * \f[ 2) y(k) = x(k) \sum_{i=0}^{L_{FIR}-1}   state(i)\f]*/
int ExecuteFIRDF1(const double* inputBuffer, double* outputBuffer, int amount_values);

/*! Execute one filter-iteration for one frame, amount_values must be bigger 
 * than amount_taps during initialization
 * Functionality:
 * \f[ H(z) = \sum_{i=0}^{L_{FIR}-1} a_i \cdot z^{-i} \f]
 * This implementation of the FIR filter is not suited for time variant 
 * FIR filters as the coefficients are multiplied to the internal
 * states:
 * \f[ 1) state[i] = x(k-i) \f] and 
 * \f[ 2) y(k) = \sum_{i=0}^{L_{FIR}-1} a_i \cdot state(i)\f]*/
int ExecuteFIRDF2(const double* inputBuffer, double* outputBuffer, int amount_values);

/*! Execute one filter-iteration for one frame, amount_values must be bigger 
 * than amount_taps during initialization
 * Functionality:
 * \f[ H(z) = \sum_{i=0}^{L_{FIR}-1} a_i \cdot z^{-i} \f]
 * This implementation of the FIR filter is not suited for time variant 
 * FIR filters as the coefficients are multiplied to the internal
 * states:
 * For all states: \f[ 1) state[i] = x(k) \cdot a_i + state[i-j] \f] and 
 * \f[ 2) y(k) = x(k) \sum_{i=0}^{L_{FIR}-1}   state(i)\f]*/
int ExecuteFIRDF1Long(const double* inputBuffer, double* outputBuffer, int amount_values);

/*! Execute one filter-iteration for one frame, amount_values must be bigger 
 * than amount_taps during initialization
 * Functionality:
 * \f[ H(z) = \sum_{i=0}^{L_{FIR}-1} a_i \cdot z^{-i} \f]
 * This implementation of the FIR filter is not suited for time variant 
 * FIR filters as the coefficients are multiplied to the internal
 * states:
 * \f[ 1) state[i] = x(k-i) \f] and 
 * \f[ 2) y(k) = \sum_{i=0}^{L_{FIR}-1} a_i \cdot state(i)\f]*/
int ExecuteFIRDF2Long(const double* inputBuffer, double* outputBuffer, int amount_values);

/*! Function to set the states of the internal shift-registers.
 * states[0] will be the first value in the states (time = 1) etc.
 */
int SetStatesFIR(const double* states);

/*! Function to return the states. This is necessary in order to use multiple
 * FIR-filters. If one was using C++ this would never be necessary!!! */
int ReturnStatesFIR(double* states);

#endif
