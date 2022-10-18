#pragma once
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "sql/parser/parse_defs.h"

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

extern cast_func_ptr cast_to[AttrType::FLOATS + 1][AttrType::FLOATS + 1];
