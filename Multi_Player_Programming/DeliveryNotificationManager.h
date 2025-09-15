#pragma once

#include "AckRange.h"
#include "InFlightPacket.h"

class OutputMemoryBitStream;
class InputMemoryBitStream;

class DeliveryNotificationManager
{
public:
	InFlightPacket* WriteSequenceNumber(OutputMemoryBitStream& inPacket);
	bool ProcessSequenceNumber(InputMemoryBitStream& inPacket);

	void AddPendingAck(PacketSequenceNumber inSequenceNumber);
	void WritePendingAcks(OutputMemoryBitStream& inPacket);
	void ProcessAcks(InputMemoryBitStream& inPacket);

	void ProcessTimedOutPackets();

	void HandlePacketDeliverySuccess(const InFlightPacket& inFlightPacket);
	void HandlePacketDeliveryFailure(const InFlightPacket& inFlightPacket);

private:
	PacketSequenceNumber mNextOutgoingSequenceNumber = 0;
	PacketSequenceNumber mNextExpectedSequenceNumber = 0;
	uint32_t mDispatchedPacketCount = 0;
	uint32_t mDeliveredPacketCount = 0;
	uint32_t mDroppedPacketCount = 0;
	std::deque<InFlightPacket> mInflightPackets;
	std::deque<AckRange> mPendingAcks;

	std::chrono::duration<float> kAckTimeout{ 1.f };
};
