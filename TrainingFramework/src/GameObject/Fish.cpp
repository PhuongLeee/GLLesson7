#include "Fish.h"
#include "GameManager/ResourceManagers.h"
#include <GameStates\GSPlay.h>  
#include <iomanip> 

Fish::Fish(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture)
	:Sprite2D(model, shader, texture)
{
	m_active = false;
	m_MaxCooldown = 0.3;
	m_Cooldown = 0.0;
	m_speed = rand() % 150 + 100;
	m_MaxSpeed = 500;
	m_Explosive = false;
	m_SizeCollider = 20;
	int ran = rand() % 2;
	if (ran == 0) ran = -1;
	m_positionY = ran * rand() % 20 + 10;
	m_timeChangeDir = 0;
	m_timeChangeDirRan = ran % 300 + 100;
}

void Fish::Init() {
	int ran = rand() % 2;
	if (ran == 0) ran = -1;
	m_positionY = ran * rand() % 20 + 10;
	m_timeChangeDir = 0;
	m_timeChangeDirRan = ran % 300 + 100;
}

Fish::~Fish()
{
}


void Fish::Update(float deltaTime)
{
	if (!m_active)
		return;

	if (m_Explosive)
	{
		m_active = false;
		return;
	}

	if (m_Cooldown > 0)
	{
		m_Cooldown -= deltaTime;
	}
	if (m_timeChangeDir >= 0) {
		if (m_timeChangeDir < m_timeChangeDirRan)
			m_timeChangeDir++; 
		else {
			m_timeChangeDir = -1;
			m_director = rand() % 2;
			if (m_director == 0) m_director = -1;
			SetTextureByDirection();
		}
	}

	Vector2 pos = Get2DPosition();
	pos.x += m_director * m_speed * deltaTime;
	pos.y += m_positionY * deltaTime;
	Set2DPosition(pos);

	if (pos.y > Application::screenHeight + 50)
		m_active = false;
} 

void Fish::CheckCollider(std::vector<std::shared_ptr<Boom>>& listBoom, std::vector<std::shared_ptr<Fish>> listFish)
{
	Vector2 pos = Get2DPosition();
	for (auto fish : listFish)
	{
		if (fish->IsActive())
		{
			if (distance(pos, fish->Get2DPosition()) < m_SizeCollider + fish->GetColliderSize())
			{
				if (fish->GetLevel() < GetLevel()) {
					fish->SetActive(false); 
				}
				else if (fish->GetLevel() > GetLevel()) {
					m_active = false;
					SetActive(false); 
				}
			}
		} 
	}
}

void Fish::SetTextureByDirection() {
	std::stringstream stream;
	stream << std::fixed << std::setprecision(0) << m_level;
	std::string tex = "Fish" + stream.str();
	if (m_director < 0) tex += "v2";
	auto texture = ResourceManagers::GetInstance()->GetTexture(tex);
	SetTexture(texture);
}

float Fish::distance(Vector2 pos, Vector2 target)
{
	return sqrt((pos.x - target.x) * (pos.x - target.x) + (pos.y - target.y) * (pos.y - target.y));
}

bool Fish::IsActive()
{
	return m_active;
}

void Fish::SetActive(bool status)
{
	m_active = status;
	m_Explosive = false;
}

void Fish::SetDirection(int dir)
{
	m_director = dir;
}
void Fish::SetLevel(int level)
{
	m_level = level;
}


void Fish::Explosive()
{
	m_Explosive = true;
}


void Fish::SetColliderSize(float size)
{
	m_SizeCollider = size;
}

float Fish::GetColliderSize()
{
	return m_SizeCollider;
}

int Fish::GetLevel()
{
	return m_level;
}
