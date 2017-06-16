#include "C_Utils.h"
C_Utils Utils;
//=================================================
void C_Utils::Log(const char* Message, ...)
{
	va_list list;
	char buffer[0xFFFF];
	va_start(list, Message);
	_vsnprintf_s(buffer, 0xFFFF, Message, list);
	va_end(list);

	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), buffer, strlen(buffer), 0, 0);
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), "\n", strlen("\n"), 0, 0);
}
//=================================================
void C_Utils::Log(DWORD Color, const char* Message, ...)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY
		| Color);

	va_list list;
	char buffer[0xFFFF];
	va_start(list, Message);
	_vsnprintf_s(buffer, 0xFFFF, Message, list);
	va_end(list);

	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), buffer, strlen(buffer), 0, 0);
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), "\n", strlen("\n"), 0, 0);
}
//=================================================
float C_Utils::GetHitgroupModifiedDamage(float dmg, int hitgroup)
{
	static float hitgroupModifiers[] = { 1.f, 4.f, 1.f, 1.25f, 1.f, 1.f, .75f, .75f };
	return (dmg * hitgroupModifiers[hitgroup]);
}
