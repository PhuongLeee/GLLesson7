#include "Bubble.h"
#include "GameManager/ResourceManagers.h"

Bubble::Bubble(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture)
	:Sprite2D(model, shader, texture)
{ 
	sizeX = GetSize().x;
	sizeY = GetSize().y;
	Init();
}
 
Bubble::~Bubble()
{
} 
void Bubble::Init() {
	m_speed = rand() % 30 + 30; 
	Set2DPosition(rand() % Application::screenWidth, rand() % 250 + Application::screenHeight);
	float scale = (rand() % 7 + 2)*0.1;
	SetSize(sizeX * scale, sizeY * scale);
	m_active = true;
}

void Bubble::Update(GLfloat deltatime)
{
	if (!m_active)
		return;
	Vector2 pos = Get2DPosition(); 

	pos.y = pos.y - m_speed * deltatime; 
	Set2DPosition(pos);

	if (pos.y <= 0)
		Init();
}

bool Bubble::IsActive()
{
	return m_active;
}

void Bubble::SetActive(bool status)
{
	m_active = status;
}

void Bubble::SetSpeed(float speed)
{
	m_speed = speed;
}  