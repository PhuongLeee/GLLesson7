#pragma once
#include "Helper/Singleton.h"
#include "GameConfig.h"
#include "Helper/ThreadPool.h"

class SoundManager : public CSingleton<SoundManager>
{
public:
	SoundManager();
	~SoundManager();

	void PlaySound(const std::string& name, bool loop = false);
private:

};
