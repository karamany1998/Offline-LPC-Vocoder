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


	wavWrite();
	wavWrite(wavEinlesen readFile);
	void writeFile(string newName);


	string returnType()
	{
		return "WAV";
	}

};

