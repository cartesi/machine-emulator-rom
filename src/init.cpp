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

#include <stddef.h>

#include "util.h"
#include "device-tree.h"


extern "C" void *rom_init(struct pma *pma, char *rom_extra_space, void *fdtbuf, uint64_t buflen, uint64_t misa)
{
	// Check invalid values and if misa XLEN is 64bit
	if (pma == NULL || rom_extra_space == NULL || fdtbuf == NULL || buflen == 0 || !(misa & (1UL<<63)))
		return NULL;

	if (build_device_tree(pma, rom_extra_space, misa, fdtbuf, buflen) < 0)
		return NULL;

	return fdtbuf;
}
