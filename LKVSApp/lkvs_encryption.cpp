#include "pch.h"
#include "lkvs_encryption.h"
#include "md5.h"
#include <cstring>


void lkvs_encryption::encrypt_block(char *)
{
}

void lkvs_encryption::decrypt_block(char *)
{
}

void lkvs_encryption::encrypt(char *, int)
{
}

void lkvs_encryption::decrypt(char *, int)
{
}

void lkvs_encryption::set_password(const char *password, int length)
{
	// ��������MD5��Ϊ��Կ
	using joyee::MD5;
	MD5 hash;
	hash.update(password, length);
	hash.finalize();
	memcpy(m_key, hash.digest, 16);
}
