#pragma once
#include "lkvs_constants.h"
#include "lkvs_errors.h"
#include "lkvs_types.h"
#include "lkvs_kernel_base.h"

// lkvs_base : 在 lkvs_kernel_base 的基础上增加自动内核管理
// 用户模式，打开操作返回句柄
// 提供相对安全的访问模式

class lkvs_base : protected lkvs_kernel_base {
	/* ========================基类函数声明======================== */
	/* =========================================================== */
public:
	

	/* ========================自动管理部分======================== */
	/* =========================================================== */
public:

	
	/* ======================内核管理数据结构====================== */
	/* =========================================================== */
private:

};