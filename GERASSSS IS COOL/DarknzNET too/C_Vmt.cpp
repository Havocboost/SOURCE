#include "C_Vmt.h"
// sets members and performs actual hooking
CVMT::CVMT(void *instance, bool shouldHook)
{
	m_instance = (void***)(instance);
	m_original = *m_instance;


	if (!CountTable(m_original))
	{
		//LOG_ERROR( "Failed counting table at [%X], shouldHook = %i", (DWORD)instance, (int)shouldHook );
		return;
	}


	m_modified = (void**)(malloc((m_size + 3) * sizeof(void*)));
	m_modified[2] = m_original[-1];


	for (int index = 0; index < m_size; ++index)
	{
		m_modified[index + 3] = m_original[index];
	}


	m_isHooked = shouldHook;
	if (m_isHooked)
	{
		*m_instance = (m_modified + 3);
	}
}
//=================================================
CVMT::~CVMT(void)
{
	free(m_modified);
	m_modified = 0;
}
//=================================================
bool CVMT::UnHook(void)
{
	if (m_isHooked && m_instance)
	{
		*m_instance = m_original;
		m_isHooked = false;
	}

	return (m_instance && !m_isHooked);
}
//=================================================
bool CVMT::ReHook(void)
{
	if (!m_isHooked && m_instance)
	{
		*m_instance = (m_modified + 3);
		m_isHooked = true;
	}

	return (m_instance && m_isHooked);
}
//=================================================
bool CVMT::CountTable(void **vtable)
{
	m_size = -1;

	for (; !IsBadCodePtr((FARPROC)vtable[m_size]); ++m_size);

	return (m_size > -1);
}
//=================================================
void CVMT::HookMethod(void *function, int index)
{
	m_modified[index + 3] = function;
}
//=================================================
void *CVMT::thisptr(void)
{
	return m_instance;
}