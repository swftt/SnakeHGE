#include "stdafx.h"
#include "music.h"
#include "configManager.h"
#include "renderHelpers.h"
#include "gameModel.h"
#include "mainMenu.h"
#include "menuitem.h"

MainMenu::MainMenu()
{
	init();
}
void MainMenu::SetCurrentResIdx()
{
	switch(GameModel::getInstance()->GetConfigManager()->getScreenWidth())
	{
	case 800:
		_currentResIdx = 0;
		break;
	case 1024:
		_currentResIdx = 1;
		break;
	case 1280:
		_currentResIdx = 2;
		break;
	case 1440:
		_currentResIdx = 3;
		break;
	case 1600:
		_currentResIdx = 4;
		break;
	case 1650:
		_currentResIdx = 5;
		break;
	case 1920:
		_currentResIdx = 6;
		break;
	}
}
MainMenu::~MainMenu()
{
	GameModel::hge->Texture_Free(_tex);
	GameModel::hge->Texture_Free(tex);
	GameModel::hge->Texture_Free(bgtex);

	delete _fpsFnt;
	delete spr;
	delete _spr;
	delete _gui;
	delete _fnt;
	delete fnt;

}
void MainMenu::Render()
{
	bgspr->RenderEx(0,0,0,float(_screenHeight*_screenWidth) / float(500*750));
	_gui->Render();
	_fpsFnt->printf(7, 7, HGETEXT_LEFT, "FPS: %d",GameModel::hge->Timer_GetFPS());
	_fpsFnt->SetScale(_scale);
	_fpsFnt->printf(_screenWidth/3, _screenHeight/4, HGETEXT_LEFT, "RESOLUTION: %s",_resolutions[_currentResIdx].c_str());
	_fpsFnt->printf(_screenWidth/3, _screenHeight/4 + 200, HGETEXT_LEFT, "FIELD SIZE: %s",_fieldParams[_currentFParamIdx].c_str());
}
INT32 MainMenu::getState()
{
	return _state;
}

std::string MainMenu::GetResolution()
{
	return _resolutions[_currentResIdx];
}


void MainMenu::init()
{

	_state = sNone;
	_playersQty = GameModel::getInstance()->GetConfigManager()->getPlayersQty();
	_screenHeight = GameModel::getInstance()->GetConfigManager()->getScreenHeight();
	_screenWidth = GameModel::getInstance()->GetConfigManager()->getScreenWidth();
	_screenBPP = GameModel::getInstance()->GetConfigManager()->getScreenBPP();
	_music=new Music();
	maxObjects=50*((_screenWidth/800)+(_screenHeight/600));
	bgtex = GameModel::hge->Texture_Load("../data/textures/bg.png");
	tex = GameModel::hge->Texture_Load("../data/textures/Tetris_block_cyan.png");
	_tex = GameModel::hge->Texture_Load("../data/textures/cursor.png");
	fnt=new hgeFont("../data/fonts/somefnt.fnt");
	fnt->SetColor(0xFFFF0000);
	_fpsFnt=new hgeFont("../data/fonts/somefnt.fnt");
	_fpsFnt->SetColor(0xFF00FF00);
	_fnt = new hgeFont("../data/fonts/somefnt.fnt");
	_spr = new hgeSprite(_tex,0,0,32,32);
	spr = new hgeSprite(tex, 0, 0, 30, 30);
	spr->SetHotSpot(32, 32);
	_scale = GameModel::getInstance()->GetConfigManager()->getScreenHeight() * GameModel::getInstance()->GetConfigManager()->getScreenWidth();
	_scale/=480000;
	bgspr = new hgeSprite(bgtex, 0, 0, 750,500);
	bgspr->SetBlendMode(BLEND_COLORADD | BLEND_ALPHABLEND | BLEND_NOZWRITE);
	bgspr->SetColor(0xFF000000, 0);
	bgspr->SetColor(0xFF000000, 1);
	bgspr->SetColor(0xFF000040, 2);
	bgspr->SetColor(0xFF000040, 3);

	_gui = new hgeGUI();
	int incrementer=0;
	fnt->SetScale(2);
	_gui->AddCtrl(new hgeGUIMenuItem(1,fnt,_music->PlayMenuSound(), _screenWidth/4,_screenWidth/4, 0.0f,"Play"));
	_gui->AddCtrl(new hgeGUIMenuItem(2, fnt, _music->PlayMenuSound(), _screenWidth/4, _screenWidth/4 + 100, 0.0f, "Exit"));

	incrementer+=_screenHeight / 12;
	incrementer+=_screenHeight/12;
	fnt->SetScale(1);
	_gui->AddCtrl(new hgeGUIMenuItem(3, fnt, _music->PlayMenuSound(), _screenWidth/2, _screenHeight/3+incrementer, 0.0f, "1 Player"));
	_gui->AddCtrl(new hgeGUIMenuItem(4, fnt, _music->PlayMenuSound(), _screenWidth/2, _screenHeight/3+incrementer, 0.0f, "2 Players"));
	_gui->AddCtrl(new hgeGUIMenuItem(5, fnt, _music->PlayMenuSound(), _screenWidth/2, _screenHeight/3+incrementer, 0.0f, "4 Players"));
	_gui->ShowCtrl(3,false);
	_gui->ShowCtrl(4,false);
	_gui->ShowCtrl(5,false);
	_gui->EnableCtrl(3,false);
	_gui->EnableCtrl(4,false);
	_gui->EnableCtrl(5,false);
	INT32 offsetX = _screenWidth/2 + _screenWidth/6;
	INT32 offsetY = _screenHeight/3;

	_gui->AddCtrl(new hgeGUIMenuItem(6, fnt, _music->PlayMenuSound(), offsetX, offsetY, 0.0f, "<=="));
	_gui->AddCtrl(new hgeGUIMenuItem(7, fnt, _music->PlayMenuSound(), offsetX + 250, offsetY, 0.0f, "==>"));
	_gui->AddCtrl(new hgeGUIMenuItem(8, fnt, _music->PlayMenuSound(), offsetX, offsetY + 100, 0.0f, "<=="));
	_gui->AddCtrl(new hgeGUIMenuItem(9, fnt, _music->PlayMenuSound(), offsetX + 250, offsetY + 100, 0.0f, "==>"));

	_gui->SetNavMode(HGEGUI_UPDOWN | HGEGUI_CYCLED);
	_gui->SetCursor(_spr);
	_gui->SetFocus(1);
	_gui->Enter();
	_resolutions.push_back("800x600");
	_resolutions.push_back("1024x768");
	_resolutions.push_back("1280x960");
	_resolutions.push_back("1440x900");
	_resolutions.push_back("1600x900");
	_resolutions.push_back("1650x1080");
	_resolutions.push_back("1920x1080");

	_fieldParams.push_back("20x20");
	_fieldParams.push_back("30x30");
	_fieldParams.push_back("40x40");
	SetCurrentResIdx();
	SetFieldParamIdx();
}

void MainMenu::SetState(int otherState)
{
	_state=otherState; 
}

void MainMenu::DeleteMenuCtrl()
{
	_gui->ShowCtrl(1,false);
	_gui->ShowCtrl(2,false);
	_gui->EnableCtrl(1,false);
	_gui->EnableCtrl(2,false);

}

void MainMenu::SetMenuCtrl()
{
	_gui->ShowCtrl(1,true);
	_gui->ShowCtrl(2,true);
	_gui->EnableCtrl(1,true);
	_gui->EnableCtrl(2,true);

}

void MainMenu::SetPlayCtrl()
{

	if(_playersQty<= 1)
	{
		_gui->EnableCtrl(3,true);
		_gui->ShowCtrl(3,true);
	}
	else if(_playersQty < 4)
	{
		_gui->EnableCtrl(3,true);
		_gui->ShowCtrl(3,true);
		_gui->EnableCtrl(4,true);
		_gui->ShowCtrl(4,true);
	}
	else if(_playersQty == 4)
	{
		_gui->EnableCtrl(3,true);
		_gui->ShowCtrl(3,true);
		_gui->EnableCtrl(4,true);
		_gui->ShowCtrl(4,true);
		_gui->EnableCtrl(5,true);
		_gui->ShowCtrl(5,true);
	}

}

void MainMenu::DeletePlayCtrl()
{
	if(_playersQty<= 1)
	{
		_gui->EnableCtrl(4,false);
		_gui->ShowCtrl(4,false);
	}
	else if(_playersQty <= 2)
	{
		_gui->EnableCtrl(4,false);
		_gui->ShowCtrl(4,false);
		_gui->EnableCtrl(5,false);
		_gui->ShowCtrl(5,false);
	}
	else if(_playersQty == 4)
	{
		_gui->EnableCtrl(4,false);
		_gui->ShowCtrl(4,false);
		_gui->EnableCtrl(5,false);
		_gui->ShowCtrl(5,false);
		_gui->EnableCtrl(6,false);
		_gui->ShowCtrl(6,false);
	}

}


void MainMenu::SetSettings(INT32 dir,INT32 option)
{
	switch(option)
	{
	case 1:
		if(dir)
		{
			if(_currentResIdx+1 > -1 && _currentResIdx+1 < _resolutions.size())
			{
				_currentResIdx ++;
			}
		}
		else
		{
			if(_currentResIdx - 1 > -1 && _currentResIdx - 1 < _resolutions.size())
				_currentResIdx --;
		}
		GameModel::getInstance()->GetConfigManager()->setMenuAppSettings(_resolutions[_currentResIdx],_fieldParams[_currentFParamIdx]);
		break;
	case 2:
		if(dir)
		{
			if(_currentFParamIdx + 1 > -1 && _currentFParamIdx + 1 < _fieldParams.size())
				_currentFParamIdx++;

		}
		else
		{
			if(_currentFParamIdx - 1 > -1 && _currentFParamIdx - 1 < _fieldParams.size())
				_currentFParamIdx--;
		}
		GameModel::getInstance()->GetConfigManager()->setMenuAppSettings(_resolutions[_currentResIdx],_fieldParams[_currentFParamIdx]);

		break;
	default:
		GameModel::getInstance()->GetConfigManager()->setMenuAppSettings(_resolutions[_currentResIdx],_fieldParams[_currentFParamIdx]);


	}
}

void MainMenu::Settings(INT32 choice)
{
	//_state = sSettings;
	switch(choice)
	{
	case 6:
		SetSettings(0,1);
		break;
	case 7:
		SetSettings(1,1);
		break;
	case 8:
		SetSettings(0,2);
		break;
	case 9:
		SetSettings(1,2);
		break;
	}
}

void MainMenu::SetFieldParamIdx()
{
	switch(GameModel::getInstance()->GetConfigManager()->getFieldHeight())
	{
	case 20:
		_currentFParamIdx = 0;
		break;
	case 30:
		_currentFParamIdx = 1;
		break;
	case 40:
		_currentFParamIdx = 2;
		break;
	default: _currentFParamIdx = 0;
	}
}
void MainMenu::Update(float dt)
{
	static int lastid = 0;
	int id = _gui->Update(dt);
	GameModel::hge->Effect_Play(_music->PlayMenuMusic());
	if(id == -1)
	{
		switch(lastid)
		{
		case 1:
			GameModel::hge->Effect_Free(_music->PlayMenuMusic());
			DeleteMenuCtrl();
			SetPlayCtrl();
			_gui->SetFocus(1);
			_gui->Enter();
			break;
		case 2:
			_state = sExit;
			break;
		case 3:
			_state = sPlay;
			GameModel::getInstance()->GetConfigManager()->setChosenPlayersQty(1);
			break;
		case 4:
			_state = sPlay;
			GameModel::getInstance()->GetConfigManager()->setChosenPlayersQty(2);
			break;
		case 5:
			_state = sPlay;
			GameModel::getInstance()->GetConfigManager()->setChosenPlayersQty(4);
			break;
		case 6:
			SetSettings(0,1);
			lastid = -1;
			MoveWindow((HWND)(GameModel::hge->System_GetState(HGE_HWND)),560 ,240,800,640,1);
			_gui->SetFocus(6);
			_gui->Enter();
			break;
		case 7:
			SetSettings(1,1);
			lastid = -1;
			MoveWindow((HWND)(GameModel::hge->System_GetState(HGE_HWND)),0,0,800,600,1); 

			_gui->SetFocus(7);
			_gui->Enter();
			break;
		case 8:
			SetSettings(0,2);
			lastid = -1;
			_gui->SetFocus(8);
			_gui->Enter();
			break;
		case 9:
			SetSettings(1,2); 
			lastid = -1;
			_gui->SetFocus(9);
			_gui->Enter();
			break;
		default:
			return;
		}
	}
	else if(id)
	{ 
		lastid = id;
		_gui->Leave();
	}
}
