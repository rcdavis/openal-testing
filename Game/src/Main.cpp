
#include "AudioEngine.h"

#include "SoundEffect.h"

#include <thread>

int main(int argc, char** argv) {
	if (!AudioEngine::Init()) {
		return -1;
	}

	auto sfx = AudioEngine::PlaySfx("res/sfx/CashRegister.wav");
	if (sfx) {
		while (sfx->IsPlaying()) {
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	}

	AudioEngine::Shutdown();
	return 0;
}
