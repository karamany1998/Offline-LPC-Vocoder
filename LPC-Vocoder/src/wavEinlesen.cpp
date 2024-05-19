#include "wavEinlesen.h"
#include <cstring>
#include <iostream>

using namespace std;

wavEinlesen::wavEinlesen()
{
	this->name = "";
}


//initializes the object with information about the wav file such as name, number of channels , sampleRate , bytes per sample...etc

wavEinlesen::wavEinlesen(std::string name) 
{
	cout << "in ctor for wav file with name " << name << endl;
	this->name = name;
	string currName = this->name + ".wav";
	FILE* wavhandleRead = NULL;
	wavhandleRead = fopen(currName.c_str(), "rb");
	if (wavhandleRead == NULL)
	{
		cout << "file failed to open" << endl;
		return;
	}
	
	fread(&RIFF, 4, 1, wavhandleRead);
	fread(&totalLength, 4, 1, wavhandleRead);
	fread(&wav, 4, 1, wavhandleRead);

	fseek(wavhandleRead, 22, SEEK_SET);
	fread(&numChannel, 2, 1, wavhandleRead); //read 2 bytes starting form byte 22 to get how many channels 
	fread(&sampleRate, 4, 1, wavhandleRead); //read next 4 bytes to get sample rate
	fread(&bytePerSecond, 4, 1, wavhandleRead);
	fread(&bytePerSample, 2, 1, wavhandleRead);
	fread(&bitsPerSample, 2, 1, wavhandleRead);

	fclose(wavhandleRead);
	

	cout << "===============information from wav file=====================" << endl;
	cout << "RIFF found is " << RIFF << endl;
	cout << "total length of file is " << totalLength << endl;
	cout << "numChannel " << numChannel << endl;
	cout << "sampleRate " << sampleRate << endl;
	cout << "byte per second " << bytePerSecond << endl;
	cout << "byte per sample " << bytePerSample << endl;
	cout << "bits per sample " << bitsPerSample << endl;

	cout << "============================================ ";


}


void wavEinlesen::readFile()
{
	audioRahmen.clear();
	cout << "in readFile function " << endl;
	FILE* handle = NULL;

	string currName = this->name + ".wav";
	handle = fopen(currName.c_str(), "rb");
	if (handle == NULL)
	{
		cout << "file failed to open" << endl;
		printf("Cannot open file: error=%s\n", strerror(errno));

		return;
	}
	
	fseek(handle , 44, SEEK_SET); // after getting required information, start from 44 because that's where the audio file starts

	 
	short buffer[160];
	vector<short> buffer2;

	//read 160 bytes at each step to get sound values
	//and out put to console

	if (handle != NULL)
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