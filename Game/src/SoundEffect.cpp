#include "SoundEffect.h"

#include <AL/al.h>

SoundEffect::SoundEffect(uint32_t bufferId) :
	id(0)
{
	alGenSources(1, &id);
	alSourcei(id, AL_BUFFER, (ALint)bufferId);
}

SoundEffect::~SoundEffect() {
	alDeleteSources(1, &id);
}

void SoundEffect::Play(bool isLooping) {
	alSourcei(id, AL_LOOPING, isLooping ? AL_TRUE : AL_FALSE);
	alSourcePlay(id);
}

void SoundEffect::Stop() {
	alSourceStop(id);
}

bool SoundEffect::IsPlaying() const {
	ALint state;
	alGetSourcei(id, AL_SOURCE_STATE, &state);
	return state == AL_PLAYING;
}
