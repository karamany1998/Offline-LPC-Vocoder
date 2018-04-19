/*============================================================
 * FUNCTION TO IMPLEMENT FIR_FILTER IN FLOATING POINT
 *============================================================*/

#ifndef __IIR__H
#define __IIR__H

/*! Initialize the fir-filter: Set nominator, denominator and
 * initial states. The states are used as they are.
 * This initialize function determines the length for the 
 * delay line, nominator and denominator taps:
 * Definitions: \f[ L_{iir} = amountTaps \f]
 * \f[ a_i = nomTaps[i] \f] \f[ b_i = denomTaps[i] \f]
 * BE AWARE:denomTaps[0] is used as a normalization factor
 * denomTaps[i] = denomTaps[i]/denomTaps[0]!!! */
int InitIIR(const double* stateTaps, const double* nomTaps, 
			const double*denomTaps, int amount_taps);

/*! Terminate the IIR-filter: Free all states etc and set amount to 0
 */
int TerminateIIR();

/*! Execute filtering for frame_in, store result in frame_out.
 * The state is however updated.
 * The functionality is the following, applying direct form 1:
 * \f[ x(k) = frame\_in[k] \f] \f[ y(k)= frame\_out[k] \f]
 * \f[ k = 0 \cdots amount\_values \f]
 * \f[ H(z) = \frac{\sum_{i=0}^{L_{iir}} a_i \cdot z^{-i}}
 * {\sum_{j=0}^{L_{win}} \frac{b_j}{b_0} \cdot z^{-j}} \f]
 */
int ExecuteIIRDF1(const double *frame_in, double *frame_out, int amount_values);

/*! Execute filtering for frame_in, store result in frame_out.
 * The state is however updated.
 * The functionality is the following, applying direct form 2:
 * \f[ x(k) = frame\_in[k] \f] \f[ y(k)= frame\_out[k] \f]
 * \f[ k = 0 \cdots amount\_values \f]
 * \f[ H(z) = \frac{\sum_{i=0}^{L_{iir}} a_i \cdot z^{-i}}
 * {\sum_{j=0}^{L_{win}} \frac{b_j}{b_0} \cdot z^{-j}} \f]
 */
int ExecuteIIRDF2(const double *frame_in, double *frame_out, int amount_values);

/*! Function to set the internal states of the IIR-filter;
 * states[0] is the first in the register-queue (time = 1) etc.
 */
int SetStatesIIR(const double* states);

/*! Return the state of the filter. this function is required to handle more 
 * than one filters*/
int ReturnStatesIIR(double* stateReturn);

#endif
