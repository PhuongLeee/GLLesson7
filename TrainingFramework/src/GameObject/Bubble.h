#pragma once
#pragma once
#include "Sprite2D.h"
#include "Application.h"
 
class Bubble : public Sprite2D
{
public:
	Bubble(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture);
	~Bubble();

	void		Update(GLfloat deltatime) override;
	void		SetSpeed(float speed);

	bool		IsActive();
	void		SetActive(bool status);
	void		Init();

private:
	bool	m_active;
	float	m_speed;
	float	m_time;
	float	sizeX;
	float	sizeY;
	
};
