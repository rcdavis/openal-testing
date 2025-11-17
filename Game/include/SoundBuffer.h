#pragma once

#include <cstdint>

/**
 * Represents the actual audio data within a buffer.
 */
class SoundBuffer {
public:
	SoundBuffer();
	~SoundBuffer();

	uint32_t Id() const { return id; }

	/**
	 * Parses an audio file into a buffer.
	 * Only supports WAV files for now.
	 */
	bool Load(const char* filename);

private:
	uint32_t id;
};
