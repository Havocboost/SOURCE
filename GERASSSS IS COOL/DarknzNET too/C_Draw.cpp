#include "C_Draw.h"

HFont fontMenu;
HFont MenuBoxesTitle;
HFont GlobalFont;
HFont m_font;
HFont m_distanceFonts[6];

C_Draw Draw;


void C_Draw::SetFont(DWORD *font, const char *name, int size, int flags)
{
	void *thisptr = Interface->Surface()->thisptr();

	*font = Interface->Surface()->GetOriginalMethod<CreateFont_t>(INDEX_CREATEFONT)(thisptr);
	Interface->Surface()->GetOriginalMethod<SetFontGlyphSet_t>(INDEX_SETFONTGLYPHSET)(thisptr, *font, name, size, 0, 0, 0, flags, 0, 0);
}
//=================================================
void C_Draw::FillRGBAKamay(int x, int y, int w, int h, int r, int g, int b, int a)
{

	void *thisptr = Interface->Surface()->thisptr();

	Interface->Surface()->GetOriginalMethod<DrawSetColor_t>(INDEX_DRAWSETCOLOR)(thisptr, r, g, b, a);
	Interface->Surface()->GetOriginalMethod<DrawRect_t>(INDEX_DRAWOUTLINEDRECT)(thisptr, x, y, x + w, y + h);
}
//=================================================
void C_Draw::DrawString(bool shouldcenter, int fontIndex, int x, int y, const Color &colour, const char *format, ...)
{
	
	va_list list;
	char buffer[0xFF];

	va_start(list, format);
	_vsnprintf_s(buffer, 0xFF, format, list);
	va_end(list);


	wchar_t wide[0xFF];
	::MultiByteToWideChar(CP_UTF8, 0, buffer, 0xFF, wide, 0xFF);


	void *thisptr = Interface->Surface()->thisptr();


	int textsize[VECTOR2D];
	Interface->Surface()->GetOriginalMethod<GetTextSize_t>(INDEX_GETTEXTSIZE)(thisptr, Draw.m_distanceFonts[fontIndex], wide, textsize[X], textsize[Y]);


	Interface->Surface()->GetOriginalMethod<DrawSetTextColor_t>(INDEX_DRAWSETTEXTCOLOR)(thisptr, colour.r(), colour.g(), colour.b(), colour.a());
	Interface->Surface()->GetOriginalMethod<DrawSetTextFont_t>(INDEX_DRAWSETTEXTFONT)(thisptr, Draw.m_distanceFonts[fontIndex]);


	int mod = ((shouldcenter) ? (textsize[X] * .5f) : 0);
	Interface->Surface()->GetOriginalMethod<DrawSetTextPos_t>(INDEX_DRAWSETTEXTPOS)(thisptr, (x - mod), y);
	Interface->Surface()->GetOriginalMethod<DrawPrintText_t>(INDEX_DRAWPRINTTEXT)(thisptr, wide, wcslen(wide), 0);
}
//=================================================
void C_Draw::DrawStringMenu(int iAlign, int fontIndex, int x, int y, const Color &colour, const char *format, ...) // (1 = center XY) (2 = right center Y) ( 3 = center Y)
{
	// print vars
	va_list list;
	char buffer[0xFF];

	va_start(list, format);
	_vsnprintf_s(buffer, 0xFF, format, list);
	va_end(list);


	// convert to wchar
	wchar_t wide[0xFF];
	::MultiByteToWideChar(CP_UTF8, 0, buffer, 0xFF, wide, 0xFF);


	void *thisptr = Interface->Surface()->thisptr();


	int textsize[VECTOR2D];
	Interface->Surface()->GetOriginalMethod<GetTextSize_t>(INDEX_GETTEXTSIZE)(thisptr, Draw.m_distanceFonts[fontIndex], wide, textsize[X], textsize[Y]);


	Interface->Surface()->GetOriginalMethod<DrawSetTextColor_t>(INDEX_DRAWSETTEXTCOLOR)(thisptr, colour.r(), colour.g(), colour.b(), colour.a());
	Interface->Surface()->GetOriginalMethod<DrawSetTextFont_t>(INDEX_DRAWSETTEXTFONT)(thisptr, Draw.m_distanceFonts[fontIndex]);


	int modX = 0, modY = 0;
	if (iAlign == 1)
	{
		modX = textsize[X] * 0.5f;
		modY = textsize[Y] * 0.5f;
	}
	if (iAlign == 2)
	{
		modX = textsize[X];
		modY = textsize[Y] * 0.5f;
	}
	if (iAlign == 3)
	{
		modY = textsize[Y] * 0.5f;
	}

	Interface->Surface()->GetOriginalMethod<DrawSetTextPos_t>(INDEX_DRAWSETTEXTPOS)(thisptr, (x - modX), y - modY);
	Interface->Surface()->GetOriginalMethod<DrawPrintText_t>(INDEX_DRAWPRINTTEXT)(thisptr, wide, wcslen(wide), 0);
}
//=================================================
void C_Draw::OutRGBA(int x, int y, int w, int h, const Color &colour)
{

	void *thisptr = Interface->Surface()->thisptr();

	Interface->Surface()->GetOriginalMethod<DrawSetColor_t>(INDEX_DRAWSETCOLOR)(thisptr, colour.r(), colour.g(), colour.b(), colour.a());
	Interface->Surface()->GetOriginalMethod<DrawRect_t>(INDEX_DRAWOUTLINEDRECT)(thisptr, x, y, w, h);

}
//=================================================
void C_Draw::DrawOutlinedRect(int x, int y, int w, int h, const Color &colour)
{
	void *thisptr = Interface->Surface()->thisptr();

	Interface->Surface()->GetOriginalMethod<DrawSetColor_t>(INDEX_DRAWSETCOLOR)(thisptr, colour.r(), colour.g(), colour.b(), colour.a());
	Interface->Surface()->GetOriginalMethod<DrawRect_t>(INDEX_DRAWOUTLINEDRECT)(thisptr, x, y, (x + w), (y + h));
}
//=================================================
void C_Draw::DrawFilledRect(int x, int y, int w, int h, const Color &colour)
{
	void *thisptr = Interface->Surface()->thisptr();

	Interface->Surface()->GetOriginalMethod<DrawSetColor_t>(INDEX_DRAWSETCOLOR)(thisptr, colour.r(), colour.g(), colour.b(), colour.a());
	Interface->Surface()->GetOriginalMethod<DrawRect_t>(INDEX_DRAWFILLEDRECT)(thisptr, x, y, (x + w), (y + h));
}
//=================================================
bool C_Draw::WorldToScreen(const Vector &vOrigin, Vector &vScreen)
{
	const VMatrix& worldToScreen = Interface->Engine()->GetVTable<IVEngineClient>()->WorldToScreenMatrix();

	float w = worldToScreen[3][0] * vOrigin[0] + worldToScreen[3][1] * vOrigin[1] + worldToScreen[3][2] * vOrigin[2] + worldToScreen[3][3];
	vScreen.z = 0;

	if (w > 0.001)
	{
		float fl1DBw = 1 / w;

		int screensize[VECTOR2D];
		Interface->Engine()->GetVTable<IVEngineClient>()->GetScreenSize(screensize[X], screensize[Y]);

		vScreen.x = (screensize[X] / 2) + ((((worldToScreen[0][0] * vOrigin[0] + worldToScreen[0][1] * vOrigin[1] + worldToScreen[0][2] * vOrigin[2] + worldToScreen[0][3]) * fl1DBw) / 2) * screensize[X] + 0.5);
		vScreen.y = (screensize[Y] / 2) - ((((worldToScreen[1][0] * vOrigin[0] + worldToScreen[1][1] * vOrigin[1] + worldToScreen[1][2] * vOrigin[2] + worldToScreen[1][3]) * fl1DBw) / 2) * screensize[Y] + 0.5);
		return true;
	}

	return false;
}
//=================================================
void C_Draw::DrawLineRGBA(int x, int y, int w, int h, const Color &colour)
{
	void *thisptr = Interface->Surface()->thisptr();
	Interface->Surface()->GetOriginalMethod<DrawSetColor_t>(INDEX_DRAWSETCOLOR)(thisptr, colour.r(), colour.g(), colour.b(), colour.a());
	Interface->Surface()->GetOriginalMethod<DrawLine_t>(INDEX_DRAWLINE)(thisptr, x, y, w, h);
}
//=================================================
__forceinline int GetFontIndexByDistance(const float& distance)
{
	float copy = max(min(distance, 1000.f), 1.f);

	return (5 * (int)(copy / 1000.f));
}
//=================================================
void C_Draw::BorderBox(int x, int y, int w, int h, int thickness, Color color)
{
	DrawFilledRect(x, y, w, thickness, color);
	DrawFilledRect(x, y, thickness, h, color);
	DrawFilledRect(x + w, y, thickness, h, color);
	DrawFilledRect(x, y + h, w + thickness, thickness, color);
}
//=================================================
void C_Draw::RectOutlined(int x, int y, int w, int h, int thickness, Color color, Color outlined)
{
	DrawFilledRect(x, y, w, h, color);
	BorderBox(x - thickness, y - thickness, w + thickness, h + thickness, thickness, outlined);
}
//=================================================
int C_Draw::TweakColor(int c1, int c2, int variation)
{
	if (c1 == c2)
		return c1;
	else if (c1 < c2)
		c1 += variation;
	else
		c1 -= variation;
	return c1;
}
//=================================================
void C_Draw::GardientRect(int x, int y, int w, int h, Color color1, Color color2, int variation)
{
	int r1 = color1.r();
	int g1 = color1.g();
	int b1 = color1.b();
	int a1 = color1.a();

	int r2 = color2.r();
	int g2 = color2.g();
	int b2 = color2.b();
	int a2 = color2.a();

	for (int i = 0; i <= w; i++)
	{
		DrawFilledRect(x + i, y, 1, h, Color(r1, g1, b1, a1));
		r1 = TweakColor(r1, r2, variation);
		g1 = TweakColor(g1, g2, variation);
		b1 = TweakColor(b1, b2, variation);
		a1 = TweakColor(a1, a2, variation);
	}
}
//=================================================
void C_Draw::Circle(int x, int y, int radius, int segments, Color color)
{
	void *thisptr = Interface->Surface()->thisptr();

	Interface->Surface()->GetOriginalMethod<DrawSetColor_t>(INDEX_DRAWSETCOLOR)(thisptr, color.r(), color.g(), color.b(), color.a());
	Interface->Surface()->GetOriginalMethod<DrawSetColor_t>(99)(thisptr, x, y, radius, segments);
}
//=================================================
void C_Draw::Rect(int x, int y, int w, int h, Color color)
{
	void *thisptr = Interface->Surface()->thisptr();

	Interface->Surface()->GetOriginalMethod<DrawSetColor_t>(INDEX_DRAWSETCOLOR)(thisptr, color.r(), color.g(), color.b(), color.a());
	Interface->Surface()->GetOriginalMethod<DrawRect_t>(INDEX_DRAWFILLEDRECT)(thisptr, x, y, (x + w), (y + h));
}
//=================================================
void __fastcall C_Draw::PrintText(HFont font, int x, int y, Color colour, bool center, const char *pszText, ...)
{
	if (pszText == 0)
		return;

	va_list list;
	char buffer[0xFF];

	va_start(list, pszText);
	_vsnprintf_s(buffer, 0xFF, pszText, list);
	va_end(list);

	// convert to wchar
	wchar_t wide[0xFF];
	::MultiByteToWideChar(CP_UTF8, 0, buffer, 0xFF, wide, 0xFF);

	void *thisptr = Interface->Surface()->thisptr();

	int textsize[2];
	Interface->Surface()->GetOriginalMethod<GetTextSize_t>(INDEX_GETTEXTSIZE)(thisptr, font, wide, textsize[0], textsize[1]);
	
	Interface->Surface()->GetOriginalMethod<DrawSetTextColor_t>(INDEX_DRAWSETTEXTCOLOR)(thisptr, colour.r(), colour.g(), colour.b(), colour.a());
	Interface->Surface()->GetOriginalMethod<DrawSetTextFont_t>(INDEX_DRAWSETTEXTFONT)(thisptr, font);
	
	int mod = ((center) ? (textsize[0] * .5f) : 0);
	Interface->Surface()->GetOriginalMethod<DrawSetTextPos_t>(INDEX_DRAWSETTEXTPOS)(thisptr, (x - mod), y);
	Interface->Surface()->GetOriginalMethod<DrawPrintText_t>(INDEX_DRAWPRINTTEXT)(thisptr, wide, wcslen(wide), 0);
}
//=================================================
void __fastcall C_Draw::Border(int x, int y, int w, int h, Color colour)
{
	void *thisptr = Interface->Surface()->thisptr();

	Interface->Surface()->GetOriginalMethod<DrawSetColor_t>(INDEX_DRAWSETCOLOR)(thisptr, colour.r(), colour.g(), colour.b(), colour.a());
	Interface->Surface()->GetOriginalMethod<DrawRect_t>(INDEX_DRAWOUTLINEDRECT)(thisptr, x, y, (x + w), (y + h));
}
//=================================================
void __fastcall C_Draw::Border2(int x, int y, int w, int h, Color colour)
{
	void *thisptr = Interface->Surface()->thisptr();

	Interface->Surface()->GetOriginalMethod<DrawSetColor_t>(INDEX_DRAWSETCOLOR)(thisptr, colour.r(), colour.g(), colour.b(), colour.a());
	Interface->Surface()->GetOriginalMethod<DrawRect_t>(INDEX_DRAWOUTLINEDRECT)(thisptr, x, y, (x + w), (y + h));
}
//=================================================
void __fastcall C_Draw::FillRGBA(int x, int y, int w, int h, Color colour)
{
	void *thisptr = Interface->Surface()->thisptr();

	Interface->Surface()->GetOriginalMethod<DrawSetColor_t>(INDEX_DRAWSETCOLOR)(thisptr, colour.r(), colour.g(), colour.b(), colour.a());
	Interface->Surface()->GetOriginalMethod<DrawRect_t>(INDEX_DRAWFILLEDRECT)(thisptr, x, y, (x + w), (y + h));
}