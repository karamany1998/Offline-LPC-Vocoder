#include <iostream>
#include <string>
#include <cstring>
#include "Einlesen.h"
#include "wavEinlesen.h"
#include "Write.h"
#include "wavWrite.h"
#include<valarray> 
#include "LPAnalysis.h"


extern "C"
{
#include "FIR.h"
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



void determineRestSignal()
{
	//Initially we will use the same functionality as milestone5, but then we the LPC-coefficients to filter the signal
	cout << "please enter the wav file you want to read to determine the LP-Coefficients" << endl;
	string wavName;
	cin >> wavName;
	wavEinlesen readerObj(wavName);
	readerObj.readFile();
	vector<vector<short>>& audioFrames = readerObj.audioRahmen;
	vector<vector<double>> audioFramesD;

	
	
	
	LPAnalysis LPC_obj(readerObj);
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

}


int main()
{
	
	//test2();
	//test3();

	//MileStone4();

	//convertSamplesToLPC();


	//MileStone5();

	determineRestSignal();

	

	return 0; 
}
