#pragma once
#include <stdexcept>

#define SET_EXCEPTION(type, pes) class type : public std::exception {\
public:\
type(const char *es = pes) : std::exception(es) {} }

SET_EXCEPTION(lkvs_kernel_base_no_compatible_vs, "lkvs_kernel_base.load_vs no compatible vs");
SET_EXCEPTION(lkvs_kernel_base_enrypted_vs, "lkvs_kernel_base lkvs is excrypted but not logined");
SET_EXCEPTION(lkvs_kernel_base_invalid_password, "lkvs_kernel_base.initialize_vs password must be non-empty and no longer than 64");

#undef SET_EXCEPTION