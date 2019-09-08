#include "stdafx.h"
#include "cell.h"
#include "snake.h"
#include "renderHelpers.h"
#include "configManager.h"
#include "gameModel.h"
#include "player.h"
#include "boostManager.h"


Snake::Snake()
{
	init();
}

Snake::~Snake()
{
	for(UINT32 i=0; i < _body.size(); ++i)
	{
		delete _body[i];
	}
	_body.clear();
	delete _head;
}

void Snake::Clear()
{
	_speed=DEFAULT_SPEED;
	_is_alive=true;
	_dir=DIRECTION_RIGHT;
}

bool Snake::IsAlive()
{
	return _is_alive;
}

void Snake::Dead()
{
	_is_alive=false;
	
}

cell_v& Snake::getBody()
{
	return _body;
}
INT32 Snake::getLength()
{
	return (INT32)_body.size();
}
float Snake::getSpeed()
{
	return _speed;
}

float Snake::getDelta()
{
	return _delta;
}

float Snake::getDefaultSpeed()
{
	return _speed;
}

void Snake::init()
{
	_speed = DEFAULT_SPEED;
	_is_alive = true ;
	_dir = DIRECTION_RIGHT;
	_points = 0;
	_delta = 0.0f;
	_need_move = false;
	_need_resize = false;
	_boost_timer = 0.0f;
	_body.push_back(new hgeVector(0,0));
	_head = NULL; 
}

void Snake::setHead(hgeVector* head)
{
	 _head = head;
	(*_body[0]) = (*_head);
}

void Snake::AddPoints(INT32 points)
{
	_player->AddPoints(points);
}
//void Snake::SetBoost(int type, float timer, float koef)
//{
//	_speed_boosts[type].timer += timer;
//	if (koef > _speed_boosts[type].koef)
//		_speed_boosts[type].koef = koef;
//}

INT32 Snake::getCellSize()
{
	return _cell_size;
}

UINT Snake::getColor()
{
	return _color;		
}

void Snake::SetSpeed(float speed)
{
	_speed = speed;
}

void Snake::SetPlayer(Player * p)
{
	if(p)
		_player = p;
}

void Snake::Update(float dt)
{
	if(!_is_alive)
		return;
	Move(dt);
}

UINT32 Snake::getDir()
{
	return _dir;
}

hgeVector* Snake::getHead()
{
	return _head;
}

void Snake::SetDir(UINT32 dir)
{
	_dir = dir;
}

void Snake::Render()
{
	for(UINT8  i = 0 ; i < _body.size();++i)
	{
		DrawCell(_body[i]);
	}
}
bool Snake::Collision(UINT32 mode,void* check_value)
{
	switch(mode)
	{
	case COLLISION_SELF:
		{
			for(UINT32 i = 1 ; i<getLength();++i)
			{
				return (*_head) == (*_body[i]);
			}
		}
		break;
	case COLLISION_FRUITS:
		{
			if(check_value)
			{
				hgeVector* fruitPos = static_cast<hgeVector*>(check_value);
				if(fruitPos)
				{
					return (*_body[0]) == (*fruitPos);
				}
			}
		}
		break;
	case COLLISION_OTHERS:
		{
			if(check_value)
			{
				cell_v* v = static_cast<cell_v*>(check_value);
				for(UINT32 i=0; i<v->size();++i)
				{
					if((*_head) == (*(*v)[i]))
						return true;
				}
			}
		}
		break;
	}
	return false;
}

void Snake::Move(float dt)
{
	_delta += dt * (_speed * GameModel::getInstance()->GetBoostManager()->getBonus(this, BoostManager::PROP_SPEED));
	for(UINT32 i = 0 ; i < _player->GetControls().size();i++)
	{
		if(GameModel::hge->Input_GetKey() == _player->GetControls()[i])
		{
			if(i != _dir && NotOppositeDir(i))
			{
				_dir = i;
				break;
			}
		}
	}
	if(_delta >= 1)
	{
		(*_head) = (*_body[0]);
		switch(_dir)
		{
		case DIRECTION_UP:
			{
				--(_head->y);
				break;
			}
		case DIRECTION_RIGHT:
			{
				++(_head->x);
				break;
			}
		case DIRECTION_DOWN:
			{
				++(_head->y);
				break;
			}
		case DIRECTION_LEFT:
			{
				--(_head->x);
				break;
			}
		}
		if(Collision(COLLISION_SELF,_head))
		{
			Dead();
		}
		if(OutOfField(_head))
		{
			ReturnOnField(_head);
		}
		if(_need_resize)
		{
			_body.push_back(new hgeVector(0,0));
			_need_resize = false;
		}
		for (size_t i=getLength()-1;i > 0;--i)
		{
			(*_body[i]) = (*_body[i-1]);
		}
		(*_body[0]) = (*_head);
		_delta = 0;
		_need_move = true;

	}

}

void Snake::DrawCell(hgeVector* pos)
{
	float l = pos->x * _cell_size;
	float t = pos->y * _cell_size;
	float r = l + _cell_size;
	float b = t + _cell_size;
	RenderHelpers::FillRect(GameModel::hge, l+1, t+1, r-1, b-1, _color);
}

bool Snake::IsNeedCheckCollision()
{
	return _need_move;
}

bool Snake::OutOfField(hgeVector* pos)
{
	if(pos->x > GameModel::getInstance()->GetConfigManager()->getFieldWidth() - 1 || pos->x < 0)
		return true;
	if(pos->y > GameModel::getInstance()->GetConfigManager()->getFieldHeight() - 1 || pos->y < 0)
		return true;
	return false;
}

bool Snake::NotOppositeDir(INT32 value)
{
	switch(_dir)
	{
	case DIRECTION_UP:
		{
			return value != DIRECTION_DOWN;
		}
	case DIRECTION_RIGHT:
		{
			return value != DIRECTION_LEFT;
		}
	case DIRECTION_DOWN:
		{
			return value != DIRECTION_UP;
		}
	case DIRECTION_LEFT:
		{
			return value != DIRECTION_RIGHT;
		}
	}
}

bool Snake::IsResize()
{
	return _need_resize;
}

void Snake::NoNeedToMove()
{
	_need_move = false;
}

void Snake::ReturnOnField(hgeVector* pos)
{
	switch(_dir)
	{
	case DIRECTION_UP:
		{
			pos->y = GameModel::getInstance()->GetConfigManager()->getFieldHeight() -1;
			break;
		}
	case DIRECTION_DOWN:
		{
			pos->y = 0;
			break;
		}
	case DIRECTION_LEFT:
		{
			pos->x = GameModel::getInstance()->GetConfigManager()->getFieldWidth() - 1;
			break;
		}
	case DIRECTION_RIGHT:
		{
			pos->x = 0;
			break;
		}
	}
}
void Snake::NeedResize()
{
	_need_resize = true;
}

void Snake::SetCellSize(UINT32 cellSize)
{
	_cell_size = cellSize;
}

void Snake::SetColor(UINT32 color)
{
	_color = color;
}
