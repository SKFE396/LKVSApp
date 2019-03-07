#pragma once
#include "lkvs_constants.h"
#include "lkvs_types.h"

#pragma pack(1)
// λ��VD�ײ��Ŀ飬���ڱ�ʾVS�ĸ���Ϣ

struct header_node {
	char file_type_mark[4]; // = 'lkvs'
	unsigned char lkvs_version[4]; // = { {1, 0}, {0, 0} }
};