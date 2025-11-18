#include "SoundBuffer.h"

#include <AL/al.h>
#include <iostream>
#include <vector>

#include "Utils/FileUtils.h"

SoundBuffer::SoundBuffer() :
	id(0)
{
	alGenBuffers(1, &id);
}

SoundBuffer::~SoundBuffer() {
	alDeleteBuffers(1, &id);
}

bool SoundBuffer::Load(const char* filename) {
	std::vector<uint8_t> audioData;
	uint32_t format = 0;
	uint32_t sampleRate = 0;
	if (!FileUtils::ParseWav(filename, audioData, format, sampleRate)) {
		std::cerr << "Could not open file " << filename << "\n";
		return false;
	}

	alBufferData(id, format, audioData.data(), audioData.size(), sampleRate);

	return true;
}
