#pragma once
#include "lkvs_types.h"

struct base_adaptor_interface {
	// all functions return 0 if successful

	virtual int read_block(block_id, void *) = 0;
	// ��ȡ��

	virtual int write_block(block_id, void *) = 0;
	// д���

	virtual int create_vd(const char *) = 0;
	// ����������VD�ⲿ���ƣ���������VD

	virtual int open_vd(const char *) = 0;
	// ����������VD�ⲿ���ƣ���VD

	virtual int close_vd() = 0;
	// �ر��Ѵ򿪵�VD

	virtual int resize_vd(block_id) = 0;
	// �������������趨VD��������
};
