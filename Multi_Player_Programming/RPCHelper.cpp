#include "RPCHelper.h"

#include "UserFunction.h"

void RegisterRPCs(RPCManager* inRPCManger) {
	inRPCManger->RegisterUnwrapFunction('PSND', UnwrapPlaySound);
}

void UnwrapPlaySound(InputMemoryBitStream& inStream) {
	std::string soundName;
	Vector3 location;
	float volume;

	inStream.Read(soundName);
	inStream.Read(location);
	inStream.Read(volume);
	PlaySound(soundName, location, volume);
}