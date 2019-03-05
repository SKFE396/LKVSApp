#pragma once
#include <io.h>
#include "lkvs_constants.h"
#include "base_adaptor_interface.h"

class base_adaptor_file : public base_adaptor_interface {
public:
	virtual int read_block(block_id, void *);
	virtual int write_block(block_id, void *);
	virtual int create_vd(const char *);
	virtual int open_vd(const char *);
	virtual int close_vd();
	virtual int resize_vd(block_id);
	virtual ~base_adaptor_file();

private:
	int m_handle = -1;
};