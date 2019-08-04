#pragma once

#include "Sprite2D.h"

class Fish : public Sprite2D
{
public:
	Fish(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture);
	~Fish();
	bool		IsActive();
	void		SetActive(bool status);

	void		Update(float deltaTime) override;


	void		SetColliderSize(float size);
	float		GetColliderSize();


	void		Explosive();
	void		SetDirection(int dir);
	void		SetLevel(int level);
	int			GetLevel();

private: 
	bool	m_active;
	bool	m_Explosive;
	float	m_speed;
	float	m_MaxSpeed;
	float	m_MaxCooldown;
	float	m_Cooldown;
	float	m_SizeCollider;
	int		m_director;
	int		m_positionY;
	int		m_level;

	float distance(Vector2 pos, Vector2 target);

};
