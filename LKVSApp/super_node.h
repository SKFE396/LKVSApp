#pragma once
#include "lkvs_constants.h"
#include "lkvs_types.h"

#pragma pack(1)
// λ��VD�ײ��Ŀ飬���ڱ�ʾVS�ĸ���Ϣ

struct header_node {
	unsigned long file_type_mark; // = 'lkvs'
	unsigned long lkvs_version; // = { {1, 0}, {0, 0} }
};