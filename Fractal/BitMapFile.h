#ifndef BITMAPFILE_H
#define BITMAPFILE_H
#pragma once

// Makes C++ store struct exactly as written in memory. No padding bits.
// No extra padding or optimization
#pragma pack(2)
struct BitmapFileHeader{
	char header[2]{ 'B', 'N'};
	int32_t fileSize, reserved{0}, dataOffset; //Guaranteed to be 32 bits
};

#endif // !BITMAPFILE_H
