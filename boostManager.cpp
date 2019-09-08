#include "stdafx.h"
#include "fruit.h"
#include "snake.h"
#include "gameModel.h"
#include "boostManager.h"


BoostManager* BoostManager::_instance = NULL;
bool BoostManager::applyBoost(Fruit* fruit,Snake* current_snake,std::vector<Snake*>* snakes)
{
	if(!current_snake)
		return false;
	switch(fruit->getState())
	{
	case Fruit::FRUIT_TYPE_UNKNOWN:
		{
			return false;
		}
	case Fruit::FRUIT_TYPE_FOOD_APPLE:
		{
			current_snake->AddPoints(Fruit::FRUIT_REWARD_FOOD_APPLE);
			current_snake->NeedResize();
			return true;
		}
	case Fruit::FRUIT_TYPE_FOOD_APPLES:
		{
			current_snake->AddPoints(Fruit::FRUIT_REWARD_FOOD_APPLES);
			current_snake->NeedResize();
			return true;
		}
	case Fruit::FRUIT_TYPE_SPEED_UP:
		{
			bool flag = false;
			std::vector<Bonus>* current_snake_bonuses = &snake_bonuses[current_snake];
			for(UINT32 i=0; i<current_snake_bonuses->size();++i)
			{
				Bonus* currBonus = &(*current_snake_bonuses)[i];
				if(currBonus->type == fruit->getState())
				{
					float newCoef = Fruit::FRUIT_SPEED_UP / current_snake->getDefaultSpeed();
					if(currBonus->coef < newCoef)
						currBonus->coef = newCoef;
					currBonus->timer = Fruit::FRUIT_TIME_SPEED_UP;
					flag = true;
					break;
				}
			}
			if(!flag)
			{
				float coef =   Fruit::FRUIT_SPEED_UP / current_snake->getDefaultSpeed();
				current_snake_bonuses->push_back(Bonus(Fruit::FRUIT_TYPE_SPEED_UP,PROP_SPEED,Fruit::FRUIT_TIME_SPEED_UP,coef));
			}
			return true;
		}
	case Fruit::FRUIT_TYPE_SPEED_DOWN:
		{
			bool flag = false;
			std::vector<Bonus>* current_snake_bonuses = &snake_bonuses[current_snake];
			for(UINT32 i=0; i<current_snake_bonuses->size();++i)
			{
				Bonus* currBonus = &(*current_snake_bonuses)[i];
				if(currBonus->type == fruit->getState())
				{
					float newCoef = Fruit::FRUIT_SPEED_DOWN / current_snake->getDefaultSpeed();
					if(currBonus->coef < newCoef)
						currBonus->coef = newCoef;
					currBonus->timer = Fruit::FRUIT_TIME_SPEED_DOWN;
					flag = true;
					break;
				}
			}
			if(!flag)
			{
				float coef =   Fruit::FRUIT_SPEED_DOWN / current_snake->getDefaultSpeed();
				current_snake_bonuses->push_back(Bonus(Fruit::FRUIT_TYPE_SPEED_DOWN,PROP_SPEED,Fruit::FRUIT_TIME_SPEED_DOWN,coef));
			}
			return true;
		}
	case Fruit::FRUIT_TYPE_SPEED_RANDOM_FREEZE:
		{
			for(UINT32 i=0; i<snakes->size();++i)
			{
				Snake* tmp_snake = (*snakes)[i];
				if(tmp_snake && tmp_snake->IsAlive() && tmp_snake != current_snake)
				{
					if(GameModel::hge->Random_Int(0,1))
					{	
						tmp_snake->SetSpeed(Fruit::FRUIT_SPEED_FREEZE);
						break;
					}
				}
			}
			return true;
		}
	case Fruit::FRUIT_TYPE_SPEED_ALL_FREEZE:
		{
			for(UINT32 i=0; i<snakes->size();++i)
			{
				Snake* tmp_snake = (*snakes)[i];
				if(tmp_snake && tmp_snake->IsAlive() && tmp_snake != current_snake)
				{
					tmp_snake->SetSpeed(Fruit::FRUIT_SPEED_FREEZE);
				}
			}
			return true;
		}
	case Fruit::FRUIT_TYPE_SPEED_SELF_FREEZE:
		{
			current_snake->SetSpeed(Fruit::FRUIT_SPEED_FREEZE);
			return true;
		}
	}
	return false;
}

float BoostManager::getBonus(Snake* snake,UINT32 prop)
{
	float coef = 1.0f;
	std::vector<Bonus>* current_snake_bonuses = &snake_bonuses[snake];
	for(UINT32 i=0; i<current_snake_bonuses->size();++i)
	{
		Bonus currBonus = (*current_snake_bonuses)[i];
		if(currBonus.prop == prop && currBonus.timer > 0)
		{
			coef *=currBonus.coef;
		}
	}
	return coef;

}

void BoostManager::update(float dt)
{
	std::map<Snake*,std::vector<Bonus>>::iterator it  = snake_bonuses.begin();
	for( it; it != snake_bonuses.end();++it)
	{
		std::vector<Bonus>* current_snake_bonuses = &(it->second);
		for(UINT32 i=0; i< current_snake_bonuses->size();++i)
		{
			Bonus* currBonus = &(*current_snake_bonuses)[i];
			currBonus->timer -=dt;
			if(currBonus->timer <= 0.0f)
			{
				currBonus->timer = 0.0f;
			}
		}

	}
}

void BoostManager::init()
{
	

}

BoostManager::BoostManager()
{

}

BoostManager::~BoostManager()
{

}

BoostManager* BoostManager::getInstance()
{
	if(!_instance)
		_instance = new BoostManager();
	return _instance;
}

BoostManager::Bonus::Bonus()
:type(Fruit::FRUIT_TYPE_UNKNOWN),
prop(PROP_UNKNOWN),
timer(0.0f),
coef(1.0f)
{}


BoostManager::Bonus::Bonus(UINT32 bonus_type,UINT32 bonus_prop,float bonus_timer,float bonus_coef)
{
	type = bonus_type;
	prop = bonus_prop;
	timer = bonus_timer;
	coef = bonus_coef;
}
