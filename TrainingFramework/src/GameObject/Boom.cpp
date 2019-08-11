#include "Boom.h"
#include "GameManager/ResourceManagers.h"

Boom::Boom(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture)
	:Sprite2D(model, shader, texture)
{
	m_speed =100.0;
	m_active = true; 
	m_SizeCollider = 10; 
	m_maxPosY = (rand() %400 + 400);
	m_timeDestroy = 0; 
	m_listStateHide.push_back(ResourceManagers::GetInstance()->GetTexture("TNT2"));
	m_listStateHide.push_back(ResourceManagers::GetInstance()->GetTexture("TNT3"));
	m_listStateHide.push_back(ResourceManagers::GetInstance()->GetTexture("TNT"));
	SetTexture(m_listStateHide[2]);
}

void Boom::Init() { 
	m_maxPosY = (rand() % 400 + 400);
	m_timeDestroy = 0; 
	SetTexture(m_listStateHide[2]);
}

Boom::~Boom()
{
}

void Boom::Update(GLfloat deltatime)
{
	if (!m_active)
		return;
	Vector2 pos = Get2DPosition();
	if (pos.y < m_maxPosY) {
		pos.y = pos.y + m_speed * deltatime;
	}
	else {
		if (m_timeDestroy < 150) {
			m_timeDestroy++;
			if (m_timeDestroy == 100) {
				SetTexture(m_listStateHide[0]);
			}
			else if (m_timeDestroy == 130) {
				SetTexture(m_listStateHide[1]);
			}
		}
		else {
			SetActive(false);
			m_active = false; 
		}
	}
	Set2DPosition(pos);

	if (pos.y <= 0 || pos.y > Application::screenHeight)
		m_active = false;
}

bool Boom::IsActive()
{
	return m_active;
}

void Boom::SetActive(bool status)
{
	m_active = status;
}

void Boom::SetSpeed(float speed)
{
	m_speed = speed;
}

void Boom::SetType(BULLET_TYPE type)
{
	m_type = type;
}

BULLET_TYPE Boom::GetType()
{
	return m_type;
}

void Boom::SetColliderSize(float size)
{
	m_SizeCollider = size;
}
float Boom::GetColliderSize()
{
	return m_SizeCollider;
}  
