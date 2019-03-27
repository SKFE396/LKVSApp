#pragma once
#include <exception>

/*
    此文件定义可能被lkvs_adaptor<>类抛出的异常
*/

/*#define LKVS_UNKNOWN_ERROR 1
#define LKVS_CREATE_VS_DIRECTORY_OR_READ_ONLY 2
#define LKVS_CREATE_VS_FILE_EXISTS 3
#define LKVS_CERATE_VS_OUT_OF_HANDLE 4
#define LKVS_CREATE_VS_PATH_NOT_FOUND 5
#define LKVS_FORMAT_VD_OUT_OF_SPACE 6
#define LVKS_CREATE_VS_INVALID_ARGUMENT 7
#define LKVS_FILE_NOT_OPEN 8
#define LKVS_WRIET_ACCESS_ON_READ_ONLY 9
#define LKVS_INVALID_FILE_NUMBER 10
#define LKVS_INVALID_FILE_NUMBER_OR_READ_ONLY 11
#define LKVS_NULL_BUFFER 12
#define LKVS_UNEXPECTED_EOF 13
#define LKVS_SEEK_ERROR 14
#define LKVS_WRITE_OUT_OF_SPACE 15
#define LKVS_FILE_IS_LOCKED 16*/

#define SET_EXCEPTION(type, pes) class type : public std::exception {\
public:\
type(const char *es = pes) : std::exception(es) {} }


SET_EXCEPTION(lkvs_unknown_error, "LKVS : unknown error");
SET_EXCEPTION(lkvs_create_vs_error, "LKVS-CreateVS error");
SET_EXCEPTION(lkvs_format_vd_error, "LKVS-FormatVD error");
