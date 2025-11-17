#pragma once

#include <cstdint>

class SoundEffect {
public:
	SoundEffect(uint32_t bufferId);
	~SoundEffect();

	void Play(bool isLooping = false);
	void Stop();

	bool IsPlaying() const;

private:
	uint32_t id;
};
