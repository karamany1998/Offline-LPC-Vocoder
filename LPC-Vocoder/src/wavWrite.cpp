#include "wavWrite.h"



wavWrite::wavWrite()
{
	this->name = "";

}


wavWrite::wavWrite(wavEinlesen readFile)	//take information from the readFile and rewrite it
{

	this->audioFile = readFile;

}

wavWrite::wavWrite(vector<vector<short>> vec)
{
	this->internalValues = vec; 
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



void wavWrite::convertPCMToWav(string pcmName)
{
	
	Einlesen pcmFile(pcmName);
	pcmFile.readFile();

	string wavName;
	cout << "please enter the name for the wav file" << endl;
	cin >> wavName;


	FILE* pcm2wav_handle = fopen((wavName + ".wav").c_str(), "wb");


	vector<vector<short>>& audioFrame = pcmFile.audioRahmen;

	//Values used for the wav file header (the header has information about the size, number of channels, sampling rate..etc)
	char* riff = "RIFF";
	char* wav = "WAVE";
	char* str3 = "fmt ";
	char* data = "data";


	unsigned int sizePCM = audioFrame.size() * 160 * 2;  //size is how many frames*size of each frame * 2 bytes
	unsigned int lenFormat = 0x10;
	short anotherInt = 0x01;
	short numChannels = 1;
	unsigned int sampleRate = 8000;
	unsigned int bytesPerSecond = 16000;

	short bytesPerSample = 2;
	short bitsPerSample = 16;

	unsigned int totalLengthBytes = sizePCM + (44 - 8);
	unsigned int fileLength = sizePCM;


	//Write the header file for the wave file at the beginning
	fwrite(riff, 1, strlen(riff), pcm2wav_handle);	//write "RIFF" to wavFile
	fwrite(&totalLengthBytes, 4, 1, pcm2wav_handle);		//write fileSize to wavFile
	fwrite(wav, strlen(wav), 1, pcm2wav_handle); //write "WAVE" to file
	fwrite(str3, strlen(str3), 1, pcm2wav_handle); // write "fmt␣" to file
	fwrite(&lenFormat, 4, 1, pcm2wav_handle);
	fwrite(&anotherInt, 2, 1, pcm2wav_handle);
	fwrite(&numChannels, 2, 1, pcm2wav_handle);
	fwrite(&sampleRate, 4, 1, pcm2wav_handle);
	fwrite(&bytesPerSecond, 4, 1, pcm2wav_handle);
	fwrite(&bytesPerSample, 2, 1, pcm2wav_handle);
	fwrite(&bitsPerSample, 2, 1, pcm2wav_handle);
	fwrite(data, strlen(data), 1, pcm2wav_handle);
	fwrite(&fileLength, 4, 1, pcm2wav_handle);


	//after the header, write the pcm file samples to the output file(Pcm files have only the samples)
	for (int i = 0; i < audioFrame.size(); i++)
	{
		int num = fwrite(&audioFrame[i][0], sizeof(short), audioFrame[i].size(), pcm2wav_handle);

	}

	cout << "Conversion from PCM to Wav is done...." << endl;
	cout << "=============================================================================================" << endl;
	cout << "=============================================================================================" << endl;
	fclose(pcm2wav_handle);
}


void wavWrite::convertVectorToWav(string wavName)
{


	FILE* handle = fopen((wavName + ".wav").c_str(), "wb");


	vector<vector<short>>& audioFrame = this->internalValues;

	//Values used for the wav file header (the header has information about the size, number of channels, sampling rate..etc)
	char* riff = "RIFF";
	char* wav = "WAVE";
	char* str3 = "fmt ";
	char* data = "data";


	unsigned int sizePCM = audioFrame.size() * 160 * 2;  //size is how many frames*size of each frame * 2 bytes
	unsigned int lenFormat = 0x10;
	short anotherInt = 0x01;
	short numChannels = 1;
	unsigned int sampleRate = 8000;
	unsigned int bytesPerSecond = 16000;

	short bytesPerSample = 2;
	short bitsPerSample = 16;

	unsigned int totalLengthBytes = sizePCM + (44 - 8);
	unsigned int fileLength = sizePCM;


	//Write the header file for the wave file at the beginning
	fwrite(riff, 1, strlen(riff), handle);	//write "RIFF" to wavFile
	fwrite(&totalLengthBytes, 4, 1, handle);		//write fileSize to wavFile
	fwrite(wav, strlen(wav), 1, handle); //write "WAVE" to file
	fwrite(str3, strlen(str3), 1, handle); // write "fmt␣" to file
	fwrite(&lenFormat, 4, 1, handle);
	fwrite(&anotherInt, 2, 1, handle);
	fwrite(&numChannels, 2, 1, handle);
	fwrite(&sampleRate, 4, 1, handle);
	fwrite(&bytesPerSecond, 4, 1, handle);
	fwrite(&bytesPerSample, 2, 1, handle);
	fwrite(&bitsPerSample, 2, 1, handle);
	fwrite(data, strlen(data), 1, handle);
	fwrite(&fileLength, 4, 1, handle);


	//after the header, write the pcm file samples to the output file(Pcm files have only the samples)
	for (int i = 0; i < audioFrame.size(); i++)
	{
		int num = fwrite(&audioFrame[i][0], sizeof(short), audioFrame[i].size(), handle);

	}

	fclose(handle);


}