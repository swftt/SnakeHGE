#pragma once

class Field;
class Snake;
class HGE;
class GamePanel;
class Fruit;

enum Handler
{
	DrawPanel,
	DrawField
};

class Mechanic
{
	Field*	_field;
	GamePanel* _panel;
	std::vector<Fruit*> _fruits;
	std::vector<Snake*> _snakes;

	UINT32 _chosen_players_qty;
	bool _game_over;


public:
	Mechanic();
	~Mechanic();

	void update(float dt);
	void render();
	void collision(Snake* snake);
	void setChosenPlayersQty(UINT32 qty);
	void setSnakes(std::vector<Snake*> snakes);
	void setFruits(std::vector<Fruit*> fruits);
	void setGamePanel(GamePanel* game_panel);
	void generateFruit(Fruit* fruit);

	void init();
	UINT32 getChosenPlayersQty();
	Field* getField();
	std::vector<Fruit*> getFruits();
	std::vector<Snake*>& getSnakes();
	hgeVector* generateFruitPos();

	bool isGameOver();
};