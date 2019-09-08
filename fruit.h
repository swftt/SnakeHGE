#pragma once

class Fruit
{
	UINT32 _state;
	UINT32 _cell_size;
	hgeSprite* _spr;
	hgeVector* _pos;

	bool _is_alive;
public:
	enum 
	{
		FRUIT_TYPE_UNKNOWN,
		FRUIT_TYPE_FOOD_APPLE,
		FRUIT_TYPE_SPEED_UP,
		FRUIT_TYPE_SPEED_DOWN,
		FRUIT_TYPE_FOOD_APPLES,
		FRUIT_TYPE_SPEED_RANDOM_FREEZE,
		FRUIT_TYPE_SPEED_ALL_FREEZE,
		FRUIT_TYPE_SPEED_SELF_FREEZE
	};
	enum
	{
		FRUIT_REWARD_FOOD_APPLE = 20,
		FRUIT_REWARD_FOOD_APPLES = 50
	};
	enum
	{
		FRUIT_TIME_FREEZE_RANDOM = 2,
		FRUIT_TIME_FREEZE_ALL = 3,
		FRUIT_TIME_FREEZE_SELF = 4,
		FRUIT_TIME_SPEED_UP = 5,
		FRUIT_TIME_SPEED_DOWN = 6,
	};
	enum 
	{
		FRUIT_SPEED_FREEZE,
		FRUIT_SPEED_DOWN = 2,
		FRUIT_SPEED_UP = 8
	};
	Fruit();
	~Fruit();
	hgeVector* getPos();
	UINT32 getState();

	void init();
	void setPos(hgeVector* pos);
	void setSprite(hgeSprite* spr);
	void setCellSIze(UINT32 cell_size);
	void setState(UINT32 state);
	void update(float dt);
	void render();
};