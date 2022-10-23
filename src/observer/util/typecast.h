#pragma once
#include <cstring>
#include "sql/parser/parse_defs.h"
#include "common/log/log.h"
#include "rc.h"
#include "storage/common/field_meta.h"
#include "util/util.h"

typedef void *(*cast_func_ptr)(void *);

void *int_to_int(void *src);
void *int_to_float(void *src);
void *int_to_char(void *src);
void *float_to_int(void *src);
void *float_to_char(void *src);
void *float_to_float(void *src);
void *char_to_int(void *src);
void *char_to_float(void *src);
void *char_to_char(void *src);
void *identity(void *src);
void *not_support(void *src);

// if you use it, you own a pointer(need to free) or only get a nullptr
extern cast_func_ptr cast_to[AttrType::FLOATS + 1][AttrType::FLOATS + 1];

extern bool type_cast_not_support(AttrType i, AttrType j);

// need to free(ret.data)
extern RC cast_value(const Value &value, FieldMeta *field, Value &ret);
