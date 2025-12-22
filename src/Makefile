# Build Related Stuff

CC=riscv64-none-elf-gcc																				# Cross Compiler
CFLAGS=-ffreestanding -nostartfiles -nostdlib -nodefaultlibs  # Compiler in freestanding mode for kernel compilation
CFLAGS+=-g -Wl,--gc-sections -mcmodel=medany									# Linker Flags (Remove unused sections, Medium memory model)

RUNTIME=kernel/entry.S																			
LINKER_SCRIPT=kernel/linker.ld
KERNEL_IMAGE=kmain



# QEMU Setup
QEMU=qemu-system-riscv64
MACH=virt                                         # QEMU Machine Type = Virtual
MEM=128M                                          # QEMU Memory Size

RUN=$(QEMU) -nographic -machine $(MACH) -m $(MEM) # -nographic coz no graphical drivers, straight to our terminal
RUN+=-bios none -kernel $(KERNEL_IMAGE)



# # QEMU (debug)
# GDB_PORT=1234



all: uart syscon common kmain
	$(CC) *.o $(RUNTIME) $(CFLAGS) -T $(LINKER_SCRIPT) -o $(KERNEL_IMAGE)

uart:
	$(CC) -c kernel/uart.c -o uart.o $(CFLAGS)

syscon:
	$(CC) -c kernel/syscon.c -o syscon.o $(CFLAGS)

common:
	$(CC) -c kernel/common.c -o common.o $(CFLAGS)

kmain:
	$(CC) -c kernel/kmain.c -o kmain.o $(CFLAGS)

run: all
	$(RUN)

# debug: all
# 	$(RUN) -s -S

clean:
	rm -vf *.o $(KERNEL_IMAGE)
