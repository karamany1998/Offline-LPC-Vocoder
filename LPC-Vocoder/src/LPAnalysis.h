#pragma once

#include <string>
#include <vector>
#include <wavEinlesen.h>
#include <valarray>

extern "C"
{
#include "FIR.h"
#include "speech2Lsf.h"
#include "signalUtils.h"
#include "lsflpcUtils.h"
}



using namespace std;

class LPAnalysis
{


protected: 

	wavEinlesen audioFile;
	string name;
	//vector<valarray<double>> LPC_Coefficients;



public: 
	vector<valarray<double>> LPC_Coefficients;
	LPAnalysis(wavEinlesen audioClass);
	void convertSamplesToLPC();





};