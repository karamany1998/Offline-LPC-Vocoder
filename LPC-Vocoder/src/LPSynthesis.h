#pragma once

#include <string>
#include <vector>
#include <wavEinlesen.h>
#include <valarray>


extern "C"
{
#include "FIR.h"
#include "IIR.h"
#include "speech2Lsf.h"
#include "signalUtils.h"
#include "lsflpcUtils.h"

}


using namespace std;

class LPSynthesis
{


protected:

	wavEinlesen audioFile;
	string name;
	//vector<valarray<double>> LPC_Coefficients;



public:
	vector<vector<double>> LPC_Coefficients;
	vector<vector<double>> filtered_frames;


	LPSynthesis();
	LPSynthesis(vector<vector<double>> lpcCoeff, vector<vector<double>> filteredFrames);
	vector<vector<double>> synthesize();
	


};