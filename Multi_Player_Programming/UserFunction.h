#pragma once

#include <string>
#include "Vector3.h"

void PlaySound(const std::string& inSoundName, 
	const Vector3& inLocation, 
	float inVolume);