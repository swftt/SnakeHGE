#pragma once

class GamePanel;
class ConfigManager;
class RenderHelpers;
class hgeVector;
class Player;
class GamePanel	//texture , font , inits ,boost  
{
	hgeVector * _pos;
	cell_v _players_panel_pos;
	hgeFont* _fnt;
	INT32 _cell_size;
	UINT32 _screen_height;
	UINT32 _screen_width;
	UINT32 _players_qty;

	bool _need_update;

	std::vector<INT32> _colors; 
public:
	GamePanel();
	~GamePanel();

	bool needUpdate();

	void init();
	void setScreenWidth(UINT32 width);
	void setScreenHeight(UINT32 height);
	void setPlayersQty(UINT32 qty);
	void setScaleFnt();
	void setPos(hgeVector* pos);
	void setInfoPos();
	void setCellSize(UINT32 cell_size);
	void setColors(std::vector<INT32> clr);
	void update(float dt);
	void render();
};