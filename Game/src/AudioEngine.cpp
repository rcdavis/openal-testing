#include "AudioEngine.h"

#include <AL/al.h>
#include <AL/alc.h>

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <memory>

#include <SoundBuffer.h>
#include <SoundEffect.h>

namespace AudioEngine {
	static ALCdevice* device = nullptr;
	static ALCcontext* context = nullptr;

	static std::vector<std::unique_ptr<SoundEffect>> sfxList;
	static std::unordered_map<std::string, std::unique_ptr<SoundBuffer>> buffers;

	bool Init() {
		Shutdown();

		device = alcOpenDevice(nullptr);
		if (!device) {
			std::cerr << "Failed to open device\n";
			return false;
		}

		std::cout << "Opened audio device\n";

		context = alcCreateContext(device, nullptr);
		alcMakeContextCurrent(context);

		return true;
	}

	void Shutdown() {
		sfxList.clear();
		buffers.clear();

		if (context) {
			alcMakeContextCurrent(nullptr);
			alcDestroyContext(context);
			context = nullptr;
		}

		if (device) {
			alcCloseDevice(device);
			device = nullptr;
		}
	}

	SoundEffect* PlaySfx(const char* filename) {
		auto iter = buffers.find(filename);
		if (iter != buffers.cend()) {
			sfxList.push_back(std::make_unique<SoundEffect>(iter->second->Id()));
			sfxList.back()->Play();
			return sfxList.back().get();
		}

		auto buffer = std::make_unique<SoundBuffer>();
		if (!buffer->Load(filename)) {
			std::cerr << "Failed to load sound buffer for " << filename << '\n';
			return nullptr;
		}

		sfxList.push_back(std::make_unique<SoundEffect>(buffer->Id()));
		buffers[filename] = std::move(buffer);
		sfxList.back()->Play();
		return sfxList.back().get();
	}
}
