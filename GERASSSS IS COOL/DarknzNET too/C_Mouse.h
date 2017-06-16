#include "main.h"

enum
{
	NEUTRAL = 0,
	PRESSED,
	RELEASED
};


enum
{
	X,
	Y,
	VECTOR2D
};

enum
{
	W = 2,
	H,
	RECTANGLE
};



class C_Mouse
{
public:
	C_Mouse(void);

	virtual void Handle(int x, int y, C_Mouse *Mouse);

	bool IsWithin(int x, int y, int w, int h, int state);

	bool CheckPos(int x, int y, int w, int h);

	void Process(int x, int y);

	int m_info[RECTANGLE];

	int m_base[VECTOR2D];

	int m_state;

private:

	void UpdateCusorPosition(void);
};

extern C_Mouse Mouse;



