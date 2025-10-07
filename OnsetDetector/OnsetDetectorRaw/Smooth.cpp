#include "Smooth.h"
#include <cmath>

namespace dsp
{
	// Lowpass static

	double Lowpass::getXFromFc(double fc) noexcept
	{
		static constexpr double Pi = 3.14159265358979323846;
		constexpr double TauD = 2. * Pi;
		return std::exp(-TauD * fc);
	}

	double Lowpass::getXFromHz(double hz, double Fs) noexcept
	{
		return getXFromFc(hz / Fs);
	}

	double Lowpass::getXFromSamples(double lengthSamples) noexcept
	{
		const auto dInv = -1. / lengthSamples;
		const auto dExp = std::exp(dInv);
		return dExp;
	}

	double Lowpass::getXFromSecs(double secs, double Fs) noexcept
	{
		const auto lengthSamples = secs * Fs;
		return getXFromSamples(lengthSamples);
	}

	double Lowpass::getXFromMs(double ms, double Fs) noexcept
	{
		const auto secs = ms * .001;
		return getXFromSecs(secs, Fs);
	}

	// Lowpass

	void Lowpass::makeFromDecayInSamples(double d) noexcept
	{
		if (d == 0.)
		{
			a0 = 1.;
			b1 = 0.;
			return;
		}
		const auto dInv = -1. / d;
		const auto dExp = std::exp(dInv);
		setX(dExp);
	}

	void Lowpass::makeFromDecayInFc(double fc) noexcept
	{
		setX(getXFromFc(fc));
	}

	void Lowpass::makeFromDecayInHz(double hz, double Fs) noexcept
	{
		setX(getXFromHz(hz, Fs));
	}

	void Lowpass::makeFromDecayInSecs(double d, double Fs) noexcept
	{
		makeFromDecayInSamples(d * Fs);
	}

	void Lowpass::makeFromDecayInSecs(float d, float Fs) noexcept
	{
		makeFromDecayInSecs(static_cast<double>(d), static_cast<double>(Fs));
	}

	void Lowpass::makeFromDecayInMs(double d, double Fs) noexcept
	{
		makeFromDecayInSecs(d * .001, Fs);
	}

	void Lowpass::makeFromDecayInMs(float d, float Fs) noexcept
	{
		makeFromDecayInMs(static_cast<double>(d), static_cast<double>(Fs));
	}

	void Lowpass::copyCutoffFrom(const Lowpass& other) noexcept
	{
		a0 = other.a0;
		b1 = other.b1;
	}

	Lowpass::Lowpass(double _startVal) :
		a0(1.),
		b1(0.),
		y1(_startVal),
		startVal(_startVal)
	{}

	void Lowpass::reset()
	{
		reset(startVal);
	}

	void Lowpass::reset(double v)
	{
		y1 = v;
	}

	void Lowpass::operator()(double* buffer, double val, int numSamples) noexcept
	{
		for (auto s = 0; s < numSamples; ++s)
			buffer[s] = processSample(val);
	}

	void Lowpass::operator()(double* buffer, int numSamples) noexcept
	{
		for (auto s = 0; s < numSamples; ++s)
		{
			const auto y = processSample(buffer[s]);
			buffer[s] = y;
		}
	}

	void Lowpass::operator()(float* buffer, int numSamples) noexcept
	{
		for (auto s = 0; s < numSamples; ++s)
		{
			const auto y = processSample(buffer[s]);
			buffer[s] = static_cast<float>(y);
		}
	}

	double Lowpass::operator()(double sample) noexcept
	{
		return processSample(sample);
	}

	double Lowpass::processSample(double x0) noexcept
	{
		y1 = x0 * a0 + y1 * b1;
		return y1;
	}

	double Lowpass::processSample(float x0) noexcept
	{
		return processSample(static_cast<double>(x0));
	}

	void Lowpass::setX(double x) noexcept
	{
		a0 = 1. - x;
		b1 = x;
	}

}