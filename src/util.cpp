// Copyright 2019 Cartesi Pte. Ltd.
//
// Licensed under the Apache License, Version 2.0 (the "License"); you may not
// use this file except in compliance with the License. You may obtain a copy of
// the License at http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
// WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
// License for the specific language governing permissions and limitations under
// the License.
//

#include <string.h>

#include "util.h"

volatile extern uint64_t tohost;
volatile extern uint64_t fromhost;

static char digits[] = "0123456789abcdef";

int ulltoa(char *str, unsigned long long value, int base)
{
    int p = 0, i = 0, j = 0;
    char c;

    if (base != 10 && base != 16)
        return -1;

    do {
        str[p++] = digits[value % base];
    } while (value /= base);
    str[p] = '\0';

    // reversing
    for (i = 0, j = p-1; i < j; i++, j--) {
	c = str[i];
	str[i] = str[j];
	str[j] = c;
    }
    return p - 1;
}

void do_tohost(uint64_t tohost_value)
{
	while (tohost)
		fromhost = 0;
	tohost = tohost_value;
}

void cputchar(int x)
{
	do_tohost(0x0101000000000000 | (unsigned char)x);
}

void cputs(const char* s)
{
	while (*s)
		cputchar(*s++);
}

