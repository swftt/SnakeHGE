#pragma once
class Fruit;
class Snake;
struct Bonus;
// when same bonus is being picked timer updates to new time,but not adding
// 
class BoostManager
{
public:
	enum
	{
		PROP_UNKNOWN,
		PROP_SPEED
	};
	struct Bonus
	{
		UINT32 type;
		UINT32 prop;
		float timer;
		float coef;
		Bonus(UINT32 bonus_type,UINT32 bonus_prop,float bonus_timer,float bonus_coef);
		Bonus();
	};
	~BoostManager();
	static BoostManager* getInstance();

	bool applyBoost(Fruit* fruit,Snake* current_snake,std::vector<Snake*>* snakes);

	float getBonus(Snake* snake,UINT32 prop);

	void update(float dt);
	void init();

private:
	static BoostManager* _instance;
	std::map<Snake*, std::vector<Bonus>> snake_bonuses;
	BoostManager();
	BoostManager(const BoostManager&);
	BoostManager& operator=(BoostManager&);

};