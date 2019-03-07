#pragma once
#include "lkvs_constants.h"
#include "lkvs_errors.h"
#include "lkvs_types.h"
#include "lkvs_base.h"

// ���ļ�ϵͳ�ӿ�ʵ�ֵײ�ӿ�

class LKVS : public LKVS_base {
	/* ========================�ײ���ʽӿ�======================== */
	/* =========================================================== */
private:
	int read_block(block_id, void *);
	int write_block(block_id, void *);
	int resize_vd(block_id);

	/* ==========================���ݳ�Ա========================== */
	/* =========================================================== */
private:
	int m_file_handle = -1;

	/* ========================�ⲿ���ʽӿ�======================== */
	/* =========================================================== */
public:
	int create_vd(const char *filename, int encrypted, const char *password);
	int open_file(const char *filename);
	int test_vs();
	int 
};