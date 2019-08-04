#include <sstream>
#include <iomanip>
#include <thread>

#include "GSPlay.h"
#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Text.h"
#include "Player.h"
#include "Bullet.h" 
#include "Fish.h"


int GSPlay::m_score = 0;
GSPlay::GSPlay()
{
	m_SpawnCooldown = 0.5;
	m_score = 0;
	pecentLevel = 70;
}


GSPlay::~GSPlay()
{

}


void GSPlay::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_play");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(Application::screenWidth / 2, Application::screenHeight / 2);
	m_BackGround->SetSize(Application::screenWidth, Application::screenHeight);

	texture = ResourceManagers::GetInstance()->GetTexture("Player");
	m_Player = std::make_shared<Player>(model, shader, texture);

	m_Player->Set2DPosition(Application::screenWidth / 2, Application::screenHeight - 100);
	m_Player->MoveToPossition(Vector2(Application::screenWidth / 2, Application::screenHeight - 100));
	m_Player->SetSize(50, 50);

	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_scoreText = std::make_shared< Text>(shader, font, "SCORE: ", TEXT_COLOR::RED, 1.0);
	m_scoreText->Set2DPosition(Vector2(5, 25));
	//m_playerHealText = std::make_shared< Text>(shader, font, "HEAL: ", TEXT_COLOR::RED, 1.0);
	//m_playerHealText->Set2DPosition(Vector2(5, 50));
}

void GSPlay::Exit()
{

}


void GSPlay::Pause()
{

}

void GSPlay::Resume()
{

}


void GSPlay::HandleEvents()
{

}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSPlay::HandleMouseEvents(int x, int y)
{
	m_Player->MoveToPossition(Vector2(x, y));
	
}


void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
}

void GSPlay::Update(float deltaTime)
{

	if (m_SpawnCooldown > 0)
	{
		m_SpawnCooldown -= deltaTime;
	}
	if (m_SpawnCooldown <= 0)
	{
		CreateRandomEnermy();
		m_SpawnCooldown = 0.3;
	}

	//update player
	if (m_Player->IsAlive())
	{
		m_Player->Update(deltaTime); 
		m_Player->CheckCollider(m_listBullet, m_listEnermy);
	}

	//update enermies
	for (auto enermy : m_listEnermy)
	{
		if (enermy->IsActive())
		{
			enermy->Update(deltaTime); 
		}
	} 

	//update Score
	std::stringstream stream;
	stream << std::fixed << std::setprecision(0) << m_score;
	std::string score = "SCORE: " + stream.str();
	m_scoreText->setText(score); 
}

void GSPlay::Draw()
{
	//ground
	m_BackGround->Draw();

	for (auto enermy : m_listEnermy)
		if (enermy->IsActive())
			enermy->Draw();

	if (m_Player->IsAlive())
		m_Player->Draw();

	for (auto bullet : m_listBullet)
		if (bullet->IsActive())
			bullet->Draw();

	//UI
	m_scoreText->Draw(); 
}

void GSPlay::CreateRandomEnermy()
{
	
	int range = Application::screenHeight + 10;
	int num = rand() % range + 10;
	int dir = rand() % 2; 
	Vector2 pos;
	pos.y = num;
	pos.x = Application::screenWidth + 100;
	// random direction
	if (dir == 0)
		dir = -1;
	else {
		pos.x = -30;
		dir = 1;
	}
	// randowm level
	int level = 0;
	int ran = rand()%101;
	if (ran < pecentLevel) {
		level = rand() % m_Player->GetLevel();
	}
	else {
		level = rand() % 3 + m_Player->GetLevel();
		if (level > 4) level = 4;
	}

	for (auto fish : m_listEnermy)
	{
		if (!fish->IsActive())
		{
			//fish->SetLevel(level);
			//fish->SetDirection(dir);
			fish->SetActive(true);
			fish->Set2DPosition(pos);
			return;
		}

	}
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	std::stringstream stream;
	stream << std::fixed << std::setprecision(0) << level; 
	std::string tex = "Fish" + stream.str();  
	if (dir < 0) tex += "v2";
	auto texture = ResourceManagers::GetInstance()->GetTexture(tex);
	
	std::shared_ptr<Fish> fish = std::make_shared<Fish>(model, shader, texture);
	fish->Set2DPosition(pos);
	// set level

	fish->SetLevel(level);
	fish->SetDirection(dir);
	if (level == 0){
		fish->SetSize(40, 40);
		fish->SetColliderSize(20);
	}
	else if (level == 1) {
		fish->SetSize(60, 60);
		fish->SetColliderSize(30);
	}
	else if (level == 2) {
		fish->SetSize(100, 100);
		fish->SetColliderSize(50);
	}
	else if (level == 3) {
		fish->SetSize(200, 200);
		fish->SetColliderSize(70);
	}
	else if (level == 4) {
		fish->SetSize(350, 300);
		fish->SetColliderSize(80);
	}
	
	//fish->SetRotation2(0,0,180);
	m_listEnermy.push_back(fish);
}
