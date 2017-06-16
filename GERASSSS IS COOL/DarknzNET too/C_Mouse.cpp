#include "main.h"


C_Mouse Mouse;

C_Mouse::C_Mouse(void)
{
	m_state = NEUTRAL;
}
//=================================================
Color outerBorder(0, 0, 0, 255);
//=================================================
// b2k5's Mouse.
void C_Mouse::Handle(int x, int y, C_Mouse *Mouse)
{
	int position[VECTOR2D] = { (m_info[X]), (m_info[Y]) };
	Draw.FillRGBA(position[X], position[Y], 1, 1, outerBorder);
	Draw.FillRGBA(position[X], (position[Y] + 1), 2, 1, outerBorder);

	for (int i = 0; i <= 8; ++i)
	{
		Draw.FillRGBA(position[X], ((position[Y] + 1) + i), 1, 1, outerBorder);
		Draw.FillRGBA((position[X] + 1), ((position[Y] + 1) + i), i, 1, Color(150, 20, 20, 230));
		Draw.FillRGBA(((position[X] + 1) + i), ((position[Y] + 1) + i), 1, 1, outerBorder);
	}

	Draw.FillRGBA(position[X], (position[Y] + 10), 1, 1, outerBorder);
	Draw.FillRGBA((position[X] + 1), (position[Y] + 10), 3, 1, Color(150, 20, 20, 230));
	Draw.FillRGBA((position[X] + 4), (position[Y] + 10), 7, 1, outerBorder);
	Draw.FillRGBA(position[X], (position[Y] + 11), 1, 1, outerBorder);
	Draw.FillRGBA((position[X] + 1), (position[Y] + 11), 2, 1, Color(150, 20, 20, 230));
	Draw.FillRGBA((position[X] + 3), (position[Y] + 11), 1, 1, outerBorder);
	Draw.FillRGBA(position[X], (position[Y] + 12), 1, 1, outerBorder);
	Draw.FillRGBA((position[X] + 1), (position[Y] + 12), 1, 1, Color(150, 20, 20, 230));
	Draw.FillRGBA((position[X] + 2), (position[Y] + 12), 1, 1, outerBorder);
	Draw.FillRGBA(position[X], (position[Y] + 13), 2, 1, outerBorder);
	Draw.FillRGBA(position[X], (position[Y] + 14), 1, 1, outerBorder);

}
//=================================================
bool C_Mouse::IsWithin(int x, int y, int w, int h, int state)
{
	return ((m_info[X] >= x)
		&& (m_info[Y] >= y)
		&& (m_info[X] < (x + w))
		&& (m_info[Y] < (y + h))
		&& (m_state == state));
}
//=================================================
void C_Mouse::Process(int x, int y)
{
	m_base[X] = x;
	m_base[Y] = y;

	UpdateCusorPosition();
}
//=================================================
bool C_Mouse::CheckPos(int x, int y, int w, int h)
{
	int position[VECTOR2D] = { (m_info[X]), (m_info[Y]) };
	return(position[X] > x && w + x > position[X] && position[Y] > y && h + y > position[Y]);
}
//=================================================
void C_Mouse::UpdateCusorPosition(void)
{
	int screensize[VECTOR2D];
	Interface->Engine()->GetVTable<IVEngineClient>()->GetScreenSize(screensize[X], screensize[Y]);
	
	int point[VECTOR2D];

	Interface->Surface()->GetVTable<ISurface>()->SurfaceGetCursorPos(point[0], point[1]);

	m_info[X] = (point[0]);
	m_info[Y] = (point[1]);


	if (Misc::MenuActive)
	{
		if (m_info[X] > (screensize[X]))
		{
			m_info[X] = (screensize[X]);
		}
		else if (m_info[X] < (0))
		{
			m_info[X] = (0);
		}


		if (m_info[Y] > (screensize[Y] ))
		{
			m_info[Y] = (screensize[Y]);
		}
		else if (m_info[Y] < (0 ))
		{
			m_info[Y] = (0 );
		}
	}
	

}