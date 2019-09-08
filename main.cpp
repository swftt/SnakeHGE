/*
** Haaf's Game Engine 1.8
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
*/
#include "stdafx.h"
#include "gameModel.h"
#include "configManager.h"
HGE* hge = 0;
GameModel* model = GameModel::getInstance();

bool FrameFunc()
{
	float dt = hge->Timer_GetDelta();
	//if(model)
		model->Update(dt);
	return false;
}

bool RenderFunc()
{
	hge->Gfx_BeginScene();

	hge->Gfx_Clear(0);
	//if(model)
		model->Render();
	hge->Gfx_EndScene();
	return false;
}


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//cfg->Save();
	// Get hge interface
	hge = hgeCreate(HGE_VERSION);
	// Set up log file, frame function, render function and window title
	hge->System_SetState(HGE_LOGFILE, "snake.log");
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
	hge->System_SetState(HGE_TITLE, "Snake");
	// Set up video mode
	hge->System_SetState(HGE_WINDOWED, model->GetConfigManager()->isWindowed());
	hge->System_SetState(HGE_SCREENWIDTH, model->GetConfigManager()->getScreenWidth());
	hge->System_SetState(HGE_SCREENHEIGHT, model->GetConfigManager()->getScreenHeight());
	hge->System_SetState(HGE_SCREENBPP, model->GetConfigManager()->getScreenBPP());

	if(hge->System_Initiate())
	{
		GameModel::hge = hge;
		//hge->System_SetState(HGE_POWERSTATUS)
		//hge->System_SetStateHwnd(HGE_HWND,(int)MoveWindow((HWND)(hge->System_GetState(HGE_HWND)),0,0,1000,1000,1));
		hge->System_Start();
		if(model)
			delete model;
	}
	else
	{
		MessageBox(NULL, hge->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
	}

	// Clean up and shutdown
	hge->System_Shutdown();
	hge->Release();
	return 0;
}
