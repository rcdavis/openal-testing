
#include <AL/al.h>
#include <AL/alc.h>
#include <iostream>

int main(int argc, char** argv) {
	ALCdevice* device = alcOpenDevice(nullptr);
	if (!device) {
		std::cerr << "Failed to open device\n";
		return -1;
	}

	std::cout << "Opened audio device\n";
	alcCloseDevice(device);

	return 0;
}
