#include "Player.h"
#include "GameManager/ResourceManagers.h"
#include <GameStates\GSPlay.h>

Player::Player(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture)
	:Sprite2D(model, shader, texture)
{
	m_TargetPosition = Vector2(0, 0);
	m_MaxCooldown = 0.1;
	m_Cooldown = 0.0;
	m_speed = 250;
	m_MaxSpeed = 500; 
	m_SizeCollider = 15;
	m_isAlive = true;
	m_Level = 1;
	SetSize(50, 50);
}

Player::~Player()
{
}


void Player::MoveToPossition(Vector2 pos)
{
	m_TargetPosition = pos;
}

void Player::Update(GLfloat deltatime)
{
	if (!m_isAlive)
		return; 
	if (m_Cooldown > 0)
	{
		m_Cooldown -= deltatime;
	}

	Vector2 pos = Get2DPosition();

	if (pos.x < m_TargetPosition.x)
	{ 
		SetTexture(ResourceManagers::GetInstance()->GetTexture("Player"));
		pos.x += m_speed * deltatime;
		if (pos.x > m_TargetPosition.x)
			pos.x = m_TargetPosition.x;
	}

	if (pos.x > m_TargetPosition.x)
	{
		SetTexture(ResourceManagers::GetInstance()->GetTexture("Playerv2"));
		pos.x -= m_speed * deltatime;
		if (pos.x < m_TargetPosition.x)
			pos.x = m_TargetPosition.x;
	}

	if (pos.y < m_TargetPosition.y)
	{
		pos.y += m_speed * deltatime;
		if (pos.y > m_TargetPosition.y)
			pos.y = m_TargetPosition.y;
	}

	if (pos.y > m_TargetPosition.y)
	{
		pos.y -= m_speed * deltatime;
		if (pos.y < m_TargetPosition.y)
			pos.y = m_TargetPosition.y;
	}

	Set2DPosition(pos);
}

bool Player::CanShoot()
{
	return (m_Cooldown <= 0);
}

void Player::Shoot(std::vector<std::shared_ptr<Bullet>>& listBullet)
{
	//m_Cooldown = m_MaxCooldown;
	//for (auto bullet : listBullet)
	//{
	//	if (!bullet->IsActive())
	//	{
	//		bullet->SetActive(true);
	//		bullet->Set2DPosition(Get2DPosition());
	//		bullet->SetSpeed(500);
	//		bullet->SetType(BULLET_TYPE::Player);
	//		return;
	//	}
	//}

	//auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	//auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	//auto texture = ResourceManagers::GetInstance()->GetTexture("bullet");

	//std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(model, shader, texture);
	//bullet->SetSize(20, 20);
	//bullet->Set2DPosition(Get2DPosition());
	//bullet->SetSpeed(500);
	//bullet->SetType(BULLET_TYPE::Player);

	//listBullet.push_back(bullet);
}

float Player::distance(Vector2 pos, Vector2 target)
{
	return sqrt((pos.x - target.x) * (pos.x - target.x) + (pos.y - target.y) * (pos.y - target.y));
}

void Player::CheckCollider(std::vector<std::shared_ptr<Bullet>>& listBullet, std::vector<std::shared_ptr<Fish>> listFish)
{
	Vector2 pos = Get2DPosition();
	for (auto fish : listFish)
	{
		if (fish->IsActive())
		{
			if (distance(pos, fish->Get2DPosition()) < m_SizeCollider + fish->GetColliderSize())
			{
				if (fish->GetLevel() < GetLevel()) {
					GSPlay::m_score++;
					if (GSPlay::m_score % 10 == 0 && m_Level < 5) {
						m_Level++;  
						if (m_Level == 2) {
							SetSize(100, 100);
							SetColliderSize(50);
						}
						else if (m_Level == 3) {
							SetSize(200, 200);
							SetColliderSize(100);
						}
						else if (m_Level == 4) {
							SetSize(350, 350);
							SetColliderSize(200);
						}
					}
					fish->SetActive(false);
				}
				else if (fish->GetLevel() > GetLevel())
					m_isAlive = false; 
			}
		}
	} 
}

void Player::SetColliderSize(float size)
{
	m_SizeCollider = size;
}
float Player::GetColliderSize()
{
	return m_SizeCollider;
}
 
bool Player::IsAlive()
{
	return m_isAlive;
}
void Player::SetLevel(int level)
{
	m_Level = level;
}
int Player::GetLevel() {
	return m_Level;
}