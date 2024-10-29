#pragma once

#include <unordered_map>

#include "GameObject.h"

// uint32_t 타입의 식별자는 호스트간 동일하게 유지한다.
// GameObject* 타입은 호스트별 메모리 주소가 다르게 유지된다.
class LinkingContext
{
public:
	LinkingContext();

	void AddGameObject(GameObject* inGameObject, uint32_t inNetworkId);
	void RemoveGameObject(GameObject* const inGameObject);

	uint32_t GetNetworkId(
		GameObject* const inGameObject,
		bool inShouldCreateIfNotFound);
	uint32_t GetNetworkId(GameObject* const inGameObject);

	GameObject* GetGameObject(uint32_t inNetworkId);

private:
	std::unordered_map<uint32_t, GameObject*> mNetworkIdToGameObjectMap;
	std::unordered_map<GameObject*, uint32_t> mGameObjectToNetworkIdMap;

	uint32_t mNextNetworkId;
};