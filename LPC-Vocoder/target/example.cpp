#include <iostream>
#include <string>
#include <cstring>
#include "Einlesen.h"
#include "wavEinlesen.h"
#include "Write.h"
#include "wavWrite.h"
#include<valarray> 

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





//this function is used to convert a set of audio samples(divided into frames of size N=160) to LPC coefficients
void convertSamplesToLPC()
{


	//first we have to read either a PCM or Wav File
	//for this function,  we will read a wav file.

	
	cout << "please enter the wav file you want to read to determine the LP-Coefficients" << endl;
	string wavName;
	cin >> wavName;
	wavEinlesen readerObj(wavName);
	readerObj.readFile();
	vector<vector<short>>& currVec = readerObj.audioRahmen; 
	vector<valarray<short>> valArr;




	//go over the vector<vector<short>> of audio frames and convert it to valrray for ease of computation
	for (int i = 0; i < currVec.size(); i++)		
	{
		valarray<short> cpy(  currVec[i].data(), currVec[i].size()  );
		valArr.push_back(cpy);
	}


	vector<valarray<double>> LSF_vec; 

	//construct the hamming function(will be used later to computer Line Spectral Frequencies)
	double arrayWindowSpeech[10 + 160 + 80];	
	for (int idx = 0; idx < 250; idx++)
	{	
		if (idx == 240)	//used for debugging
		{
			arrayWindowSpeech[idx] = hammingWindow(idx, 125, 10 + 160 + 80);
		}
		else
		{
			arrayWindowSpeech[idx] = hammingWindow(idx, 125, 10 + 160 + 80);
		}
		

	}
	

	//now, we can loop over the vector of valarrays and then get the 10 lookback samples, 80 lockahead samples and current samples(will equal 160)
	//then combine into one vec/valarray of size N = 250
	//after that we can use the given functions to convert the samples to line spectral frequencies and then to LPC 
	for (int i = 0; i < valArr.size(); i++)
	{
		int n = valArr.size();
		valarray<short> lookBackVec(valArr[i][0] , 10); // default set to first value
		valarray<short> lookAheadVec(valArr[i][159] , 80);  //default set to last value
		vector<double> combinedSamples; 


		if (i != 0 )	//we can get both 10 lookBack samples 
		{
			lookBackVec = valArr[i - 1][slice(160 - 11, 10, 1)];		
		}
		if (i != valArr.size() - 1)
		{
			lookAheadVec = valArr[i + 1][slice(160 - 80 - 1, 80, 1)];
		}
		
		for (int j = 0; j < lookBackVec.size(); j++)combinedSamples.push_back(lookBackVec[j]);
		for (int j = 0; j < valArr[i].size(); j++)combinedSamples.push_back(valArr[i][j]);
		for (int j = 0; j < lookAheadVec.size(); j++)combinedSamples.push_back(lookAheadVec[j]);


		//now combined samples has 10+160 + 80 samples
		//we can now use speech2lsp_array
		double outputLSF[10];
		double outputLPC[10];
	
		double arrayWindowCorrelation[10];
		for (int k = 0; k < 10; k++)arrayWindowCorrelation[k] = 1;

		
		speech2lsp_array(combinedSamples.data(), outputLSF, 250, 10, arrayWindowSpeech , arrayWindowCorrelation);
		convertLsf2Lpc(outputLSF, outputLPC, 10);

		cout << "LPC Coefficients for i = " <<i<<" are "<< endl;


		for (int k = 0; k < 10; k++)
		{
			cout << outputLPC[k] << " ";
		}

		cout << endl;
		



		
	}

	





}


int main()
{
	
	cout << "size of short is " << sizeof(short) << endl;
	//test2();
	//test3();

	//MileStone4();

	convertSamplesToLPC();


	

	return 0; 
}
