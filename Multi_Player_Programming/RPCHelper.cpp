#include "RPCHelper.h"

#include "UserFunction.h"
#include "ReplicationHeader.h"

void RegisterRPCs(RPCManager* inRPCManger)
{
	inRPCManger->RegisterUnwrapFunction('PSND', UnwrapPlaySound);
}

void UnwrapPlaySound(InputMemoryBitStream& inStream)
{
	std::string soundName;
	Vector3 location;
	float volume;

	inStream.Read(soundName);
	inStream.Read(location);
	inStream.Read(volume);
	PlaySound(soundName, location, volume);
}
void PlaySoundRPC(OutputMemoryBitStream& inStream,
	std::string inSoundName,
	Vector3 inLocation,
	float inVolume)
{
	ReplicationHeader rh(ReplicationAction::RA_RPC);
	rh.Write(inStream);
	inStream.Write('PSND');
	inStream.Write(inSoundName);
	inStream.Write(inLocation);
	inStream.Write(inVolume);
}