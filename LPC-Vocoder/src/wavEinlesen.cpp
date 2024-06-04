#include "wavEinlesen.h"
#include <cstring>
#include <iostream>

using namespace std;

wavEinlesen::wavEinlesen()
{
	Einlesen();
}




//initializes the object with information about the wav file such as name, number of channels , sampleRate , bytes per sample...etc

wavEinlesen::wavEinlesen(std::string name)
{
	cout << "in ctor for wav file with name " << name << endl;
	this->name = name;
	string currName = this->name + ".wav";
	FILE* handle = NULL;
	handle = fopen(currName.c_str(), "rb");
	if (handle == NULL)
	{
		cout << "file failed to open" << endl;
		return;
	}

	fseek(handle, 22, SEEK_SET);
	fread(&numChannel, 2, 1, handle); //read 2 bytes starting form byte 22 to get how many channels 
	fread(&sampleRate, 4, 1, handle); //read next 4 bytes to get sample rate
	fread(&bytePerSecond, 4, 1, handle);
	fread(&bytePerSample, 2, 1, handle);
	fread(&bitsPerSample, 2, 1, handle);

	fclose(handle);


	cout << "===============information from wav file=====================" << endl;
	cout << "numChannel " << numChannel << endl;
	cout << "sampleRate " << sampleRate << endl;
	cout << "byte per second " << bytePerSecond << endl;
	cout << "byte per sample " << bytePerSample << endl;
	cout << "bits per sample " << bitsPerSample << endl;
	cout << "============================================ ";


}


void wavEinlesen::readFile()
{

	cout << "in readFile function " << endl;
	FILE* handle = NULL;

	string currName = this->name + ".wav";
	handle = fopen(currName.c_str(), "rb");
	if (handle == NULL)
	{
		cout << "file failed to open" << endl;
		return;
	}

	fseek(handle, 44, SEEK_SET); // after getting required information, start from 44 because that's where the audio file starts


	vector<short> buffer(160);
	if (handle != NULL)
	{
		while (fread(buffer.data(), bytePerSample, 160, handle))
		{
			this->audioRahmen.push_back(buffer);
		}
	}

	fclose(handle);
}


int wavEinlesen::getSampleRate()
{
	return this->sampleRate;
}

int wavEinlesen::getBytePerSample()
{
	return this->bytePerSample;
}
int wavEinlesen::getNumChannel()
{
	return this->numChannel;
}