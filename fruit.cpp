#include "stdafx.h"
#include "fruit.h"
#include "cell.h"
#include "gameModel.h"
Fruit::Fruit()
{
	/*std::vector<int> chance;
	for (int i = 0; i < 3; i++)
		chance.push_back(FRUIT_TYPE_FOOD_APPLE);
	for (int i = 0; i < 1; i++)
		chance.push_back(FRUIT_TYPE_FOOD_APPLES);
	GameModel::hge->Random_Int(0, chance.size()-1);*/
	init();
}	

Fruit::~Fruit()
{
	if(_pos)
		delete _pos;
	if(_spr)
		delete _spr;
}

hgeVector* Fruit::getPos()
{
	return _pos;
}
UINT32 Fruit::getState()
{
	return (UINT32)_state;
}

void Fruit::init()
{
	_pos = NULL;
	_spr = NULL;
	_state = FRUIT_TYPE_UNKNOWN;
	_is_alive = true;
	_cell_size = 0;
}

void Fruit::setPos(hgeVector* pos)
{
	if(pos)
		_pos = pos;
}

void Fruit::setSprite(hgeSprite* spr)
{
	_spr = spr;
}

void Fruit::setCellSIze(UINT32 cell_size)
{
	_cell_size = cell_size;
}

void Fruit::setState(UINT32 state)
{
	_state = state;
}

void Fruit::update(float dt)
{
	if(!_is_alive)
	{
		return;
	}
}

void Fruit::render()
{
	_spr->RenderEx(_pos->x * _cell_size,_pos->y * _cell_size,0,_cell_size/_spr->GetHeight());
}