#pragma once

class SoundEffect;

namespace AudioEngine {
	/**
	 * Initializes the system to play audio.
	 */
	bool Init();

	/**
	 * Cleanups all resources for playing audio.
	 */
	void Shutdown();

	SoundEffect* PlaySfx(const char* filename);
}
