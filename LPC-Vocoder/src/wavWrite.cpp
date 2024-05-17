#include "wavWrite.h"



wavWrite::wavWrite()
{
	this->name = "";

}


wavWrite::wavWrite(wavEinlesen readFile)	//take information from the readFile and rewrite it
{

	this->audioFile = readFile;

}

void wavWrite::writeFile(string newName)
{
	vector<vector<short>>& data = this->audioFile.audioRahmen; //data is reference to audioRahmen in the audioFile


	cout << "size of read audio samples is " << data.size() << endl;

	string currName = newName + ".wav";
	FILE* handle = NULL;

	handle = fopen(currName.c_str(), "wb");	//open a new file with name "newName" with type .srt and just put the values that we got from the readFile
	if (handle == NULL)
	{
		cout << "file failed to open " << endl;
		cout << "aborting...." << endl;
		return;
	}
	for (int i = 0; i < data.size(); i++)
	{
		
		if (i >= 635)
		{

			fwrite(&data[i], sizeof(short), data[i].size(), handle);
		}
		else
		{
			fwrite(&data[i], sizeof(short), data[i].size(), handle);
		}
		
	}

	fclose(handle);
}


