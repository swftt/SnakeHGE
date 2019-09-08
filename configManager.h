#pragma once
class Player;
class ConfigManager
{
	INT32 _field_height;
	INT32 _field_width;
	INT32 _screen_height;
	INT32 _screen_width;
	INT32 _screen_bpp;
	INT32 _players_qty ;
	INT32 _chosen_players_qty;
	bool _windowed;
	std::vector<Player*> _players;
	std::vector<INT32> _colors;
public:
	ConfigManager();
	~ConfigManager();
	INT32 getPlayersQty();
	INT32 getFieldHeight();
	INT32 getFieldWidth();
	INT32 getScreenHeight();
	INT32 getScreenWidth();
	INT32 getScreenBPP();
	INT32 getChosenPlayersQty();
	std::vector<Player*>& getPlayers();
	std::vector<INT32>& getColors();

	bool isWindowed();

	void setChosenPlayersQty(INT32 qty);
	void loadPlayers();	
	void savePlayers();
	void load();
	void save();
	void saveGame();
	void saveFruits();
	void loadSnakes();
	void loadFruits();
	void setMenuAppSettings(std::string resolution,std::string fieldParams);

	
};