

#include "Write.h"


Write::Write()
{
	this->name = "";

}



Write::Write(string name)
{
	this->name = name; 
}


void Write::writeFile()
{

	
	string currName = name + ".srt";
	FILE* handle = NULL;
	handle = fopen(currName.c_str(), "wb");
	
	char arr[40];
	memset(arr, 0, 40); //put 40 bytes each equal to 0 in arr
	fwrite(arr, 1, 40, handle);//first 40 bytes equal to 0 in file






}