#pragma once
#include "lkvs_constants.h"
#include "lkvs_errors.h"
#include "lkvs_types.h"
#include "lkvs_base.h"

// 用文件系统接口实现底层接口

class LKVS : public LKVS_base {
	/* ========================底层访问接口======================== */
	/* =========================================================== */
private:
	int read_block(block_id, void *);
	int write_block(block_id, void *);
	int resize_vd(block_id);

	/* ==========================数据成员========================== */
	/* =========================================================== */
private:
	int m_file_handle = -1;

	/* ========================外部访问接口======================== */
	/* =========================================================== */
public:
	int create_vd(const char *filename, int encrypted, const char *password);
	int open_file(const char *filename);
	int test_vs();
	int 
};