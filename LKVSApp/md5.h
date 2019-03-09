#pragma once

namespace joyee {

	typedef unsigned char uint8_t;  // 8-bit
	typedef unsigned int uint32_t;  // 32-bit
	typedef unsigned int size_t;  // size type

	struct MD5 {
		MD5();
		MD5& update(const unsigned char* in, size_t inputLen);
		MD5& update(const char* in, size_t inputLen);
		MD5& finalize();

		void init();
		void transform(const uint8_t block[64]);

		uint8_t buffer[64];  // buffer of the raw data
		uint8_t digest[16];  // result hash, little endian

		uint32_t state[4];  // state (ABCD)
		uint32_t lo, hi;    // number of bits, modulo 2^64 (lsb first)
		bool finalized;  // if the context has been finalized
	};
}