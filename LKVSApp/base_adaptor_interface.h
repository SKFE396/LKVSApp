#pragma once
#include "lkvs_types.h"

struct base_adaptor_interface {
	// return 0 if successful
	virtual int read_block(block_id, void *) = 0;
	virtual int write_block(block_id, void *) = 0;
	virtual int create_vd(const char *) = 0;
	virtual int open_vd(const char *) = 0;
	virtual int close_vd() = 0;
	virtual int resize_vd(block_id) = 0;
};
