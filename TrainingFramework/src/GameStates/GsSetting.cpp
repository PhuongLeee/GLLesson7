#include "GsSetting.h"

bool GsSetting::m_OnSound = true;
GsSetting::GsSetting()
{

} 

GsSetting::~GsSetting()
{
} 
void GsSetting::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_main_menu");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(Application::screenWidth / 2, Application::screenHeight / 2);
	m_BackGround->SetSize(Application::screenWidth, Application::screenHeight);

	//play button
	if(GsSetting::m_OnSound) texture = ResourceManagers::GetInstance()->GetTexture("button_on");
	else texture = ResourceManagers::GetInstance()->GetTexture("button_off");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Application::screenWidth / 2 + 100, 300);
	button->SetSize(150, 90);
	
	button->SetOnClick([]() { 
		GsSetting::m_OnSound = !GsSetting::m_OnSound;
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Setting);
		});
	m_listButton.push_back(button);
	//exit Setting
	texture = ResourceManagers::GetInstance()->GetTexture("button_back");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Application::screenWidth / 2, 600);
	button->SetSize(300, 90);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Menu);
		});
	m_listButton.push_back(button); 

	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("BADABB__");
	m_Text_gameName = std::make_shared< Text>(shader, font, "SETTING", TEXT_COLOR::GREEN, 3.0);
	m_Text_gameName->Set2DPosition(Vector2(Application::screenWidth / 2 - 50, 120));

	m_Text_gameName = std::make_shared< Text>(shader, font, "SOUND", TEXT_COLOR::GREEN, 2.0);
	m_Text_gameName->Set2DPosition(Vector2(Application::screenWidth / 2 - 170, 320));
}


void GsSetting::Exit()
{
}


void GsSetting::Pause()
{

}

void GsSetting::Resume()
{

}


void GsSetting::HandleEvents()
{

}

void GsSetting::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GsSetting::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GsSetting::HandleMouseEvents(int x, int y)
{
}

void GsSetting::Update(float deltaTime)
{
	m_BackGround->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GsSetting::Draw()
{
	m_BackGround->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_Text_gameName->Draw();
}
