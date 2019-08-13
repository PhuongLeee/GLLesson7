#pragma once
#pragma once
#include "gamestatebase.h"
#include "GameButton.h"
#include "Player.h"

class GsSetting :
	public GameStateBase
{
public:
	GsSetting();
	~GsSetting();

	void Init()override;
	void Exit()override;

	void Pause()override;
	void Resume()override;

	void HandleEvents()override;
	void HandleKeyEvents(int key, bool bIsPressed)override;
	void HandleTouchEvents(int x, int y, bool bIsPressed)override;
	void HandleMouseEvents(int x, int y) override;
	void Update(float deltaTime)override;
	void Draw()override; 
	static bool m_OnSound;
private:
	std::shared_ptr<Sprite2D> m_BackGround;
	std::shared_ptr<Sprite2D> m_PlayerTheme;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::shared_ptr<Text>  m_Text_gameName; 
};

