#include "pch.h"
#include <algorithm>
#include "lkvs_kernel_base.h"
#include "lkvs_kernel_base_errors.h"
#include <cstring>

static void set_bit(int& x, int index, int value) {
	x = x & (0xFFFFFFFF ^ (1 << index)) | ((!!value) << index);
}

int lkvs_kernel_base::check_vs() {
	// 0 未找到VS 1 找到可以加载的VS 2 找到过高版本的VS
	read_block(0, mp_super_node);
	char checkarr[4] = { 'l', 'k', 'v', 's' };
	if (memcmp(mp_super_node->sys.file_type_mark, checkarr, 4))
		return 0;
	int currentver[4] = { 1, 0, 0, 0 };
	unsigned char *p = mp_super_node->sys.lkvs_version;
	for (int i = 0; i < 4; ++i, ++p)
		if (*p != currentver[i])
			return 1 + !!(*p > currentver[i]);
	return 1;
}

static int bit_reverse6(int x) {
	int ret = 0;
	for (int i = 0; i < 6; ++i) {
		ret = (ret << 1) | (x & 1);
		x >>= 1;
	}
	return ret;
}

int lkvs_kernel_base::initialize_vs(int encrypted, const char* password, block_id block_count) {
	if (block_count < 2)
		block_count = 2;
	int password_length = strlen(password);
	if (password_length > 64 || !password_length)
		throw lkvs_kernel_base_invalid_password();
	memset(mp_super_node->user_data, 0, lkvs_internal::super_node::USER_DATA_SIZE);
	mp_super_node->sys.dir_count = 0;
	mp_super_node->sys.encrypted = !!encrypted;
	mp_super_node->sys.file_count = 0;
	memcpy(mp_super_node->sys.file_type_mark, "lkvs", 4);
	char version_array[] = { 1, 0, 0, 0 };
	memcpy(mp_super_node->sys.lkvs_version, version_array, 4);
	mp_super_node->sys.total_blocks = 2;
	mp_super_node->sys.total_file_size = 0;
	if (block_count > 2) {
		// add additional blocks into management
	}
	else {
		mp_super_node->sys.used_blocks = 2;
	}
	if (encrypted) {
		mp_super_node->sys.encrypted = 1;
		memcpy(mp_super_node->sys.password_check, password, password_length);
		for (int i = password_length; i < 64; ++i)
			mp_super_node->sys.password_check[i] = bit_reverse6(i);
		for (int i = 0; i < 64; ++i) {
			int k = bit_reverse6(i);
			if (i < k)
				std::swap(mp_super_node->sys.password_check[i], mp_super_node->sys.password_check[k]);
		}
		m_encryptor.set_password((char *)mp_super_node->sys.password_check, 64);
		for (int i = 0; i < 64; ++i)
			mp_super_node->sys.password_check[i] = password[i % password_length];
		m_encryptor.encrypt((char *)mp_super_node->sys.password_check, 64);
	}
	return 0;
}

int lkvs_kernel_base::load_vs(int read_only) {
	if (check_vs() != 1)
		throw lkvs_kernel_base_no_compatible_vs("Cannot load a compatible vs, call check_vs() for further information");
	set_bit(m_status, 0, 1);
	set_bit(m_status, 1, read_only);
	set_bit(m_status, 2, mp_super_node->sys.encrypted);
	set_bit(m_status, 3, !mp_super_node->sys.encrypted);
	return 0;
}

int lkvs_kernel_base::vs_status() {
	return m_status;
}

lkvs_kernel_base::lkvs_kernel_base() : m_encryptor() {
	m_status = 0;
	mp_super_node = nullptr;
	mp_super_node = new lkvs_internal::super_node;
}

lkvs_kernel_base::~lkvs_kernel_base() {
	delete mp_super_node;
}
