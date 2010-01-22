%include "grub.inc" ; needed for the multiboot header

[BITS 32]

[global start]
[extern posk_start] ; this is in the c file

start:
  call posk_start
  cli
  hlt


; Multiboot header for GRUB bootloader. This must be in the first 8K
; these are in the linker script file
EXTERN code, bss, end

ALIGN 4
mboot:
	dd MULTIBOOT_HEADER_MAGIC
	dd MULTIBOOT_HEADER_FLAGS
	dd MULTIBOOT_CHECKSUM
; aout kludge. These must be PHYSICAL addresses
	dd mboot
	dd code
	dd bss
	dd end
	dd start
