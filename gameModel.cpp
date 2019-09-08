#include "stdafx.h"
#include "gameModel.h"
#include "player.h"
#include "mechanic.h"
#include "mainMenu.h"
#include "menuitem.h"
#include "configManager.h"
#include "boostManager.h"
#include "TextureManager.h"
#include "FontManager.h"
#include "snake.h"
enum AppState
{
	Play,
	Pause,
	Continue,
	Settings,
	Exit
};
HGE* GameModel::hge = NULL;
GameModel* GameModel::_instance = NULL;
GameModel::GameModel()
{
	Init();
}
GameModel::~GameModel()
{
	if(_mechanic)
		delete _mechanic;
	if(!_players.empty())
	{
		for (UINT32 i =0; i<_players.size();++i)
		{
			delete _players[i];
		}
		_players.clear();
	}
	if(_config_manager)
		delete _config_manager;
	if(_menu)
		delete _menu;
	if(_texture_manager)
		delete _texture_manager;
	if(_font_manager)
		delete _font_manager;
	if(_boost_manager)
		delete _boost_manager;
}

GameModel* GameModel::getInstance()
{
	if(!_instance)
		_instance = new  GameModel();
	return _instance;
}

std::vector<Player*>& GameModel::GetPlayers()
{
	return _players;
}

ConfigManager* GameModel::GetConfigManager()
{
	return _config_manager;
}

MainMenu* GameModel::GetMainMenu()
{
	return _menu;
}

BoostManager* GameModel::GetBoostManager()
{
	return _boost_manager;
}

FontManager* GameModel::getFontManager()
{
	return _font_manager;
}

TextureManager* GameModel::getTextureManager()
{
	return _texture_manager;
}

Mechanic* GameModel::GetMechanic()
{
	return _mechanic;
}

bool GameModel::Update(float dt)
{
	if(!_menu)
	{
		InitMenu();
	}
	if(_menu->getState() == sPlay && !_mechanic)
	{
		InitMechanic();
	}
	if(_mechanic && _menu->getState() == sNone)
	{
		delete _mechanic;
	}
	if(_mechanic && _menu->getState() == sPlay )
	{
		_boost_manager->update(dt);
		_mechanic->update(dt);
	}
	else
	{
		_menu->Update(dt);
		if(_menu->getState() == sExit)
			return true;
		if (hge->Input_GetKeyState(HGEK_ESCAPE)) 
			return true;
	}	

	return false;
}

void GameModel::Render()
{
	if(_mechanic && _menu->getState() == sPlay)
	{
		_mechanic->render();
	}
	else
	{
		_menu->Render();
	}
}

void GameModel::Init()
{
	_config_manager = new ConfigManager();
	_mechanic = NULL;
	_menu = NULL;
	_boost_manager = NULL;
	_texture_manager = TextureManager::getInstance();
	_font_manager = FontManager::getInstance();
}

bool GameModel::GameOver()
{
	if(_mechanic)
		return _mechanic->isGameOver();
	return true;
}

void GameModel::InitMechanic()
{
	_mechanic = new Mechanic();
	InitBoostManager();
}

void GameModel::InitMenu()
{
	_menu = new MainMenu();
}

void GameModel::InitBoostManager()
{
	_boost_manager = BoostManager::getInstance();
}

void GameModel::SetMainMenu(MainMenu* menu)
{
	if(menu)
		_menu = menu;
}
void GameModel::SetPlayers(std::vector<Player*> players)
{
	if(!players.empty())
		_players = players;
}

void GameModel::SetConfigManager(ConfigManager* cfg)
{
	if(cfg)
		_config_manager = cfg;
}

