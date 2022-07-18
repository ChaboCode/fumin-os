#pragma once

// <stdbool.h>
// https://github.com/gcc-mirror/gcc/blob/master/gcc/ginclude/stdbool.h
#define bool	_Bool
#if defined __STDC_VERSION__ && __STDC_VERSION__ > 201710L
#define true	((_Bool)+1u)
#define false	((_Bool)+0u)
#else
#define true	1
#define false	0
#endif

// <stdint.h>
// https://github.com/gcc-mirror/gcc/blob/master/gcc/ginclude/stdint-gcc.h
#ifdef __INT8_TYPE__
typedef __INT8_TYPE__ int8_t;
#endif
#ifdef __INT16_TYPE__
typedef __INT16_TYPE__ int16_t;
#endif
#ifdef __INT32_TYPE__
typedef __INT32_TYPE__ int32_t;
#endif
#ifdef __INT64_TYPE__
typedef __INT64_TYPE__ int64_t;
#endif
#ifdef __UINT8_TYPE__
typedef __UINT8_TYPE__ uint8_t;
#endif
#ifdef __UINT16_TYPE__
typedef __UINT16_TYPE__ uint16_t;
#endif
#ifdef __UINT32_TYPE__
typedef __UINT32_TYPE__ uint32_t;
#endif
#ifdef __UINT64_TYPE__
typedef __UINT64_TYPE__ uint64_t;
#endif

#if !(defined (__GNUG__) && defined (size_t))
typedef __SIZE_TYPE__ size_t;
#ifdef __BEOS__
typedef long ssize_t;
#endif /* __BEOS__ */
#endif 

#define low_16(address) (uint16_t)((address) & 0xFFFF)
#define high_16(address) (uint16_t)(((address) >> 16) & 0xFFFF)

void memory_copy(uint8_t *source, uint8_t *dest, uint32_t nbytes);

void reverse(char s[]);

void int_to_string(int n, char str[]);
