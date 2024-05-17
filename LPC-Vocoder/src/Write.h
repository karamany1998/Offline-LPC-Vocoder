#pragma once

#include <string>
#include <iostream>
#include <vector>
#include "Einlesen.h"
using namespace std;


class Write
{

protected:
	string name;
	Einlesen audioFile;
	vector<short> data; //saved audio data that will be written in name in .srt format
public: 



	Write();
	Write(Einlesen readFile);
	void writeFile(string newName);
	string returnType()
	{
		return "PCM";
	}



};