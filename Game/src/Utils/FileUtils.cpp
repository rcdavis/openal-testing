#include "Utils/FileUtils.h"

#include <fstream>
#include <iostream>
#include <cstring>
#include <string>

#include <AL/al.h>

namespace FileUtils {
	struct WavChunkHeader {
		char id[4];
		uint32_t size;
	};

	struct WavFmtChunk {
		uint16_t audioFormat;
		uint16_t numChannels;
		uint32_t sampleRate;
		uint32_t byteRate;
		uint16_t blockAlign;
		uint16_t bitsPerSample;
	};

	bool ParseWav(const char* filename, std::vector<uint8_t>& audioData, uint32_t& format, uint32_t& sampleRate) {
		format = 0;
		sampleRate = 0;

		std::ifstream file(filename, std::ios::binary);
		if (!file) {
			std::cerr << "Could not open file\n";
			return false;
		}

		std::cout << "Parsing WAV file " << filename << "\n";

		WavChunkHeader riffHeader;
		file.read((char*)&riffHeader, sizeof(WavChunkHeader));

		if (strncmp(riffHeader.id, "RIFF", 4) != 0) {
			std::cerr << filename << " Doesn't have the RIFF chunk\n";
			return false;
		}

		char waveId[4];
		file.read(waveId, 4);

		if (strncmp(waveId, "WAVE", 4) != 0) {
			std::cerr << filename << " is not a valid WAV file\n";
			return false;
		}

		while (file) {
			WavChunkHeader header;
			file.read((char*)&header, sizeof(WavChunkHeader));
			if (!file)
				break; // EOF

			std::cout << "  Found chunk \"" << std::string(header.id, 4) << "\" (" << header.size << " bytes)\n";

			if (strncmp(header.id, "fmt ", 4) == 0) {
				std::vector<uint8_t> fmtBuffer(header.size);
				file.read((char*)fmtBuffer.data(), header.size);

				WavFmtChunk fmtChunk;
				memcpy(&fmtChunk, fmtBuffer.data(), header.size);

				if (fmtChunk.numChannels == 1 && fmtChunk.bitsPerSample == 8)
					format = AL_FORMAT_MONO8;
				else if (fmtChunk.numChannels == 1 && fmtChunk.bitsPerSample == 16)
					format = AL_FORMAT_MONO16;
				else if (fmtChunk.numChannels == 2 && fmtChunk.bitsPerSample == 8)
					format == AL_FORMAT_STEREO8;
				else if (fmtChunk.numChannels == 2 && fmtChunk.bitsPerSample == 16)
					format == AL_FORMAT_STEREO16;
				else
					return false;

				sampleRate = fmtChunk.sampleRate;
			} else if (strncmp(header.id, "data", 4) == 0) {
				audioData.resize(header.size);
				file.read((char*)audioData.data(), header.size);
			} else {
				// Other chunk types I don't care about for right now
				file.seekg(header.size, std::ios::cur);
			}

			// If the header size is odd, there's an extra padding byte
			if (header.size % 2 == 1)
				file.seekg(1, std::ios::cur);
		}

		return true;
	}
}
