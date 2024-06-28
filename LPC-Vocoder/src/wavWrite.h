#pragma once

#include "Write.h"
#include "wavEinlesen.h"

#include <string>
#include <iostream>
#include <vector>

class wavWrite : public Write
{


protected:

	wavEinlesen audioFile;
	
	


public:

	vector<vector<short>> internalValues;

	wavWrite();
	wavWrite(vector<vector<short>> vec);
	wavWrite(wavEinlesen readFile);
	void writeFile(string newName);
	void convertVectorToWav(string wavName);
	void convertPCMToWav(string pcmName);


	string returnType()
	{
		return "WAV";
	}

};

