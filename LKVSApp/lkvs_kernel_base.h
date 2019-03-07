#pragma once
#include "lkvs_constants.h"
#include "lkvs_types.h"
#include "lkvs_errors.h"

class lkvs_kernel_base {
	// lkvs_kernel_base : 抽象主类，实现LKVS主要逻辑功能。由实现底层接口后成为完整类型。
	// 内核模式，打开操作直接返回工具对象。
	// 如果调用者违规使用（例如超出工具对象的逻辑生命周期使用对象），可能对数据造成严重破坏。

	/* ========================底层访问接口======================== */
	/* =========================================================== */
protected:

	virtual int read_block(block_id, void *) = 0;
	// 读取块

	virtual int write_block(block_id, void *) = 0;
	// 写入块

	virtual int resize_vd(block_id) = 0;
	// 给定块数量，设定VD的新容量。
	// LKVS内部通过调用此函数通知子类，LKVS的数据需要占用更多的空间，或者尾部部分空间成为未使用状态。



	/* =================子类可以用于进一步包装的接口================= */
	/* =========================================================== */
protected:

	int check_vs();
	// 0 未找到VS 1 找到过高版本的VS 2 找到可以加载的VS

	int initialize_vs(int encrypted = 0, const char *password = nullptr, block_id block_count = 1);
	// 用于在新的VD上初始化文件系统结构，类似于“格式化”，应在连接到新的空白VD时调用。

	int load_vs(const char *password = nullptr, int read_only = 0);
	// 用于从VD中加载文件系统基本信息，应在连接到已存在VS的VD后调用。

	int vs_status();
	// bit0 是否加载 bit1 是否加密 bit2 是否验证通过 bit3 是否只读

	int login(const char *password);
	// 对已加密的VS验证密码
	
	int sync_vs();
	// 用于将所有已缓存的改动同步到VD，应在断开到VD的连接前调用。

};