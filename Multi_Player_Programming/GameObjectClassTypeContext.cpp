#include "OutputMemoryBitStream.h"
#include "RoboCat.h"

class GameObjectClassTypeContext {
public:
	void WriteClassType(
		OutputMemoryBitStream& inStream,
		const GameObject* inGameObject)
	{
		if (dynamic_cast<const RoboCat*>(inGameObject))
			// 'RBCT' == 1380074324
			// '0' == 48
			// '00' == 48 << 8 + 48 = 12336
			// 작은따옴표 안의 char 4자까지 biject로 int로 값을 바꾼다.
			// 따라서 아래와 같은 static_cast가 동작한다.
			inStream.Write(static_cast<uint32_t>('RBCT'));
		// else if ...
	}
};