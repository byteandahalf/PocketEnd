#include "CommonTypes.h"

BlockID::BlockID() {
	value = 0;
}

BlockID::BlockID(unsigned char other) {
	value = other;
}

BlockID::BlockID(const BlockID& other) {
	value = other.value;
}

bool BlockID::operator==(unsigned char other) {
	return value == other;
}

bool BlockID::operator==(BlockID other) {
	return value == other.value;
}

BlockID& BlockID::operator=(const unsigned char& other) {
	value = other;
	return *this;
}

BlockID::operator unsigned char() {
	return value;
}

BlockID::operator int() {
	return value;
}
