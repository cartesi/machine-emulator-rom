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

#ifndef UTIL_H
#define UTIL_H

#include <cstdint>

void do_tohost(uint64_t tohost_value);
void cputchar(int x);
void cputs(const char *s);
int ulltoa(char *str, unsigned long long value, int base);

#endif /* end of UTIL_H */
