
#include "AudioEngine.h"

int main(int argc, char** argv) {
	if (!AudioEngine::Init()) {
		return -1;
	}

	AudioEngine::Shutdown();
	return 0;
}
