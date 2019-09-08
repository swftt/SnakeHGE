#include "stdafx.h"
#include "configManager.h"
#include "tinystr.h"
#include "tinyxml.h"
#include "player.h"
ConfigManager::ConfigManager():
_chosen_players_qty(1)
{
	load();
	/*std::vector<INT32> ctrls;
	ctrls.push_back(hgeK_UP);
	ctrls.push_back(hgeK_RIGHT);
	ctrls.push_back(hgeK_DOWN);
	ctrls.push_back(hgeK_LEFT);
	for(int i=0;i<4;i++)
	{
		_players.push_back(new Player("Player1",ctrls,0));
	}
	SavePlayers();*/
	loadPlayers();
}

ConfigManager::~ConfigManager()
{
	save();
	savePlayers();
	for(UINT8 i = 0 ;i < _players.size();++i)
	{
		delete _players[i];
	}
	_players.clear();
}

INT32 ConfigManager::getPlayersQty()
{
	return _players_qty;
}

INT32 ConfigManager::getFieldHeight()
{
	return _field_height;
}

INT32 ConfigManager::getFieldWidth()
{
	return _field_width;
}

INT32 ConfigManager::getScreenHeight()
{
	return _screen_height;
}

INT32 ConfigManager::getScreenWidth()
{
	return _screen_width;
}

INT32 ConfigManager::getScreenBPP()
{
	return _screen_bpp;
}


INT32 ConfigManager::getChosenPlayersQty()
{
	return _chosen_players_qty;
}

bool ConfigManager::isWindowed()
{
	return _windowed;
}


void ConfigManager::setChosenPlayersQty(INT32 qty)
{
	_chosen_players_qty = qty;
}

void ConfigManager::loadPlayers()
{
	TiXmlDocument doc("Players.xml");
	if(!doc.LoadFile())
	{
		std::vector<INT32> ctrls;
		ctrls.push_back(HGEK_UP);
		ctrls.push_back(HGEK_RIGHT);
		ctrls.push_back(HGEK_DOWN);
		ctrls.push_back(HGEK_LEFT);
		_players.push_back(new Player("Player",ctrls,0));
		_players_qty = _players.size();
		return;
	}
	TiXmlHandle hDoc(&doc);
	_players.clear();
	TiXmlElement * root = hDoc.FirstChild("Players").FirstChild().Element();
	for(root;root;root=root->NextSiblingElement())
	{
		std::vector<INT32> ctrls;
		ctrls.resize(4,0);
		std::string nickName;
		INT32 score;
		nickName = root->Attribute("Nickname");
		root->QueryIntAttribute("Score",&score);
		root->QueryIntAttribute("UP",&ctrls[0]);
		root->QueryIntAttribute("RIGHT",&ctrls[1]);
		root->QueryIntAttribute("DOWN",&ctrls[2]);
		root->QueryIntAttribute("LEFT",&ctrls[3]);
		_players.push_back(new Player(nickName,ctrls,score));
	}
	_players_qty = _players.size();
}

void ConfigManager::savePlayers()
{
	TiXmlDocument doc;  
	TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "", "" );  
	doc.LinkEndChild( decl );  
	TiXmlElement * root = new TiXmlElement("Players");  
	doc.LinkEndChild(root);
	for(UINT i = 0 ; i<_players.size();++i)
	{	
		TiXmlElement * player;
		player = new TiXmlElement("Players");
		root->LinkEndChild(player);
		player->SetAttribute("Nickname",_players[i]->GetNickName().c_str());
		player->SetAttribute("Score",_players[i]->GetScore());
		player->SetAttribute("UP",_players[i]->GetControls()[0]);
		player->SetAttribute("RIGHT",_players[i]->GetControls()[1]);
		player->SetAttribute("DOWN",_players[i]->GetControls()[2]);
		player->SetAttribute("LEFT",_players[i]->GetControls()[3]);

	}
	doc.SaveFile("Players.xml");
}

void ConfigManager::load()
{
	TiXmlDocument doc("Settings.xml");
	if(!doc.LoadFile())
	{ 
		_screen_bpp = 32;
		_screen_height = 600;
		_screen_width = 800;
		_field_height = 20;
		_field_width = 20;
		_windowed = true;
		return;
	}
	TiXmlHandle hDoc(&doc);
	TiXmlElement* pElem = hDoc.FirstChild("settings").Element();
	pElem->QueryIntAttribute("ScreenWidth",&_screen_width);
	pElem->QueryIntAttribute("ScreenHeight",&_screen_height);
	pElem->QueryIntAttribute("ScreenBPP",&_screen_bpp);
	pElem->QueryIntAttribute("FieldWidth",&_field_width);
	pElem->QueryIntAttribute("FieldHeight",&_field_height);
	pElem->QueryBoolAttribute("Windowed",&_windowed);
	INT32 red,blue,yellow,white;
	pElem->QueryIntAttribute("RedColor",&red);
	pElem->QueryIntAttribute("YellowColor",&yellow);
	pElem->QueryIntAttribute("WhiteColor",&white);
	pElem->QueryIntAttribute("BlueColor",&blue);
	_colors.push_back(red);
	_colors.push_back(blue);
	_colors.push_back(white);
	_colors.push_back(yellow);
	if(_screen_width < 800 || _screen_width > 1920)
	{
		_screen_width = 800;
	}
	if(_screen_height < 600 || _screen_height > 1080)
	{
		_screen_height = 600;
	}
	if(_field_height < 20 || _field_height > 40)
	{
		_field_height = 20;
		_field_width = 20;
	}
	if(_field_width != _field_height)
		_field_width = _field_height;

}

void ConfigManager::save()
{
	TiXmlDocument doc;
	TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "", "" );  
	doc.LinkEndChild( decl );  
	TiXmlElement * root = new TiXmlElement( "settings" );  
	root->SetAttribute("ScreenWidth",_screen_width);
	root->SetAttribute("ScreenHeight",_screen_height);
	root->SetAttribute("ScreenBPP",_screen_bpp);
	root->SetAttribute("FieldHeight",_field_height);
	root->SetAttribute("FieldWidth",_field_width);
	root->SetAttribute("Windowed",_windowed);
	root->SetAttribute("RedColor",_colors[0]);
	root->SetAttribute("BlueColor",_colors[1]);
	root->SetAttribute("WhiteColor",_colors[2]);
	root->SetAttribute("YellowColor",_colors[3]);
	doc.LinkEndChild( root );
	doc.SaveFile("Settings.xml");
}

void ConfigManager::saveGame()
{

}

//void ConfigManager::SaveSnakes(std::vector<Snake*> snakes)
//{
//	TiXmlDocument doc;  
//	TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "", "" );  
//	doc.LinkEndChild( decl );  
//	TiXmlElement * root = new TiXmlElement("Players");  
//	doc.LinkEndChild(root);
//	for(UINT i = 0 ; i<snakes.size();++i)
//	{	
//		TiXmlElement * snake;
//		snake = new TiXmlElement("Snakes");
//		root->LinkEndChild(snake);
//		snake->SetAttribute("IsAlive",snakes[i]->IsAlive());
//		snake->SetAttribute("NeedMove",snakes[i]->IsNeedCheckCollision());
//		snake->SetAttribute("IsResize",snakes[i]->IsResize());
//		snake->SetAttribute("Direction",snakes[i]->GetDir());
//		snake->SetAttribute("Length",snakes[i]->GetLength());
//		snake->SetAttribute("Points",snakes[i]->GetPoints());
//		snake->SetAttribute("Color",snakes[i]->GetColor());
//		snake->SetDoubleAttribute("Speed",snakes[i]->GetSpeed());
//		snake->SetDoubleAttribute("Delta",snakes[i]->GetDelta());
//		snake->SetDoubleAttribute("Speed",snakes[i]->GetSpeed());
//		for(UINT j=0; j<snakes[i]->GetBody().size();++j)
//		{
//			TiXmlElement* coord;
//			coord = new TiXmlElement("Coord");
//			root->LinkEndChild(coord);
//			coord->SetAttribute("X",snakes[i]->GetBody()[j]->x);
//			coord->SetAttribute("Y",snakes[i]->GetBody()[j]->y);
//		}
//	}
//	doc.SaveFile("Snakes.xml");
//
//}

void ConfigManager::saveFruits()
{

}

void ConfigManager::loadSnakes()
{
	//TiXmlDocument doc;  
	//TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "", "" );  
	//doc.LinkEndChild( decl );  
	//TiXmlElement * root = new TiXmlElement("Snakes");  
	//doc.LinkEndChild(root);
	//for(UINT i = 0 ; i<_players.size();++i)
	//{	
	//	TiXmlElement * snake;
	//	snake = new TiXmlElement("Snakes");
	//	root->LinkEndChild(snake);
	//	snake->SetAttribute("Nickname",_players[i]->GetNickName().c_str());
	//	snake->SetAttribute("HighScore",_players[i]->GetHighScore());
	//	snake->SetAttribute("UP",_players[i]->GetControls()[0]);
	//	snake->SetAttribute("RIGHT",_players[i]->GetControls()[1]);
	//	snake->SetAttribute("DOWN",_players[i]->GetControls()[2]);
	//	snake->SetAttribute("LEFT",_players[i]->GetControls()[3]);
	//	// 
	//}
	//doc.SaveFile("Players.xml");
}

void ConfigManager::loadFruits()
{

}

void ConfigManager::setMenuAppSettings(std::string resolution,std::string fieldParams)
{
	if(resolution == "800x600")
	{
		_screen_width = 800;
		_screen_height = 600;
	}
	else if(resolution == "1024x768")
	{
		_screen_width = 1024;
		_screen_height = 768;
	}
	else if(resolution == "1280x960")
	{
		_screen_width = 1280;
		_screen_height = 960;
	}
	else if(resolution == "1440x900")
	{
		_screen_width = 1440;
		_screen_height = 900;
	}
	else if(resolution == "1600x900")
	{
		_screen_width = 1600;
		_screen_height = 900;
	}
	else if (resolution == "1650x1080")
	{
		_screen_width = 1650;
		_screen_height = 1080;
	}
	else 
	{
		_screen_width = 1920;
		_screen_height = 1080;
	}

	if(fieldParams == "20x20")
	{
		_field_height = 20;
		_field_width = 20;
	}
	else if(fieldParams == "30x30")
	{
		_field_width = 30;
		_field_height = 30;
	}
	else 
	{
		_field_height = 40;
		_field_width = 40;
	}

	save();
}

std::vector<Player*>& ConfigManager::getPlayers()
{
	return _players;
}

std::vector<INT32> & ConfigManager::getColors()
{
	return _colors;
}
