#pragma once

#include <iostream>

#include "OutputMemoryBitStream.h"
#include "InputMemoryBitStream.h"

enum class ReplicationAction
{
	RA_Create,
	RA_Update,
	RA_Destroy,
	RA_RPC,
	RA_MAX
};

class ReplicationHeader
{
public:
	ReplicationHeader() {}
	ReplicationHeader(ReplicationAction inRA,
		uint32_t inNetworkId = 0, uint32_t inClassId = 0) :
		mReplicationAction(inRA), mNetworkId(inNetworkId), mClassId(inClassId) {}

	void Write(OutputMemoryBitStream& inStream);
	void Read(InputMemoryBitStream& inStream);

	ReplicationAction mReplicationAction;
	uint32_t mNetworkId;
	uint32_t mClassId;
};

