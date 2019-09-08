#pragma once

class HGE;
class Field;
class Mechanic;
class Snake;

class Field
{
	UINT32  _height;
	UINT32  _width;
	UINT32 _cell_size;

	bool _need_draw;
public:
	Field();
	~Field();

	UINT32 getHeight();
	UINT32 getWidth();
	UINT32 getCellSize();

	void init();
	void setCellSize(UINT32 cellSize);
	void setHeight(UINT32 height);
	void setWidth(UINT32 width);
	void update(float dt); 
	void render();
	void needDraw();

};