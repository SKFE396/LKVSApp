#pragma once
#include "lkvs_constants.h"
#include "lkvs_types.h"

#pragma pack(1)
// λ��VD�ײ��Ŀ飬���ڱ�ʾVS�ĸ���Ϣ

namespace lkvs_internal {

	struct super_node {
		struct sys_type {
			char file_type_mark[4]; // = 'lkvs'
			unsigned char lkvs_version[4]; // = { {1, 0}, {0, 0} }
			unsigned long long total_blocks;
			unsigned long long used_blocks;
			long encrypted;
			unsigned char password_check[64]; // ���뱻���ν����ҵ���������Ժ��ֵ
			// ���¿�ʼΪ������Ϣ
			unsigned long long file_count;
			unsigned long long dir_count;
			unsigned long long total_file_size;
		} sys;
		enum { USER_DATA_SIZE = LKVS_BLOCK_SIZE - sizeof(sys) };
		char user_data[USER_DATA_SIZE];
	};

}