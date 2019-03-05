#pragma once
#include "lkvs_types.h"

class base_adaptor {
	virtual int read_block(block_id, void *) = 0;
	virtual int write_block(block_id, void *) = 0;
};
