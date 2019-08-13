#include "GSGameOver.h"
#include <sstream>
#include <iomanip> 
#include "GSPlay.h"

GSGameOver::GSGameOver()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("Bubble");
	for (int i = 0; i < 10; i++) {
		std::shared_ptr<Bubble> bubble = std::make_shared<Bubble>(model, shader, texture);
		bubble->Init();
		m_listBubbleEffect.push_back(bubble);
	}
}


GSGameOver::~GSGameOver()
{
}



void GSGameOver::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_main_menu");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(Application::screenWidth / 2, Application::screenHeight / 2);
	m_BackGround->SetSize(Application::screenWidth, Application::screenHeight);

	//play button
	texture = ResourceManagers::GetInstance()->GetTexture("button_play_again");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Application::screenWidth / 2, 400);
	button->SetSize(300, 90);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Play);
		});
	m_listButton.push_back(button);

	//home button
	texture = ResourceManagers::GetInstance()->GetTexture("button_home");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Application::screenWidth / 2, 500);
	button->SetSize(300, 90);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Menu);
		});
	m_listButton.push_back(button);

	//exit button
	texture = ResourceManagers::GetInstance()->GetTexture("button_quit");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Application::screenWidth / 2, 600);
	button->SetSize(300, 90);
	button->SetOnClick([]() {
		exit(0);
		});
	m_listButton.push_back(button);

	//text game over
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_Text_gameover = std::make_shared< Text>(shader, font, "GAMEOVER", TEXT_COLOR::GREEN, 3.0);
	m_Text_gameover->Set2DPosition(Vector2(Application::screenWidth / 2 - 180, 120));
	// text game score  
	m_Text_Score = std::make_shared< Text>(shader, font, "", TEXT_COLOR::GREEN, 2.0);
	m_Text_Score->Set2DPosition(Vector2(Application::screenWidth / 2 - 150, 200));
	std::stringstream stream;
	stream << std::fixed << std::setprecision(0) << GSPlay::m_score;
	std::string score = "SCORE: " + stream.str();
	m_Text_Score->setText(score);
}

void GSGameOver::Exit()
{
}


void GSGameOver::Pause()
{

}

void GSGameOver::Resume()
{

}


void GSGameOver::HandleEvents()
{

}

void GSGameOver::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSGameOver::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSGameOver::HandleMouseEvents(int x, int y)
{
}

void GSGameOver::Update(float deltaTime)
{
	m_BackGround->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
	for (auto bubble : m_listBubbleEffect) {
		bubble->Update(deltaTime);
	}
}

void GSGameOver::Draw()
{
	m_BackGround->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_Text_Score->Draw();
	m_Text_gameover->Draw();
	for (auto bubble : m_listBubbleEffect) {
		bubble->Draw();
	}
}
