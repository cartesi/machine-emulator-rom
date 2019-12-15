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

#ifndef DEVICE_TREE_H
#define DEVICE_TREE_H

#include <cstdint>

int build_device_tree(struct pma *pma, const char *bootargs, uint64_t misa, void *buf, uint64_t buflen);

#endif /* DEVICE_TREE_H */
