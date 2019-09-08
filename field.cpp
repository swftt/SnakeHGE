#include "stdafx.h"
#include "field.h"
#include "gameModel.h"

Field::Field()
:_need_draw(true)
{

}
Field::~Field()
{
}


UINT32 Field::getHeight()
{
	return _height;
}

UINT32 Field::getWidth()
{
	return _width;
}

UINT32 Field::getCellSize()
{
	return _cell_size;
}

void Field::init()
{

}

void Field::setCellSize(UINT32 cellSize)
{
	_cell_size = cellSize;
}

void Field::setHeight(UINT32 height)
{
	_height = height;
}

void Field::setWidth(UINT32 width)
{
	_width = width;
}

void Field::needDraw()
{
	_need_draw = true;
}

void Field::update(float dt)
{
	// no need to update??
}

void Field::render()
{
	/*if(_needDraw)
	{*/
		UINT32 color = 0xFFFFFFFF;
		UINT32 cellColor = 0x64646480;
		float l = 0;
		float t = 0;
		float r = _width* _cell_size;
		float b = _height* _cell_size;
		for(INT32 i=0,j=0;i<_height;i++,j+=_cell_size)
		{
			GameModel::hge->Gfx_RenderLine(l,j,r,j,cellColor);
		}
		for(INT32 i=0,j=0;i<_width;i++,j+=_cell_size)
		{
			GameModel::hge->Gfx_RenderLine(j,b,j,t,cellColor);
		}
		GameModel::hge->Gfx_RenderLine(l, t, l, b, color);
		GameModel::hge->Gfx_RenderLine(l, b, r, b, color);
		GameModel::hge->Gfx_RenderLine(r, b, r, t, color);
		/*_needDraw = false;
	}*/
}

