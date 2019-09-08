#pragma once

class TextureManager
{
	std::map<std::string,HTEXTURE> _textures;
	static TextureManager* _instance;

	TextureManager();
	TextureManager(const TextureManager&);
	TextureManager& operator=(TextureManager&);
public:
	~TextureManager();
	void unloadTextures();
	void loadTexture(const std::string& name,const std::string& file_name);
	void dropTexture(const std::string& name);

	HTEXTURE& getTexture(const std::string& name);
	static TextureManager* getInstance();
};