#ifndef AUTOCORRELATION_H__
#define AUTOCORRELATION_H__

/*! Function to determine the autocorrelation coefficients for a given speech
 *  buffer:
 *  \f[ cor(k) = (\sum_{i=0}^{L_{speech}-i-1} x_{in}(i) \cdot h_{speech}(i) 
 *      \cdot x_{in}(i+k) \cdot h_{speech}(i+k)) \cdot h_{corr}(k) \f]
 *  with:
 *  \f[ cor = correlation \f]
 *  \f[ L_{speech} = amountSpeechSamples \f]
 *  \f[ h_{speech} = speechWindow \f]
 *  \f[ h_{corr} = correlationWindow \f] */
void autoCorrelation(double* correlation, const double* correlationWindow, 
					 int amountCorr, const double* xin, 
					 const double* speechWindow, int amountSpeechSamples);

#endif
