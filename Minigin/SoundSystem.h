#pragma once

class SoundSystem
{
public:
	virtual ~SoundSystem() = default;

	SoundSystem(const SoundSystem&) = delete;
	SoundSystem(SoundSystem&&) = delete;
	SoundSystem& operator= (const SoundSystem&) = delete;
	SoundSystem& operator= (const SoundSystem&&) = delete;
};
