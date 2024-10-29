#pragma once

#include <vector>

#include "OutputMemoryBitStream.h"
#include "GameObject.h"
#include "LinkingContext.h"

class ReplicationManager {
public:
	enum PacketType
	{
		PT_Hello,
		PT_ReplicationData,
		PT_Disconnect,
		PT_MAX
	};

	void ReplicateWorldState(OutputMemoryBitStream& inStream,
		const std::vector<GameObject*>& inAllObjects);

private:
	void ReplicateIntoStream(OutputMemoryBitStream& inStream,
		GameObject* inGameObject);

	LinkingContext* mLinkingContext;
};

