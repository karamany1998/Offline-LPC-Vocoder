#pragma once

#include <string>
#include "Einlesen.h"

class wavEinlesen : public Einlesen
{
private: 

	std::string name; 
	int numChannel = 0;
	int sampleRate = 0;
	int bytePerSecond = 0;
	int bytePerSample = 0;
	int bitsPerSample = 0;

public: 

	wavEinlesen();
	wavEinlesen(std::string name);
	void readFile();

	void changeWavFile(std::string name);

	//add some getters for future use
	int getSampleRate();
	int getBytePerSample();
	int getNumChannel();

};