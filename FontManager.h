#pragma once
class FontManager
{
	static FontManager* _instance;
	std::map<std::string,hgeFont*> _fonts;

	FontManager();
	FontManager(const FontManager&);
	FontManager& operator=(FontManager&);
public:
	~FontManager();
	void loadFont( const std::string& name,const std::string& file_name);
	void unloadFonts();
	void dropFont( const std::string& name);

	static FontManager* getInstance();
	hgeFont* getFont( const std::string& name);

};