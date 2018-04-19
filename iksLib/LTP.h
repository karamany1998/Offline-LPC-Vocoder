/* Module to determine the ltp-delay. This module only support 
 * integer sample delay combined with linear interpolation inbetween!
 * The LTP-sample buffer must be stored outside if the LTp-struct is terminated during 
 * execution otherwhise the states are held */
#ifndef __LTP__H__
#define __LTP__H__


/* Enums planed: So far only waveform-matching works. */
typedef enum {WAVEFORMMATCHING, ELSE} COMPARE_TYPE;

/*! Initialize the usage of the LTP-module:
 * The delay is searched in the range of lowRange and uppRange. prec
 * specifies the amount of steps inbetween samples for linear interpolation.
 * Be aware that the fractional parts are always positive.
 * statesPrevious is an array of elements that includes the state during
 * previous LTP-execution, buffer_size is the appertaining size and tp is
 * an instance of the COMPARE_TYPE enum*/
int InitLTP(const int range_low, const int range_upp, const int prec, 
			const double* statesPrevious, const int buffer_size, COMPARE_TYPE tp);


/*! Execute the LTP: current_buffer and amount_buffer are understood.
 * val_in_range is the returnvalue for integer delay,
 * steps_fraction the fractional delay (positive, between 0 and (precision-1)
 * max_value is the criteria-value for the maximum and gain_val the
 * appertaining gain-factor.*/
int ExecuteLTP(const double* current_buffer, const int amount_buffer,
			   unsigned int* val_in_range, unsigned int* steps_fraction,
			   double* max_value, double *gain_val);

/*! Terminate LTP */
int TerminateLTP();

/*! Access function for the states in case of multiple usage of LTP. */
int ReturnStatesLTP(double *states);

/*! Access function for the states in case of multiple usage of LTP. */
int SetStatesLTP(const double *states);

#endif
