# Prereqs: grub-pc-bin, xorriso, mtools, qemu-system-i386, nasm, gcc, ld, grub-mkrescue
# Prereqs: gcc-multilib, binutils-multilib

NAME = kfs

CC = gcc
CFLAGS = -m32 -fno-pic -fno-pie -ffreestanding -fno-stack-protector -fno-builtin -fno-stack-protector -fno-omit-frame-pointer -fno-optimize-sibling-calls -nostdlib -nodefaultlibs -Wall -Wextra -Werror -Iinclude
ASM = nasm
ASMFLAGS = -f elf32

GRUBMKRESCUE:= grub-mkrescue
GRUBMKRESCUEFLAGS := --compress=xz
GRUB_BIOS_DIR ?= /usr/lib/grub/i386-pc

LD = ld
LDFLAGS = -m elf_i386 -T linker.ld

QEMU        := qemu-system-i386

BUILD_DIR   := build
ISO_DIR     := iso
BOOT_DIR    := grub
KERNEL_DIR  := kernel
DRIVERS_DIR := drivers

KERNEL      := kernel.bin
ISO_IMAGE   := os.iso

OBJCOPY		:= objcopy

SRCS_S        := \
               $(BOOT_DIR)/multiboot.asm \

SRCS_C       := $(KERNEL_DIR)/kmain.c \
						$(KERNEL_DIR)/kernel_printf.c \
						$(KERNEL_DIR)/kernel_shell.c \
						$(DRIVERS_DIR)/term.c \
						$(DRIVERS_DIR)/scroller.c \
						$(DRIVERS_DIR)/keyboard.c \

OBJS_S     := $(SRCS_S:%.asm=$(BUILD_DIR)/%.asm.o)
OBJS_C     := $(SRCS_C:%.c=$(BUILD_DIR)/%.c.o)
OBJS       := $(OBJS_S) $(OBJS_C)

all: $(KERNEL)

$(KERNEL): $(OBJS) linker.ld
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

$(BUILD_DIR)/%.asm.o: %.asm
	@mkdir -p $(dir $@)
	$(ASM) $(ASMFLAGS) $< -o $@

$(BUILD_DIR)/%.c.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

iso: $(ISO_IMAGE)

$(ISO_IMAGE): $(KERNEL) grub/grub.cfg
	@mkdir -p $(ISO_DIR)/boot/grub
	cp $(KERNEL) $(ISO_DIR)/boot/kernel.bin
	cp grub/grub.cfg $(ISO_DIR)/boot/grub/
	$(GRUBMKRESCUE) $(GRUBMKRESCUEFLAGS) -o $@ $(ISO_DIR)

run-iso: $(ISO_IMAGE)
	$(QEMU) -cdrom $(ISO_IMAGE)

size:
	@ls -lh $(KERNEL) $(ISO_IMAGE)
	@stat -c "%n %s bytes" $(KERNEL) $(ISO_IMAGE)

clean:
	rm -rf $(BUILD_DIR)
	rm -f $(OBJS) *.o $(BOOT_DIR)/*.o

fclean: clean
	rm -f $(KERNEL) kernel.elf $(ISO_IMAGE)
	rm -rf $(ISO_DIR)

re: fclean all

.PHONY: all clean fclean re
