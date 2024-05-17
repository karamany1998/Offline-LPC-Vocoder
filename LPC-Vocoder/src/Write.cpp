
#include "Write.h"


Write::Write()
{
	this->name = "";

}


Write::Write(Einlesen readFile)	//take information from the readFile and rewrite it
{

	this->audioFile = readFile;

}

void Write::writeFile(string newName)
{
	vector<vector<short>>& data = this->audioFile.audioRahmen; //data is reference to audioRahmen in the audioFile


	cout << "size of read audio samples is " << data.size() << endl;

	string currName = newName + ".srt";
	FILE* handle = NULL;

	handle = fopen(currName.c_str(), "wb");	//open a new file with name "newName" with type .srt and just put the values that we got from the readFile
	if (handle == NULL)
	{
		cout << "file failed to open " << endl;
		cout << "aborting...." << endl;
		return;
	}
	for (int i = 0 ; i<data.size();  i++)
	{
		fwrite(&data[i], sizeof(short), data[i].size(), handle);
		
	}

	fclose(handle);

}