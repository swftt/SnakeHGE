#pragma once


class Player
{  
	std::string _nickName;
	std::vector<INT32> _controls;
	INT32 _score;
public:
	Player(std::string nickName,std::vector<INT32> controls,INT32 score = 0);
	~Player();

	std::vector<INT32> GetControls();
	std::string GetNickName();

	void SetControls(std::vector<INT32> &newControls);
	void SetNickName(std::string nickName);
	void AddPoints(INT32 score);

	INT32 GetScore();


protected:
	Player();

};