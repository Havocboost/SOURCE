#ifndef __MENU_H__
#define __MENU_H__

#ifdef _MSC_VER
#pragma once
#endif

#include "main.h"


class C_Menu
{
private:
	bool			m_bActive;
	bool			m_bAimHitboxCombo;
	bool			m_bTeamCheckCombo;
	bool			m_bSelected;
	bool			m_bBuyBotCombo;
	bool			m_bPosAdjusmentCombo;
	bool			m_bTargetSelectionCombo;
	bool			m_bAimHitscanCombo;
	bool			m_bAimSilentCombo;
	bool			m_bVisBoxCombo;
	bool			m_bVisWeaponsCombo;
	bool			m_bVisHandsCombo;
	bool			m_bVisChamsCombo;
	bool			m_bEdgeModeCombo;
	bool			m_bAntiAimCombo;
	bool			m_bPitchCombo;
	bool			m_bAntiAimTypeCombo;
	bool			m_bFakeLagCombo;
	bool			m_bPlayerListPitchCombo;
	bool			m_bPlayerListYawCombo;
	bool			m_bInaccuracy;
	//color combosss
	bool			m_bEspTerroristColor;
	bool			m_bEspCTColor;
	bool			m_bChamsTerroristColor;
	bool			m_bChamsCTColor;
	bool			m_bWhitelistColor;
	bool			m_bAimspotlineColor;
	bool			m_bCrosshairColor;
	bool			m_bMenuColor;
	bool			m_bCursorColor;
	bool			m_bColourSelector;
	int				m_iX;
	int				m_iY;
	int				m_iW;
	int				m_iH;

	std::vector< std::string >	m_strHitboxes;
	std::vector< std::string >	m_strTargetSelection;
	std::vector< std::string >	m_strHitscans;
	std::vector< std::string >	m_strTeamCheck;
	std::vector< std::string >	m_strAimbotSelected;
	std::vector< std::string >	m_strInaccuracy;
	std::string					m_strCurrentInput;
	std::vector< std::string >	m_strHistory;
	std::vector< std::string >	m_strVisBoxes;
	std::vector< std::string >	m_strVisWeapons;
	std::vector< std::string >	m_strVisHands;
	std::vector< std::string >	m_strVisChams;
	std::vector< std::string >	m_strColors;
	std::vector< std::string >	m_strBuybot;
	std::vector< std::string >	m_strPosAdjusment;
	std::vector< std::string >	m_strEdgeMode;
	std::vector< std::string >	m_strAntiAim;
	std::vector< std::string >	m_strPitch;
	std::vector< std::string >	m_strAntiAimType;
	std::vector< std::string >	m_strFakelag;

	std::vector< std::string >	m_strPlayerListPitch;
	std::vector< std::string >	m_strPlayerListYaw;
	std::vector< std::string >	m_strColourSelector;

	int				m_iCurrentTap;
private:
	void Echo(const char* fmt, ...);
	void FilterArgs(std::string strInput, std::vector< std::string >& strArgs);
	void HandleInput(std::string strInput);
	void RenderTab(int x, int y, int w, int h, std::string strText, int iIndex, int& iStatus);
	void RenderCheckbox(int x, int y, std::string strText, float &cvar);
	void RenderSlider(int x, int y, int w, int h, std::string strText, float &cvar, int min, int max);
	void RenderComboBox(int x, int y, int w, int h, std::vector< std::string > strNotes, int &cvar, bool& bState);
	
	void Drag(int w, int h);
	void RenderPlayerList(int x, int y, int w, int h);

	void RenderAimbotTab(int x, int y, int w, int h);
	void RenderVisualsTab(int x, int y, int w, int);
	void RenderMiscTab(int x, int y, int w, int h);
	void RenderColor(int x, int y, int w, int h);
	void RenderCredits(int x, int y, int w, int h);

public:
	C_Menu(void);
	~C_Menu(void);

	void SetActive(bool active);
	void HandleInputChar(int iKey);
	void Render(void);
	void SetPosition(int x, int y);
};

extern C_Menu gMenu;

#endif