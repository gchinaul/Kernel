#pragma once
#ifndef KERNEL_H
#define KERNEL_H

#include "vga.h"
#include "stdarg.h"
#include "inline.h"
#include "type.h"
#include "libft.h"

// Banner
#include "banner.h"

// Tables
#include "tables/gdt.h"

// Kernel
#include "kernel/kernel_shell.h"
#include "kernel/kernel_shell_cmds.h"
#include "kernel/kernel_printf.h"

// Drivers
#include "drivers/term.h"
#include "drivers/keyboard.h"

#endif