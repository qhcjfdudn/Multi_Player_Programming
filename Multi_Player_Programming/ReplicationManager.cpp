#include"ReplicationManager.h"
#include "GetRequiredBits.h"

void ReplicationManager::ReplicateWorldState(OutputMemoryBitStream& inStream,
	const std::vector<GameObject*>& inAllObjects) {
	// 1. 객체 데이터를 replication하는 것임을 기록
	inStream.WriteBits(PT_ReplicationData, GetRequiredBits<PT_MAX>::value);
	// 2. 모든 객체를 기록
	for (auto go : inAllObjects) {
		ReplicateIntoStream(inStream, go);
	}
}

void ReplicationManager::ReplicateIntoStream(OutputMemoryBitStream& inStream,
	GameObject* inGameObject) {
	// 1. Network ID 기록
	inStream.Write(mLinkingContext->GetNetworkId(inGameObject));
	// 2. Class ID 기록
	inStream.Write(inGameObject->GetClassId());
	// 3. 객체 직렬화 기록
	inGameObject->Write(inStream);
}

void ReplicationManager::ReceiveWorld(InputMemoryBitStream& inStream) {
	std::unordered_set<GameObject*> receivedObjects;

	while (inStream.GetRemainingBitCount() > 0) {
		GameObject* receivedGameObject = ReceiveReplicatedObject(inStream);
		receivedObjects.insert(receivedGameObject);
	}

	// 새로 받은 replicatedGameObject 중 기존의 object가 없다면 삭제로 간주
	for (auto go : mObjectsReplicatedToMe) {
		if (receivedObjects.find(go) == receivedObjects.end()) {
			mLinkingContext->RemoveGameObject(go);
			go->Destroy();
		}
	}

	mObjectsReplicatedToMe = receivedObjects;
}

GameObject* ReplicationManager::ReceiveReplicatedObject(InputMemoryBitStream& inStream) {
	uint32_t networkId;
	uint32_t classId;
	inStream.Read(networkId);
	inStream.Read(classId);

	GameObject* go = mLinkingContext->GetGameObject(networkId);
	if (!go) {
		// 객체를 새로 생성해 networkId로 mLinkingContext를 갱신
	}

	go->Read(inStream);

	return go;
}