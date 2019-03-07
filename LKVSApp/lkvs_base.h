#pragma once
#include "lkvs_constants.h"
#include "lkvs_types.h"
#include "lkvs_errors.h"

class LKVS_base {
	// lkvs_base : �������࣬ʵ��LKVS��Ҫ�߼����ܡ���ʵ�ֵײ�ӿں��Ϊ�������͡�

	/* ========================�ײ���ʽӿ�======================== */
	/* =========================================================== */
protected:

	virtual int read_block(block_id, void *) = 0;
	// ��ȡ��

	virtual int write_block(block_id, void *) = 0;
	// д���

	virtual int resize_vd(block_id) = 0;
	// �������������趨VD����������
	// LKVS�ڲ�ͨ�����ô˺���֪ͨ���࣬LKVS��������Ҫռ�ø���Ŀռ䣬����β�����ֿռ��Ϊδʹ��״̬��



	/* =================����������ڽ�һ����װ�Ľӿ�================= */
	/* =========================================================== */
protected:

	int valid_vs();
	// ����VD���Ƿ���ںϷ�VS

	int vs_status();
	// 0 δ���� 1 �Ѽ��� δ���� 2 �Ѽ��� �Ѽ��� δ��֤ 3 �Ѽ��� �Ѽ��� ����֤

	int login(const char *password);

	int initialize_vs(int encrypted = 0, const char *password = nullptr);
	// �������µ�VD�ϳ�ʼ���ļ�ϵͳ�ṹ�������ڡ���ʽ������Ӧ�����ӵ��µĿհ�VDʱ���á�

	int load_vs(const char *password = nullptr);
	// ���ڴ�VD�м����ļ�ϵͳ������Ϣ��Ӧ�����ӵ��Ѵ���VS��VD����á�

	int sync_vs();
	// ���ڽ������ѻ���ĸĶ�ͬ����VD��Ӧ�ڶϿ���VD������ǰ���á�

};