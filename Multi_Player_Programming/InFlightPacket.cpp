#include "pch.h"
#include "InFlightPacket.h"

#include "DeliveryNotificationManager.h"

InFlightPacket::InFlightPacket(PacketSequenceNumber packetSequenceNumber) :
	mPacketSequenceNumber(packetSequenceNumber),
	mTimeDispatched(std::chrono::system_clock::now())
{}

PacketSequenceNumber InFlightPacket::GetSequenceNumber() const
{
	return mPacketSequenceNumber;
}

std::chrono::system_clock::time_point InFlightPacket::GetTimeDispatched() const
{
	return mTimeDispatched;
}

void InFlightPacket::HandlePacketDeliverySuccess(DeliveryNotificationManager* inFlightPacket) const 
{
}

void InFlightPacket::HandlePacketDeliveryFailure(DeliveryNotificationManager* inFlightPacket) const
{
}
