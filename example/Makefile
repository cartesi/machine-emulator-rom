RVCC  = riscv64-linux-gnu-gcc-8
RVCOPY = riscv64-linux-gnu-objcopy
RVDUMP = riscv64-linux-gnu-objdump
CFLAGS=-static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles

rom.bin: rom
	$(RVCOPY) -S -O binary rom rom.bin
	$(RVDUMP) -d rom > rom.dump

rom: rom.S ROM.ld
	$(RVCC) $(CFLAGS) -TROM.ld -o rom rom.S

clean:
	rm -rf rom rom.bin rom.dump

.PHONY: clean
