#include"ReplicationManager.h"
#include "GetRequiredBits.h"
#include "ReplicationHeader.h"

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

void ReplicationManager::ReplicateCreate(OutputMemoryBitStream& inStream,
	GameObject* inGameObject)
{
	ReplicationHeader rh(ReplicationAction::RA_Create,
		mLinkingContext->GetNetworkId(inGameObject, true),
		inGameObject->GetClassId());

	rh.Write(inStream);
	inGameObject->Write(inStream);
}

void ReplicationManager::ReplicateUpdate(OutputMemoryBitStream& inStream,
	GameObject* inGameObject)
{
	ReplicationHeader rh(ReplicationAction::RA_Update,
		mLinkingContext->GetNetworkId(inGameObject, false),
		inGameObject->GetClassId());

	rh.Write(inStream);
	inGameObject->Write(inStream);
}

void ReplicationManager::ReplicateDestroy(OutputMemoryBitStream& inStream,
	GameObject* inGameObject)
{
	ReplicationHeader rh(ReplicationAction::RA_Destroy,
		mLinkingContext->GetNetworkId(inGameObject, false));

	rh.Write(inStream);
}

void ReplicationManager::ProcessReplicationAction(InputMemoryBitStream& inStream)
{
	ReplicationHeader rh;
	rh.Read(inStream);

	switch (rh.mReplicationAction)
	{
	case ReplicationAction::RA_Create:
		// CreateRegistry::Get() 메서드가 있다면 객체 생성. 아니라면 rh.mClassId를 보고 생성.
		GameObject* go = nullptr;

		mLinkingContext->AddGameObject(go, rh.mNetworkId);
		go->Read(inStream);
		
		break;

	case ReplicationAction::RA_Update:
		GameObject* go = mLinkingContext->GetGameObject(rh.mNetworkId);

		if (go) {
			go->Read(inStream);
		}
		else {
			// 아직 ReplicateCreate가 되지 못한 상태로 전달되었을 수 있다.
			// 다음 stream을 읽기 위해 어쨌든 stream의 head를 전진시켜야 하기 때문에, 
			// 정상적인 것처럼 수신한 뒤 객체 폐기한다.
			// CreateRegistry::Get() 메서드가 있다면 객체 생성. 아니라면 rh.mClassId를 보고 생성.
			go = nullptr;
			go->Read(inStream);
			delete go;
		}
		
		break;

	case ReplicationAction::RA_Destroy:
		GameObject* go = mLinkingContext->GetGameObject(rh.mNetworkId);
		mLinkingContext->RemoveGameObject(go);
		go->Destroy();
		
		break;
		
	default:
		break;
	}
}