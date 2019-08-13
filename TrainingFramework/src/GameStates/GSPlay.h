#pragma once
#include "gamestatebase.h"

class Player;
class Boom;
class Fish;
class Text;
class ExplosiveEffect;
class Bubble;

class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

	void Init()override;
	void Exit()override;

	void Pause()override;
	void Resume()override;

	void HandleEvents() override;
	void HandleKeyEvents(int key, bool bIsPressed) override;
	void HandleMouseEvents(int x, int y) override;

	void HandleTouchEvents(int x, int y, bool bIsPressed) override;
	void Update(float deltaTime) override;
	void Draw() override; 
	static int m_score;
	
	void SetLevelTexture(int point); 

private:
	std::shared_ptr<Sprite2D> m_BackGround;
	std::shared_ptr<Sprite2D> m_Level;
	std::shared_ptr<Sprite2D> m_Level1;
	std::shared_ptr<Text>  m_scoreText;
	std::shared_ptr<Text>  m_levelText;
	//std::shared_ptr<Text>  m_playerHealText;
	std::shared_ptr<Player> m_Player;
	std::vector<std::shared_ptr<Boom>> m_listBoom;
	std::vector<std::shared_ptr<Fish>> m_listFish;
	std::vector<std::shared_ptr<ExplosiveEffect>> m_listExplosiveEffect;  
	std::vector<std::shared_ptr<Sprite2D> > m_levelFish;
	std::list<std::shared_ptr<Bubble>> m_listBubbleEffect;
	float m_SpawnCooldown;
	int pecentLevel;
	int m_timeRandomBoom;
	int m_timeDelayGameOver;

	void CreateRandomFish();
	void CreateRandomBoom();
	void SpawnExplosive(Vector2 pos);
};

