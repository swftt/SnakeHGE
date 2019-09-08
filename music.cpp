#include "stdafx.h"
#include "music.h"
#include "gameModel.h"

Music::Music()
{
}
Music::~Music()
{
	GameModel::hge->Effect_Free(_start);
	GameModel::hge->Effect_Free(_turn);
	GameModel::hge->Effect_Free(_lineRemove);
	GameModel::hge->Effect_Free(_gameMusic);
	GameModel::hge->Effect_Free(_menuMusic);
	GameModel::hge->Effect_Free(_pause);
	GameModel::hge->Effect_Free(_menuSound);
}

HEFFECT Music::PlayMenuMusic()
{
	return _menuMusic;
}
HEFFECT Music::PlayMenuSound()
{
	return _menuSound;
}
HEFFECT Music::PlayGameMusic()
{
	return _gameMusic;
}

HEFFECT Music::PlayPause()
{
	return _pause;
}

HEFFECT Music::PlayStart()
{
	return _start;
}

HEFFECT Music::PlayLineRemove()
{
	return _lineRemove;
}

HEFFECT Music::PlayTurn()
{
	return _turn;
}
HEFFECT Music::PlayGameOver()
{
	return _end;
}
HEFFECT Music::PlayDown()
{
	return _down;
}
void Music::NullGameMusic()
{
	_gameMusic=0;
}