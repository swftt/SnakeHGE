#pragma once

class HGE;

class RenderHelpers
{
public:
	static void DrawRect(HGE * hge,hgeRect const &rect,UINT32 color);
	static void DrawRect(HGE * hge, float const &l,float const &t,float const &r,float const &b, UINT32 color);
	static void FillRect(HGE * hge, hgeRect const &rect , UINT32 color);
	static void FillRect(HGE * hge, float const &l,float const &t,float const &r,float const &b, UINT32 color);
};