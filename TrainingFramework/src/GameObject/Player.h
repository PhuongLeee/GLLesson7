#pragma once
#include "Sprite2D.h"
#include "Bullet.h"
#include <Fish.h>

class Player : public Sprite2D
{
	
public:
	Player(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture);
	~Player();

	void MoveToPossition(Vector2 pos);
	void Update(GLfloat deltatime) override; 

	void CheckCollider(std::vector<std::shared_ptr<Bullet>>& listBullet, std::vector<std::shared_ptr<Fish>> listEnermy);

	void		SetColliderSize(float size);
	float		GetColliderSize(); 
	bool		IsAlive();
	void		SetLevel(int level);
	int			GetLevel();

private:
	Vector2 m_TargetPosition; 
	bool	m_isAlive;
	float	m_speed;
	float	m_MaxSpeed;
	float	m_MaxCooldown;
	float	m_Cooldown;
	float	m_SizeCollider;
	int		m_Level;

	float distance(Vector2 pos, Vector2 target);
};
