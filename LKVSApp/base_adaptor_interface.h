#pragma once
#include "lkvs_types.h"

struct base_adaptor_interface {
	// all functions return 0 if successful

	virtual int read_block(block_id, void *) = 0;
	// 读取块

	virtual int write_block(block_id, void *) = 0;
	// 写入块

	virtual int create_vd(const char *) = 0;
	// 给定完整的VD外部名称，创建并打开VD

	virtual int open_vd(const char *) = 0;
	// 给定完整的VD外部名称，打开VD

	virtual int close_vd() = 0;
	// 关闭已打开的VD

	virtual int resize_vd(block_id) = 0;
	// 给定块数量，设定VD的新容量
};
