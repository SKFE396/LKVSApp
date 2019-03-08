#pragma once
#include "lkvs_constants.h"
#include "lkvs_errors.h"
#include "lkvs_types.h"
#include <io.h>
#include <errno.h>
#include <fcntl.h>
#include <share.h>
#include <sys\stat.h>
#include <stdio.h>
#include "lkvs_kernel_base.h"
#include "lkvs_base.h"

// class lkvs_adaptor : 用文件系统接口实现底层接口

template<typename base_T>
class lkvs_adaptor : public base_T {
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
	int is_read_only();
	int is_vd_file_formated(); // 0 no 1 supported version 2 unsupported version
	int format_vd_file(int encrypted = 0, const char *password = nullptr, block_id block_count = 1);
	int load_vfs();
	int is_vfs_encrypted();
	int is_vfs_unlocked();
	int unlock_vfs(const char *password);
	int close_vd_file();

	/* ==========================数据成员========================== */
	/* =========================================================== */
private:
	int m_file_handle = -1;
	int m_read_only = 1;

};

template<typename base_T>
inline int lkvs_adaptor<base_T>::read_block(block_id bid, void *buffer)
{
	const long long destaddr = bid * LKVS_BLOCK_SIZE;
	long long retl = _lseeki64(m_handle, destaddr, SEEK_SET);
	if (retl == -1) {
		int errcode = errno;
		switch (errcode) {
		case EBADF: return LKVS_INVALID_FILE_NUMBER;
		default: return LKVS_UNKNOWN_ERROR;
		}
	}
	if (retl != destaddr)
		return LKVS_SEEK_ERROR;
	int ret = _read(m_handle, buffer, LKVS_BLOCK_SIZE);
	if (ret == -1) {
		int errcode = errno;
		switch (errcode) {
		case EBADF: return LKVS_INVALID_FILE_NUMBER;
		case EINVAL: return LKVS_NULL_BUFFER;
		default: return LKVS_UNKNOWN_ERROR;
		}
	}
	if (ret != LKVS_BLOCK_SIZE)
		return LKVS_UNEXPECTED_EOF;
	return 0;
}

template<typename base_T>
inline int lkvs_adaptor<base_T>::write_block(block_id, void *)
{
	const long long destaddr = bid * LKVS_BLOCK_SIZE;
	long long retl = _lseeki64(m_handle, destaddr, SEEK_SET);
	if (retl == -1) {
		int errcode = errno;
		switch (errcode) {
		case EBADF: return LKVS_INVALID_FILE_NUMBER;
		default: return LKVS_UNKNOWN_ERROR;
		}
	}
	if (retl != destaddr)
		return LKVS_SEEK_ERROR;
	int ret = _write(m_handle, buffer, LKVS_BLOCK_SIZE);
	if (ret == -1) {
		int errcode = errno;
		switch (errcode) {
		case EBADF: return LKVS_INVALID_FILE_NUMBER;
		case EINVAL: return LKVS_NULL_BUFFER;
		case ENOSPC: return LKVS_WRITE_OUT_OF_SPACE;
		default: return LKVS_UNKNOWN_ERROR;
		}
	}
	if (ret != LKVS_BLOCK_SIZE)
		return LKVS_UNEXPECTED_EOF;
	return 0;
}

template<typename base_T>
inline int lkvs_adaptor<base_T>::resize_vd(block_id block_count)
{
	int errcode = _chsize_s(m_handle, block_count * (unsigned long long)LKVS_BLOCK_SIZE);
	switch (errcode) {
	case 0: return 0;
	case EACCES: return LKVS_FILE_IS_LOCKED;
	case EBADF: return LKVS_INVALID_FILE_NUMBER_OR_READ_ONLY;
	case ENOSPC:
	case EINVAL: return LKVS_FORMAT_VD_OUT_OF_SPACE;
	default: return LKVS_UNKNOWN_ERROR;
	}
}

template<typename base_T>
inline int lkvs_adaptor<base_T>::create_lkvs(const char * filename, int encrypted, const char * password, block_id block_count)
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
		case EINVAL:
			return LVKS_CREATE_VS_INVALID_ARGUMENT;
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

	// 格式化VD
	errcode = format_vd_file(excrypted, password, block_count);
	if (errcode) {
		_close(handle);
		remove(filename);
		m_handle = -1;
		return errcode;
	}
	return 0;
}

template<typename base_T>
inline int lkvs_adaptor<base_T>::open_vd_file(const char * filename, int read_only)
{
	int err = 0, ret = 0;
	int errcode;
	int handle;
	if (!read_only)
		_sopen_s(&handle, filename, _O_RDWR | _O_BINARY | _O_RANDOM, _SH_DENYRW, S_IREAD | _S_IWRITE);
	else
		_sopen_s(&handle, filename, _O_BINARY | _O_RANDOM | _O_RDONLY, _SH_DENYWR);
	if (handle == -1) {
		errcode = errno;
		switch (errcode) {
		case EACCES:
			return LKVS_CREATE_VS_DIRECTORY_OR_READ_ONLY;
		case EEXIST:
			return LKVS_CREATE_VS_FILE_EXISTS;
		case EINVAL:
			return LVKS_CREATE_VS_INVALID_ARGUMENT;
		case EMFILE:
			return LKVS_CERATE_VS_OUT_OF_HANDLE;
		case ENOENT:
			return LKVS_CREATE_VS_PATH_NOT_FOUND;
		default:
			return LKVS_UNKNOWN_ERROR;
		}
	}
	m_handle = handle;
	m_read_only = read_only;
	return 0;
}

template<typename base_T>
inline int lkvs_adaptor<base_T>::is_open()
{
	return m_handle != -1;
}

template<typename base_T>
inline int lkvs_adaptor<base_T>::is_read_only()
{
	return m_read_only;
}

template<typename base_T>
inline int lkvs_adaptor<base_T>::is_vd_file_formated()
{
	return bast_T::check_vs();
}

template<typename base_T>
inline int lkvs_adaptor<base_T>::format_vd_file(int encrypted, const char * password, block_id block_count)
{
	if (handle == -1)
		return LKVS_FILE_NOT_OPEN;
	if (read_only)
		return LKVS_WRIET_ACCESS_ON_READ_ONLY;
	if (block_count < 1)
		block_count = 1;
	int errcode = _chsize_s(m_handle, block_count * (unsigned long long)LKVS_BLOCK_SIZE);
	int err = 0;
	switch (errcode) {
	case 0: break;
	case EACCES:
		ret = LKVS_FILE_IS_LOCKED;
		err = 1;
		break;
	case EBADF:
		ret = LKVS_INVALID_FILE_NUMBER_OR_READ_ONLY;
		err = 1;
		break;
	case ENOSPC:
	case EINVAL:
		ret = LKVS_FORMAT_VD_OUT_OF_SPACE;
		err = 1;
		break;
	default:
		ret = LKVS_UNKNOWN_ERROR;
		err = 1;
		break;
	}
	if (err)
		return ret;
	return base_T::initialize_vs(encrypted, password, block_count);
}

template<typename base_T>
inline int lkvs_adaptor<base_T>::load_vfs()
{
	if (m_handle == -1)
		return LKVS_FILE_NOT_OPEN;
	return base_T::load_vs(m_read_only);
}

template<typename base_T>
inline int lkvs_adaptor<base_T>::is_vfs_encrypted()
{
	if (m_handle == -1)
		return 0;
	return vs_state() & 2;
}

template<typename base_T>
inline int lkvs_adaptor<base_T>::is_vfs_unlocked()
{
	if (m_handle == -1)
		return 0;
	return vs_state() & 4;
}

template<typename base_T>
inline int lkvs_adaptor<base_T>::unlock_vfs(const char * password)
{
	if (m_handle == -1)
		return LKVS_FILE_NOT_OPEN;
	return base_T::login(password);
}

template<typename base_T>
inline int lkvs_adaptor<base_T>::close_vd_file()
{
	if (m_handle == -1)
		return 0;
	if (!m_read_only) {
		int code = base_T::reset_state();
		if (code)
			return code;
	}
	if (_close(m_handle) == -1) {
		m_handle = -1;
		return LKVS_INVALID_FILE_NUMBER;
	}
	m_handle = -1;
	m_read_only = 1;
	return 0;
}

typedef lkvs_adaptor<lkvs_base> LKVS;
typedef lkvs_adaptor<lkvs_kernel_base> LKVS_Kernel;
