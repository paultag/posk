/**
 * Sets up the multiboot spec to make our kenrel bootable
 * This is all documented in the multiboot spec.
 * Wana know where that is?
 *
 * Website:
 *  http://www.gnu.org/software/grub/manual/multiboot/multiboot.html
 *
 * Pray the GNU faries have not changed the web layout. A-fucking-gain.
 * @file multiboot.h
 */

#include <types.h>

#ifndef MULTIBOOT_H_
#define MULTIBOOT_H_ MAYBE

#define MULTIBOOT_FLAG_MEM     0x001
#define MULTIBOOT_FLAG_DEVICE  0x002
#define MULTIBOOT_FLAG_CMDLINE 0x004
#define MULTIBOOT_FLAG_MODS    0x008
#define MULTIBOOT_FLAG_AOUT    0x010
#define MULTIBOOT_FLAG_ELF     0x020
#define MULTIBOOT_FLAG_MMAP    0x040
#define MULTIBOOT_FLAG_CONFIG  0x080
#define MULTIBOOT_FLAG_LOADER  0x100
#define MULTIBOOT_FLAG_APM     0x200
#define MULTIBOOT_FLAG_VBE     0x400


/**
 * Multiboot struct that gets pushed to the kernel as one big happy glob
 */
typedef struct {
	uint32_t flags;         /**< RTFM */
	uint32_t mem_lower;     /**< RTFM */
	uint32_t mem_upper;     /**< RTFM */
	uint32_t boot_device;   /**< RTFM */
	uint32_t cmdline;       /**< RTFM */
	uint32_t mods_count;    /**< RTFM */
	uint32_t mods_addr;     /**< RTFM */
	uint32_t num;           /**< RTFM */
	uint32_t size;          /**< RTFM */
	uint32_t addr;          /**< RTFM */
	uint32_t shndx;         /**< RTFM */
	uint32_t mmap_length;   /**< RTFM */
	uint32_t mmap_addr;     /**< RTFM */
	uint32_t drives_length; /**< RTFM */
	uint32_t drives_addr;   /**< RTFM */
	uint32_t config_table;  /**< RTFM */
	uint32_t boot_loader_name; /**< RTFM */
	uint32_t apm_table;     /**< RTFM */
	uint32_t vbe_control_info; /**< RTFM */
	uint32_t vbe_mode_info; /**< RTFM */
	uint32_t vbe_mode;      /**< RTFM */
	uint32_t vbe_interface_seg; /**< RTFM */
	uint32_t vbe_interface_off; /**< RTFM */
	uint32_t vbe_interface_len; /**< RTFM */
} __attribute__((packed)) multiboot_t;

/**
 * The memory map that gets shoved down our kernel's throat.
 */
typedef struct {
	uint32_t size;           /**< RTFM */
	uint32_t base_addr_low;  /**< RTFM */
	uint32_t base_addr_high; /**< RTFM */
	uint32_t length_low;     /**< RTFM */
	uint32_t length_high;    /**< RTFM */
	uint32_t type;           /**< RTFM */
} __attribute__((packed)) mmap_entry_t;

#endif
