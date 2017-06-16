#include "main.h"


C_Netvars *Netvars = 0;


C_Netvars::C_Netvars(void)
{
	m_tables.clear();
	
	ClientClass *clientClass = Interface->Client()->GetVTable<IBaseClientDLL>()->GetAllClasses();

	if (!clientClass)
	{
		Utils.Log("ClientClass was not found");
		return;
	}

	while (clientClass)
	{
		RecvTable *recvTable = clientClass->m_pRecvTable;
		m_tables.push_back(recvTable);
		clientClass = clientClass->m_pNext;
	}
}
//=================================================
int C_Netvars::GetOffset(const char *tableName, const char *propName)
{
	int offset = GetProp(tableName, propName);

	if (!offset)
	{
		Utils.Log("Failed to find offset for prop: %s from table: %s", propName, tableName);
		return 0;
	}

	return offset;
}



//=================================================
RecvVarProxyFn C_Netvars::HookProp(const char *tableName, const char *propName, RecvVarProxyFn function)
{
	RecvProp *recvProp = 0;

	if (!GetProp(tableName, propName, &recvProp))
	{
		Utils.Log("Failed to hook prop: %s from table: %s", propName, tableName);
		return 0;
	}


	RecvVarProxyFn old = recvProp->m_ProxyFn;
	recvProp->m_ProxyFn = function;

	return old;
}

//=================================================
int C_Netvars::GetProp(const char *tableName, const char *propName, RecvProp **prop)
{
	RecvTable *recvTable = GetTable(tableName);

	if (!recvTable)
	{
		Utils.Log("Failed to find table: %s", tableName);
		return 0;
	}


	int offset = GetProp(recvTable, propName, prop);

	if (!offset)
	{
		Utils.Log("Failed to find prop: %s from table: %s", propName, tableName);
		return 0;
	}


	return offset;
}
//=================================================
int C_Netvars::GetProp(RecvTable *recvTable, const char *propName, RecvProp **prop)
{
	int extraOffset = 0;

	for (int i = 0; i < recvTable->m_nProps; ++i)
	{
		RecvProp *recvProp = &recvTable->m_pProps[i];

		RecvTable *child = recvProp->m_pDataTable;

		if (child
			&& (child->m_nProps > 0))
		{
			int tmp = GetProp(child, propName, prop);

			if (tmp)
			{
				extraOffset += (recvProp->m_Offset + tmp);
			}
		}


		// do this for all used props that are two of in 1 datatable
		if (!stricmp(propName, "m_flStamina") && stricmp(recvTable->m_pNetTableName, "DT_CSLocalPlayerExclusive"))
		{
			continue;
		}

		if (stricmp(recvProp->m_pVarName, propName))
		{
			continue;
		}

		if (prop && !*prop)
		{
			*prop = recvProp;
		}
		
		return (recvProp->m_Offset + extraOffset);
	}

	return extraOffset;
}
//=================================================
RecvTable *C_Netvars::GetTable(const char *tableName)
{
	if (m_tables.empty())
	{
		Utils.Log("Failed to find table: %s (m_tables is empty)", tableName);
		return 0;
	}


	for each (RecvTable *table in m_tables)
	{
		if (!table)
		{
			continue;
		}


		if (stricmp(table->m_pNetTableName, tableName) == 0)
		{
			return table;
		}
	}

	return 0;
}