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
#include "Boom.h" 
#include "Bubble.h" 
#include "Fish.h"
#include "GsSetting.h"
#include "ExplosiveEffect.h"
#include "GSMenu.h"


int GSPlay::m_score = 0;

GSPlay::GSPlay()
{
	m_SpawnCooldown = 0.5;
	m_score = 0;
	pecentLevel = 70;
	m_timeRandomBoom = 100;
	m_timeDelayGameOver = 0;
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
	//Player
	texture = ResourceManagers::GetInstance()->GetTexture("Player");
	m_Player = std::make_shared<Player>(model, shader, texture);

	m_Player->Set2DPosition(Application::screenWidth / 2, Application::screenHeight - 100);
	m_Player->MoveToPossition(Vector2(Application::screenWidth / 2, Application::screenHeight - 100));
	//m_Player->SetSize(70, 80);

	//Level  
	texture = ResourceManagers::GetInstance()->GetTexture("levelGround1");
	m_Level = std::make_shared<Sprite2D>(model, shader, texture);
	m_Level->Set2DPosition(330, 55);
	m_Level->SetSize(400, 10);
	texture = ResourceManagers::GetInstance()->GetTexture("levelGround");
	m_Level1 = std::make_shared<Sprite2D>(model, shader, texture);
	m_Level1->Set2DPosition(130, 55);
	m_Level1->SetSize(0, 10);
	std::string tex;
	std::stringstream stream;
	m_levelFish.push_back(std::make_shared<Sprite2D>(model, shader, ResourceManagers::GetInstance()->GetTexture("Fish0")));
	float sizeX = m_levelFish.back()->GetSize().x*0.1;
	float sizeY = m_levelFish.back()->GetSize().y*0.1;
	m_levelFish.back()->SetSize(sizeX, sizeY);
	m_levelFish.back()->Set2DPosition(120, 38);
	for (int i = 0; i < 4; i++) {
		stream.str("");
		stream << std::fixed << std::setprecision(0) << (i + 1);
		tex = "Fish" + stream.str(); 
		m_levelFish.push_back(std::make_shared<Sprite2D>(model, shader, ResourceManagers::GetInstance()->GetTexture(tex))); 
		m_levelFish.back()->SetSize(sizeX, sizeY);
		m_levelFish.back()->Set2DPosition(130 + (int)m_Player->leveltarget[i] * 400 / 300, 38);
	}

	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("BADABB__");
	m_scoreText = std::make_shared< Text>(shader, font, "SCORE: ", TEXT_COLOR::RED, 1.0);
	m_scoreText->Set2DPosition(Vector2(800, 60));
	m_levelText = std::make_shared< Text>(shader, font, "LEVEL: ", TEXT_COLOR::RED, 1.0);
	m_levelText->Set2DPosition(Vector2(5, 60));

	//init effect
	model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	texture = ResourceManagers::GetInstance()->GetTexture("explosive");
	shader = ResourceManagers::GetInstance()->GetShader("SpriteShader");
	std::shared_ptr<ExplosiveEffect> exp = std::make_shared<ExplosiveEffect>(model, shader, texture, Vector2(960, 768), Vector2(192, 192), 0, 19, 0.7);
	exp->SetSize(100, 100);
	exp->SetActive(false);
	m_listExplosiveEffect.push_back(exp);

	//init sound
	SoundManager::GetInstance()->AddSound("eat");
	SoundManager::GetInstance()->AddSound("explosive_2");
	SoundManager::GetInstance()->AddSound("diee");
	// init BUbble
	model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	texture = ResourceManagers::GetInstance()->GetTexture("Bubble");
	for (int i = 0; i < 5; i++) {
		std::shared_ptr<Bubble> bubble = std::make_shared<Bubble>(model, shader, texture);
		bubble->Init();
		m_listBubbleEffect.push_back(bubble);
	}
}

void GSPlay::SetLevelTexture(int point) {
	if (m_Level1->GetSize().x >= 400) {
		m_Level1->SetSize(400, 10);
		return;
	}
	m_Level1->SetSize((int)(point * 400 / 300), 10);
	m_Level1->Set2DPosition(130 + (int)(point * 400 / 300) / 2, 55);
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
		CreateRandomFish();
		m_SpawnCooldown = 0.3;
	}
	// random Boom
	if (m_timeRandomBoom < 150) m_timeRandomBoom++;
	else {
		m_timeRandomBoom = 0;
		CreateRandomBoom();
	}

	//update player
	if (m_Player->IsAlive())
	{
		m_Player->Update(deltaTime);
		m_Player->CheckCollider(m_listBoom, m_listFish);
	}
	else {
		if (m_Player->GetIsBooming()) {
			SpawnExplosive(m_Player->Get2DPosition());
			m_Player->SetIsBooming(false);
			if (GsSetting::m_OnSound) {
				SoundManager::GetInstance()->PlaySound("explosive_2");
			}
		}
		if (m_timeDelayGameOver < 90) {
			m_timeDelayGameOver++;
		}
		else { 

			if (GsSetting::m_OnSound) {
				SoundManager::GetInstance()->PlaySound("diee");
			}
			GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_GameOver);
		}
 
	}

	//update fish
	for (auto fish : m_listFish)
	{
		if (fish->IsActive())
		{
			fish->Update(deltaTime);
			fish->CheckCollider(m_listBoom, m_listFish);
		}

	}
	// update boom
	for (auto boom : m_listBoom)
	{
		if (boom->IsActive())
		{
			boom->Update(deltaTime);
		}
	}
	//update Score
	std::stringstream stream;
	stream << std::fixed << std::setprecision(0) << m_score;
	std::string score = "SCORE: " + stream.str();
	m_scoreText->setText(score);
	SetLevelTexture(m_score);
	// update ex
	for (auto exp : m_listExplosiveEffect)
	{
		if (exp->IsActive())
		{
			exp->Update(deltaTime);
		}
	}
	for (auto bubble : m_listBubbleEffect) {
		bubble->Update(deltaTime);
	}
}

void GSPlay::Draw()
{
	//ground
	m_BackGround->Draw();
	m_Level->Draw();
	m_Level1->Draw();
	for (auto fish : m_listFish)
		if (fish->IsActive())
			fish->Draw();

	if (m_Player->IsAlive())
		m_Player->Draw();
	for (int i = 0; i < 5; i++)
		m_levelFish[i]->Draw();

	for (auto boom : m_listBoom)
		if (boom->IsActive())
			boom->Draw();
	for (auto exp : m_listExplosiveEffect)
		if (exp->IsActive())
			exp->Draw(); 
	//UI
	m_scoreText->Draw();
	m_levelText->Draw();
	for (auto bubble : m_listBubbleEffect) {
		bubble->Draw();
	}
}

void GSPlay::CreateRandomFish()
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
	int ran = rand() % 101;
	if (ran < pecentLevel) {
		level = rand() % m_Player->GetLevel();
	}
	else {
		level = rand() % 3 + m_Player->GetLevel();
		if (level > 4) level = 4;
	}

	for (auto fish : m_listFish)
	{
		if (!fish->IsActive())
		{
			fish->SetActive(true);
			fish->Set2DPosition(pos);
			fish->Init();
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
	if (level == 0) {
		fish->SetSize(fish->GetSize().x*0.1, fish->GetSize().y * 0.1);
		fish->SetColliderSize(20);
	}
	else if (level == 1) {
		fish->SetSize(fish->GetSize().x * 0.2, fish->GetSize().y * 0.2);
		fish->SetColliderSize(30);
	}
	else if (level == 2) {
		fish->SetSize(fish->GetSize().x * 0.4, fish->GetSize().y * 0.4);
		fish->SetColliderSize(40);
	}
	else if (level == 3) {
		fish->SetSize(fish->GetSize().x * 0.5, fish->GetSize().y * 0.5);
		fish->SetColliderSize(50);
	}
	else if (level == 4) {
		fish->SetSize(fish->GetSize().x * 0.7, fish->GetSize().y * 0.7);
		fish->SetColliderSize(60);
	}

	//fish->SetRotation2(0,0,180);
	m_listFish.push_back(fish);
}

void GSPlay::CreateRandomBoom() {
	//if (m_listBoom.size() < 5) {
	Vector2 pos;
	pos.y = 0;
	pos.x = rand() % (Application::screenWidth - 100) + 30;

	for (auto boom : m_listBoom)
	{
		if (!boom->IsActive())
		{
			boom->SetActive(true);
			boom->Set2DPosition(pos);
			boom->Init();
			return;
		}

	}
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("TNT");

	std::shared_ptr<Boom> boom = std::make_shared<Boom>(model, shader, texture);
	boom->SetSize(70, 70);
	boom->SetColliderSize(50);
	boom->Set2DPosition(pos);
	m_listBoom.push_back(boom);
	//}
}
void GSPlay::SpawnExplosive(Vector2 pos)
{
	for (auto exp : m_listExplosiveEffect)
	{
		if (!exp->IsActive())
		{
			exp->SetActive(true);
			exp->Set2DPosition(pos);
			return;
		}
	}

	//animation
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("explosive");
	auto shader = ResourceManagers::GetInstance()->GetShader("SpriteShader");
	std::shared_ptr<ExplosiveEffect> exp = std::make_shared<ExplosiveEffect>(model, shader, texture, Vector2(960, 768), Vector2(192, 192), 0, 19, 0.7);
	exp->SetSize(100, 100);
	exp->Set2DPosition(pos);
	m_listExplosiveEffect.push_back(exp);
}

