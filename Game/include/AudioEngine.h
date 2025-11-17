#pragma once

namespace AudioEngine {
	/**
	 * Initializes the system to play audio.
	 */
	bool Init();

	/**
	 * Cleanups all resources for playing audio.
	 */
	void Shutdown();
}
