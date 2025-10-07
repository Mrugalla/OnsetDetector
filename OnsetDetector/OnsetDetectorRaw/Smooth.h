#pragma once

namespace dsp
{
	struct Lowpass
	{
		// decay
		static double getXFromFc(double) noexcept;
		// decay, Fs
		static double getXFromSamples(double) noexcept;
		// decay, Fs
		static double getXFromHz(double, double) noexcept;
		// decay, Fs
		static double getXFromSecs(double, double) noexcept;
		// decay, Fs
		static double getXFromMs(double, double) noexcept;

		// decay
		void makeFromDecayInSamples(double) noexcept;
		// decay, Fs
		void makeFromDecayInSecs(double, double) noexcept;
		// decay, Fs
		void makeFromDecayInSecs(float, float) noexcept;
		// fc
		void makeFromDecayInFc(double) noexcept;
		// decay, Fs
		void makeFromDecayInHz(double, double) noexcept;
		// decay, Fs
		void makeFromDecayInMs(double, double) noexcept;
		// decay, Fs
		void makeFromDecayInMs(float, float) noexcept;

		void copyCutoffFrom(const Lowpass&) noexcept;

		// startVal
		Lowpass(double = 0.);

		// resets to startVal
		void reset();

		// value
		void reset(double);

		// buffer, val, numSamples
		void operator()(double*, double, int) noexcept;

		// buffer, numSamples
		void operator()(double*, int) noexcept;

		// buffer, numSamples
		void operator()(float*, int) noexcept;

		// val
		double operator()(double) noexcept;

		void setX(double) noexcept;

		double a0, b1, y1, startVal;

		double processSample(double) noexcept;

		double processSample(float) noexcept;
	};
}