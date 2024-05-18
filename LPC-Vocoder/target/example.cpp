#include <iostream>
#include <string>
#include <cstring>
#include "Einlesen.h"
#include "wavEinlesen.h"
#include "Write.h"
#include "wavWrite.h"



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

/*
//a function that converts a pcm file to a wav file 
void convertPCMToWAV()
{
	string pcmName;
	cout << "please insert the name for the pcm file to read " << endl;
	cin >> pcmName;
	Einlesen pcmFile(pcmName);
	pcmFile.readFile();

	string wavName; 
	cout << "please enter the name for the wav file" << endl;
	cin >> wavName;
	FILE* pcm2wav_handle = fopen((wavName+".wav").c_str(), "wb");
	

	vector<vector<short>>& audioFrame = pcmFile.audioRahmen;


	char* riff =  "RIFF" ;
	char* wav = "WAVE";
	char* str3 = "fmt ";
	char* data = "data";

	cout << "length of RIFF char* is " << strlen(riff) << endl;


	string test;
	cin >> test;
	unsigned int sizePCM = audioFrame.size() * 160 * 2;  //size is how many frames*size of each frame * 2 bytes
	unsigned int lenFormat = 0x10;
	short anotherInt = 0x01;
	short numChannels = 1;
	unsigned int sampleRate = 8000;
	unsigned int bytesPerSecond = 16000;

	short bytesPerSample = 2; 
	short bitsPerSample = 16;

	unsigned int totalLengthBytes = sizePCM + (44-8); 
	unsigned int fileLength = sizePCM;


	//Write the header file for the wave file at the beginning

	fwrite(riff, 1 , strlen(riff), pcm2wav_handle);	//write "RIFF" to wavFile
	fwrite(&totalLengthBytes, 4, 1, pcm2wav_handle);		//write fileSize to wavFile
	fwrite(wav, strlen(wav), 1, pcm2wav_handle); //write "WAVE" to file
	fwrite(str3, strlen(str3), 1, pcm2wav_handle); // write "fmt␣" to file
	fwrite(&lenFormat, 4, 1, pcm2wav_handle);
	fwrite(&anotherInt, 2, 1, pcm2wav_handle);
	fwrite(&numChannels, 2, 1, pcm2wav_handle);
	fwrite(&sampleRate, 4, 1, pcm2wav_handle);
	fwrite(&bytesPerSecond, 4, 1, pcm2wav_handle);
	fwrite(&bytesPerSample, 2, 1, pcm2wav_handle);
	fwrite(&bitsPerSample, 2, 1, pcm2wav_handle);
	fwrite(data, strlen(data), 1, pcm2wav_handle);
	fwrite(&fileLength, 4, 1, pcm2wav_handle);


	//after the header, write the pcm file samples to the output file
	//write pcm data to file
	for (int i = 0; i < audioFrame.size(); i++)
	{
		int num = fwrite( &audioFrame[i][0] , sizeof(short), audioFrame[i].size(), pcm2wav_handle);
		
	}

	cout << "Conversion from PCM to Wav is done...." << endl;
	cout << "=============================================================================================" << endl;
	cout << "=============================================================================================" << endl;
	fclose(pcm2wav_handle);

}
*/


int main()
{
	
	cout << "size of short is " << sizeof(short) << endl;
	//test2();
	//test3();

	MileStone4();


	

	return 0; 
}
