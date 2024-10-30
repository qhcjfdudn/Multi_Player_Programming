#pragma once

#include <iostream>

#include "OutputMemoryBitStream.h"
#include "InputMemoryBitStream.h"

class GameObject {
public:
	enum { kClassId = 'GOBJ' };
	virtual uint32_t GetClassId() const { return kClassId; }
	static GameObject* CreateInstance() { return new GameObject(); }

	virtual void Write(OutputMemoryBitStream& inStream) {

	}
	virtual void Read(InputMemoryBitStream& inStream) {

	}
	void Destroy() {}
};