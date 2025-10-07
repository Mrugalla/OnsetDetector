#include "Resonator.h"
#include <cmath>

namespace dsp
{
	// ResonatorBase

	ResonatorBase::ResonatorBase() :
		fc(0.), bw(0.)
	{}

	void ResonatorBase::setCutoffFc(double _fc) noexcept
	{
		fc = _fc;
	}

	void ResonatorBase::setCutoffFc(float _fc) noexcept
	{
		fc = static_cast<double>(_fc);
	}

	void ResonatorBase::setBandwidth(double _bw) noexcept
	{
		bw = _bw;
	}

	void ResonatorBase::setBandwidth(float _bw) noexcept
	{
		bw = static_cast<double>(_bw);
	}

	double ResonatorBase::distort(double y) const noexcept
	{
		return y > 1. ? 1. : y < -1. ? -1. : y;
	}

	double ResonatorBase::operator()(float x) noexcept
	{
		return operator()(static_cast<double>(x));
	}

	// Resonator2

	Resonator2::Resonator2() :
		ResonatorBase(),
		b2(0.), b1(0.), a0(0.),
		z1(0.), z2(0.)
	{}

	void Resonator2::reset() noexcept
	{
		z1 = 0.;
		z2 = 0.;
	}

	void Resonator2::update() noexcept
	{
		static constexpr double Pi = 3.14159265358979323846;
		static constexpr double TauD = 2. * Pi;
		b2 = std::exp(-TauD * bw);
		const auto fcTau = TauD * fc;
		const auto b2_4 = 4. * b2;
		const auto cosFc = std::cos(fcTau);
		b1 = (-b2_4 / (1. + b2)) * cosFc;
		const auto sqrtVal = static_cast<float>(1. - b1 * b1 / b2_4);
		a0 = (1. - b2) * std::sqrt(sqrtVal);
	}

	void Resonator2::copyFrom(const Resonator2& other) noexcept
	{
		b2 = other.b2;
		b1 = other.b1;
		a0 = other.a0;
	}

	double Resonator2::operator()(double x) noexcept
	{
		auto y =
			a0 * x
			- b1 * z1
			- b2 * z2;
		y = distort(y);
		z2 = z1;
		z1 = y;
		return y;
	}

	// Resonator3

	void Resonator3::reset() noexcept
	{
		Resonator2::reset();
		lp.reset();
	}

	void Resonator3::update() noexcept
	{
		Resonator2::update();
		lp.makeFromDecayInFc(fc);
	}

	void Resonator3::copyFrom(const Resonator3& other) noexcept
	{
		Resonator2::copyFrom(other);
		lp.copyCutoffFrom(other.lp);
	}

	double Resonator3::operator()(double x) noexcept
	{
		auto y = Resonator2::operator()(x);
		y -= lp(y);
		return y;
	}

	// ResonatorStereo

	template<class ResoClass>
	ResonatorStereo<ResoClass>::ResonatorStereo() :
		resonators{ ResoClass(), ResoClass() }
	{}

	template<class ResoClass>
	void ResonatorStereo<ResoClass>::reset() noexcept
	{
		reset(0);
		reset(1);
	}

	template<class ResoClass>
	void ResonatorStereo<ResoClass>::reset(int ch) noexcept
	{
		resonators[ch].reset();
	}

	template<class ResoClass>
	void ResonatorStereo<ResoClass>::setCutoffFc(double _fc, int ch) noexcept
	{
		resonators[ch].setCutoffFc(_fc);
	}

	template<class ResoClass>
	void ResonatorStereo<ResoClass>::setCutoffFc(float _fc, int ch) noexcept
	{
		resonators[ch].setCutoffFc(_fc);
	}

	template<class ResoClass>
	void ResonatorStereo<ResoClass>::setBandwidth(double _bw, int ch) noexcept
	{
		resonators[ch].setBandwidth(_bw);
	}

	template<class ResoClass>
	void ResonatorStereo<ResoClass>::setBandwidth(float _bw, int ch) noexcept
	{
		resonators[ch].setBandwidth(_bw);
	}

	template<class ResoClass>
	void ResonatorStereo<ResoClass>::update(int ch) noexcept
	{
		resonators[ch].update();
	}

	template<class ResoClass>
	void ResonatorStereo<ResoClass>::update() noexcept
	{
		resonators[0].update();
		resonators[1].copyFrom(resonators[0]);
	}

	template<class ResoClass>
	double ResonatorStereo<ResoClass>::operator()(double x, int ch) noexcept
	{
		return resonators[ch](x);
	}

	template<class ResoClass>
	double ResonatorStereo<ResoClass>::operator()(float x, int ch) noexcept
	{
		return resonators[ch](x);
	}

	template struct ResonatorStereo<Resonator2>;
	template struct ResonatorStereo<Resonator3>;
}