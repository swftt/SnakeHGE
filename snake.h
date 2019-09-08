#pragma once
#include "cell.h"

#define  DEFAULT_SPEED 5

class Player;

class Snake
{
	Player* _player;
	cell_v _body;
	hgeVector* _head;

	UINT32 _dir;
	INT32 _cell_size;
	INT32 _points;
	UINT _color;

	float _speed;
	float _delta;
	float _boost_timer;

	bool _is_alive;
	bool _need_move;
	bool _need_resize;

	
public:
	enum 
	{
		DIRECTION_UP,
		DIRECTION_RIGHT,
		DIRECTION_DOWN,
		DIRECTION_LEFT
	};
	enum 
	{
		COLLISION_SELF,
		COLLISION_FRUITS,
		COLLISION_OTHERS
	};
	Snake();
	~Snake();

	cell_v& getBody();
	INT32 getLength();
	INT32 getPoints();
	INT32 getCellSize();
	UINT getColor();
	UINT32 getDir();

	hgeVector* getHead();

	float getSpeed();
	float getDelta();

	float getDefaultSpeed();
	void init();
	void setHead(hgeVector* head);
	void AddPoints(INT32 points);
	void SetDir(UINT32 dir);
	void SetSpeed(float speed);
	void SetPlayer(Player * p);
	void Update(float dt);
	void Render();
	void Clear();
	void Dead();
	void Move(float dt);
	void DrawCell(hgeVector* pos);
	void NoNeedToMove();
	void ReturnOnField(hgeVector* pos);
	void NeedResize();
	void SetCellSize(UINT32 cellSize);
	void SetColor(UINT32 color);

	bool Collision(UINT32 mode,void* check_value);
	bool IsAlive();
	bool IsNeedCheckCollision();
	bool OutOfField(hgeVector* pos);
	bool NotOppositeDir(INT32 value);
	bool IsResize();

};