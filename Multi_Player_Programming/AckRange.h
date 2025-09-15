#pragma once

class OutputMemoryBitStream;
class InputMemoryBitStream;

class AckRange
{
public:
	AckRange() = default;
	AckRange(PacketSequenceNumber packetSequenceNumber);

	bool ExtendIfShould(PacketSequenceNumber inSequenceNumber);

	PacketSequenceNumber GetStart() const;
	uint32_t GetCount() const;

	void Write(OutputMemoryBitStream& inPacket) const;
	void Read(InputMemoryBitStream& inPacket);

private:
	PacketSequenceNumber mStart;
	uint32_t mCount;
};
