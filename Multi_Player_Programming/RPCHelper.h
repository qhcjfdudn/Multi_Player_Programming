#pragma once

#include "RPCManager.h"
#include "OutputMemoryBitStream.h"

void RegisterRPCs(RPCManager* inRPCManager);

void UnwrapPlaySound(InputMemoryBitStream& inStream);

void PlaySoundRPC(OutputMemoryBitStream& inStream,
	std::string inSoundName,
	Vector3 inLocation,
	float inVolume);