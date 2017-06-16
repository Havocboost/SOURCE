#include "main.h"
//#include "mouse.h"

C_Menu::C_Menu( void )
{
	m_iCurrentTap = -1;

	m_bActive = false;
	m_bAimHitboxCombo = false;
	m_bTeamCheckCombo = false;
	m_bTeamCheckCombo = false;
	m_bAimHitscanCombo = false;
	m_bVisBoxCombo = false;
	m_bVisWeaponsCombo = false;

	SetPosition( 100, 20 );
	m_iW = 640;
	m_iH = 600;
	m_iCurrentTap = 0;

	//	m_pMouseInput = new CMouseInput( 1 );
	//m_pKeyInput = new CKeyInput( );

	m_strHitboxes.push_back( "Head" );
	m_strHitboxes.push_back( "Neck" );
	m_strHitboxes.push_back( "LowerNeck" );
	m_strHitboxes.push_back( "Pelvis" );
	m_strHitboxes.push_back( "Body" );

	m_strTeamCheck.push_back( "All" );
	m_strTeamCheck.push_back( "Enemy" );
	m_strTeamCheck.push_back( "Team" );

	m_strTargetSelection.push_back( "Distance" );
	m_strTargetSelection.push_back( "Health" );
	m_strTargetSelection.push_back( "NextShoot" );
	m_strTargetSelection.push_back( "Random" );

	m_strHitscans.push_back( "Off" );
	m_strHitscans.push_back( "Visible" );
	m_strHitscans.push_back( "Autowall|Visible" );
	m_strHitscans.push_back( "Loop" );

	m_strVisBoxes.push_back( "Disabled" );
	m_strVisBoxes.push_back( "Border Box" );
	m_strVisBoxes.push_back( "Edge Bounding Box" );
	m_strVisWeapons.push_back( "Disabled" );
	m_strVisWeapons.push_back( "Weapon Symbol" );
	m_strVisWeapons.push_back( "Weapon Name" );
	m_strVisHands.push_back( "Disabled" );
	m_strVisHands.push_back( "Remove Hands " );
	m_strVisHands.push_back( "Wireframe Hands" );
	m_strVisChams.push_back( "Disabled" );
	m_strVisChams.push_back( "Normal" );
	m_strVisChams.push_back( "Full Brightness" );

	m_strColors.push_back( "Grey" );
	m_strColors.push_back( "Red" );
	m_strColors.push_back( "LightRed" );
	m_strColors.push_back( "Blue" );
	m_strColors.push_back( "LightBlue" );
	m_strColors.push_back( "Black" );
	m_strColors.push_back( "White" );
	m_strColors.push_back( "Green" );
	m_strColors.push_back( "Yellow" );
	m_strColors.push_back( "ICS_Blue" );
	m_strColors.push_back( "Cool_Grey" );
	m_strColors.push_back( "Indigo" );

	m_strBuybot.push_back( "AK/USP" );
	m_strBuybot.push_back( "M249/USP" );
	m_strBuybot.push_back( "AK/DEAGLE" );
	m_strBuybot.push_back( "M249/DEAGLE" );
	m_strBuybot.push_back( "AWP/DEAGLE" );

	m_strPosAdjusment.push_back( "Off" );
	m_strPosAdjusment.push_back( "Adjustment_1" );
	m_strPosAdjusment.push_back( "Adjustment_2" );

	m_strEdgeMode.push_back( "Normal" );
	m_strEdgeMode.push_back( "FakeOut" );
	m_strEdgeMode.push_back( "JitterOut" );

	m_strFakelag.push_back( "None" );
	m_strFakelag.push_back( "Constant" );
	m_strFakelag.push_back( "Const + Attack" );
	m_strFakelag.push_back( "Const + NoAttack" );
	m_strFakelag.push_back( "Alternative" );
	m_strFakelag.push_back( "Alternative + Attack" );
	m_strFakelag.push_back( "Alternative + NoAttack" );

	//m_strAntiAim.push_back( "Sideways" );
	m_strAntiAim.push_back( "Backwards" );
	m_strAntiAim.push_back( "Test Fake" );
	m_strAntiAim.push_back( "Static test" );
	m_strAntiAim.push_back( "Backwards Jitter" );
	m_strAntiAim.push_back( "Sideways Jitter" );
	m_strAntiAim.push_back( "Backwards Jitter 2" );
	m_strAntiAim.push_back( "Fake Forward" );
	m_strAntiAim.push_back( "Jitter Synced" );
	m_strAntiAim.push_back( "Sideways" );
	m_strAntiAim.push_back( "Test static and follow" );


	m_strPitch.push_back( "Off" );
	m_strPitch.push_back( "Down" );
	m_strPitch.push_back( "FakeDown" );
	m_strPitch.push_back( "Emotion" );
	m_strPitch.push_back( "MM Down" );
	//m_strPitch.push_back( "LISPDOWN" );
	//m_strPitch.push_back( "ANGELDOWN" );
	//m_strPitch.push_back( "ANGELUP" );

	m_strAntiAimType.push_back( "Static" );
	m_strAntiAimType.push_back( "IN_ATTACK" );
	m_strAntiAimType.push_back( "At Targets" );

	m_strPlayerListPitch.push_back( "Off" );
	m_strPlayerListPitch.push_back( "Down" );
	m_strPlayerListPitch.push_back( "Up" );
	m_strPlayerListPitch.push_back( "Inverse" );
	m_strPlayerListPitch.push_back( "Face" );

	m_strPlayerListYaw.push_back( "Off" );
	m_strPlayerListYaw.push_back( "Inverse" );
	m_strPlayerListYaw.push_back( "Sideways R" );
	m_strPlayerListYaw.push_back( "Sideways L" );
	m_strPlayerListYaw.push_back( "Follow" );
	m_strPlayerListYaw.push_back( "Follow Side R" );
	m_strPlayerListYaw.push_back( "Follow Side L" );
	m_strPlayerListYaw.push_back( "Follow Inverse" );
	m_strPlayerListYaw.push_back( "Spinbot" );

	m_strColourSelector.push_back( "ESP Terrorist Color:" );
	m_strColourSelector.push_back( "ESP C-T Color:" );
	m_strColourSelector.push_back( "Chams Terrorist Color:" );
	m_strColourSelector.push_back( "Chams C-T Color:" );
	m_strColourSelector.push_back( "Whitelist Color:" );
	m_strColourSelector.push_back( "Aimspot/Line ESP Color:" );
	m_strColourSelector.push_back( "Crosshair Color:" );
	m_strColourSelector.push_back( "Menu Color:" );
	m_strColourSelector.push_back( "Cursor Color:" );

	m_strInaccuracy.push_back( "Off" );
	m_strInaccuracy.push_back( "No Spread" );
	m_strInaccuracy.push_back( "No Recoil" );
	m_strInaccuracy.push_back( "Both ^" );

	m_strAimbotSelected.push_back( "Simple" );
	m_strAimbotSelected.push_back( "Advanced" );

}
//=================================================
C_Menu::~C_Menu( void )
{
	//SafeDelete( &m_pMouseInput );
}
//=================================================
void C_Menu::RenderTab( int x, int y, int w, int h, std::string strText, int iIndex, int& iStatus )
{
	bool bActive;
	auto bHover = Mouse.CheckPos( x, y, w, h );
	Color color = Color( 42, 42, 42, 255 );
	if ( iIndex == iStatus )
	{
		bActive = true;
	}
	else
	{
		bActive = false;
	}
	if ( bActive )
	{
		color = Color( 25, 25, 25, 255 );
	}
	if ( bHover )
	{
		color = Color( 25, 25, 25, 255 );
	}

	if ( bHover && GetAsyncKeyState( VK_LBUTTON ) & 1 )
		iStatus = iIndex;

	Draw.RectOutlined( x, y, w, h, 1, color, Color( 0, 0, 0, 255 ) );

	Draw.PrintText( fontMenu, x + ( w / 2 ), y + ( h / 2 ) - 7, Color( 255, 255, 255, 255 ), true, strText.c_str() );
}
//=================================================
void C_Menu::RenderCheckbox( int x, int y, std::string strText, float &cvar )
{
	auto bHover = Mouse.CheckPos( x, y, 20, 20 );

	static auto size = 20;

	//Draw.DrawFilledRect(x, y, size, size, Color(50, 50, 50, 240));
	if ( cvar )
	{
		Draw.DrawFilledRect( x + 2, y + 2, size - 4, size - 4, Color( 20, 70, 145, 255 ) );
	}
	if ( bHover )
	{
		if ( cvar ) 
			Draw.DrawFilledRect( x + 2, y + 2, size - 4, size - 4, Color( 30, 80, 155, 255 ) );
		else 
			Draw.DrawFilledRect( x + 2, y + 2, size - 4, size - 4, Color( 60, 60, 135, 255 ) );

		if ( (GetAsyncKeyState( VK_LBUTTON ) & 1) && Visual::canmodify )
			cvar = !cvar;
	}
	Draw.Border2( x, y, 20, 20, Color( 90, 90, 90, 230 ) );

	Draw.PrintText( fontMenu, x + size + 5, y + 2, Color( 255, 255, 255, 255 ), false, strText.c_str() );
}
//=================================================
void C_Menu::RenderSlider( int x, int y, int w, int h, std::string strText, float &cvar, int min, int max )
{
	static auto cvarstore = cvar;
	Draw.DrawFilledRect( x, y, w, h, Color( 50, 50, 50, 240 ) );

	auto bHover = Mouse.CheckPos( x, y, w, h );
	auto flValue = cvar;
	auto flStep = float( ( w / max ) * flValue );


	float flDelta[ 2 ] ={ 0.f };
	flDelta[ 0 ] = float( ( Mouse.m_info[ X ] ) - x );
	flDelta[ 1 ] = float( Mouse.m_info[ Y ] );

	bHover = Mouse.CheckPos( x - 3, y, w + 5, h );
	if ( GetAsyncKeyState( VK_LBUTTON ) && bHover && Visual::canmodify )
	{
		if ( !( flDelta[ 0 ] >= 0.f ) || !( flDelta[ 0 ] <= w + 5 ) )
			return;

		flValue = ceil( min + ( ( max + min ) * ( flDelta[ 0 ] / w ) ) );
		cvar = flValue;

		flStep = flDelta[ 0 ];

	}

	char pszBuffer[ 0x20 ];
	sprintf_s( pszBuffer, "%d", ( int ) flValue );

	auto strInfo = strText + std::string( ": " ) + pszBuffer;
	int iFontSize[ 2 ] ={ 0 };

	//	g_pRenderSurface->GetTextSize( "Tahoma", strInfo, iFontSize );
	Draw.DrawFilledRect( x, y, flStep, h, Color( 0, 162, 232, 200 ) );
	Draw.PrintText( fontMenu, x + ( w / 2 ), y + ( h / 2 ) - 3, Color( 255, 255, 255, 240 ), false, strInfo.c_str() );
}
//=================================================
void C_Menu::RenderComboBox( int x, int y, int w, int h, std::vector< std::string > strNodes, int& cvar, bool& bState )
{
	auto iIndex = cvar;
	auto nSize = strNodes.size();
	static float storedcvar = cvar;
	if ( iIndex >= ( int ) nSize )
		iIndex = ( int ) nSize - 1;

	int iFontSize[ 2 ] ={ 0 };
	auto strCurrentString = strNodes[ iIndex ];

	//	g_pRenderSurface->GetTextSize( "Tahoma", strCurrentString, iFontSize );
	Draw.DrawFilledRect( x, y, w, h, Color( 50, 50, 50, 230 ) );
	Draw.DrawFilledRect( x + w - h, y, h, h, Color( 30, 80, 155, 255 ) );
	Draw.Border2( x, y, w, h, Color( 90, 90, 90, 255 ) );
	Draw.PrintText( fontMenu, x + 5, y + ( h / 2 ) - 7, Color( 255, 255, 255, 230 ), false, strCurrentString.c_str() );
	static bool press = false;
	if ( GetAsyncKeyState( VK_LBUTTON ) && Visual::canmodify )
	{
		if ( Mouse.CheckPos( x + w - h, y, h, h ) && !press )
		{
			bState = !bState;
			press = true;
		}
	}
	else
		press = false;

	if ( bState )
	{
		auto Y = y + h;
		for ( int i = 0; i < ( int ) nSize; i++ )
		{
			auto bHover = Mouse.CheckPos( x, Y + 2 + ( i * 20 ), w, 18 );

			Draw.DrawFilledRect( x, Y + 2 + ( i * 20 ), w, 18, bHover ? Color( 150, 20, 20, 230 ) : Color( 50, 50, 50, 230 ) );
			Draw.Border2( x, Y + 2 + ( i * 20 ), w, 18, Color( 90, 90, 90, 255 ) );
			Draw.PrintText( fontMenu, x + 5, Y + 3 + ( i * 20 ), Color( 255, 255, 255, 255 ), false, strNodes[ i ].c_str() );

			if ( bHover && ( GetAsyncKeyState( VK_LBUTTON ) ) && Visual::canmodify )
			{
				cvar = i;
				bState = false;
			}
		}



		//		if( (GetAsyncKeyState(VK_LBUTTON)) && !Mouse.CheckPos( x, Y, w, nSize ) )
		//		bState = false;
		//	if(storedcvar != cvar)
		//	bState = false;
	}


	if ( !bState )
	{
		// draw arrow pointing down
		Draw.DrawFilledRect( ( x + w - h + 113 - 107 ), ( y + 8 ), 1, 1, Color( 255, 255, 255, 255 ) );
		Draw.DrawFilledRect( ( x + w - h + 114 - 107 ), ( y + 8 ), 1, 2, Color( 255, 255, 255, 255 ) );
		Draw.DrawFilledRect( ( x + w - h + 115 - 107 ), ( y + 8 ), 1, 3, Color( 255, 255, 255, 255 ) );
		Draw.DrawFilledRect( ( x + w - h + 116 - 107 ), ( y + 8 ), 1, 4, Color( 255, 255, 255, 255 ) );
		Draw.DrawFilledRect( ( x + w - h + 117 - 107 ), ( y + 8 ), 1, 3, Color( 255, 255, 255, 255 ) );
		Draw.DrawFilledRect( ( x + w - h + 118 - 107 ), ( y + 8 ), 1, 2, Color( 255, 255, 255, 255 ) );
		Draw.DrawFilledRect( ( x + w - h + 119 - 107 ), ( y + 8 ), 1, 1, Color( 255, 255, 255, 255 ) );
	}
	else
	{
		// draw arrow pointing up
		Draw.DrawFilledRect( ( x + w - h + 113 - 107 ), ( y + 11 ), 1, 1, Color( 255, 255, 255, 255 ) );
		Draw.DrawFilledRect( ( x + w - h + 114 - 107 ), ( y + 10 ), 1, 2, Color( 255, 255, 255, 255 ) );
		Draw.DrawFilledRect( ( x + w - h + 115 - 107 ), ( y + 9 ), 1, 3, Color( 255, 255, 255, 255 ) );
		Draw.DrawFilledRect( ( x + w - h + 116 - 107 ), ( y + 8 ), 1, 4, Color( 255, 255, 255, 255 ) );
		Draw.DrawFilledRect( ( x + w - h + 117 - 107 ), ( y + 9 ), 1, 3, Color( 255, 255, 255, 255 ) );
		Draw.DrawFilledRect( ( x + w - h + 118 - 107 ), ( y + 10 ), 1, 2, Color( 255, 255, 255, 255 ) );
		Draw.DrawFilledRect( ( x + w - h + 119 - 107 ), ( y + 11 ), 1, 1, Color( 255, 255, 255, 255 ) );
	}
}
//=================================================
void DrawSlider( int x, int y, bool bInt, float& Input, float iMin, float iMax, const char* szName, Color pColor )
{
	float sliderpos, barpos;

	// 1/2ratio exemple : w = 240 calculation based with 1/2 of 240 so 120

	if ( Mouse.CheckPos( x, y + 3, 180, 9 ) && GetAsyncKeyState( 0x1 ) && Visual::canmodify )
	{
		sliderpos = float( ( Mouse.m_info[ X ] ) - x );
	}
	else
	{
		sliderpos = ( ( ( Input * 90 ) * 2 ) / iMax );
	}

	Input = ( iMax * ( sliderpos / 2 ) / 90 );
	barpos = ( sliderpos / 180 * 90 ) * 2;

	if ( barpos > 180 )
		barpos = 180;

	if ( bInt )
	{
		int iOutput;
		double integral;
		float fraction = ( float ) modf( Input, &integral );
		iOutput = ( int ) integral;
		if ( fraction >= 0.5 )
			iOutput = int( iOutput + 1 );
		Input = iOutput;
	}

	Input = ( clamp( Input, iMin, iMax ) );

	Draw.FillRGBA( x, y + 5, 182, 7, Color( 42, 42, 42, 255 ) ); //background

	Draw.FillRGBA( x, y + 5, int( barpos ), 7, pColor );

	Draw.Border2( x, y + 5, 182, 7, Color( 90, 90, 90, 255 ) );

	Draw.FillRGBA( x + int( barpos ), y + 2, 5, 13, pColor );

	Draw.Border2( x + int( barpos ), y + 2, 5, 13, Color( 90, 90, 90, 255 ) ); //Cursor border, Sexy <3

	Draw.PrintText( fontMenu, x, y - 16, Color( 255, 255, 255, 255 ), false, bInt ? "%s : [%0.2f] :" : "%s : [%0.2f]", szName, Input );
}
//=================================================
void DrawSlider( int x, int y, int w, bool bInt, float& Input, float iMin, float iMax, const char* szName )
{
	float sliderpos, barpos;

	// 1/2ratio exemple : w = 240 calculation based with 1/2 of 240 so 120

	if ( Mouse.CheckPos( x, y + 3, w, 9 ) )
	{
		//DrawInfo(Input->GetDescription().c_str());
	}

	if ( Mouse.CheckPos( x, y + 3, w, 9 ) && GetAsyncKeyState( 0x1 ) && Visual::canmodify )
	{
		sliderpos = float( ( Mouse.m_info[ X ] ) - x );
	}
	else
	{
		sliderpos = ( ( ( Input * ( w / 2 ) * 2 ) / iMax ) );
	}

	Input = ( iMax * ( sliderpos / 2 ) / ( w / 2 ) );
	barpos = ( sliderpos / w * ( w / 2 ) * 2 );

	if ( barpos > w )
		barpos = w;

	if ( bInt )
	{
		int iOutput;
		double integral;
		float fraction = ( float ) modf( Input, &integral );
		iOutput = ( int ) integral;
		if ( fraction >= 0.5 )
			iOutput = int( iOutput + 1 );
		Input = iOutput;
	}

	Input = ( clamp( Input, iMin, iMax ) );

	Draw.FillRGBA( x, y + 5, ( w + 2 ), 7, Color( 42, 42, 42, 255 ) ); //background

	Draw.FillRGBA( x, y + 5, int( barpos ), 7, Color( 25, 25, 25, 255 ) ); //Color till cursor

	Draw.Border2( x, y + 5, ( w + 2 ), 7, Color( 90, 90, 90, 255 ) );

	Draw.FillRGBA( x + int( barpos ), y + 2, 5, 13, Color( 25, 25, 25, 255 ) ); //Cursor

	Draw.Border2( x + int( barpos ), y + 2, 5, 13, Color( 90, 90, 90, 255 ) ); //Cursor border, Sexy <3	

	Draw.PrintText( fontMenu, x, y - 16, Color( 255, 255, 255, 255 ), false, bInt ? "%s : [%0.2f] :" : "%s : [%0.2f]", szName, Input );
}
//=================================================
void C_Menu::RenderAimbotTab( int x, int y, int w, int h )
{
	static float nothing = 0.0f;
	static std::string strCheckboxes[ 6 ] ={ "Active", "Autoshoot", "SilentAim", "Send On Attack", "Autowall","Hitchance" };
	static float flCheckboxesCVars[ 6 ] ={ Aimbot::Enable,Aimbot::Autoshoot,Aimbot::Silent,Aimbot::SendAttck,Aimbot::Autowall,Aimbot::Hitchance };
	for ( int i = 0; i < 6; i++ )
	{
		RenderCheckbox( x, y + ( i * 20 ) + ( i * 5 ), strCheckboxes[ i ], flCheckboxesCVars[ i ] );
	}
	Aimbot::Enable = flCheckboxesCVars[ 0 ];
	Aimbot::Autoshoot = flCheckboxesCVars[ 1 ];
	Aimbot::Silent = flCheckboxesCVars[ 2 ];
	Aimbot::SendAttck = flCheckboxesCVars[ 3 ];
	Aimbot::Autowall = flCheckboxesCVars[ 4 ];
	Aimbot::Hitchance = flCheckboxesCVars[ 5 ];
	//RenderCheckbox(x + 290, y + 100, "Send On Attack", Aimbot::SendAttck);

	static int iSliderMinsAdjust[ 4 ] ={ 0,0,0,1 };
	static int iSliderMaxsAdjust[ 4 ] ={ 10,10,10 ,100 };
	static std::string strSlider[ 4 ] ={ "Adjust X", "Adjust Y", "Adjust Z" ,"Autowall Dmg" };
	static float flSliderCVarsAdjusts[ 4 ] ={ Aimbot::Adjust_X, Aimbot::Adjust_Y, Aimbot::Adjust_Z,Aimbot::AutowallDmg };

	for ( int i = 0; i < 4; i++ )
		DrawSlider( x, y + h - 210 + ( i * 25 ) + ( i * 10 ), 435, false, flSliderCVarsAdjusts[ i ], iSliderMinsAdjust[ i ], iSliderMaxsAdjust[ i ], strSlider[ i ].c_str() );

	Aimbot::Adjust_X = flSliderCVarsAdjusts[ 0 ];
	Aimbot::Adjust_Y = flSliderCVarsAdjusts[ 1 ];
	Aimbot::Adjust_Z = flSliderCVarsAdjusts[ 2 ];
	Aimbot::AutowallDmg = flSliderCVarsAdjusts[ 3 ];

	static std::string strComboboxLabel[ 5 ] ={ "Aimbot:", "Target Selection:", "Hitscans:", "Hitbox:", "Inaccuracy:" };
	for ( int i = 0; i < 5; i++ )
		Draw.PrintText( fontMenu, x + 170, y + 10 + ( i * 25 ) - 8, Color( 255, 255, 255, 255 ), false, strComboboxLabel[ i ].c_str() );

	RenderComboBox( x + 290, y, 150, 20, m_strAimbotSelected, Aimbot::Selected, m_bSelected );

	if ( !m_bSelected && !m_bTeamCheckCombo )
		RenderComboBox( x + 290, y + 25, 150, 20, m_strTargetSelection, Aimbot::TargetSelection, m_bTargetSelectionCombo );

	if ( !m_bSelected && !m_bTargetSelectionCombo )
		RenderComboBox( x + 290, y + 50, 150, 20, m_strHitscans, Aimbot::Hitscans, m_bAimHitscanCombo );

	if ( !m_bTeamCheckCombo && !m_bTargetSelectionCombo && !m_bAimHitscanCombo )
		RenderComboBox( x + 290, y + 75, 150, 20, m_strHitboxes, Aimbot::Hitbox, m_bAimHitboxCombo );

	if ( !m_bTeamCheckCombo && !m_bTargetSelectionCombo && !m_bAimHitscanCombo && !m_bAimHitboxCombo )
		RenderComboBox( x + 290, y + 100, 150, 20, m_strInaccuracy, Aimbot::Inaccuracy, m_bInaccuracy );
}
//=================================================
void C_Menu::RenderVisualsTab( int x, int y, int w, int h )
{
	static int nothing = 0;
	static std::string strCheckboxes[ 18 ] =
	{ "Enable ESP", "Box ESP", "Health ESP", "Armor ESP","Name ESP","Weapon ESP","AA X ESP","AA Y ESP",
		"Enable Hitmarker","Enable Crosshair","No Sky","No Hands","Asus","Enable Model",
		"Player Chams","Outline Player Chams","Weapon Chams","Outline Weapon Chams" };

	static float flCheckboxesCVars[ 18 ] =
	{ Visual::Esp::Enable,Visual::Esp::Box,Visual::Esp::Health,Visual::Esp::Armor,Visual::Esp::Name,
		Visual::Esp::Weapon,Visual::Esp::AAx,Visual::Esp::AAy,Visual::Hitmarker,Visual::Crosshair,
		Visual::NoSky,Visual::NoHands,Visual::Asus,Visual::Chams::Enable,Visual::Chams::Player,Visual::Chams::PlayerOutline,
		Visual::Chams::Weapon,Visual::Chams::WeaponOutline };

	for ( int i = 0; i < 18; i++ )
	{
		if ( i < 6 )
			RenderCheckbox( x, y + ( i * 20 ) + ( i * 5 ), strCheckboxes[ i ], flCheckboxesCVars[ i ] );
		else if ( i < 12 )
			RenderCheckbox( x + 145, y + ( i * 20 ) - ( 7 * 20 ) - 10 + ( i * 5 ), strCheckboxes[ i ], flCheckboxesCVars[ i ] );
		else if ( i < 19 )
			RenderCheckbox( x + 290, y + ( i * 20 ) - ( 15 * 20 ) + ( i * 5 ), strCheckboxes[ i ], flCheckboxesCVars[ i ] );
	}


	Visual::Esp::Enable = flCheckboxesCVars[ 0 ];
	Visual::Esp::Box = flCheckboxesCVars[ 1 ];
	Visual::Esp::Health = flCheckboxesCVars[ 2 ];
	Visual::Esp::Armor = flCheckboxesCVars[ 3 ];
	Visual::Esp::Name = flCheckboxesCVars[ 4 ];
	Visual::Esp::Weapon = flCheckboxesCVars[ 5 ];
	Visual::Esp::AAx = flCheckboxesCVars[ 6 ];
	Visual::Esp::AAy = flCheckboxesCVars[ 7 ];
	Visual::Hitmarker = flCheckboxesCVars[ 8 ];
	Visual::Crosshair = flCheckboxesCVars[ 9 ];
	Visual::NoSky = flCheckboxesCVars[ 10 ];
	Visual::NoHands = flCheckboxesCVars[ 11 ];
	Visual::Asus = flCheckboxesCVars[ 12 ];
	Visual::Chams::Enable = flCheckboxesCVars[ 13 ];
	Visual::Chams::Player = flCheckboxesCVars[ 14 ];
	Visual::Chams::PlayerOutline = flCheckboxesCVars[ 15 ];
	Visual::Chams::Weapon = flCheckboxesCVars[ 16 ];
	Visual::Chams::WeaponOutline = flCheckboxesCVars[ 17 ];
}
//=================================================
void C_Menu::RenderMiscTab( int x, int y, int w, int h )
{
	static std::string strSliderAA[ 6 ] ={ "Fakelag value","IN_ATTACK value","Blocked Packets","Sent Packets","Spin Speed","Jitter Angle" };
	static float flSliderCVarsAA[ 6 ] ={ Misc::AntiAim::Constant_Force, Misc::AntiAim::InAttackForce,Misc::AntiAim::TicksBlocked, Misc::AntiAim::TicksSent, Misc::AntiAim::Spinspeed ,Misc::AntiAim::JitterAngle };

	static int iSliderMinsAA[ 6 ] ={ 1,1,1,1,1,1 };
	static int iSliderMaxsAA[ 6 ] ={ 15,15,15,15,20,180 };

	for ( size_t i = 0; i < 6; i++ )
	{
		DrawSlider( x + 155, y + 40 + (i-1) * 30, 180, true, flSliderCVarsAA[ i ], iSliderMinsAA[ i ], iSliderMaxsAA[ i ], strSliderAA[ i ].c_str() );
	}

	/*for ( int i = 0; i < 6; i++ )
	{
		if ( i < 3 )
			DrawSlider( x, y + h - 180 + ( i * 20 ) + ( i * 10 ), 180, true, flSliderCVarsAA[ i ], iSliderMinsAA[ i ], iSliderMaxsAA[ i ], strSliderAA[ i ].c_str() );
		else
			if ( !m_bFakeLagCombo && !m_bBuyBotCombo )
			{
				DrawSlider( x + 260, y + h - 210 + ( i * 20 ) - ( 2 * 20 ) - 20 + ( i * 10 ), 180, true, flSliderCVarsAA[ i ], iSliderMinsAA[ i ], iSliderMaxsAA[ i ], strSliderAA[ i ].c_str() );
			}
	}*/

	Misc::AntiAim::Constant_Force = flSliderCVarsAA[ 0 ];
	Misc::AntiAim::InAttackForce = flSliderCVarsAA[ 1 ];
	Misc::AntiAim::TicksBlocked = flSliderCVarsAA[ 2 ];
	Misc::AntiAim::TicksSent = flSliderCVarsAA[ 3 ];
	Misc::AntiAim::Spinspeed = flSliderCVarsAA[ 4 ];
	Misc::AntiAim::JitterAngle = flSliderCVarsAA[ 5 ];

	static int nothing = 0;
	static std::string strCheckboxes[ 8 ] ={ "Bunnyhop", "Autostrafe", "Sv_Cheats Bypass", "Hitsound","Roundsay","Headshotsay","EnableBuyBot" ,"AutoMM" };
	static float flCheckboxesCVars[ 8 ] ={ Misc::Bunnyhop,Misc::AutoStrafer,Misc::Sv_CheatsBypass,Misc::Hitsound,Misc::Roundsay,Misc::HeadshotSay,Misc::BuyBotEnable,Misc::AutoMM };

	for ( int i = 0; i < 8; i++ )
		RenderCheckbox( x, y + ( i * 20 ) + ( i * 5 ), strCheckboxes[ i ], flCheckboxesCVars[ i ] );

	RenderCheckbox( x + 440, y, "Enable AntiAim", Misc::AntiAim::Enable );

	Misc::Bunnyhop = flCheckboxesCVars[ 0 ];
	Misc::AutoStrafer = flCheckboxesCVars[ 1 ];
	Misc::Sv_CheatsBypass = flCheckboxesCVars[ 2 ];
	Misc::Hitsound = flCheckboxesCVars[ 3 ];
	Misc::Roundsay = flCheckboxesCVars[ 4 ];
	Misc::HeadshotSay = flCheckboxesCVars[ 5 ];
	Misc::BuyBotEnable = flCheckboxesCVars[ 6 ];
	Misc::AutoMM = flCheckboxesCVars[ 7 ];
	
	static std::string strComboboxLabelAA[ 10 ] ={ "EdgeMode:", "AntiAim:", "Pitch:", "AA Type:","Fakelag:","BuyBot:" };
	for ( int i = 0; i < 6; i++ )
		Draw.PrintText( fontMenu, x + 350, y + 35 + ( i * 25 ) - 8, Color( 255, 255, 255, 230 ), false, strComboboxLabelAA[ i ].c_str() );


	RenderComboBox( x + 440, y + 25, 180, 20, m_strEdgeMode, Misc::AntiAim::EdgeMode, m_bEdgeModeCombo );
	if ( !m_bEdgeModeCombo )
		RenderComboBox( x + 440, y + 50, 180, 20, m_strAntiAim, Misc::AntiAim::AntiaimType, m_bAntiAimCombo );
	if ( !m_bEdgeModeCombo && !m_bAntiAimCombo )
		RenderComboBox( x + 440, y + 75, 180, 20, m_strPitch, Misc::AntiAim::Pitch, m_bPitchCombo );
	if ( !m_bAntiAimCombo && !m_bPitchCombo && !m_bEdgeModeCombo )
		RenderComboBox( x + 440, y + 100, 180, 20, m_strAntiAimType, Misc::AntiAim::AntiAimMode, m_bAntiAimTypeCombo );
	if ( !m_bAntiAimCombo && !m_bPitchCombo && !m_bAntiAimTypeCombo )
		RenderComboBox( x + 440, y + 125, 180, 20, m_strFakelag, Misc::AntiAim::FakelagMode, m_bFakeLagCombo );
	if ( !m_bAntiAimCombo && !m_bPitchCombo && !m_bAntiAimTypeCombo && !m_bFakeLagCombo )
		RenderComboBox( x + 440, y + 150, 180, 20, m_strBuybot, Misc::BuyBot, m_bBuyBotCombo );

	
}
//=================================================
void ForceFullUpdates()
{
	typedef void( __cdecl *ForceFullUpdate_t )( void );

	ConCommand* cmdFullUpdate = Interface->Cvar()->GetVTable<ICvar>()->FindCommand( "cl_fullupdate" );

	ForceFullUpdate_t ForceUpdate = ( ForceFullUpdate_t ) cmdFullUpdate->m_fnCommandCallback;

	ForceUpdate();
}
//=================================================
void C_Menu::RenderPlayerList( int x, int y, int w, int h )
{

	static int height = 0;
	static int index = 0;
	static int storeupdateX = 0;
	static int storeupdateY = 0;
	static bool pitch_open = false;
	static bool yaw_open = false;
	static bool do_onceX = false;
	static bool do_onceY = false;
	C_MyEntity *pLocal = ( C_MyEntity* ) Interface->EntityList()->GetVTable<IClientEntityList>()->GetClientEntity( Interface->Engine()->GetVTable<IVEngineClient>()->GetLocalPlayer() );

	if ( !pLocal ) return;

	player_info_t pInfo;

	int iHeight = 0;
	height = 0;

	int offset = -20;
	int offset2 = -60;

	for ( int i = 1; i <= Interface->Engine()->GetVTable<IVEngineClient>()->GetMaxClients(); i++ )
	{
		C_MyEntity *pEntity = ( C_MyEntity* ) Interface->EntityList()->GetVTable<IClientEntityList>()->GetClientEntity( i );

		if ( pEntity == pLocal || !pEntity )
			continue;

		if ( !Interface->Engine()->GetVTable<IVEngineClient>()->GetPlayerInfo( i, &pInfo ) )
			continue;

		if ( pLocal->GetTeamNum() == pEntity->GetTeamNum() )
			continue;

		//increase per player
		iHeight += 20;
		height = iHeight;

		//List player names
		Draw.PrintText( fontMenu, x + 30 + offset - 5, y + 20 + offset2 + 5 + 3 + height, Color( 255, 255, 255, 255 ), false, "%s", pInfo.name );

		if ( Mouse.CheckPos( x + 25 + offset - 5, y + 20 + offset2 + 5 + height, 0 + 300, 0 + 30 ) && GetAsyncKeyState( VK_LBUTTON ) )
		{
			PlayerList[ pEntity->GetIndex() ].bPlayerListActive = 1;
			//store entityindex
			index = pEntity->GetIndex();
		}
		if ( pEntity->GetIndex() == index )
		{
			storeupdateX = PlayerList[ pEntity->GetIndex() ].iAAFixX;
			do_onceX = false;
			storeupdateY = PlayerList[ pEntity->GetIndex() ].iAAFixY;
			do_onceY = false;

			//Active player highlight
			Draw.Border( x + 20 + offset - 5, y + 20 + 5 + height + offset2, 300, 0 + 20, Color( 255, 255, 255, 255 ) );

			RenderCheckbox( x + 360 + offset, y + 61 + offset2, "BodyAim", PlayerList[ pEntity->GetIndex() ].flBodyaim );
			RenderCheckbox( x + 360 + offset, y + 86 + offset2, "WhiteList", PlayerList[ pEntity->GetIndex() ].flWhitelist );

			RenderComboBox( x + 360 + offset, y + 116 + offset2, 100, 17, m_strPlayerListPitch, PlayerList[ pEntity->GetIndex() ].iAAFixX, m_bPlayerListPitchCombo );
			if ( !m_bPlayerListPitchCombo )
				RenderComboBox( x + 360 + offset, y + 136 + offset2, 100, 17, m_strPlayerListYaw, PlayerList[ pEntity->GetIndex() ].iAAFixY, m_bPlayerListYawCombo );

			//Ghetto fullupdate to update player angles
			if ( PlayerList[ pEntity->GetIndex() ].iAAFixX != storeupdateX )
			{
				if ( !do_onceX )
				{
					ForceFullUpdates();
					do_onceX = true;
				}
			}
			if ( PlayerList[ pEntity->GetIndex() ].iAAFixY != storeupdateY )
			{
				if ( !do_onceY )
				{
					ForceFullUpdates();
					do_onceY = true;
				}
			}
		}

		//Not same player enymore
		if ( index != pEntity->GetIndex() )
		{
			PlayerList[ pEntity->GetIndex() ].bPlayerListActive = 0;
		}
	}
}
//=================================================
void _FixPos( int& x, int& y, int X, int Y )
{
	x += X;
	y += Y;
}
//=================================================
void _FixSize( int& w, int& h, int W, int H )
{
	w += W;
	h += H;
}
//=================================================
void C_Menu::Drag( int w, int h )
{
	//if( !m_pMouseInput )
	//return;

	static int iXDif = 0;
	static int iYDif = 0;

	int iMousePosition[ 2 ] ={ 0 };

	Interface->Surface()->GetVTable<ISurface>()->SurfaceGetCursorPos( iMousePosition[ 0 ], iMousePosition[ 1 ] );

	int iCurrentPosition[ 2 ] ={ m_iX, m_iY };

	if ( Mouse.CheckPos( iCurrentPosition[ 0 ], iCurrentPosition[ 1 ], w, h ) && GetAsyncKeyState( 1 ) )
	{
		if ( iXDif == -1 || iYDif == -1 )
		{
			iXDif = iMousePosition[ 0 ] - m_iX;
			iYDif = iMousePosition[ 1 ] - m_iY;
		}
		m_iX += iMousePosition[ 0 ] - ( iXDif + iCurrentPosition[ 0 ] );
		m_iY += iMousePosition[ 1 ] - ( iYDif + iCurrentPosition[ 1 ] );
	}
	else
	{
		iXDif = -1;
		iYDif = -1;
	}
}
//=================================================
void C_Menu::SetActive( bool active )
{
	m_bActive = active;

	//if( g_pEngine->IsIngame( ) )
	{
		char pszBuffer[ 0x200 ];
		sprintf_s( pszBuffer, "cl_mouseenable %d", !active );
		Interface->Engine()->GetVTable<IVEngineClient>()->ClientCmd( pszBuffer );
	}
}
//=================================================
void DragWindow( int* x, int* y, const int w, const int h )
{
	static bool isMouseHovering = false;
	static int mousePtr[ 2 ];
	if ( Misc::MenuActive && GetAsyncKeyState( VK_LBUTTON ) )
	{
		if ( Mouse.CheckPos( *x - 3, *y + 2, w + 13, h ) )
		{
			isMouseHovering = true;
		}
	}
	else isMouseHovering = false;

	if ( isMouseHovering )
	{
		*x += ( Mouse.m_info[ X ] - mousePtr[ 0 ] );
		*y += ( Mouse.m_info[ Y ] - mousePtr[ 1 ] );
	}

	mousePtr[ 0 ] = Mouse.m_info[ X ];
	mousePtr[ 1 ] = Mouse.m_info[ Y ];
}
//=================================================
void C_Menu::RenderColor( int x, int y, int w, int h ) {


	//PrintText(fontMenu, x, y + 10 + 25 - 8, Color(255, 255, 255, 230), false, "Element Selection:");

	RenderComboBox( x, y + 160, 180, 20, m_strColourSelector, Visual::Colors::ElementColorSelected, m_bColourSelector );

	static float flSliderCVarsColours[ 3 ];

	static int iSliderMinsColors[ 3 ] ={ 0,0,0 };
	static int iSliderMaxsColors[ 3 ] ={ 255,255,255 };


	static std::string strSliderColours[ 3 ] =
	{ "RED","GREEN","BLUE" };
	switch ( Visual::Colors::ElementColorSelected )
	{
	case 0:

		if ( !m_bColourSelector && !( Mouse.CheckPos( x, y + 190, 180, 20 ) ) && ( GetKeyState( VK_LBUTTON ) & 0x80 ) != 0 )
		{
			Visual::Colors::TRed = flSliderCVarsColours[ 0 ];
			Visual::Colors::TGreen = flSliderCVarsColours[ 1 ];
			Visual::Colors::TBlue = flSliderCVarsColours[ 2 ];
		}
		else
		{
			flSliderCVarsColours[ 0 ] = Visual::Colors::TRed;
			flSliderCVarsColours[ 1 ] = Visual::Colors::TGreen;
			flSliderCVarsColours[ 2 ] = Visual::Colors::TBlue;
		}
		break;
	case 1:

		if ( !m_bColourSelector && !( Mouse.CheckPos( x, y + 190, 180, 20 ) ) && ( GetKeyState( VK_LBUTTON ) & 0x80 ) != 0 )
		{
			Visual::Colors::CTred = flSliderCVarsColours[ 0 ];
			Visual::Colors::CTGreen = flSliderCVarsColours[ 1 ];
			Visual::Colors::CTBlue = flSliderCVarsColours[ 2 ];
		}
		else
		{
			flSliderCVarsColours[ 0 ] = Visual::Colors::CTred;
			flSliderCVarsColours[ 1 ] = Visual::Colors::CTGreen;
			flSliderCVarsColours[ 2 ] = Visual::Colors::CTBlue;
		}
		break;
	case 2:

		if ( !m_bColourSelector && !( Mouse.CheckPos( x, y + 190, 180, 20 ) ) && ( GetKeyState( VK_LBUTTON ) & 0x80 ) != 0 )
		{
			Visual::Colors::ChamsTRed = flSliderCVarsColours[ 0 ];
			Visual::Colors::ChamsTGreen = flSliderCVarsColours[ 1 ];
			Visual::Colors::ChamsTBlue = flSliderCVarsColours[ 2 ];
		}
		else
		{
			flSliderCVarsColours[ 0 ] = Visual::Colors::ChamsTRed;
			flSliderCVarsColours[ 1 ] = Visual::Colors::ChamsTGreen;
			flSliderCVarsColours[ 2 ] = Visual::Colors::ChamsTBlue;
		}
		break;
	case 3:

		if ( !m_bColourSelector && !( Mouse.CheckPos( x, y + 190, 180, 20 ) ) && ( GetKeyState( VK_LBUTTON ) & 0x80 ) != 0 )
		{
			Visual::Colors::ChamsCTRed = flSliderCVarsColours[ 0 ];
			Visual::Colors::ChamsCTGreen = flSliderCVarsColours[ 1 ];
			Visual::Colors::ChamsCTBlue = flSliderCVarsColours[ 2 ];
		}
		else
		{
			flSliderCVarsColours[ 0 ] = Visual::Colors::ChamsCTRed;
			flSliderCVarsColours[ 1 ] = Visual::Colors::ChamsCTGreen;
			flSliderCVarsColours[ 2 ] = Visual::Colors::ChamsCTBlue;
		}
		break;
	case 4:

		if ( !m_bColourSelector && !( Mouse.CheckPos( x, y + 190, 180, 20 ) ) && ( GetKeyState( VK_LBUTTON ) & 0x80 ) != 0 )
		{
			Visual::Colors::WhiteListRED = flSliderCVarsColours[ 0 ];
			Visual::Colors::WhiteListGreen = flSliderCVarsColours[ 1 ];
			Visual::Colors::WhiteListBlue = flSliderCVarsColours[ 2 ];
		}
		else
		{
			flSliderCVarsColours[ 0 ] = Visual::Colors::WhiteListRED;
			flSliderCVarsColours[ 1 ] = Visual::Colors::WhiteListGreen;
			flSliderCVarsColours[ 2 ] = Visual::Colors::WhiteListBlue;
		}
		break;
	case 5:

		if ( !m_bColourSelector && !( Mouse.CheckPos( x, y + 190, 180, 20 ) ) && ( GetKeyState( VK_LBUTTON ) & 0x80 ) != 0 )
		{
			Visual::Colors::AimspotRed = flSliderCVarsColours[ 0 ];
			Visual::Colors::AimspotGreen = flSliderCVarsColours[ 1 ];
			Visual::Colors::AimspotBlue = flSliderCVarsColours[ 2 ];
		}
		else
		{
			flSliderCVarsColours[ 0 ] = Visual::Colors::AimspotRed;
			flSliderCVarsColours[ 1 ] = Visual::Colors::AimspotGreen;
			flSliderCVarsColours[ 2 ] = Visual::Colors::AimspotBlue;
		}
		break;
	case 6:

		if ( !m_bColourSelector && !( Mouse.CheckPos( x, y + 190, 180, 20 ) ) && ( GetKeyState( VK_LBUTTON ) & 0x80 ) != 0 )
		{
			Visual::Colors::CrosshairRed = flSliderCVarsColours[ 0 ];
			Visual::Colors::CrosshairGreen = flSliderCVarsColours[ 1 ];
			Visual::Colors::CrosshairBlue = flSliderCVarsColours[ 2 ];
		}
		else
		{
			flSliderCVarsColours[ 0 ] = Visual::Colors::CrosshairRed;
			flSliderCVarsColours[ 1 ] = Visual::Colors::CrosshairGreen;
			flSliderCVarsColours[ 2 ] = Visual::Colors::CrosshairBlue;
		}
		break;
	case 7:

		if ( !m_bColourSelector && !( Mouse.CheckPos( x, y + 190, 180, 20 ) ) && ( GetKeyState( VK_LBUTTON ) & 0x80 ) != 0 )
		{
			Visual::Colors::MenuRed = flSliderCVarsColours[ 0 ];
			Visual::Colors::MenuGreen = flSliderCVarsColours[ 1 ];
			Visual::Colors::MenuBlue = flSliderCVarsColours[ 2 ];
		}
		else
		{
			flSliderCVarsColours[ 0 ] = Visual::Colors::MenuRed;
			flSliderCVarsColours[ 1 ] = Visual::Colors::MenuGreen;
			flSliderCVarsColours[ 2 ] = Visual::Colors::MenuBlue;
		}
		break;
	case 8:

		if ( !m_bColourSelector && !( Mouse.CheckPos( x, y + 190, 180, 20 ) ) && ( GetKeyState( VK_LBUTTON ) & 0x80 ) != 0 )
		{
			Visual::Colors::CursorRed = flSliderCVarsColours[ 0 ];
			Visual::Colors::CursorGreen = flSliderCVarsColours[ 1 ];
			Visual::Colors::CursorBlue = flSliderCVarsColours[ 2 ];
		}
		else
		{
			flSliderCVarsColours[ 0 ] = Visual::Colors::CursorRed;
			flSliderCVarsColours[ 1 ] = Visual::Colors::CursorGreen;
			flSliderCVarsColours[ 2 ] = Visual::Colors::CursorBlue;
		}
		break;
	}


	//for (int i = 0; i < 3; i++)
	DrawSlider( x + 250, y + h - 210 + ( 0 * 25 ) + ( 0 * 8 ), true, flSliderCVarsColours[ 0 ], iSliderMinsColors[ 0 ], iSliderMaxsColors[ 0 ], strSliderColours[ 0 ].c_str(),
		Color( 255, 0, 0, 255 ) );

	DrawSlider( x + 250, y + h - 210 + ( 1 * 25 ) + ( 1 * 8 ), true, flSliderCVarsColours[ 1 ], iSliderMinsColors[ 1 ], iSliderMaxsColors[ 1 ], strSliderColours[ 1 ].c_str(),
		Color( 0, 255, 0, 255 ) );

	DrawSlider( x + 250, y + h - 210 + ( 2 * 25 ) + ( 2 * 8 ), true, flSliderCVarsColours[ 2 ], iSliderMinsColors[ 2 ], iSliderMaxsColors[ 2 ], strSliderColours[ 2 ].c_str(),
		Color( 0, 0, 255, 255 ) );
	if ( !m_bColourSelector )
		Draw.RectOutlined( x, y + 195, 180, 60, 1, Color( flSliderCVarsColours[ 0 ], flSliderCVarsColours[ 1 ], flSliderCVarsColours[ 2 ], 255 ), Color( 0, 0, 0, 230 ) );

}
//=================================================
void C_Menu::RenderCredits( int x, int y, int w, int h )
{
	Draw.PrintText( fontMenu, x + w / 2, y, Color( 255, 255, 255, 255 ), true, "Credits : phoon / priority / sinister / kamay" );
}
//=================================================
void C_Menu::Render( void )
{

	int w = 640, h = 425; //640
	
	Draw.RectOutlined( Misc::Menu_X, Misc::Menu_Y, w, h, 1, Color( 40, 40, 40, 220 ), Color( 0, 0, 0 ) );
	Draw.RectOutlined( Misc::Menu_X + 5, Misc::Menu_Y + 75, w - 10, h - 80, 1, Color( 10, 10, 10, 220 ), Color( 0, 0, 0 ) );
	Draw.RectOutlined( Misc::Menu_X + 5, Misc::Menu_Y + 35, w - 10, 40, 1, Color( 10, 10, 10, 220 ), Color( 0, 0, 0 ) );

	Draw.GardientRect( Misc::Menu_X + 5, Misc::Menu_Y + 75, (w - 10) / 2, 3, Color( 0, 160, 255, 200 ), Color( 160, 0, 255, 230 ), 1 );
	Draw.GardientRect( Misc::Menu_X + 5 + ( w - 10 ) / 2, Misc::Menu_Y + 75, ( w - 10 ) / 2, 3, Color( 160, 0, 255, 200 ), Color( 255, 255, 0, 230 ), 1 );

	Draw.PrintText( fontMenu, Misc::Menu_X + w / 2, Misc::Menu_Y + 15, Color( 255, 255, 255, 255 ), true, "creds to: phoon/priority - sinister - kamay" );

	static float tabsize = (w - 10) / 4;
	static char* strTabs[ 1 ] ={ "AIMBOT", "VISUALS", "MISC",  "PLAYERLIST" };

	for ( size_t n = 0; n < 4; n++ )
	{
		Draw.FillRGBA( Misc::Menu_X + tabsize * n, Misc::Menu_Y + 35, 1, 40, Color( 0, 0, 0 ) );
		if ( Mouse.CheckPos( Misc::Menu_X + tabsize * n, Misc::Menu_Y + 35, tabsize, 40 ) && GetAsyncKeyState( VK_LBUTTON ) & 1 )
			m_iCurrentTap = n;
	}

	for ( size_t n = 1; n < 5; n++ )
	{
		if ( n -1 == m_iCurrentTap )
			Draw.PrintText( fontMenu, Misc::Menu_X + tabsize * n - ( tabsize / 2 ), Misc::Menu_Y + 50, Color( 20, 70, 145, 255 ), true, strTabs[ n - 1 ] );
		else
			Draw.PrintText( fontMenu, Misc::Menu_X + tabsize * n - ( tabsize / 2 ), Misc::Menu_Y + 50, Color( 255, 255, 255, 255 ), true, strTabs[ n - 1 ] );
	}

	switch ( m_iCurrentTap )
	{
	case 0:
		RenderAimbotTab( Misc::Menu_X + 10, Misc::Menu_Y + 85, w - 20, h );
		break;
	case 1:
		RenderVisualsTab( Misc::Menu_X + 10, Misc::Menu_Y + 85, w - 20, h );
		RenderColor( Misc::Menu_X + 10, Misc::Menu_Y + 85, w - 20, h );
		break;
	case 2:
		RenderAimbotTab( Misc::Menu_X + 10, Misc::Menu_Y + 85, w - 20, h );
		break;
	case 3:
		RenderAimbotTab( Misc::Menu_X + 10, Misc::Menu_Y + 85, w - 20, h );
		break;
	}

	DragWindow( &Misc::Menu_X, &Misc::Menu_Y, w, 20 );
	Mouse.Process( Mouse.m_info[ X ], Mouse.m_info[ Y ] );
	Mouse.Handle( Mouse.m_info[ X ], Mouse.m_info[ Y ], &Mouse );
}
//=================================================
void C_Menu::SetPosition( int x, int y )
{
	m_iX = x;
	m_iY = y;
}

C_Menu gMenu;