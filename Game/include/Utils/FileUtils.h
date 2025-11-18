#pragma once

#include <cstdint>
#include <vector>

namespace FileUtils {
	bool ParseWav(const char* filename, std::vector<uint8_t>& audioData, uint32_t& format, uint32_t& sampleRate);
}
