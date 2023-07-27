/* Copyright Cartesi and individual authors (see AUTHORS)
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#include <stddef.h>
#include <stdint.h>
#include <ctype.h>
#include <limits.h>


int memcmp(const void* s1, const void* s2, size_t n)
{
  // If s1 and s2 are aligned to uintptr_t
  if ((((uintptr_t)s1 | (uintptr_t)s2) & (sizeof(uintptr_t)-1)) == 0) {
    const uintptr_t* u1 = s1;
    const uintptr_t* u2 = s2;
    const uintptr_t* end = u1 + (n / sizeof(uintptr_t));
    while (u1 < end) {
      if (*u1 != *u2)
        break;
      u1++;
      u2++;
    }
    n -= (const void*)u1 - s1;
    s1 = u1;
    s2 = u2;
  }

  while (n--) {
    unsigned char c1 = *(const unsigned char*)s1++;
    unsigned char c2 = *(const unsigned char*)s2++;
    if (c1 != c2)
      return c1 - c2;
  }

  return 0;
}

void* memcpy(void* dest, const void* src, size_t len)
{
  // If dest, src and len are aligned to uintptr_t
  if ((((uintptr_t)dest | (uintptr_t)src | len) & (sizeof(uintptr_t)-1)) == 0) {
    const uintptr_t* s = src;
    uintptr_t *d = dest;
    while (d < (uintptr_t*)(dest + len))
      *d++ = *s++;
  } else {
    const char* s = src;
    char *d = dest;
    while (d < (char*)(dest + len))
      *d++ = *s++;
  }
  return dest;
}

void* memset(void* dest, int byte, size_t len)
{
  // If dest and len are aligned to uintptr_t
  if ((((uintptr_t)dest | len) & (sizeof(uintptr_t)-1)) == 0) {
    uintptr_t word = byte & 0xFF;
    word |= word << 8;
    word |= word << 16;
    word |= word << 16 << 16;

    uintptr_t *d = dest;
    while (d < (uintptr_t*)(dest + len))
      *d++ = word;
  } else {
    char *d = dest;
    while (d < (char*)(dest + len))
      *d++ = byte;
  }
  return dest;
}

void * memmove(void *dest, const void *src, size_t len)
{
  char *d = dest;
  char *s = (char *)src;
  if (d < s)
    while (len--)
      *d++ = *s++;
  else
    {
      char *lasts = s + (len-1);
      char *lastd = d + (len-1);
      while (len--)
        *lastd-- = *lasts--;
    }
  return dest;
}

size_t strnlen(const char *s, size_t maxlen)
{
  const char *p = s;
  while (*p && (p-s < maxlen))
    p++;
  return p - s;
}

size_t strlen(const char *s)
{
    return strnlen(s, ULONG_MAX);
}



