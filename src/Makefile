BUILD_DIR ?= $(abspath ../build)
SRC_DIR ?= .

ifneq ($(EMULATOR_INC),)
EMULATOR_FLAGS= -I$(EMULATOR_INC)
endif

CC = riscv64-unknown-linux-gnu-gcc
CXX = riscv64-unknown-linux-gnu-g++
OBJCOPY=riscv64-unknown-linux-gnu-objcopy
OBJDUMP=riscv64-unknown-linux-gnu-objdump
CFLAGS=-static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -I$(BUILD_DIR)/include $(EMULATOR_FLAGS)
CXXFLAGS=-static -fno-exceptions -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -I$(BUILD_DIR)/include $(EMULATOR_FLAGS)

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