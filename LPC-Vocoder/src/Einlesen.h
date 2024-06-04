#pragma once

#include <string>
#include <vector>

using namespace std;


class Einlesen
{

protected:

	std::string name;


public:

	 

	vector< vector<short> > audioRahmen;


	Einlesen(); //Default ctor
	Einlesen(std::string name); //Ctor that gets name of file to open

	void readFile();
	string getName();
	vector<vector<short>> getAudioData();
	



};

