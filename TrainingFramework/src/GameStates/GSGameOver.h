#pragma once 
#include "GameButton.h"
#include "Bubble.h"
#include "GameStates/GameStatebase.h"

class GSGameOver :
	public GameStateBase
{
public:
	GSGameOver();
	~GSGameOver();

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

private:
	std::shared_ptr<Sprite2D> m_BackGround;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::shared_ptr<Text>  m_Text_gameover;
	std::shared_ptr<Text>  m_Text_Score;
	std::list<std::shared_ptr<Bubble>> m_listBubbleEffect;

};