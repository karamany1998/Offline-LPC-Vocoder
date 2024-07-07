
Implementation of an offline audio codec.

The code has different classes such as <br />
1-wavEinlesen: which reads a .wav audio file and extracts the audio samples  <br />
2-wavWrite: which writes the samples to a .wav file and then you can hear the audio by just opening the file. <br />
3- LPAnalysis: performs LPC analysis and determines the LP Coefficients which are used later to synthesize the audio. <br />
4- LPSynthesis: takes the excitation signal(this signal is basically pulses at a specific pitch period which varies from frame to frame), the LP Coefficients and then
performs IIR-filter(which is just the reverse of the FIR-filtering operation done in LPAnalysis), then the output of this step would be the synthesized audio. <br />

<br />
<br />
There are also different functions in example.cpp, by running mileStone10() and enter the file called sprache when prompted to do so, you can see  the overall operation of the audio codec. <br />
Previous milestones test different functionalities such as reading and writing .wav files and LPAnalysis, but everything culminates in
milestone10.

<br />
Done by Mohamed Elkaramany
Finished on 05/07/2024





