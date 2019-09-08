#include "stdafx.h"
#include "TextureManager.h"
#include "gameModel.h"

TextureManager* TextureManager::_instance = NULL;
TextureManager::TextureManager()
{

}

TextureManager::~TextureManager()
{
	unloadTextures();
}
void TextureManager::unloadTextures()
{
	std::map<std::string,HTEXTURE>::iterator it;
	for( it = _textures.begin(); it!=_textures.end();++it)
	{
		GameModel::hge->Texture_Free(it->second);
	}
	_textures.clear();
}

void TextureManager::loadTexture(const std::string& name,const std::string& file_name)
{
	HTEXTURE tex;
	if(GameModel::hge->Texture_Load(file_name.c_str()))
		_textures[name] = tex;
}

void TextureManager::dropTexture(const std::string& name)
{
	std::map<std::string,HTEXTURE>::iterator it = _textures.find(name);
	if( it != _textures.end())
	{
		GameModel::hge->Texture_Free(getTexture(name));
		_textures.erase(it);
	}
}

HTEXTURE& TextureManager::getTexture(const std::string& name)
{
	std::map<std::string,HTEXTURE>::iterator it = _textures.find(name);
	HTEXTURE tex = 0;
	if( it == _textures.end())
		return tex;
	return it->second;
}

TextureManager* TextureManager::getInstance()
{
	if(!_instance)
		_instance = new TextureManager();
	return _instance;
}
