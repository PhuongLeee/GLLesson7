#include "Fish.h"
#include "GameManager/ResourceManagers.h"
#include <GameStates\GSPlay.h>

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
	m_positionY = ran*rand() % 20 + 10;

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

	Vector2 pos = Get2DPosition();
	pos.x += m_director * m_speed * deltaTime ;
	pos.y += m_positionY * deltaTime;
	Set2DPosition(pos);

	if (pos.y > Application::screenHeight)
		m_active = false;
}


//void Fish::Shoot(std::vector<std::shared_ptr<Bullet>>& listBullet)
//{
//	m_Cooldown = m_MaxCooldown;
//	for (auto bullet : listBullet)
//	{
//		if (!bullet->IsActive())
//		{
//			bullet->SetActive(true);
//			bullet->Set2DPosition(Get2DPosition());
//			bullet->SetSpeed(-500);
//			bullet->SetType(BULLET_TYPE::Enermy);
//			return;
//		}
//	}
//
//	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
//	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
//	auto texture = ResourceManagers::GetInstance()->GetTexture("bullet");
//
//	std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(model, shader, texture);
//	bullet->SetSize(20, 20);
//	bullet->Set2DPosition(Get2DPosition());
//	bullet->SetSpeed(-500);
//	bullet->SetType(BULLET_TYPE::Enermy);
//	listBullet.push_back(bullet);
//}

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
 