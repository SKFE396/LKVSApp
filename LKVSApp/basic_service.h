#pragma once
#include "lkvs_constants.h"
#include "lkvs_types.h"
#include "lkvs_errors.h"

#include "base_adaptor_file.h"

// VS�ײ���񣬽��VD�ĵײ��ʾ

class basic_service {
private:
	base_adaptor_file *const m_pbase; // ���ڶ�д

public:
	basic_service(base_adaptor_file*);
	int initialize_vs();
};