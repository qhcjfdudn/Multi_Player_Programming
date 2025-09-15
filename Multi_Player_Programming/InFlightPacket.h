#pragma once

class DeliveryNotificationManager;

class InFlightPacket
{
public:
	InFlightPacket(PacketSequenceNumber packetSequenceNumber);

	PacketSequenceNumber GetSequenceNumber() const;
	
	std::chrono::system_clock::time_point GetTimeDispatched() const;

	void HandlePacketDeliverySuccess(DeliveryNotificationManager* inFlightPacket) const;
	void HandlePacketDeliveryFailure(DeliveryNotificationManager* inFlightPacket) const;

private:
	PacketSequenceNumber mPacketSequenceNumber;
	std::chrono::system_clock::time_point mTimeDispatched;
};
