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

BUILD_DIR ?= $(abspath ../build)
SRC_DIR ?= .

ifneq ($(EMULATOR_INC),)
EMULATOR_FLAGS= -I$(EMULATOR_INC)
endif

CC = riscv64-cartesi-linux-gnu-gcc
CXX = riscv64-cartesi-linux-gnu-g++
OBJCOPY=riscv64-cartesi-linux-gnu-objcopy
OBJDUMP=riscv64-cartesi-linux-gnu-objdump
CFLAGS=-static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -I$(BUILD_DIR)/include $(EMULATOR_FLAGS)
CXXFLAGS=-static -fno-exceptions -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -I$(BUILD_DIR)/include $(EMULATOR_FLAGS)

ifeq ($(fd_emulation),yes)
CFLAGS += -DRISCV_SUPPORT_FD_EMULATION
CXXFLAGS += -DRISCV_SUPPORT_FD_EMULATION
endif

TARGET_EXEC ?= rom
FINAL_EXEC ?= $(TARGET_EXEC).bin

SRCS := $(shell find $(SRC_DIR) -name  "*.cpp" -or -name "*.c" -or -name "*.S")
OBJS := $(SRCS:%=$(SRC_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

LIBFDT := $(BUILD_DIR)/lib/libfdt.a

LDIN := rom.in.ld
LDOUT := $(BUILD_DIR)/rom.ld

INC_DIRS := $(shell find $(SRC_DIR) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS ?= $(INC_FLAGS) -MMD -MP
LDFLAGS ?= -T$(LDOUT)

all: $(BUILD_DIR) $(BUILD_DIR)/$(FINAL_EXEC)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/$(FINAL_EXEC): $(BUILD_DIR)/$(TARGET_EXEC)
	$(OBJDUMP) -d $(BUILD_DIR)/$(TARGET_EXEC) > $(BUILD_DIR)/$(TARGET_EXEC).dump
	$(OBJCOPY) -S -O binary $(BUILD_DIR)/$(TARGET_EXEC) $(BUILD_DIR)/$(FINAL_EXEC)

$(LDOUT): $(LDIN)
	$(CC) -E -x c $(CFLAGS) $(LDIN) | grep -v '^#' >> $(LDOUT)

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS) $(LDOUT)
	$(CC) $(OBJS) -o $@ $(LIBFDT) $(CFLAGS) $(LDFLAGS)

# assembly
$(SRC_DIR)/%.S.o: %.S
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# c source
$(SRC_DIR)/%.c.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# c++ source
$(SRC_DIR)/%.cpp.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@


.PHONY: all clean

clean:
	$(RM) -rf $(BUILD_DIR)/rom* $(SRC_DIR)/*.o $(SRC_DIR)/*.d

-include $(DEPS)
