#include "util/typecast.h"

cast_func_ptr cast_to[4][4] = {{
                                   not_support,
                                   not_support,
                                   not_support,
                                   not_support,
                               },
    {
        not_support,
        identity,
        char_to_int,
        char_to_float,
    },
    {
        not_support,
        int_to_char,
        identity,
        int_to_float,
    },
    {
        not_support,
        float_to_char,
        float_to_int,
        identity,
    }};
void *identity(void *src)
{
  return src;
}
void *not_support(void *src)
{
  return nullptr;
}
void *int_to_float(void *src)
{
  float *res = new float(*(int *)src);
  return res;
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
  int *res = new int(s + 0.5);
  return res;
}

void *float_to_char(void *src)
{
  float &s = *(float *)src;
  char *res = new char[33];
  sprintf(res, "%f", s);
  return res;
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
