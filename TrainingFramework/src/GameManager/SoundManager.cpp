#include "SoundManager.h"



SoundManager::SoundManager()
{
	ThreadPool::GetInstance()->init();
}

SoundManager::~SoundManager()
{
	ThreadPool::GetInstance()->shutdown();
}

void SoundManager::PlaySound(const std::string& name, bool loop)
{
	//ThreadPool::GetInstance()->submit();
}
