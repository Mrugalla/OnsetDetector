#pragma once
#include <array>
#include "OnsetAxiom.h"

namespace dsp
{
	struct OnsetBuffer
	{
		OnsetBuffer() :
			buffer()
		{ }

		void copyFrom(const OnsetBuffer& other, int numSamples) noexcept
		{
			for (auto s = 0; s < numSamples; ++s)
				buffer[s] = other[s];
		}

		float* getSamples() noexcept
		{
			return buffer.data();
		}

		float getMaxMag(int numSamples) const noexcept
		{
			auto max = 0.f;
			for (auto s = 0; s < numSamples; ++s)
				if (max < buffer[s])
					max = buffer[s];
			return max;
		}

		void clear(int numSamples) noexcept
		{
			for(auto i = 0; i < numSamples; ++i)
				buffer[i] = 0.f;
		}

		float& operator[](int i) noexcept
		{
			return buffer[i];
		}

		const float& operator[](int i) const noexcept
		{
			return buffer[i];
		}

		void rectify(int numSamples) noexcept
		{
			for (auto s = 0; s < numSamples; ++s)
				buffer[s] = std::abs(buffer[s]);
		}

		void copyFromMid(float** samples, int numChannels, int numSamples) noexcept
		{
			for(auto i = 0; i < numSamples; ++i)
				buffer[i] = samples[0][i];
			if (numChannels != 2)
				return;
			for (auto i = 0; i < numSamples; ++i)
			{
				buffer[i] += samples[1][i];
				buffer[i] *= .5f;
			}
		}

		void copyTo(float** samples, int numChannels, int numSamples) noexcept
		{
			for (auto ch = 0; ch < numChannels; ++ch)
				for (auto i = 0; i < numSamples; ++i)
					samples[ch][i] = buffer[i];
		}
	protected:
		std::array<float, BlockSize> buffer;
	};
}