#pragma once

#include <vector>
#include <unordered_set>

#include "OutputMemoryBitStream.h"
#include "InputMemoryBitStream.h"
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
	void ReceiveWorld(InputMemoryBitStream& inStream);

	void ReplicateCreate(OutputMemoryBitStream& inStream,
		GameObject* inGameObject);
	void ReplicateUpdate(OutputMemoryBitStream& inStream,
		GameObject* inGameObject);
	void ReplicateDestroy(OutputMemoryBitStream& inStream,
		GameObject* inGameObject);
	void ProcessReplicationAction(InputMemoryBitStream& inStream);

private:
	void ReplicateIntoStream(OutputMemoryBitStream& inStream,
		GameObject* inGameObject);

	GameObject* ReceiveReplicatedObject(InputMemoryBitStream& inStream);

	LinkingContext* mLinkingContext;

	std::unordered_set<GameObject*> mObjectsReplicatedToMe;
};

