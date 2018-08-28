#include <nvm.h>

#define FLASH_ROW_SIZE (NVMCTRL_ROW_PAGES * NVMCTRL_PAGE_SIZE) // should be 4*64 = 256 bytes
#define FLASH_ROW_OFFSET 512

void flash_init(void);
void flash_write_rowAligned(uint32_t, const uint8_t*, uint16_t);
void flash_write_rowAligned2(uint32_t, const uint8_t*, uint16_t);
void flash_read_rowAligned(uint32_t, uint8_t*, uint16_t);
void flash_read_rowAligned2(uint32_t, uint8_t*, uint16_t);

