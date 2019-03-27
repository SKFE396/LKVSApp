#include "pch.h"
#include "lkvs_kernel_base.h"
#include <cstring>

int lkvs_kernel_base::check_vs() {
	// 0 δ�ҵ�VS 1 �ҵ����Լ��ص�VS 2 �ҵ����߰汾��VS
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

int lkvs_kernel_base::load_vs(int read_only) {
	if (check_vs() != 1)
		
	return 0;
}

lkvs_kernel_base::lkvs_kernel_base() {
	status = 0;
	mp_super_node = nullptr;
	mp_super_node = new lkvs_internal::super_node;
}

lkvs_kernel_base::~lkvs_kernel_base() {
	delete mp_super_node;
}
