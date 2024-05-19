#include "Einlesen.h"
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

Einlesen::Einlesen()
{
	this->name = "";
}
Einlesen::Einlesen(std::string name) 
{
	this->name = name; 

}



vector<vector<short>> Einlesen::getAudioData()
{
	return this->audioRahmen;
}


string Einlesen::getName()
{
	return this->name;
}

void Einlesen::readFile()
{
	FILE* handle = NULL;
	string currName = this->name + ".srt";
	handle = fopen(currName.c_str() , "rb");

	short buffer[160];
	vector<short> buffer2;

	//read 160 bytes at each step to get sound values
	//and out put to console

	if (handle !=  NULL)
	{
		while (fread(buffer, sizeof(short), 160, handle))
		{
			for (int i = 0; i < 160; i++)
			{
				//cout << buffer[i] << " ";
				buffer2.push_back(buffer[i]); //saves values from .srt file in the buffer2 vector
			}
			cout << "size of buffer2 is " << buffer2.size() << endl;
			this->audioRahmen.push_back(buffer2);
			cout << endl;
			buffer2.clear();
		}
	}
	
	fclose(handle);
}


