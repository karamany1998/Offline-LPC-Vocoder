#include "Einlesen.h"
#include <cstring>
#include <iostream>


using namespace std;

Einlesen::Einlesen()
{
	this->name = "";
}
Einlesen::Einlesen(std::string name) 
{
	this->name = name; 

}

void Einlesen::readFile()
{
	FILE* handle = NULL;
	string currName = this->name + ".srt";
	handle = fopen(currName.c_str() , "rb");

	short buffer[160];


	//read 160 bytes at each step to get sound values
	//and out put to console

	if (handle !=  NULL)
	{
		while (fread(buffer, sizeof(short), 160, handle))
		{

			for (int i = 0; i < 160; i++)
			{
				cout << buffer[i] << " ";
			}
			cout << endl;

		}

	}

	fclose(handle);
	

}