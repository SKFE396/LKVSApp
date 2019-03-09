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

void lkvs_encryption::set_password(const char *password)
{
	// 求出密码的MD5作为密钥
	using joyee::MD5;
	MD5 hash;
	hash.update(password, strlen(password));
	hash.finalize();
	memcpy(m_key, hash.digest, 16);
}
