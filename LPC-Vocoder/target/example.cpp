﻿#include <iostream>
#include <string>
#include <cstring>
#include "Einlesen.h"
#include "wavEinlesen.h"
#include "Write.h"
#include "wavWrite.h"
#include<valarray> 
#include "LPAnalysis.h"
#include "LPSynthesis.h"
#include "openLoopPitchEstimation.h"
#include <cstdlib>


extern "C"
{
#include "FIR.h"
#include "IIR.h"
#include "speech2Lsf.h"
#include "signalUtils.h"
#include "lsflpcUtils.h"

}


using namespace std;



void test2()
{

	cout << "enter a name for file" << endl;
	string name;
	cin >> name;
	Einlesen object(name);

	object.readFile();

}
void test3()
{

	cout << "enter a name for file" << endl;
	string name;
	cin >> name;
	wavEinlesen object2(name);
	object2.readFile();

}


//Testing the class Write and wavWrite
void test4()
{


	cout << "enter a name for file" << endl;
	string name;
	cin >> name;
	Einlesen object(name);

	object.readFile();



	cout << "enter new file to save the previosuly read data " << endl;
	string writeName;
	cin >> writeName;

	Write writeObj(object);
	writeObj.writeFile(writeName);


	Einlesen obj2(writeName);
	obj2.readFile();


}


void MileStone4()
{
	cout << "==================================================" << endl;
	cout << "PCM to Wav conversion... " << endl;

	//ask user for the pcm file name
	string pcmName; 
	cout << "Please enter the PCM file name " << endl;
	cin >> pcmName;
	wavWrite wavWriterObject;
	//wavWriterObject will call the convertPCMToWav method and write output a wavFile
	wavWriterObject.convertPCMToWav(pcmName);
}


void MileStone5()	//will create a class to do LP Analysis by putting the function convertSamplesToLPC() inside it
{

	cout << "please enter the wav file you want to read to determine the LP-Coefficients" << endl;
	string wavName;
	cin >> wavName;
	wavEinlesen readerObj(wavName);
	readerObj.readFile();

	LPAnalysis LPC_obj(readerObj);
	LPC_obj.convertSamplesToLPC();


}



vector<vector<double>> determineRestSignal()
{
	//Initially we will use the same functionality as milestone5, but then we the LPC-coefficients to filter the signal
	cout << "please enter the wav file you want to read to determine the LP-Coefficients" << endl;
	string wavName;
	cin >> wavName;
	wavEinlesen readerObj(wavName);
	readerObj.readFile();
	vector<vector<short>>& audioFrames = readerObj.audioRahmen;
	vector<vector<double>> audioFramesD;

	
	
	
	LPAnalysis LPC_obj(audioFrames);
	LPC_obj.convertSamplesToLPC();

	vector<valarray<double>>& LPC_coefficients = LPC_obj.LPC_Coefficients;
	double initalStates[11];
	double LP_arr[11];


	for (int j = 0; j < 11; j++)
		LP_arr[j] = LPC_coefficients[0][j];

	for (int i = 0; i < 11; i++)	//initial states will be set initially to 0
	{
		initalStates[i] = 0;
	}
	
	vector<vector<double>> restSignal;

	//move over all the frames
	for (int i = 0; i < audioFrames.size(); i++)
	{
		//copy current frame as vector of doubles
		std::vector<double> currentFrame(audioFrames[i].begin(), audioFrames[i].end()); 

		//array used to save output frame after filtering the input frame
		double outputBuffer[160]; 

		//the current LPC-Coefficients for frame i
		double currentCoefficient[11];
		for (int j = 0; j < 11; j++)currentCoefficient[j] = LPC_coefficients[i][j];

		//initalize the FIR-filter
		InitFIR(initalStates, currentCoefficient , 11);

		//execute the FIR-operation and save the result in output buffer
		ExecuteFIRDF2(currentFrame.data(), outputBuffer, audioFrames[i].size());

		//save the array in the vector curr and push it to the vector of vectors called restSignal
		vector<double> curr(outputBuffer , outputBuffer+160);
		restSignal.push_back(curr);

		//save the internal states to the initialStates array(the FIR changes internally after each iteration, so we need to save this change for the next 
		//iteration
		ReturnStatesFIR(initalStates); 

		TerminateFIR(); //terminate FIR-filter and iterate to the next audio frame with the modified states
	
	}

	 
	cout << "Filtering the input signal is over..." << endl;
	
	cout << "=============================================================" << endl;

	cout << "what name would you like to name the rest signal " << endl;
	
	string restSignalName; 
	cin >> restSignalName; 
	
	cout << "The rest signal after filtering is:: " << endl;
	
	vector<vector<short>> restSignal_short(restSignal.size());

	for (int i = 0; i < restSignal.size(); i++)
	{
		/*
		for (int j = 0; j < restSignal[i].size(); j++)
		{
			cout << restSignal[i][j] << " ";
		}
		*/
		
		vector<short> vec(restSignal[i].begin(), restSignal[i].end());
		//for (auto& x : vec)cout << x << " ";
		cout << endl;
		restSignal_short[i] = vec;
	}
	wavWrite wavObject(restSignal_short);
	wavObject.convertVectorToWav(restSignalName);

	return restSignal;

}


void mileStone7()	//synthesize signal and write to file
{

	cout << "what name's the name of the audio file do you want to analyse?" << endl;
	string nameAnalysis;
	cin >> nameAnalysis;

	//read the sprache wav signal and save the samples in a vector<vector<short>> 
	wavEinlesen einlesenWavObj(nameAnalysis);
	einlesenWavObj.readFile();

	vector<vector<short>> audioSamples = einlesenWavObj.audioRahmen;

	//We will choose different pitch-periods and just give different signals to the LPSynthesis class to test it

	vector<int> pitchPeriod;
	pitchPeriod.push_back(40);
	pitchPeriod.push_back(40);
	pitchPeriod.push_back(40);
	pitchPeriod.push_back(40);

	vector<vector<short>> testInput;
	for (int i = 0; i < 640; i++)
	{
		int currentPitchPeriod = pitchPeriod[i % 4];
		vector<short> vec(160);

		for (int j = 0; j < 160; j+= currentPitchPeriod)
		{
			vec[j] = 1000;
			
		}

		testInput.push_back(vec);
	}


	LPAnalysis analysisObj(audioSamples);
	vector<vector<double>> LPC_values = analysisObj.convertSamplesToLPC();

	vector<vector<double>> testInput_double;
	for (auto x : testInput)
	{
		vector<double> curr(x.begin(), x.end());
		testInput_double.push_back(curr);

	}

	//LPSynthesis(vector<vector<double>> lpcCoeff, vector<vector<double>> filteredFrames);
	LPSynthesis synthesisObj(LPC_values, testInput_double);


	vector<vector<double>> synthesized_frames = synthesisObj.synthesize();
	vector<vector<short>> synthesized_frames_short;
	for (auto x : synthesized_frames)
	{
		vector<short> curr(x.begin(), x.end());
		synthesized_frames_short.push_back(curr);
	}
	

	//============================================================================================
	
	
	wavWrite wavObj(synthesized_frames_short);
	cout << "what name for the synthesized audio samples do you want?" << endl;
	string name; 
	cin >> name; 
	wavObj.convertVectorToWav(name);
	


}



void mileStone8()	//synthesize signal and modify the gain and then write to file
{

	//first we need to determine the analysed signal 
	//second, we need to make sure that the pitched-signal has the same energy as the analysed signal.
	



	cout << "what name's the name of the audio file do you want to analyse?" << endl;
	string nameAnalysis;
	cin >> nameAnalysis;

	//read the sprache wav signal and save the samples in a vector<vector<short>> 
	wavEinlesen einlesenWavObj(nameAnalysis);
	einlesenWavObj.readFile();

	vector<vector<short>> audioSamples = einlesenWavObj.audioRahmen;

	//We will choose different pitch-periods and just give different signals to the LPSynthesis class to test it

	vector<int> pitchPeriod;
	pitchPeriod.push_back(40);
	pitchPeriod.push_back(40);
	pitchPeriod.push_back(40);
	pitchPeriod.push_back(40);



	vector<vector<short>> testInput;
	for (int i = 0; i < 640; i++)
	{
		int currentPitchPeriod = pitchPeriod[i % 4];
		vector<short> vec(160);

		for (int j = 0; j < 160; j+= currentPitchPeriod)
		{
			vec[j] = 1000;
			
		}

		testInput.push_back(vec);
	}


	////=======================================================================================================================
	//(Determining the g_all, so that testInput has the same energy as the signal after analysis
	double g_all = 1; 

	

	vector<vector<double>> restSignal = determineRestSignal();

	for (int i = 0; i < restSignal.size(); i++)
	{
		double analysis_energy = 0;
		double anregung_energy = 0;

		for (int j = 0; j < restSignal[i].size(); j++)
		{
			analysis_energy += (restSignal[i][j]) * (restSignal[i][j]);
		}

		for (int j = 0; j < testInput[i].size(); j++)
		{
			anregung_energy += (testInput[i][j]) * (testInput[i][j]);
		}

		g_all = sqrt(analysis_energy / anregung_energy);

		//multiply all values of testInput by g_all to make it have the same energy as the analysed signal
		for (int j = 0; j < testInput[i].size(); j++) testInput[i][j] = g_all * testInput[i][j];

	}


	////=======================================================================================================================
	//=======================================================================================================================


	LPAnalysis analysisObj(audioSamples);
	vector<vector<double>> LPC_values = analysisObj.convertSamplesToLPC();

	vector<vector<double>> testInput_double;
	for (auto x : testInput)
	{
		vector<double> curr(x.begin(), x.end());
		testInput_double.push_back(curr);

	}


	LPSynthesis synthesisObj(LPC_values, testInput_double);
	vector<vector<double>> synthesized_frames = synthesisObj.synthesize();
	vector<vector<short>> synthesized_frames_short;
	for (auto x : synthesized_frames)
	{
		vector<short> curr(x.begin(), x.end());
		synthesized_frames_short.push_back(curr);
	}


	//============================================================================================


	wavWrite wavObj(synthesized_frames_short);
	cout << "what name for the synthesized audio samples do you want?" << endl;
	string name;
	cin >> name;
	wavObj.convertVectorToWav(name);
}



vector<vector<double>> audioSamplesOptimalPitch(vector<vector<short>> inputSignal , bool modelNoise)
{	
	//convert inputSignal to double
	vector<vector<double>> audioSamples_double;
	for (auto x : inputSignal)
	{
		vector<double> curr(x.begin(), x.end());
		audioSamples_double.push_back(curr);
	}


	//initalize the open loop class
	openLoopPitchEstimation pitchEstimator(150, 30, 160, 0.9, 2);

	double v_crit = 0; 
	vector<vector<double>> anregungsVector;

	//consider how many samples left over from previous anregungs_frame
	int leftOver = 0; 

	
	for (int i = 0; i < audioSamples_double.size(); i++)
	{
		//convert current frame from vector of doubles  to valArray of doubles

		valarray<double> currFrame(audioSamples_double[i].data() , audioSamples_double[i].size());
		
		bool check = pitchEstimator.setInput(currFrame);
		if (check == false)
		{
			cout << "pitch estimation failed ...." << endl;
		}

		int pitch = pitchEstimator.determineOpenLoopPitch(v_crit);
		vector<double> vec(160);
		int v_grenze = 0; 
		double g_mix = 0; 
		if (v_crit > 0)
		{
			g_mix = (double)(1 - v_crit) / (1 - v_grenze);
		}
		

		//set the start value for j
		int j;
		if (leftOver != 0 && (pitch-leftOver>=0))	//
		{
			j = pitch - leftOver; 
		}
		else
		{
			j = 0;
		}

		for (; j < 160; j += pitch)
		{
			int noiseVal = (rand()) % 1000; //set 1000 as the max value for the noise value
			if (j < 160)leftOver = 160 - j;
			if (modelNoise)
			{
				vec[j] = (1 - g_mix) * 1000 + g_mix * noiseVal;
			}
			else
			{
				vec[j] = 1000;
			}
			
		}
		anregungsVector.push_back(vec);
	}
	return anregungsVector;
}


vector<vector<double>> getAnregungWithGain(vector<vector<double>> anregung_vectors, vector<vector<double>> restSignal)
{

	double g_all = 1;
	for (int i = 0; i < restSignal.size(); i++)
	{
		double analysis_energy = 0;
		double anregung_energy = 0;

		for (int j = 0; j < restSignal[i].size(); j++)
		{
			analysis_energy += (restSignal[i][j]) * (restSignal[i][j]);
		}

		for (int j = 0; j < anregung_vectors[i].size(); j++)
		{
			anregung_energy += (anregung_vectors[i][j]) * (anregung_vectors[i][j]);
		}

		g_all = sqrt(analysis_energy / anregung_energy);

		//multiply all values of testInput by g_all to make it have the same energy as the analysed signal
		for (int j = 0; j < anregung_vectors[i].size(); j++) anregung_vectors[i][j] = g_all * anregung_vectors[i][j];

	}
	return anregung_vectors;


}



void mileStone9()
{
	//first we need to determine the analysed signal 
	//second, we need to make sure that the pitched-signal has the same energy as the analysed signal.

	cout << "what name's the name of the audio file do you want to analyse?" << endl;
	string nameAnalysis;
	cin >> nameAnalysis;

	//read the sprache wav signal and save the samples in a vector<vector<short>> 
	wavEinlesen einlesenWavObj(nameAnalysis);
	einlesenWavObj.readFile();

	vector<vector<short>> audioSamples = einlesenWavObj.audioRahmen;

	//We will choose different pitch-periods and just give different signals to the LPSynthesis class to test it

	



	vector<vector<double>> anregung_vectors = audioSamplesOptimalPitch(audioSamples , false);
	


	////=======================================================================================================================
	//(Determining the g_all, so that testInput has the same energy as the signal after analysis ->check function getAnregungWithGain()
	double g_all = 1;

	vector<vector<double>> restSignal = determineRestSignal();
	anregung_vectors = getAnregungWithGain(anregung_vectors, restSignal);
	


	////=======================================================================================================================
	//=======================================================================================================================


	LPAnalysis analysisObj(audioSamples);
	vector<vector<double>> LPC_values = analysisObj.convertSamplesToLPC();

	vector<vector<double>> anregung_vectors_double;
	for (auto x : anregung_vectors)
	{
		vector<double> curr(x.begin(), x.end());
		anregung_vectors_double.push_back(curr);

	}


	LPSynthesis synthesisObj(LPC_values, anregung_vectors);
	vector<vector<double>> synthesized_frames = synthesisObj.synthesize();

	vector<vector<short>> synthesized_frames_short;
	for (auto x : synthesized_frames)
	{
		vector<short> curr(x.begin(), x.end());
		synthesized_frames_short.push_back(curr);
	}


	//============================================================================================


	wavWrite wavObj(synthesized_frames_short);
	cout << "what name for the synthesized audio samples do you want?" << endl;
	string name;
	cin >> name;
	wavObj.convertVectorToWav(name);
}


void mileStone10()
{
	//first we need to determine the analysed signal 
	//second, we need to make sure that the pitched-signal has the same energy as the analysed signal.

	cout << "what name's the name of the audio file do you want to analyse?" << endl;
	string nameAnalysis;
	cin >> nameAnalysis;

	//read the sprache wav signal and save the samples in a vector<vector<short>> 
	wavEinlesen einlesenWavObj(nameAnalysis);
	einlesenWavObj.readFile();

	vector<vector<short>> audioSamples = einlesenWavObj.audioRahmen;

	//We will choose different pitch-periods and just give different signals to the LPSynthesis class to test it





	vector<vector<double>> anregung_vectors = audioSamplesOptimalPitch(audioSamples, true);



	////=======================================================================================================================
	//(Determining the g_all, so that testInput has the same energy as the signal after analysis ->check function getAnregungWithGain()
	

	vector<vector<double>> restSignal = determineRestSignal();
	anregung_vectors = getAnregungWithGain(anregung_vectors, restSignal);



	////=======================================================================================================================
	//=======================================================================================================================


	LPAnalysis analysisObj(audioSamples);
	vector<vector<double>> LPC_values = analysisObj.convertSamplesToLPC();

	vector<vector<double>> anregung_vectors_double;
	for (auto x : anregung_vectors)
	{
		vector<double> curr(x.begin(), x.end());
		anregung_vectors_double.push_back(curr);

	}


	LPSynthesis synthesisObj(LPC_values, anregung_vectors);
	vector<vector<double>> synthesized_frames = synthesisObj.synthesize();

	vector<vector<short>> synthesized_frames_short;
	for (auto x : synthesized_frames)
	{
		vector<short> curr(x.begin(), x.end());
		synthesized_frames_short.push_back(curr);
	}


	//============================================================================================


	wavWrite wavObj(synthesized_frames_short);
	cout << "what name for the synthesized audio samples do you want?" << endl;
	string name;
	cin >> name;
	wavObj.convertVectorToWav(name);
}


int main()
{
	
	//test2();
	//test3();

	//MileStone4();

	//convertSamplesToLPC();


	//MileStone5();

	//determineRestSignal();

	//mileStone7();
	//mileStone8();

	//mileStone9();

	mileStone10();

	

	return 0; 
}
