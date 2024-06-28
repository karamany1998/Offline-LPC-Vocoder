#include "LPSynthesis.h"




LPSynthesis::LPSynthesis()
{
	
}
LPSynthesis::LPSynthesis(vector<vector<double>> lpcCoeff , vector<vector<double>> filteredFrames)
{

	this->LPC_Coefficients = lpcCoeff;
	this->filtered_frames = filteredFrames;

}

vector<vector<double>> LPSynthesis::synthesize()
{


	double initialStates[11];
	vector<vector<double>> synthesized_vector;

	for (int i = 0; i < 11; i++)	//initial states will be set initially to 0
	{
		initialStates[i] = 0;
	}

	vector<double> numerator;
	numerator.push_back(1);
	for (int i = 0; i < 10; i++)numerator.push_back(0);
	


	for (int i = 0; i < LPC_Coefficients.size(); i++)
	{
		

		//array used to save output frame after filtering the input frame
		double outputBuffer[160];

		//the current LPC-Coefficients for frame i
		double currentCoefficient[11];
		for (int j = 0; j < 11; j++)currentCoefficient[j] = LPC_Coefficients[i][j];

		//initalize the IIR-filter
		InitIIR(initialStates,numerator.data(), currentCoefficient , 11);

		
		//execute the IIR-operation and save the result in output buffer
		ExecuteIIRDF2(this->filtered_frames[i].data(), outputBuffer, 160);
		
		vector<double> curr(outputBuffer, outputBuffer + 160);
		synthesized_vector.push_back(curr);

		//save the internal states to the initialStates array(the IIR changes internally after each iteration, so we need to save this change for the next 
		//iteration
		ReturnStatesIIR(initialStates);

		TerminateIIR(); //terminate IIR-filter and iterate to the next audio frame with the modified states

	}

	return synthesized_vector;

}