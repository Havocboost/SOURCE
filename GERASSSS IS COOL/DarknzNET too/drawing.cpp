#include "main.h"


CDrawing g_Drawing;


void CDrawing::SetFont( DWORD *font, const char *name, int size, int flags )
{
	void *thisptr = g_InterfaceManager->Surface()->thisptr();

	*font = g_InterfaceManager->Surface()->GetOriginalMethod<CreateFont_t>( INDEX_CREATEFONT )( thisptr );
	g_InterfaceManager->Surface()->GetOriginalMethod<SetFontGlyphSet_t>( INDEX_SETFONTGLYPHSET )( thisptr, *font, name, size, 0, 0, 0, flags, 0, 0 );
}

void CDrawing::FillRGBAKamay( int x, int y, int w, int h, int r, int g, int b, int a )
{

	void *thisptr = g_InterfaceManager->Surface()->thisptr();

	g_InterfaceManager->Surface()->GetOriginalMethod<DrawSetColor_t>( INDEX_DRAWSETCOLOR )(thisptr, r, g, b, a ); 
	g_InterfaceManager->Surface()->GetOriginalMethod<DrawRect_t>( INDEX_DRAWOUTLINEDRECT )( thisptr, x, y, x + w, y + h ); 
}




void CDrawing::DrawString( bool shouldcenter, int fontIndex, int x, int y, const Color &colour, const char *format, ... )
{
	// print vars
	va_list list;
	char buffer[0xFF];

	va_start( list, format );
	_vsnprintf_s( buffer, 0xFF, format, list );
	va_end( list );


	// convert to wchar
	wchar_t wide[0xFF];
	::MultiByteToWideChar( CP_UTF8, 0, buffer, 0xFF, wide, 0xFF );


	void *thisptr = g_InterfaceManager->Surface()->thisptr();


	int textsize[VECTOR2D];
	g_InterfaceManager->Surface()->GetOriginalMethod<GetTextSize_t>( INDEX_GETTEXTSIZE )( thisptr, g_Drawing.m_distanceFonts[fontIndex], wide, textsize[X], textsize[Y] );


	g_InterfaceManager->Surface()->GetOriginalMethod<DrawSetTextColor_t>( INDEX_DRAWSETTEXTCOLOR )( thisptr, colour.r(), colour.g(), colour.b(), colour.a() );
	g_InterfaceManager->Surface()->GetOriginalMethod<DrawSetTextFont_t>( INDEX_DRAWSETTEXTFONT )( thisptr, g_Drawing.m_distanceFonts[fontIndex] );


	int mod = ( ( shouldcenter ) ? ( textsize[X] * .5f ) : 0 );
	g_InterfaceManager->Surface()->GetOriginalMethod<DrawSetTextPos_t>( INDEX_DRAWSETTEXTPOS )( thisptr, ( x - mod ), y );
	g_InterfaceManager->Surface()->GetOriginalMethod<DrawPrintText_t>( INDEX_DRAWPRINTTEXT )( thisptr, wide, wcslen( wide ), 0 );
}

void CDrawing::DrawStringMenu( int iAlign, int fontIndex, int x, int y, const Color &colour, const char *format, ... ) // (1 = center XY) (2 = right center Y) ( 3 = center Y)
{
	// print vars
	va_list list;
	char buffer[0xFF];

	va_start( list, format );
	_vsnprintf_s( buffer, 0xFF, format, list );
	va_end( list );


	// convert to wchar
	wchar_t wide[0xFF];
	::MultiByteToWideChar( CP_UTF8, 0, buffer, 0xFF, wide, 0xFF );


	void *thisptr = g_InterfaceManager->Surface()->thisptr();


	int textsize[VECTOR2D];
	g_InterfaceManager->Surface()->GetOriginalMethod<GetTextSize_t>( INDEX_GETTEXTSIZE )( thisptr, g_Drawing.m_distanceFonts[fontIndex], wide, textsize[X], textsize[Y] );


	g_InterfaceManager->Surface()->GetOriginalMethod<DrawSetTextColor_t>( INDEX_DRAWSETTEXTCOLOR )( thisptr, colour.r(), colour.g(), colour.b(), colour.a() );
	g_InterfaceManager->Surface()->GetOriginalMethod<DrawSetTextFont_t>( INDEX_DRAWSETTEXTFONT )( thisptr, g_Drawing.m_distanceFonts[fontIndex] );


	int modX=0, modY=0;
	if( iAlign == 1)
	{ 
		modX = textsize[X] * 0.5f;
		modY = textsize[Y] * 0.5f;
	}
	if( iAlign == 2) 
	{
		modX = textsize[X];
		modY = textsize[Y] * 0.5f;
	}
	if( iAlign == 3)
	{
		modY = textsize[Y] * 0.5f;
	}

	g_InterfaceManager->Surface()->GetOriginalMethod<DrawSetTextPos_t>( INDEX_DRAWSETTEXTPOS )( thisptr, ( x - modX ), y - modY);
	g_InterfaceManager->Surface()->GetOriginalMethod<DrawPrintText_t>( INDEX_DRAWPRINTTEXT )( thisptr, wide, wcslen( wide ), 0 );
}

void CDrawing::OutRGBA( int x, int y, int w, int h, const Color &colour )
{

	void *thisptr = g_InterfaceManager->Surface()->thisptr();

	g_InterfaceManager->Surface()->GetOriginalMethod<DrawSetColor_t>( INDEX_DRAWSETCOLOR )( thisptr, colour.r(), colour.g(), colour.b(), colour.a() );
	g_InterfaceManager->Surface()->GetOriginalMethod<DrawRect_t>( INDEX_DRAWOUTLINEDRECT )( thisptr, x, y, w, h );

}

void CDrawing::DrawOutlinedRect( int x, int y, int w, int h, const Color &colour )
{
	void *thisptr = g_InterfaceManager->Surface()->thisptr();

	g_InterfaceManager->Surface()->GetOriginalMethod<DrawSetColor_t>( INDEX_DRAWSETCOLOR )( thisptr, colour.r(), colour.g(), colour.b(), colour.a() );
	g_InterfaceManager->Surface()->GetOriginalMethod<DrawRect_t>( INDEX_DRAWOUTLINEDRECT )( thisptr, x, y, ( x + w ), ( y + h ) );
}


void CDrawing::DrawFilledRect( int x, int y, int w, int h, const Color &colour )
{
	void *thisptr = g_InterfaceManager->Surface()->thisptr();

	g_InterfaceManager->Surface()->GetOriginalMethod<DrawSetColor_t>( INDEX_DRAWSETCOLOR )( thisptr, colour.r(), colour.g(), colour.b(), colour.a() );
	g_InterfaceManager->Surface()->GetOriginalMethod<DrawRect_t>( INDEX_DRAWFILLEDRECT )( thisptr, x, y, ( x + w ), ( y + h ) );
}



bool CDrawing::WorldToScreen( const Vector &vOrigin, Vector &vScreen ) 
{ 
	const VMatrix& worldToScreen = g_InterfaceManager->Engine()->GetVTable<IVEngineClient>()->WorldToScreenMatrix(); 

	float w = worldToScreen[3][0] * vOrigin[0] + worldToScreen[3][1] * vOrigin[1] + worldToScreen[3][2] * vOrigin[2] + worldToScreen[3][3]; 
	vScreen.z = 0; 

	if( w > 0.001 ) 
	{ 
		float fl1DBw = 1 / w; 

		int screensize[VECTOR2D];
		g_InterfaceManager->Engine()->GetVTable<IVEngineClient>()->GetScreenSize( screensize[X], screensize[Y] );

		vScreen.x = (screensize[X] / 2) + ((((worldToScreen[0][0] * vOrigin[0] + worldToScreen[0][1] * vOrigin[1] + worldToScreen[0][2] * vOrigin[2] + worldToScreen[0][3]) * fl1DBw) / 2) * screensize[X] + 0.5); 
		vScreen.y = (screensize[Y] / 2) - ((((worldToScreen[1][0] * vOrigin[0] + worldToScreen[1][1] * vOrigin[1] + worldToScreen[1][2] * vOrigin[2] + worldToScreen[1][3]) * fl1DBw) / 2) * screensize[Y] + 0.5); 
		return true; 
	} 

	return false; 
} 


void CDrawing::DrawLineRGBA( int x, int y, int w, int h, const Color &colour )
{
	void *thisptr = g_InterfaceManager->Surface()->thisptr();
	g_InterfaceManager->Surface()->GetOriginalMethod<DrawSetColor_t>( INDEX_DRAWSETCOLOR )( thisptr, colour.r(), colour.g(), colour.b(), colour.a() );
	g_InterfaceManager->Surface()->GetOriginalMethod<DrawLine_t>( INDEX_DRAWLINE )( thisptr, x, y, w, h );
}
//bool CDrawing::WorldToScreen( const Vector &point, Vector &screen )
//{
//	typedef int ( __cdecl *ScreenTransform_t )( const Vector &point, Vector &screen );
//	static ScreenTransform_t ScreenTransform = (ScreenTransform_t)Memory::FindPattern( GetModuleHandle( "client.dll" ), "\x55\x8B\xEC\x8B\x0D????\x8B\x01\x8B\x90????\xFF\xD2\x8B\x4D\x08" );
//	
//	if ( !ScreenTransform )
//	{
//		LOG_ERROR( "ScreenTransform not found" );
//	}
//
//
//	// the point is on screen
//	if ( !ScreenTransform( point, screen ) )
//	{
//		int screensize[VECTOR2D];
//		g_InterfaceManager->Engine()->GetVTable<IVEngineClient>()->GetScreenSize( screensize[X], screensize[Y] );
//
//		if ( screensize[X]
//			&& screensize[Y] )
//		{
//			screen.x = ( ( screensize[X] * .5f ) + ( .5f * screen.x * screensize[X] + .5f ) );
//			screen.y = ( ( screensize[Y] * .5f ) - ( .5f * screen.y * screensize[Y] + .5f ) );
//			return true;
//		}
//	}
//
//
//	return false;
//}


__forceinline int GetFontIndexByDistance( const float& distance )
{
	float copy = max( min( distance, 1000.f ), 1.f );

	return ( 5 * (int)( copy / 1000.f ) );
}