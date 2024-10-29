#pragma once

#include <iostream>

class GameObject {
public:
	enum { kClassId = 'GOBJ' };
	virtual uint32_t GetClassId() const { return kClassId; }
	static GameObject* CreateInstance() { return new GameObject(); }
};