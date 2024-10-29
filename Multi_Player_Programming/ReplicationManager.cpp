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