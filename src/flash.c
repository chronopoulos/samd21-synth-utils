/*
Copyright (c) 2018 Chris Chronopoulos

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "flash.h"

void flash_init(void) {

	struct nvm_config config_nvm;
	nvm_get_config_defaults(&config_nvm);
	config_nvm.manual_page_write = false;
	nvm_set_config(&config_nvm);

}

void flash_write_rowAligned2(uint32_t rowNumber, const uint8_t *buffer, uint16_t nrows) {

    /* buffer must be exactly nrows long, else overrun will occur */

    enum status_code error_code;

    uint32_t rowAddress;
    const uint8_t *bufferPtr;

    int i, j;

    /* erase and then write one row at a time */
    for (i=0; i<nrows; i++) {

        rowAddress = (rowNumber + i) * FLASH_ROW_SIZE;
        bufferPtr = buffer + i*FLASH_ROW_SIZE;

        do {
            error_code = nvm_erase_row(rowAddress);
        } while (error_code == STATUS_BUSY);

        for (j=0; j<NVMCTRL_ROW_PAGES; j++) {
            do {
                error_code = nvm_write_buffer(rowAddress + j*NVMCTRL_PAGE_SIZE,
                                                bufferPtr + j*NVMCTRL_PAGE_SIZE, NVMCTRL_PAGE_SIZE);
            } while (error_code == STATUS_BUSY);
        }

    }

}

void flash_read_rowAligned(uint32_t rowNumber, uint8_t *buffer, uint16_t nrows) {

    /* buffer must be exactly nrows long, else overrun will occur */

    enum status_code error_code;

    do {
        error_code = nvm_read_buffer(rowNumber*FLASH_ROW_SIZE, buffer, nrows*FLASH_ROW_SIZE);
    } while (error_code == STATUS_BUSY);

}

void flash_read_rowAligned2(uint32_t rowNumber, uint8_t *buffer, uint16_t nrows) {

    enum status_code error_code;

    uint32_t rowAddress;
    uint8_t *bufferPtr;

    int i, j;

    /* erase and then write one row at a time */
    for (i=0; i<nrows; i++) {

        rowAddress = (rowNumber + i) * FLASH_ROW_SIZE;
        bufferPtr = buffer + i*FLASH_ROW_SIZE;

        for (j=0; j<NVMCTRL_ROW_PAGES; j++) {
            do {
                error_code = nvm_read_buffer(rowAddress + j*NVMCTRL_PAGE_SIZE,
                                                bufferPtr + j*NVMCTRL_PAGE_SIZE, NVMCTRL_PAGE_SIZE);
            } while (error_code == STATUS_BUSY);
        }

    }

}
