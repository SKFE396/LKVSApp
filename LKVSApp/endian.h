#pragma once

// endian.h : 此文件提供字节序检测和转换操作

constexpr int little_endian() {
	constexpr int LE_test = 0x00000001;
	return (int)*(char*)&LE_test;
}

// 在Big-Endian主机上执行转换

inline short endian_convert(register short x) {
	if (little_endian()) return x;
	return (short)(((unsigned short)x & 0xFF) << 8) | (((unsigned short)x & 0xFF00) >> 8);
}

inline unsigned short endian_convert(register unsigned short x) {
	if (little_endian()) return x;
	return (unsigned short)((x & 0xFF) << 8) | ((x & 0xFF00) >> 8);
}

inline int endian_convert(register int x) {
	if (little_endian()) return x;
	return (((unsigned int)x & 0xFF) << 24) | (((unsigned int)x & 0xFF00) << 8) |
		(((unsigned int)x & 0xFF0000) >> 8) | (((unsigned int)x & 0xFF000000) >> 24);
}

inline unsigned int endian_convert(register unsigned int x) {
	if (little_endian()) return x;
	return ((x & 0xFF) << 24) | ((x & 0xFF00) << 8) | ((x & 0xFF0000) >> 8) | ((x & 0xFF000000) >> 24);
}

inline long endian_convert(register long x) {
	if (little_endian()) return x;
	return (((unsigned long)x & 0xFF) << 24) | (((unsigned long)x & 0xFF00) << 8) |
		(((unsigned long)x & 0xFF0000) >> 8) | (((unsigned long)x & 0xFF000000) >> 24);
}

inline unsigned long endian_convert(register unsigned long x) {
	if (little_endian()) return x;
	return ((x & 0xFF) << 24) | ((x & 0xFF00) << 8) | ((x & 0xFF0000) >> 8) | ((x & 0xFF000000) >> 24);
}

inline long long endian_convert(register long long x) {
	if (little_endian()) return x;
	x = (((unsigned long long)x & 0xFFFFFFFFll) << 32) | (((unsigned long long)x & 0xFFFFFFFF00000000ll) >> 32);
	x = (((unsigned long long)x & 0xFFFF0000FFFF0000ll) >> 16) | (((unsigned long long)x & 0x0000FFFF0000FFFFll) << 16);
	return (((unsigned long long)x & 0xFF00FF00FF00FF00ll) >> 8 | ((unsigned long long)x & 0x00FF00FF00FF00FF) << 8);
}

inline unsigned long long endian_convert8(register unsigned long long x) {
	if (little_endian()) return x;
	x = ((x & 0xFFFFFFFFll) << 32) | ((x & 0xFFFFFFFF00000000ll) >> 32);
	x = ((x & 0xFFFF0000FFFF0000ll) >> 16) | ((x & 0x0000FFFF0000FFFFll) << 16);
	return ((x & 0xFF00FF00FF00FF00ll) >> 8 | (x & 0x00FF00FF00FF00FF) << 8);
}
