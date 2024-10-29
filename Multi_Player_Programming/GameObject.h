#pragma once

#include <iostream>

#include "OutputMemoryBitStream.h"

class GameObject {
public:
	enum { kClassId = 'GOBJ' };
	virtual uint32_t GetClassId() const { return kClassId; }
	static GameObject* CreateInstance() { return new GameObject(); }

	virtual void Write(OutputMemoryBitStream& inStream) {

	}
	void Destroy() {}
};