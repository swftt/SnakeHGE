#pragma once


class hgeGUI;
class hgeFont;
class hgeSprite;
class HGE;
class GameModel;
class RenderHelpers;
class ConfigManager;
class Music;

enum MenuState {
	sNone,
	sPlay,
	sExit,
	sSettings,
};

class MainMenu
{
	hgeGUI* _gui;
	hgeFont* _fnt;
	hgeSprite* _spr;
	hgeFont* fnt;
	hgeFont* _fpsFnt;
	hgeQuad square;
	hgeQuad quad;
	HTEXTURE _tex;
	hgeSprite* spr;
	hgeSprite* bgspr;
	HTEXTURE tex, bgtex;
	hgeGUIText* text;

	Music* _music;

	INT32 _playersQty;
	INT32 maxObjects;
	INT32 nBlend;
	INT32 _screenWidth,_screenHeight,_screenBPP;
	INT32 _state;

	float _scale;

	INT32 _currentResIdx;
	INT32 _currentFParamIdx;
	std::vector<std::string> _resolutions;
	std::vector<std::string> _fieldParams;

	bool _needChangeRes;
public:
	MainMenu();
	virtual ~MainMenu();
	INT32 getState();
	std::string GetResolution();

	void init();
	void SetCurrentResIdx();
	void Render();
	void Update(float dt);
	void SetState(int otherState);
	void DeleteMenuCtrl();
	void SetMenuCtrl();
	void SetPlayCtrl();
	void DeletePlayCtrl();
	void SetSettings(INT32 dir,INT32 option);
	void Settings(INT32 choice);
	void SetFieldParamIdx();
	
};