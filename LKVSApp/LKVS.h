#pragma once
#include "lkvs_constants.h"
#include "lkvs_errors.h"
#include "lkvs_types.h"
#include <io.h>
#include <errno.h>
#include <fcntl.h>
#include <share.h>
#include <sys\stat.h>
#include "lkvs_kernel_base.h"
#include "lkvs_base.h"

// 用文件系统接口实现底层接口

template<typename base_T>
class LKVS : public base_T {
	/* ========================底层访问接口======================== */
	/* =========================================================== */
private:
	int read_block(block_id, void *);
	int write_block(block_id, void *);
	int resize_vd(block_id);

	/* ========================外部访问接口======================== */
	/* =========================================================== */
public:
	int create_lkvs(const char *filename, int encrypted = 0, const char *password = nullptr, block_id block_count = 1);
	int open_vd_file(const char *filename, int read_only = 0);
	int is_open();
	int is_vd_file_formated();
	int format_vd_file(int encrypted = 0, const char *password = nullptr, block_id block_count = 1);
	int load_vfs();
	int is_vfs_encrypted();
	int is_vfs_unlocked();
	int unlock_vfs(const char *password);

	/* ==========================数据成员========================== */
	/* =========================================================== */
private:
	int m_file_handle = -1;
	int m_read_only;

};

template<typename base_T>
inline int LKVS<base_T>::create_lkvs(const char * filename, int encrypted, const char * password, block_id block_count)
{
	int err = 0, ret = 0;
	int errcode;
	int handle;
	// 创建文件
	_sopen_s(&handle, filename, _O_CREAT | _O_EXCL | _O_RDWR | _O_BINARY | _O_RANDOM, _SH_DENYRW, _S_IREAD | _S_IWRITE);
	if (handle == -1) {
		int code = errno;
		switch (code) {
		case EACCES:
			return LKVS_CREATE_VS_DIRECTORY_OR_READ_ONLY;
		case EEXIST:
			return LKVS_CREATE_VS_FILE_EXISTS;
		case EMFILE:
			return LKVS_CERATE_VS_OUT_OF_HANDLE;
		case ENOENT:
			return LKVS_CREATE_VS_PATH_NOT_FOUND;
		default:
			return LKVS_UNKNOWN_ERROR;
		}
	}
	if (block_count < 1)
		block_count = 1;

	// 初始化文件大小
	errcode = _chsize_s(handle, block_count * (unsigned long long)BLOCK_SIZE);
	switch (errcode) {
	case 0: break;
	case ENOSPC:
		ret = LKVS_CREATE_VS_OUT_OF_SPACE;
		err = 1;
		break;
	default:
		ret = LKVS_UNKNOWN_ERROR;
		err = 1;
		break;
	}
	if (err) {
		_close(handle);
		remove(filename);
		return ret;
	}

	// 格式化虚拟磁盘
	int errcode = base_T::initialize_vs(encrypted, password, block_count);
	if (errcode) {
		_close(handle);
		remove(filename);
		return errcode;
	}

	m_handle = handle;
	return 0;
}

template<typename base_T>
inline int LKVS<base_T>::open_vd_file(const char * filename, int read_only)
{
	int err = 0, ret = 0;
	int errcode;
	int handle;
	if (!read_only)
		_sopen_s(&handle, filename, _O_RDWR | _O_BINARY | _O_RANDOM, _SH_DENYRW, S_IREAD | _S_IWRITE);
	else
		_sopen_s(&handle, filename, _O_BINARY | _O_RANDOM | _O_RDONLY, _SH_DENYWR)
	return 0;
}
