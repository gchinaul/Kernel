NAME        := kfs-1

ASM         := nasm
CC          := gcc
LD          := ld
GRUBMKRESCUE:= grub-mkrescue
GRUBMKRESCUEFLAGS := --compress=xz
QEMU        := qemu-system-i386

ASMFLAGS    := -f elf32
CFLAGS      := -m32 -ffreestanding -fno-stack-protector -fno-builtin -fno-stack-protector -nostdlib -nodefaultlibs -Wall -Wextra -Werror -Iinclude
LDFLAGS     := -m elf_i386 -T linker.ld

BUILD_DIR   := build
ISO_DIR     := iso
BOOT_DIR    := iso/boot
KERNEL_DIR  := kernel
DRIVER_DIR  := drivers

KERNEL      := kernel.bin
ISO_IMAGE   := os.iso

GRUB_BIOS_DIR ?= /usr/lib/grub/i386-pc

SRCS_S        := $(BOOT_DIR)/multiboot_header.s \
               $(BOOT_DIR)/boot.s \
               $(BOOT_DIR)/irq.s \
               $(BOOT_DIR)/gdt.s

SRCS_C        := $(BOOT_DIR)/kmain.c \
								$(KERNEL_DIR)/libft.c \
								$(KERNEL_DIR)/kprintf.c \
								$(KERNEL_DIR)/terminal.c \
								$(KERNEL_DIR)/cursor.c \
								$(DRIVER_DIR)/keyboard.c \
								$(DRIVER_DIR)/idt.c \
								$(DRIVER_DIR)/gdt.c

OBJS        := $(SRCS_S:%.s=$(BUILD_DIR)/%.o) $(SRCS_C:%.c=$(BUILD_DIR)/%.o)

.PHONY: all iso run run-iso check-env clean fclean re

all: $(KERNEL)

$(KERNEL): $(OBJS) linker.ld
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

$(BUILD_DIR)/%.o: %.s
	@mkdir -p $(dir $@)
	$(ASM) $(ASMFLAGS) $< -o $@

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

iso: $(ISO_IMAGE)

$(ISO_IMAGE): $(KERNEL) boot/grub/grub.cfg
	@if ! command -v $(GRUBMKRESCUE) >/dev/null 2>&1; then \
		echo "Error: $(GRUBMKRESCUE) introuvable."; \
		exit 1; \
	fi
	@if ! command -v mformat >/dev/null 2>&1; then \
		echo "Error: mformat (mtools) introuvable: impossible de generer l'ISO GRUB sans sudo."; \
		echo "Tip: utilise 'make run' (boot direct du kernel) sur les machines 42."; \
		exit 1; \
	fi
	@if [ ! -d "$(GRUB_BIOS_DIR)" ]; then \
		echo "Error: fichiers GRUB BIOS manquants dans $(GRUB_BIOS_DIR)."; \
		echo "Tip: essaie une autre machine du cluster ou un container configure."; \
		exit 1; \
	fi
	@mkdir -p $(ISO_DIR)/boot/grub
	cp $(KERNEL) $(ISO_DIR)/boot/
	cp boot/grub/grub.cfg $(ISO_DIR)/boot/grub/
	$(GRUBMKRESCUE) $(GRUBMKRESCUEFLAGS) -o $@ $(ISO_DIR)

run: $(KERNEL)
	$(QEMU) -kernel $(KERNEL)

run-iso: $(ISO_IMAGE)
	$(QEMU) -cdrom $(ISO_IMAGE)

check-env:
	@echo "== tools =="
	@command -v $(ASM) >/dev/null 2>&1 && echo "OK: $(ASM)" || echo "KO: $(ASM)"
	@command -v $(CC) >/dev/null 2>&1 && echo "OK: $(CC)" || echo "KO: $(CC)"
	@command -v $(LD) >/dev/null 2>&1 && echo "OK: $(LD)" || echo "KO: $(LD)"
	@command -v $(QEMU) >/dev/null 2>&1 && echo "OK: $(QEMU)" || echo "KO: $(QEMU)"
	@command -v $(GRUBMKRESCUE) >/dev/null 2>&1 && echo "OK: $(GRUBMKRESCUE)" || echo "KO: $(GRUBMKRESCUE)"
	@command -v mformat >/dev/null 2>&1 && echo "OK: mformat" || echo "KO: mformat (mtools)"
	@[ -d "$(GRUB_BIOS_DIR)" ] && echo "OK: $(GRUB_BIOS_DIR)" || echo "KO: $(GRUB_BIOS_DIR)"

clean:
	rm -rf $(BUILD_DIR)
	rm -f $(OBJS) *.o $(BOOT_DIR)/*.o
	rm -f $(BOOT_DIR)/kernel.bin

fclean: clean
	rm -f $(KERNEL) $(ISO_IMAGE)

re: fclean all

