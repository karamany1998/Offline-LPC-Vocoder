#include <LPAnalysis.h>

#include <cstring>
#include <iostream>
using namespace std;

LPAnalysis::LPAnalysis(wavEinlesen audioClass)
{
	this->audioFile = audioClass;
}


LPAnalysis::LPAnalysis(vector<vector<short>> vec)
{
	this->audioFrames = vec;
}



vector<vector<double>> LPAnalysis::convertSamplesToLPC()
{

	//for this function,  we will read a wav file.
	
	//(Change 25/06 - Testing class with internal sample values, rather than referring to the audioFile object - need this change for mileStone7)
	//vector<vector<short>>& currVec = this->audioFile.audioRahmen; //the current audio frames

	//(Modification --- the class will refer to internal audio frames, rather than accessing it from another class)
	vector<vector<short>>  currVec = this->audioFrames;
	vector<valarray<short>> valArr;


	//go over the vector<vector<short>> of audio frames and convert it to valrray for ease of computation
	for (int i = 0; i < currVec.size(); i++)
	{
		valarray<short> cpy(currVec[i].data(), currVec[i].size());
		valArr.push_back(cpy);
	}


	vector<valarray<double>> LPC_vec;	//a vector of valarrays where each valarray has the 11 LPC Coefficients
	vector<vector<double>> retVal;

	//construct the hamming function(will be used later to computer Line Spectral Frequencies)
	double arrayWindowSpeech[10 + 160 + 80];
	for (int idx = 0; idx < 250; idx++)
	{
		arrayWindowSpeech[idx] = hammingWindow(idx, 125, 250);
	}

	double arrayWindowCorrelation[11];
	for (int k = 0; k < 11; k++)arrayWindowCorrelation[k] = 1.0;


	//now, we can loop over the vector of valarrays and then get the 10 lookback samples, 80 lockahead samples and current samples(will equal 160)
	//then combine into one vec/valarray of size N = 250
	//after that we can use the given functions to convert the samples to line spectral frequencies and then to LPC 
	for (int i = 0; i < valArr.size(); i++)
	{
		int n = valArr.size();
		valarray<short> lookBackVec(valArr[i][0], 10); // default set to first value
		valarray<short> lookAheadVec(valArr[i][159], 80);  //default set to last value

		vector<double> combinedSamples;



		if (i > 0)	//we can get 10 lookBack samples 
		{
			int sz = valArr[i - 1].size();
			lookBackVec = valArr[i - 1][slice(sz - 10, 10, 1)];
		}
		if (i < valArr.size() - 1)	//we can get 80 lookAhead samples
		{
			int sz = valArr[i + 1].size();
			lookAheadVec = valArr[i + 1][slice(0, 80, 1)];
		}



		//now combined samples has 10+160 + 80 samples
		for (int j = 0; j < lookBackVec.size(); j++)combinedSamples.push_back(lookBackVec[j]);
		for (int j = 0; j < valArr[i].size(); j++)combinedSamples.push_back(valArr[i][j]);
		for (int j = 0; j < lookAheadVec.size(); j++)combinedSamples.push_back(lookAheadVec[j]);



		//we can now use speech2lsp_array  and convertLsf2Lpc to get the LPC- coefficients
		double outputLSF[10]; //has the line spectral frequencies
		double outputLPC[11]; //has the 11 LPC Coefficients


		speech2lsp_array(combinedSamples.data(), outputLSF, 250, 10, arrayWindowSpeech, arrayWindowCorrelation);
		convertLsf2Lpc(outputLSF, outputLPC, 10);


		valarray<double> lpcCurr(outputLPC, 11);
		vector<double> vec5(outputLPC, outputLPC + 11);
		LPC_vec.push_back(lpcCurr);
		retVal.push_back(vec5);


	}



	cout << "========================================================================" << endl;
	cout << "The LPC Coefficients computed are :" << endl;

	for (int i = 0; i < LPC_vec.size(); i++)
	{
		//cout << i << ": ";
		for (int j = 0; j < LPC_vec[i].size(); j++)
		{
		//	cout << LPC_vec[i][j] << " ";
		}
		//cout << endl;
	}

	LPC_Coefficients = LPC_vec;
	return retVal;

}