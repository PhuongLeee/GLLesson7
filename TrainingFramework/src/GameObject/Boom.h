#pragma once
#include "Sprite2D.h"
#include "Application.h"

enum class BULLET_TYPE
{
	None,
	Player,
	Enermy
};

class Boom  : public Sprite2D
{
public:
	Boom(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture);
	~Boom();

	void		Update(GLfloat deltatime) override;
	void		SetSpeed(float speed);

	bool		IsActive();
	void		SetActive(bool status);

	void		SetType(BULLET_TYPE type);
	BULLET_TYPE	GetType();

	void		SetColliderSize(float size);
	void		Init();
	float		GetColliderSize(); 
				
private:
	BULLET_TYPE m_type;
	bool	m_active;
	float	m_speed;
	float	m_SizeCollider; 
	int		m_maxPosY;
	int		m_timeDestroy;
	int		m_timeDestroyMax; 
	std::vector<std::shared_ptr<Texture>> m_listStateHide;
};
