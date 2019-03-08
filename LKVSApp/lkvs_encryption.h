#pragma once

struct lkvs_encryption {
	void encrypt_block(char *);
	void decrypt_block(char *);
	void encrypt(char *, int);
	void decrypt(char *, int);
	void set_password(const char *);
};