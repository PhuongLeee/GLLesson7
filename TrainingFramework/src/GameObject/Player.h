#pragma once
#include "Sprite2D.h"
#include "Boom.h"
#include <Fish.h>

class Player : public Sprite2D
{

public:
	Player(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture);
	~Player();

	void MoveToPossition(Vector2 pos);
	void Update(GLfloat deltatime) override;

	bool CanShoot(); 

	void CheckCollider(std::vector<std::shared_ptr<Boom>>& listBoom, std::vector<std::shared_ptr<Fish>> listFish);

	void		SetColliderSize(float size);
	float		GetColliderSize();
	bool		IsAlive();
	void		SetLevel(int level);
	int			GetLevel();
	void		SetTextureDirection();
	bool		GetIsBooming();
	void		SetIsBooming(bool booming);
	int leveltarget[4] = { 15 ,60 ,130 ,300 };

private:
	Vector2 m_TargetPosition;
	bool	m_isAlive;
	float	m_speed;
	float	m_MaxSpeed;
	float	m_MaxCooldown;
	float	m_Cooldown;
	float	m_SizeCollider;
	int		m_Level;
	int		m_direction;
	int		m_timedelay;
	bool	m_isEatting;
	bool	m_isBooming;
	std::shared_ptr<Texture> textureNormalL;
	std::shared_ptr<Texture> textureNormalR;
	std::shared_ptr<Texture> textureNormalEatL;
	std::shared_ptr<Texture> textureNormalEatR;

	float distance(Vector2 pos, Vector2 target);
};
