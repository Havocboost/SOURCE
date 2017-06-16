#pragma once
#pragma once


#include "main.h"

struct SSectionData
{
	// fills out data in the struct
	SSectionData(char *name, DWORD start, DWORD end);


	char	*m_name;

	DWORD	m_start;

	DWORD	m_end;

	DWORD	m_size;
};


class C_Module
{
public:

	// sets the module
	C_Module(HMODULE module);


	// cleanup
	virtual ~C_Module(void);


	// process the module
	void Process(void);


public:

	// finds all sections and push their data onto m_sections
	bool DumpSectionData(void);


	// scans for INT 3 (0xCC) in a section, and randomizes them
	void RandomizeSection(SSectionData *section);


	// loops through all section's data, and calls RandomizeSection on them
	void Morph(void);


	// erase the dos header
	void EraseHeader(void);


	// unlinks our module, and erases the LDR_MODULE object
	void Unlink(void);


	// erases strings in the import table
	void EraseImports(void);


	std::vector<SSectionData*>	m_sections;
	HMODULE						m_module;
	IMAGE_DOS_HEADER			*m_dos;
	IMAGE_NT_HEADERS			*m_nt;
};