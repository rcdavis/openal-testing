#include "SoundBuffer.h"

#include <AL/al.h>
#include <fstream>
#include <iostream>
#include <cstring>
#include <vector>

struct WavHeader {
	char riff[4];
	uint32_t chunkSize;
	char wave[4];
	char fmt[4];
	uint32_t subchunk1Size;
	uint16_t audioFormat;
	uint16_t numChannels;
	uint32_t sampleRate;
	uint32_t byteRate;
	uint16_t blockAlign;
	uint16_t bitsPerSample;

	char dataHeader[4];
	uint32_t dataSize;
};

SoundBuffer::SoundBuffer() :
	id(0)
{
	alGenBuffers(1, &id);
}

SoundBuffer::~SoundBuffer() {
	alDeleteBuffers(1, &id);
}

bool SoundBuffer::Load(const char* filename) {
	std::ifstream file(filename, std::ios::binary);
	if (!file) {
		std::cerr << "Could not open file\n";
		return false;
	}

	WavHeader header;
	file.read((char*)&header, sizeof(WavHeader));

	if (strncmp(header.riff, "RIFF", 4) != 0 || strncmp(header.wave, "WAVE", 4) != 0) {
		std::cerr << "Not a valid WAV file\n";
		return false;
	}

	std::vector<uint8_t> audioData(header.dataSize);
	file.read((char*)audioData.data(), header.dataSize);

	ALenum format;
	if (header.numChannels == 1 && header.bitsPerSample == 8)
		format = AL_FORMAT_MONO8;
	else if (header.numChannels == 1 && header.bitsPerSample == 16)
		format = AL_FORMAT_MONO16;
	else if (header.numChannels == 2 && header.bitsPerSample == 8)
		format == AL_FORMAT_STEREO8;
	else if (header.numChannels == 2 && header.bitsPerSample == 16)
		format == AL_FORMAT_STEREO16;
	else
		return false;

	const ALsizei sampleRate = (ALsizei)header.sampleRate;

	alBufferData(id, format, audioData.data(), audioData.size(), sampleRate);

	return true;
}
