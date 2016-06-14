#pragma once

#include <cstdint>

struct BlockID {
	unsigned char value;
	static const BlockID AIR;

	BlockID();
	BlockID(unsigned char);
	BlockID(const BlockID&);

	bool operator==(unsigned char);
	bool operator==(BlockID);
	BlockID& operator=(const unsigned char&);
	operator unsigned char();
	operator int();
};
