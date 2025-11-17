#include "AudioEngine.h"

#include <AL/al.h>
#include <AL/alc.h>
#include <iostream>

namespace AudioEngine {
	static ALCdevice* device = nullptr;
	static ALCcontext* context = nullptr;

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
}
