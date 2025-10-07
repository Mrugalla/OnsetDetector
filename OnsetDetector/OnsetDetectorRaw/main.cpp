#include "OnsetDetector.h"

int main()
{
	dsp::OnsetDetector onsetDetector;
	onsetDetector.onOnset = [](int onsetIndex)
		{
			// Handle onset event
		};
	onsetDetector.prepare(44100.);
	//onsetDetector(samples, numChannels, numSamples);
}