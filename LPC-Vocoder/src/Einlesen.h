#pragma once

#include <string>


class Einlesen
{

protected:

	std::string name;

public:

	Einlesen(); //Default ctor

	Einlesen(std::string name); //Ctor that gets name of file to open


	void readFile();
	



};

