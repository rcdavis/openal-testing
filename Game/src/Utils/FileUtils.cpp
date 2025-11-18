#include "Utils/FileUtils.h"

#include <fstream>
#include <iostream>
#include <cstring>

#include <AL/al.h>

namespace FileUtils {
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

	bool ParseWav(const char* filename, std::vector<uint8_t>& audioData, uint32_t& format, uint32_t& sampleRate) {
		format = 0;
		sampleRate = 0;

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

		audioData.resize(header.dataSize);
		file.read((char*)audioData.data(), header.dataSize);

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

		sampleRate = header.sampleRate;

		return true;
	}
}
