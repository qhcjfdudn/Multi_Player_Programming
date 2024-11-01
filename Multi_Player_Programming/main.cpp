#include <iostream>

#include "GetRequiredBits.h"

using std::cout;
using std::endl;

enum class TestEnum {
	AA, BB, CC, DD, MAX
};

int main() {
	int v = GetRequiredBits<static_cast<int>(TestEnum::MAX)>::value;

	std::cout << v << std::endl;
}