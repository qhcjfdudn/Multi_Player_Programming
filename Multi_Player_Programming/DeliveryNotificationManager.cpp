#include "pch.h"
#include "DeliveryNotificationManager.h"

#include "OutputMemoryBitStream.h"
#include "InputMemoryBitStream.h"

InFlightPacket* DeliveryNotificationManager::WriteSequenceNumber(OutputMemoryBitStream& inPacket)
{
	PacketSequenceNumber sequenceNumber = mNextOutgoingSequenceNumber++;
	inPacket.Write(sequenceNumber);

	++mDispatchedPacketCount;

	mInflightPackets.emplace_back(sequenceNumber);
	return &mInflightPackets.back();
}

bool DeliveryNotificationManager::ProcessSequenceNumber(InputMemoryBitStream& inPacket)
{
	PacketSequenceNumber sequenceNumber;
	inPacket.Read(sequenceNumber);
	
	// 같으면 기대하던 것.
	// sequenceNumber가 크면 패킷 손실 예상. 손실된 것은 송신측에서 인지하여 재전송 예정.
	if (sequenceNumber >= mNextExpectedSequenceNumber) {
		mNextExpectedSequenceNumber = sequenceNumber + 1;
		AddPendingAck(sequenceNumber);
		return true;
	}
	
	return false;
}

void DeliveryNotificationManager::AddPendingAck(PacketSequenceNumber inSequenceNumber)
{
	if (mPendingAcks.size() == 0 ||
		mPendingAcks.back().ExtendIfShould(inSequenceNumber) == false) {
		mPendingAcks.emplace_back(inSequenceNumber);
	}
}

void DeliveryNotificationManager::WritePendingAcks(OutputMemoryBitStream& inPacket)
{
	bool hasAcks = mPendingAcks.size() > 0;
	inPacket.Write(hasAcks);
	if (hasAcks) {
		mPendingAcks.front().Write(inPacket);
		mPendingAcks.pop_front();
	}
}

void DeliveryNotificationManager::ProcessAcks(InputMemoryBitStream& inPacket)
{
	bool hasAcks = false;
	inPacket.Read(hasAcks);
	if (hasAcks) {
		AckRange ackRange;
		ackRange.Read(inPacket);

		PacketSequenceNumber nextAckedSequenceNumber = ackRange.GetStart();
		uint32_t onePastAckedSequenceNumber =
			nextAckedSequenceNumber + ackRange.GetCount();

		while (nextAckedSequenceNumber < onePastAckedSequenceNumber &&
			mInflightPackets.empty() == false) {
			const InFlightPacket& nextInFlightPacket = mInflightPackets.front();
			PacketSequenceNumber nextInFlightPacketSequenceNumber =
				nextInFlightPacket.GetSequenceNumber();

			if (nextInFlightPacketSequenceNumber == nextAckedSequenceNumber)
			{
				HandlePacketDeliverySuccess(nextInFlightPacket);
				mInflightPackets.pop_front();
				++nextAckedSequenceNumber;
			}
			else if (nextInFlightPacketSequenceNumber < nextAckedSequenceNumber)
			{
				InFlightPacket copyOfInFlightPacket = nextInFlightPacket;
				mInflightPackets.pop_front();
				HandlePacketDeliveryFailure(copyOfInFlightPacket);
			}
			else if (nextInFlightPacketSequenceNumber > nextAckedSequenceNumber)
				// 이미 손실 보고한 패킷이 뒤늦게 ack가 온 경우.
				// 1. 어떤 패킷의 ack만 늦게 온 경우
				// 2. 시간초과의 이유로 이미 손실 보고된 경우
			{
				nextAckedSequenceNumber = nextInFlightPacketSequenceNumber;
			}
		}
	}
}

void DeliveryNotificationManager::ProcessTimedOutPackets()
{
	using namespace std::chrono;
	auto timeoutTime = system_clock::now() - duration_cast<system_clock::duration>(kAckTimeout);

	while (mInflightPackets.empty() == false)
	{
		const auto& nextInFlightPacket = mInflightPackets.front();
		if (nextInFlightPacket.GetTimeDispatched() < timeoutTime) {
			HandlePacketDeliveryFailure(nextInFlightPacket);
			mInflightPackets.pop_front();
		}
		else break;
	}
}

void DeliveryNotificationManager::HandlePacketDeliverySuccess(const InFlightPacket& inFlightPacket)
{
	++mDeliveredPacketCount;
	inFlightPacket.HandlePacketDeliverySuccess(this);
}

void DeliveryNotificationManager::HandlePacketDeliveryFailure(const InFlightPacket& inFlightPacket)
{
	++mDroppedPacketCount;
	inFlightPacket.HandlePacketDeliveryFailure(this);
}
