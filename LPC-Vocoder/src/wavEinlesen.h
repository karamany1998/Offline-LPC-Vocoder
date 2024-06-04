#pragma once

#include <string>
#include "Einlesen.h"

class wavEinlesen : public Einlesen
{

public: 

	string name; 
	string RIFF = "";
	string data = "";
	string str3 = "";
	string wav = "";

	int numChannel = 0; 
	int sampleRate = 0; 
	int bytePerSecond = 0; 
	int bytePerSample = 0; 
	int bitsPerSample = 0; 
	int totalLength = 0; 



	wavEinlesen();
	wavEinlesen(std::string name);
	void readFile();

	

	//add some getters for future use
	int getSampleRate();
	int getBytePerSample();
	int getNumChannel();
	

};