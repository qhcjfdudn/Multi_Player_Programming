#pragma once
#include "GameObject.h"

class RoboCat : public GameObject {
public:
	enum { kClassId = 'RBCT' };
	virtual uint32_t GetClassId() const { return kClassId; }
	static GameObject* CreateInstance() { return new RoboCat(); }
};