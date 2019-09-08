#include "stdafx.h"
#include "RenderHelpers.h"

void RenderHelpers::DrawRect(HGE* hge,  hgeRect const &rect, UINT32 color)
{
	DrawRect(hge, rect.x1, rect.y1, rect.x2, rect.y2, color);
}

// Draws each quad of rectangle
void RenderHelpers::DrawRect(HGE* hge, float const &l,float const &t, float const &r, float const &b, UINT32 color)
{
	hge->Gfx_RenderLine(l, t, r, t, color);
	hge->Gfx_RenderLine(r, t, r, b, color);
	hge->Gfx_RenderLine(r, b, l, b, color);
	hge->Gfx_RenderLine(l, b, l, t, color);
}

//Fills Rectangle with color choosed
void RenderHelpers::FillRect(HGE* hge, hgeRect const &rect, UINT32 color)
{
	FillRect(hge, rect.x1, rect.y1, rect.x2, rect.y2, color);
}

//Fills each quad of rectangle with choosed color and blends
void RenderHelpers::FillRect(HGE* hge,  float const &l,float const &t, float const &r, float const &b, UINT32 color)
{
	hgeQuad quad;

	quad.tex = 0;
	quad.blend = BLEND_DEFAULT;

	quad.v[0].x = l;
	quad.v[0].y = t;
	quad.v[0].z = 0;
	quad.v[0].col = color;
	
	quad.v[1].x = r;
	quad.v[1].y = t;
	quad.v[1].z = 0;
	quad.v[1].col = color;

	quad.v[2].x = r;
	quad.v[2].y = b;
	quad.v[2].z = 0;
	quad.v[2].col = color;

	quad.v[3].x = l;
	quad.v[3].y = b;
	quad.v[3].z = 0;
	quad.v[3].col = color;

	hge->Gfx_RenderQuad(&quad);
}