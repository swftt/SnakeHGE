#pragma once

class BoostManager;
class MainMenu;
class Mechanic;
class Player;
class ConfigManager;
class FontManager;
class TextureManager;
class GameModel
{ 
	static GameModel* _instance;
	BoostManager* _boost_manager;
	TextureManager* _texture_manager;
	FontManager* _font_manager; 
	Mechanic* _mechanic;
	std::vector<Player*> _players;
	ConfigManager* _config_manager;
	MainMenu* _menu;
	GameModel();
	GameModel(const GameModel&);
	GameModel& operator=(GameModel&);

public:
	static HGE* hge;
	static GameModel* getInstance();
	std::vector<Player*>& GetPlayers();
	MainMenu* GetMainMenu();
	Mechanic* GetMechanic();

	ConfigManager* GetConfigManager();
	BoostManager* GetBoostManager();
	FontManager* getFontManager();
	TextureManager* getTextureManager();



	void Render();
	void Init();
	void InitMechanic();
	void InitMenu();
	void InitBoostManager();
	void SetMainMenu(MainMenu* menu);
	void SetPlayers(std::vector<Player*> players);
	void SetConfigManager(ConfigManager* cfg);

	bool GameOver();
	bool Update(float dt);
	~GameModel();
};