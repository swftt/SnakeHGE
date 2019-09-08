#include "stdafx.h"
#include "mechanic.h"
#include "renderHelpers.h"
#include "gameModel.h"
#include "boostManager.h"
#include "mainMenu.h"
#include "cell.h"
#include "field.h"
#include "gamePanel.h"
#include "snake.h"
#include "fruit.h"
#include "configManager.h"

Mechanic::Mechanic():
_game_over(false)
{
	init();
}
Mechanic::~Mechanic()
{
	if(_field)
		delete _field;
	if(_panel)
		delete _panel;
	if(!_snakes.empty())
	{
		for(INT32 i = 0 ;i < _snakes.size();++i)
		{
			delete _snakes[i];
		}
		_snakes.clear();
	}
	if(!_fruits.empty())
	{
		for(INT32 i = 0 ;i < _fruits.size();++i)
		{
			delete _fruits[i];
		}
		_fruits.clear();
	}
}

void Mechanic::update(float dt)
{
	if(_game_over)
	{
		GameModel::getInstance()->GetMainMenu()->SetState(sNone);
		return;
	}
	if(_field)
		_field->update(dt);
	if(_panel)
	{
		if(_panel->needUpdate())
		{
			_panel->update(dt);
		}
	}
	if(_fruits.size() < _snakes.size())
	{
		_fruits.push_back(new Fruit());
		generateFruit(_fruits[_fruits.size()-1]);
		_fruits[_fruits.size()-1]->setCellSIze(GameModel::getInstance()->GetConfigManager()->getScreenHeight()/GameModel::getInstance()->GetConfigManager()->getFieldHeight());
	}
	for(UINT32 i=0; i < _fruits.size();++i)
	{
		if(_fruits[i])
			_fruits[i]->update(dt);
	}
	for (UINT32 i = 0;i<_snakes.size();++i)
	{
		if(!_snakes[i]->IsAlive())
			continue;
		_snakes[i]->Update(dt);
		if (_snakes[i]->IsNeedCheckCollision())
		{
			collision(_snakes[i]);
			_snakes[i]->NoNeedToMove();
		}				
	}

}

void Mechanic::render()
{
	if(_field)
		_field->render();
	if(_panel)
		_panel->render();
	for (INT32 i = 0 ; i<_snakes.size();++i)
	{
		if(_snakes[i])
			_snakes[i]->Render();
	}
	for (INT32 i = 0 ; i<_fruits.size();++i)
	{
		if(_fruits[i])
			_fruits[i]->render();
	}

}



void Mechanic::collision(Snake* snake)
{
	if (!snake)
		return;

	for(UINT32 j = 0 ; j < _snakes.size();++j)
	{
		Snake* tmp_snake = _snakes[j];
		if(tmp_snake!=snake)
		{
			if(snake->IsAlive())
			{
				if(snake->Collision(Snake::COLLISION_OTHERS, &(tmp_snake->getBody())))
				{
					snake->Dead();
					/*_snakes.erase(std::remove(_snakes.begin(),_snakes.end(),snake),_snakes.end());
					delete snake;
					if(_snakes.size() == 1)
					{
						_gameOver = true;
					}*/
					continue;
				}
			}
		}
	}
	for(UINT8 i = 0 ; i<_fruits.size(); ++i)
	{
		if(snake->Collision(Snake::COLLISION_FRUITS,_fruits[i]->getPos()))
		{
			if (GameModel::getInstance()->GetBoostManager()->applyBoost(_fruits[i], snake, &_snakes))
			{
				delete _fruits[i];
				_fruits.erase(_fruits.begin() + i);
			}
			break;
		}
	}

}

void Mechanic::setChosenPlayersQty(UINT32 qty)
{
	_chosen_players_qty = qty;
}

void Mechanic::setFruits(std::vector<Fruit*> fruits)
{

}

void Mechanic::generateFruit(Fruit* fruit)
{
	UINT32 state;
	const char* path = NULL;
	state = GameModel::hge->Random_Int(Fruit::FRUIT_TYPE_FOOD_APPLE,Fruit::FRUIT_TYPE_SPEED_DOWN); //instead of 0 must be min value of enum, instead of 3 must be max value
	// SOLUTION : to add enums FRUIT_TYPE_MIN and FRUIT_TYPE_MAX ?? 
	switch(state)
	{
	case Fruit::FRUIT_TYPE_UNKNOWN:
		{
			//??
		}
	case Fruit::FRUIT_TYPE_FOOD_APPLE:
		{
			path = "../data/textures/apple.png";
			break;
		}
	case Fruit::FRUIT_TYPE_SPEED_UP:
		{
			path = "../data/textures/buff.png";
			break;
		}
	case Fruit::FRUIT_TYPE_SPEED_DOWN:
		{
			path = "../data/textures/debuff.png";
			break;
		}
	}
	HTEXTURE tex = GameModel::hge->Texture_Load(path);
	UINT32 w = GameModel::hge->Texture_GetWidth(tex);
	UINT32 h = GameModel::hge->Texture_GetHeight(tex);
	hgeSprite* spr = new hgeSprite(tex,0,0,w,h);
	hgeVector* pos = generateFruitPos();
	fruit->setState(state);
	fruit->setPos(pos);
	fruit->setSprite(spr);
}

void Mechanic::init()
{
	_game_over = false;
	UINT32 screenHeight = GameModel::getInstance()->GetConfigManager()->getScreenHeight();
	UINT32 screenWidth = GameModel::getInstance()->GetConfigManager()->getScreenWidth();
	UINT32 fieldHeight = GameModel::getInstance()->GetConfigManager()->getFieldHeight();
	UINT32 fieldWidth = GameModel::getInstance()->GetConfigManager()->getFieldWidth();
	UINT32 cellSize = screenHeight/fieldHeight;
	_chosen_players_qty = GameModel::getInstance()->GetConfigManager()->getChosenPlayersQty();

	_field = new Field();
	_field->setCellSize(cellSize);
	_field->setHeight(fieldHeight);
	_field->setWidth(fieldWidth);

	_panel = new GamePanel();
	_panel->setCellSize(cellSize);
	_panel->setPlayersQty(_chosen_players_qty);
	_panel->setScreenHeight(screenHeight);
	_panel->setScreenWidth(screenWidth);
	_panel->setColors(GameModel::getInstance()->GetConfigManager()->getColors());
	_panel->setPos(new hgeVector(fieldWidth * cellSize,0));
	_panel->setInfoPos();

	for(UINT32 i=0; i<_chosen_players_qty;++i)
	{
		_snakes.push_back(new Snake());
		_snakes[i]->SetPlayer(GameModel::getInstance()->GetConfigManager()->getPlayers()[i]);
		_snakes[i]->SetCellSize(cellSize);
		_snakes[i]->SetColor(GameModel::getInstance()->GetConfigManager()->getColors()[i]);
	}
	for(UINT32 i=0; i<_chosen_players_qty;++i)
	{
		_fruits.push_back(new Fruit());
		generateFruit(_fruits[i]);
		_fruits[i]->setCellSIze(cellSize);
		_snakes[i]->setHead(new hgeVector(i + 3 * i,3 + 10 * i)); //TODO positioning
	}
}

UINT32 Mechanic::getChosenPlayersQty()
{
	return _chosen_players_qty;
}

std::vector<Snake*>& Mechanic::getSnakes()
{
	return _snakes;
}

hgeVector* Mechanic::generateFruitPos()
{
	hgeVector* pos = new hgeVector();
	do 
	{
		pos->x = GameModel::hge->Random_Int(0,GameModel::getInstance()->GetConfigManager()->getFieldWidth() - 1);
		pos->y = GameModel::hge->Random_Int(0,GameModel::getInstance()->GetConfigManager()->getFieldHeight() - 1);
		for(UINT32 i=0; i<_fruits.size() - 1;++i)
		{
			if(_fruits[i])
			{
				if((*pos) == (*_fruits[i]->getPos()))
					return NULL;
			}
		}
		for(UINT32 i=0; i<_snakes.size();++i)
		{
			if(_snakes[i])
			{
				if(_snakes[i]->Collision(Snake::COLLISION_FRUITS,pos))
					return NULL;
			}
		}
	}while(!pos);

	return pos;
}

bool Mechanic::isGameOver()
{
	return _game_over;
}

