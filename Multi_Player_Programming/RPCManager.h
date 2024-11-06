#pragma once

#include <unordered_map>

#include "InputMemoryBitStream.h"

using RPCUnwrapFunc = void (*)(InputMemoryBitStream& inStream);

class RPCManager
{
public:
	void RegisterUnwrapFunction(uint32_t inName, RPCUnwrapFunc func);
	void ProcessRPC(InputMemoryBitStream& inStream);

private:
	std::unordered_map<uint32_t, RPCUnwrapFunc> mNameToRPCTable;
};