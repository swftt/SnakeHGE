#include "stdafx.h"
#include "FontManager.h"

FontManager* FontManager::_instance = NULL;
FontManager::FontManager()
{
}

FontManager::~FontManager()
{
	unloadFonts();
}

void FontManager::loadFont(const std::string& name,const std::string& file_name)
{
	hgeFont* font = new hgeFont(file_name.c_str());
	if(font)
		_fonts[name] = font;
}

void FontManager::unloadFonts()
{
	for(std::map<std::string,hgeFont*>::iterator it = _fonts.begin(); it != _fonts.end(); ++it)
		delete it->second;
	_fonts.clear();
}

void FontManager::dropFont(const std::string& name)
{
	std::map<std::string,hgeFont*>::iterator it = _fonts.find(name);
	if( it != _fonts.end())
	{
		delete it->second;
		_fonts.erase(it);
	}
}

FontManager* FontManager::getInstance()
{
	if(!_instance)
		_instance = new FontManager();
	return _instance;
}

hgeFont* FontManager::getFont(const std::string& name)
{
	std::map<std::string,hgeFont*>::iterator it = _fonts.find(name);
	if( it == _fonts.end())
		return NULL;
	return it->second;
}
