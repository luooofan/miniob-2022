#include "util/typecast.h"
#include <cstdlib>
#include <cstring>

cast_func_ptr cast_to[AttrType::FLOATS + 1][AttrType::FLOATS + 1] = {{
                                                                         not_support,
                                                                         not_support,
                                                                         not_support,
                                                                         not_support,
                                                                         not_support,
                                                                     },
    {
        not_support,
        char_to_char,
        char_to_int,
        not_support,
        char_to_float,
    },
    {
        not_support,
        int_to_char,
        int_to_int,
        not_support,
        int_to_float,
    },
    {
        not_support,
        not_support,
        not_support,
        not_support,
        not_support,
    },
    {
        not_support,
        float_to_char,
        float_to_int,
        not_support,
        float_to_float,
    }};

void *identity(void *src)
{
  return src;
}
void *not_support(void *src)
{
  return nullptr;
}
void *int_to_int(void *src)
{
  return new int(*(int *)src);
}
void *int_to_float(void *src)
{
  return new float(*(int *)src);
}

void *int_to_char(void *src)
{
  int &s = *(int *)src;
  char *res = new char[11];
  sprintf(res, "%d", s);
  return res;
}

void *float_to_int(void *src)
{
  float &s = *(float *)src;
  return new int(s + 0.5);
}

void *float_to_char(void *src)
{
  float &s = *(float *)src;
  char *res = new char[33];
  memset(res, 0, 33 * sizeof(char));
  // sprintf(res, "%f", s);
  gcvt(s, 7, res);
  return res;
}

void *float_to_float(void *src)
{
  return new float(*(float *)src);
}

// make sure char* end with \0
void *char_to_int(void *src)
{
  char *s = (char *)src;
  int *res = new int(atoi(s));
  return res;
}

void *char_to_float(void *src)
{
  char *s = (char *)src;
  float *res = new float(atof(s));
  return res;
}

void *char_to_char(void *src)
{
  return new char[strlen((char *)src)];
}
