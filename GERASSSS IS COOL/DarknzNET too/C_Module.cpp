#include "main.h"

SSectionData::SSectionData(char *name, DWORD start, DWORD end)
{
	m_name = name;
	m_start = start;
	m_end = end;
	m_size = (end - start);
}
//=================================================
C_Module::C_Module(HMODULE module)
{
	m_module = module;

	m_dos = (IMAGE_DOS_HEADER*)(m_module);
	if (m_dos->e_magic != IMAGE_DOS_SIGNATURE)
	{
		m_module = 0;
		return;
	}

	m_nt = (IMAGE_NT_HEADERS*)((DWORD)m_dos + m_dos->e_lfanew);
	if (m_nt->Signature != IMAGE_NT_SIGNATURE)
	{
		m_module = 0;
		return;
	}
	DumpSectionData();
}
//=================================================
C_Module::~C_Module(void)
{
	for each (SSectionData *section in m_sections)
	{
		delete section;
	}

	m_sections.clear();
}
//=================================================
void C_Module::Process(void)
{
	if (m_module)
	{
		Morph();
		EraseHeader();
		Unlink();
		EraseImports();
	}
}
//=================================================
bool C_Module::DumpSectionData(void)
{
	IMAGE_SECTION_HEADER *sections = (IMAGE_SECTION_HEADER*)((DWORD)m_nt + (m_nt->FileHeader.SizeOfOptionalHeader + 0x18));

	for (int i = 0; i < m_nt->FileHeader.NumberOfSections; ++i)
	{
		IMAGE_SECTION_HEADER *cur = &sections[i];

		if (!cur
			|| !cur->Name
			|| !cur->VirtualAddress
			|| !cur->SizeOfRawData)
		{
			continue;
		}

		DWORD start = ((DWORD)m_module + cur->VirtualAddress);
		m_sections.push_back(new SSectionData((char*)(cur->Name), start, (start + cur->SizeOfRawData)));
	}

	return true;
}
//=================================================
void C_Module::RandomizeSection(SSectionData *section)
{
	MEMORY_BASIC_INFORMATION mbi;

	// remove page protection so we can write
	VirtualQuery((void*)(section->m_start), &mbi, sizeof(mbi));
	VirtualProtect(mbi.BaseAddress, mbi.RegionSize, PAGE_EXECUTE_READWRITE, &mbi.Protect);

	BYTE *page = (BYTE*)(section->m_start);

	for (int i = 0; i < section->m_size; ++i)
	{
		BYTE *cur = (page + i);
		for (; *cur == 0xCC; ++cur);
		DWORD end = (DWORD)cur;
		int count = (end - (DWORD)(page + i));
		bool isPageAlignment = ((end % 0x10) == 0);

		if ((count > 1) || isPageAlignment)
		{
			for (int byte = 1; byte < count; ++byte)
			{
				srand((GetTickCount() * i) * (rand() % 0xFFFFFF) * (GetTickCount() * byte) * (DWORD)page);// Big nosed faggot
				page[i + byte] = (rand() % 0xFF);
			}
		}
	}
	VirtualProtect(mbi.BaseAddress, mbi.RegionSize, mbi.Protect, 0);
	FlushInstructionCache(GetCurrentProcess(), (void*)(section->m_start), section->m_size);
}
//=================================================
void C_Module::Morph(void)
{
	for each (SSectionData *section in m_sections)
	{
		RandomizeSection(section);
	}
}
//=================================================
void C_Module::EraseHeader(void)
{
	Memory::Zero(m_module, m_nt->OptionalHeader.SizeOfHeaders);
}
//=================================================
void C_Module::Unlink(void)
{
	PEB_LDR_DATA *ldrdata = (PEB_LDR_DATA*)(Memory::GetProcessModuleInfo());

	LDR_MODULE *ldr = (LDR_MODULE*)(ldrdata->InLoadOrderModuleList.Flink);


	// find our module's LDR_MODULE object
	while (ldr->Baseintess && (ldr->Baseintess != m_module))
	{
		ldr = (LDR_MODULE*)(ldr->InLoadOrderModuleList.Flink);
	}


	// unlink from lists
	ldr->InLoadOrderModuleList.Blink->Flink = ldr->InLoadOrderModuleList.Flink;
	ldr->InLoadOrderModuleList.Flink->Blink = ldr->InLoadOrderModuleList.Blink;

	ldr->InInitializationOrderModuleList.Blink->Flink = ldr->InInitializationOrderModuleList.Flink;
	ldr->InInitializationOrderModuleList.Flink->Blink = ldr->InInitializationOrderModuleList.Blink;

	ldr->InMemoryOrderModuleList.Blink->Flink = ldr->InMemoryOrderModuleList.Flink;
	ldr->InMemoryOrderModuleList.Flink->Blink = ldr->InMemoryOrderModuleList.Blink;

	ldr->HashTableEntry.Blink->Flink = ldr->HashTableEntry.Flink;
	ldr->HashTableEntry.Flink->Blink = ldr->HashTableEntry.Blink;


	Memory::Zero(ldr->FullDllName.Buffer, ldr->FullDllName.Length);
	Memory::Zero(ldr->BaseDllName.Buffer, ldr->BaseDllName.Length);
	Memory::Zero(ldr, sizeof(LDR_MODULE));
}
//=================================================
void C_Module::EraseImports(void)
{
	IMAGE_IMPORT_DESCRIPTOR *imports = (IMAGE_IMPORT_DESCRIPTOR*)((DWORD)m_module + m_nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);

	while (imports->Characteristics)
	{
		if (!IsBadReadPtr((void*)((DWORD)m_module + imports->Name), 1))
		{
			char *module = (char*)((DWORD)m_module + imports->Name);
			Memory::Zero(module, strlen(module));

			IMAGE_THUNK_DATA *table = (IMAGE_THUNK_DATA*)((DWORD)m_module + imports->OriginalFirstThunk);

			while (table->u1.Function)
			{
				IMAGE_IMPORT_BY_NAME *import = (IMAGE_IMPORT_BY_NAME*)((DWORD)m_module + table->u1.AddressOfData);

				if (!IsBadReadPtr(import, sizeof(IMAGE_IMPORT_BY_NAME)))
				{
					Memory::Zero(import->Name, strlen(import->Name));
					++table;
				}
				else
				{
					import = (IMAGE_IMPORT_BY_NAME*)(table);
					++import;

					table = (IMAGE_THUNK_DATA*)(import);
				}
			}
			
			imports = (IMAGE_IMPORT_DESCRIPTOR*)((DWORD)imports + sizeof(IMAGE_IMPORT_DESCRIPTOR));
		}
		else
		{
			break;
		}
	}
}