# Copyright 2019 Cartesi Pte. Ltd.
#
# Licensed under the Apache License, Version 2.0 (the "License"); you may not
# use this file except in compliance with the License. You may obtain a copy of
# the License at http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
# License for the specific language governing permissions and limitations under
# the License.
#

RVCC  = riscv64-cartesi-linux-gnu-gcc
RVCOPY = riscv64-cartesi-linux-gnu-objcopy
RVDUMP = riscv64-cartesi-linux-gnu-objdump
CFLAGS=-static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles

rom.bin: rom
	$(RVCOPY) -S -O binary rom rom.bin
	$(RVDUMP) -d rom > rom.dump

rom: rom.S ROM.ld
	$(RVCC) $(CFLAGS) -TROM.ld -o rom rom.S

clean:
	rm -rf rom rom.bin rom.dump

.PHONY: clean
