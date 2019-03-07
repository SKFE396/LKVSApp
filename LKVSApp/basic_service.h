#pragma once
#include "lkvs_constants.h"
#include "lkvs_types.h"
#include "lkvs_errors.h"

#include "base_adaptor_file.h"

// VS底层服务，解读VD的底层表示

class basic_service {
private:
	base_adaptor_file *const m_pbase; // 用于读写

public:
	basic_service(base_adaptor_file*);
	int initialize_vs();
};