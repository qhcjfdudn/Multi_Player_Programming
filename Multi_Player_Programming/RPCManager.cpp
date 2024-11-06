#include "RPCManager.h"

#include <cassert>

void RPCManager::RegisterUnwrapFunction(uint32_t inName, RPCUnwrapFunc func)
{
	assert(mNameToRPCTable.find(inName) == mNameToRPCTable.end());
	mNameToRPCTable[inName] = func;
}

void RPCManager::ProcessRPC(InputMemoryBitStream& inStream)
{
	uint32_t name;
	inStream.Read(name);

	assert(mNameToRPCTable.find(name) == mNameToRPCTable.end());
	mNameToRPCTable[name](inStream);
}