#include "stdafx.h"
#include "cell.h"
#include "gamePanel.h"
#include "configManager.h"
#include "renderHelpers.h"
#include "player.h"
#include "gameModel.h"
GamePanel::GamePanel()
{
	init();
}

GamePanel::~GamePanel()
{
	if(_pos)
		delete _pos;
	for(UINT32 i=0; i< _players_panel_pos.size(); ++i)
	{
		if(_players_panel_pos[i])
			delete _players_panel_pos[i];
	}
	_players_panel_pos.clear();
}

bool GamePanel::needUpdate()
{
	return _need_update;
}

void GamePanel::setScreenWidth(UINT32 width)
{
	_screen_width = width;
}

void GamePanel::setScreenHeight(UINT32 height)
{
	_screen_height = height;
}

void GamePanel::setPlayersQty(UINT32 qty)
{
	_players_qty = qty;
}

void GamePanel::setScaleFnt()
{
	float scale = _screen_height * _screen_width;
	scale/= 800 * 600;
	_fnt->SetScale(scale);
}

void GamePanel::setPos(hgeVector* pos)
{
	if(pos)
		_pos = pos;
}

void GamePanel::setInfoPos()
{
	for(INT32 i = 0,j = 0; i < _players_qty*2 + 1;++i,j+= _screen_height/ (_players_qty*2 +1))
	{
		_players_panel_pos.push_back(new hgeVector(_pos->x,j));
	}
}

void GamePanel::setCellSize(UINT32 cell_size)
{
	_cell_size = cell_size;
}
void GamePanel::setColors(std::vector<INT32> clr)
{
	_colors = clr;
}

void GamePanel::update(float dt)
{

}
void GamePanel::render()
{
	_fnt->printf(_players_panel_pos[0]->x,_players_panel_pos[0]->y, HGETEXT_LEFT, "FPS: %d",GameModel::hge->Timer_GetFPS());
	for(UINT8 i = 1, j = 0; i < (_players_qty * 2) +1 ; i+=2,j++)
	{
		RenderHelpers::FillRect(GameModel::hge,_players_panel_pos[i]->x + _cell_size,_players_panel_pos[i]->y,_players_panel_pos[i]->x + _cell_size + _cell_size,_players_panel_pos[i]->y + _cell_size,_colors[j]);
		_fnt->printf(_players_panel_pos[i]->x  , _players_panel_pos[i]->y,HGETEXT_LEFT,"Player%d",j + 1);
		_fnt->printf(_players_panel_pos[i + 1]->x  ,_players_panel_pos[i+1]->y  ,HGETEXT_LEFT,"Score:%d",GameModel::getInstance()->GetConfigManager()->getPlayers()[i]->GetScore() );
	}
}

void GamePanel::init()
{
	_fnt = new hgeFont("../data/fonts/somefnt.fnt");
	_pos = NULL;
	_need_update = true;
}

