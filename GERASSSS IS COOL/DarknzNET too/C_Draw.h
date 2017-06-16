#pragma once
#include "main.h"


class C_Draw
{
public:

	void SetFont(DWORD *font, const char *name, int size, int flags);
	void DrawString(bool shouldcenter, int fontIndex, int x, int y, const Color &colour, const char *format, ...);
	void DrawStringMenu(int iAlign, int fontIndex, int x, int y, const Color &colour, const char *format, ...);
	void DrawOutlinedRect(int x, int y, int w, int h, const Color &colour);
	void DrawFilledRect(int x, int y, int w, int h, const Color &colour);
	bool WorldToScreen(const Vector &point, Vector &screen);
	void OutRGBA(int x, int y, int w, int h, const Color &colour);
	void DrawLineRGBA(int x, int y, int w, int h, const Color &colour);
	void FillRGBAKamay(int x, int y, int w, int h, int r, int g, int b, int a);
	// MENU STUFF
	//========================================
	void BorderBox(int x, int y, int w, int h, int thickness, Color color);
	void __fastcall Border2(int x, int y, int w, int h, Color colour);
	void __fastcall FillRGBA(int x, int y, int w, int h, Color colour);
	void RectOutlined(int x, int y, int w, int h, int thickness, Color color, Color outlined);
	int TweakColor(int c1, int c2, int variation);
	void GardientRect(int x, int y, int w, int h, Color color1, Color color2, int variation);
	void Circle(int x, int y, int radius, int segments, Color color);
	void Rect(int x, int y, int w, int h, Color color);
	void __fastcall PrintText(HFont font, int x, int y, Color colour, bool center, const char *pszText, ...);
	void __fastcall Border(int x, int y, int w, int h, Color colour);
	//========================================
	DWORD m_font;
	DWORD m_distanceFonts[6];
};


extern C_Draw Draw;
extern HFont fontMenu;
extern HFont MenuBoxesTitle;
extern HFont GlobalFont;
extern HFont m_font;
extern HFont m_distanceFonts[6];


extern int GetFontIndexByDistance(const float& distance);