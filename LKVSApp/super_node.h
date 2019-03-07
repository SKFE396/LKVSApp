#pragma once
#include "lkvs_constants.h"
#include "lkvs_types.h"

#pragma pack(1)
// 位于VD首部的块，用于表示VS的根信息

struct header_node {
	char file_type_mark[4]; // = 'lkvs'
	unsigned char lkvs_version[4]; // = { {1, 0}, {0, 0} }
};