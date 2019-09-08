#include "stdafx.h"
#include "player.h"
Player::Player(std::string nickName,std::vector<INT32> controls,INT32 score)
:_nickName(nickName),
_controls(controls),
_score(0)
{

}

Player::~Player()
{

}

void Player::SetControls(std::vector<INT32> &newControls)
{
	_controls = newControls;
}

std::vector<INT32> Player::GetControls()
{
	return _controls;
}

INT32 Player::GetScore()
{
	return _score;
}

void Player::AddPoints(INT32 score)
{
	_score+= score;
}


std::string Player::GetNickName()
{
	return _nickName;
}

void Player::SetNickName(std::string nickName)
{
	_nickName = nickName;
}
