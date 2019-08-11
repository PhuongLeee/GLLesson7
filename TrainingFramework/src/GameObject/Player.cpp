#include "Player.h"
#include "GameManager/ResourceManagers.h"
#include <GameStates\GSPlay.h>
#include <GameStates\GsSetting.h>

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
	m_direction = 1;
	m_timedelay = 0;
	m_isEatting = false;
	m_isBooming = false;
	textureNormalL = ResourceManagers::GetInstance()->GetTexture("Player");
	textureNormalR = ResourceManagers::GetInstance()->GetTexture("Playerv2");
	textureNormalEatL = ResourceManagers::GetInstance()->GetTexture("Player_eat");
	textureNormalEatR = ResourceManagers::GetInstance()->GetTexture("Player_eat_v2");

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
	if (m_isEatting) {
		if (m_timedelay < 4) m_timedelay++;
		else {
			m_timedelay = 0;
			m_isEatting = false;
			SetTextureDirection();
		}
	}
	if (!m_isAlive)
		return;
	if (m_Cooldown > 0)
	{
		m_Cooldown -= deltatime;
	}

	Vector2 pos = Get2DPosition();

	if (pos.x < m_TargetPosition.x)
	{
		m_direction = 1;
		if (!m_isEatting) {
			SetTextureDirection();
		}
		pos.x += m_speed * deltatime;
		if (pos.x > m_TargetPosition.x)
			pos.x = m_TargetPosition.x;
	}

	if (pos.x > m_TargetPosition.x)
	{
		m_direction = -1;
		if (!m_isEatting) {
			SetTextureDirection();
		}
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

void Player::SetTextureDirection() {
	if (m_direction > 0) {
		SetTexture(textureNormalL);
	}
	else {
		SetTexture(textureNormalR);
	}
}
float Player::distance(Vector2 pos, Vector2 target)
{
	return sqrt((pos.x - target.x) * (pos.x - target.x) + (pos.y - target.y) * (pos.y - target.y));
}

bool Player::GetIsBooming() {
	return m_isBooming;
}

void Player::CheckCollider(std::vector<std::shared_ptr<Boom>>& listBullet, std::vector<std::shared_ptr<Fish>> listFish)
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

					if (GsSetting::m_OnSound) {
						SoundManager::GetInstance()->PlaySound("eat");
					}
					if (m_direction < 0) {
						SetTexture(textureNormalEatR);
					}
					else {
						SetTexture(textureNormalEatL);
					}
					m_isEatting = true;
					if (m_Level < 5 && GSPlay::m_score == leveltarget[m_Level - 1]) {
						m_Level++;
						if (m_Level == 2) {
							SetSize(100, 100);
							SetColliderSize(50);
						}
						else if (m_Level == 3) {
							SetSize(150, 150);
							SetColliderSize(80);
						}
						else if (m_Level == 4) {
							SetSize(350, 350);
							SetColliderSize(200);
						}
					}
					fish->SetActive(false);
				}
				else if (fish->GetLevel() > GetLevel()) {
					m_isAlive = false;

				}
			}
		}
		for (auto boom : listBullet)
		{
			if (boom->IsActive())
			{
				if (distance(pos, boom->Get2DPosition()) < m_SizeCollider + boom->GetColliderSize())
				{
					m_isBooming = true;
					boom->SetActive(false);
					m_isAlive = false;
				}
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
void Player::SetIsBooming(bool booming) {
	m_isBooming = booming;
}