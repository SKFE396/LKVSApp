#include "pch.h"
#include <io.h>
#include <fcntl.h>
#include <errno.h>
#include "lkvs_constants.h"
#include "lkvs_errors.h"
#include "base_adaptor_file.h"

int base_adaptor_file::create_vd(const char *filename) {
	int handle = _open(filename, _O_CREAT | _O_EXCL | _O_RDWR | _O_BINARY);
	if (handle == -1) {
		int code = errno;
		switch (code) {
		case EEXIST:
			return LKVS_CREATE_VS_FILE_EXISTS;
		case EMFILE:
			return LKVS_CERATE_VS_OUT_OF_HANDLE;
		case ENOENT:
			return LKVS_CREATE_VS_NOT_FOUND;
		default:
			return LKVS_UNKNOWN_ERROR;
		}
	}
	else {
		m_handle = handle;
		return 0;
	}
}

int base_adaptor_file::open_vd(const char *);

int base_adaptor_file::close_vd();

int base_adaptor_file::read_block(block_id, void *);

int base_adaptor_file::write_block(block_id, void *);

int base_adaptor_file::resize_vd(block_id);

base_adaptor_file::~base_adaptor_file();
