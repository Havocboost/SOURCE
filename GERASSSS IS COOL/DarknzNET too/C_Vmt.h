#pragma once
#include "main.h"


class CVMT
{
	CVMT(const CVMT &other);
	CVMT &operator=(const CVMT &other);

public:

	// sets members and performs actual hooking
	CVMT(void *instance, bool shouldHook = false);


	// cleanup
	virtual ~CVMT(void);


	bool UnHook(void);


	bool ReHook(void);


	// overwrites a function in m_modified
	void HookMethod(void *function, int index);


	// returns the m_instance (the thisptr)  ca devrait tre bon ca?
	void *thisptr(void);


	// we need templated function definitions inside the class :/
	// returns the function at the given index in the original vtable
	template<typename TYPE>
	__forceinline TYPE GetOriginalMethod(int index)
	{
		return (TYPE)(m_original[index]);
	}


	// returns the the vtable casted to a sdk defined class
	template<class TYPE>
	__forceinline TYPE *GetVTable(void) const
	{
		return (TYPE*)(m_instance);
	}


private:

	// counts the size of the vtable
	bool CountTable(void **vtable);


	// instance of the interface
	void	***m_instance;

	// the game's original allocated vtable
	void	**m_original;

	// our own allocated vtable
	void	**m_modified;

	// size of vtable
	int		m_size;

	bool	m_isHooked;
};