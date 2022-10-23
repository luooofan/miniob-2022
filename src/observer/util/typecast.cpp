#include "util/typecast.h"
#include <cassert>

cast_func_ptr cast_to[AttrType::FLOATS + 1][AttrType::FLOATS + 1] = {{
                                                                         // UNDEFINED
                                                                         not_support,
                                                                         not_support,
                                                                         not_support,
                                                                         not_support,
                                                                         not_support,
                                                                         not_support,
                                                                     },
    {
        // CHARS
        not_support,
        char_to_char,
        char_to_int,
        not_support,
        not_support,
        char_to_float,
    },
    {
        // INTS
        not_support,
        int_to_char,
        int_to_int,
        not_support,
        not_support,
        int_to_float,
    },
    {
        // DATES
        not_support,
        not_support,
        not_support,
        not_support,
        not_support,
        not_support,
    },
    {
        // NULLS
        not_support,
        not_support,
        not_support,
        not_support,
        not_support,
        not_support,
    },
    {
        // FLOATS
        not_support,
        float_to_char,
        float_to_int,
        not_support,
        not_support,
        float_to_float,
    }};

bool type_cast_not_support(AttrType i, AttrType j)
{
  return cast_to[i][j] == not_support;
}

void *not_support(void *src)
{
  return nullptr;
}

void *int_to_int(void *src)
{
  assert(nullptr != src);
  void *res = malloc(sizeof(int));
  memcpy(res, (int *)src, sizeof(int));
  return res;
}

void *int_to_float(void *src)
{
  assert(nullptr != src);
  void *res = malloc(sizeof(float));
  float tmp = *(int *)src;
  memcpy(res, &tmp, sizeof(float));
  return res;
}

void *int_to_char(void *src)
{
  std::string str = std::to_string(*(int *)src);
  return strdup(str.c_str());
}

void *float_to_int(void *src)
{
  assert(nullptr != src);
  void *res = malloc(sizeof(int));
  int tmp = *(float *)src + 0.5;
  memcpy(res, &tmp, sizeof(int));
  return res;
}

void *float_to_char(void *src)
{
  std::string str = double2string(*(float *)src);
  return strdup(str.c_str());
}

void *float_to_float(void *src)
{
  assert(nullptr != src);
  void *res = malloc(sizeof(float));
  memcpy(res, (float *)src, sizeof(float));
  return res;
}

// make sure char* end with \0
void *char_to_int(void *src)
{
  assert(nullptr != src);
  void *res = malloc(sizeof(int));
  int tmp = atoi((char *)src);
  memcpy(res, &tmp, sizeof(int));
  return res;
}

void *char_to_float(void *src)
{
  assert(nullptr != src);
  void *res = malloc(sizeof(float));
  float tmp = atof((char *)src);
  memcpy(res, &tmp, sizeof(float));
  return res;
}

void *char_to_char(void *src)
{
  return strdup((char *)src);
}

RC cast_value(const Value &value, FieldMeta *field, Value &ret)
{
  // do typecast
  void *tmp_data = nullptr;
  tmp_data = cast_to[value.type][field->type()](value.data);  // nullptr or new memory
  if (nullptr == tmp_data) {
    LOG_ERROR("Invalid value type. field name=%s, type=%d, but given=%d", field->name(), field->type(), value.type);
    return RC::SCHEMA_FIELD_TYPE_MISMATCH;
  }
  ret.type = value.type;
  ret.data = tmp_data;
  return RC::SUCCESS;
}
