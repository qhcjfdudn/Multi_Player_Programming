#include "ReplicationHeader.h"
#include "GetRequiredBits.h"

void ReplicationHeader::Write(OutputMemoryBitStream& inStream) {
	inStream.WriteBits(static_cast<int>(mReplicationAction), 
		GetRequiredBits<static_cast<int>(ReplicationAction::RA_MAX)>::value);

	inStream.Write(mNetworkId);

	if (mReplicationAction != ReplicationAction::RA_Destroy)
		inStream.Write(mClassId);
}

void ReplicationHeader::Read(InputMemoryBitStream& inStream) {
	inStream.Read(&mReplicationAction,
		GetRequiredBits<static_cast<int>(ReplicationAction::RA_MAX)>::value);
	inStream.Read(mNetworkId);

	if (mReplicationAction != ReplicationAction::RA_Destroy)
		inStream.Read(mClassId);
}