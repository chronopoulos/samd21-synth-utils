PROJ_NAME = helloworld

ASF = /home/chrono/software/atmel/asf_3.42

SRC_DIR = src
INC_DIR = include
BLD_DIR = bin

CC=arm-none-eabi-gcc
LD=arm-none-eabi-ld
OBJCOPY=arm-none-eabi-objcopy
OBJDUMP=arm-none-eabi-objdump

CFLAGS = -mcpu=cortex-m0plus -mthumb
CFLAGS += -Wall -std=c11
CFLAGS += -O0
CFLAGS += -g
CFLAGS += -ffunction-sections -fdata-sections
CFLAGS += -Wl,--gc-sections -Wl,-Map=$(BLD_DIR)/$(PROJ_NAME).map
CFLAGS += -T $(ASF)/sam0/utils/linker_scripts/samd21/gcc/samd21g18au_flash.ld

CFLAGS += -D __SAMD21G18A__
CFLAGS += -D SYSTICK_MODE
CFLAGS += -D EXTINT_CALLBACK_MODE

ELF = $(BLD_DIR)/$(PROJ_NAME).elf
BIN = $(BLD_DIR)/$(PROJ_NAME).bin
LST = $(BLD_DIR)/$(PROJ_NAME).lst

########
# basics
########

SRCS += $(ASF)/sam0/utils/cmsis/samd21/source/gcc/startup_samd21.c
SRCS += $(ASF)/sam0/drivers/system/system.c
SRCS += $(ASF)/sam0/drivers/system/clock/clock_samd21_r21_da_ha1/gclk.c
SRCS += $(ASF)/sam0/drivers/system/clock/clock_samd21_r21_da_ha1/clock.c
SRCS += $(ASF)/sam0/drivers/system/pinmux/pinmux.c
SRCS += $(ASF)/common/utils/interrupt/interrupt_sam_nvic.c
SRCS += $(ASF)/sam0/drivers/sercom/sercom.c

INC_FLAGS += -I $(ASF)/sam0/utils
INC_FLAGS += -I $(ASF)/common/utils
INC_FLAGS += -I $(ASF)/thirdparty/CMSIS/Include
INC_FLAGS += -I $(ASF)/sam0/utils/preprocessor
INC_FLAGS += -I $(ASF)/sam0/utils/header_files
INC_FLAGS += -I $(ASF)/sam0/utils/cmsis/samd21/include
INC_FLAGS += -I $(ASF)/sam0/utils/cmsis/samd21/source
INC_FLAGS += -I $(ASF)/sam0/drivers/system
INC_FLAGS += -I $(ASF)/sam0/drivers/system/clock
INC_FLAGS += -I $(ASF)/sam0/drivers/system/clock/clock_samd21_r21_da_ha1
INC_FLAGS += -I $(ASF)/sam0/drivers/system/clock/clock_samd21_r21_da_ha1/module_config
INC_FLAGS += -I $(ASF)/sam0/drivers/system/pinmux
INC_FLAGS += -I $(ASF)/sam0/drivers/system/power/power_sam_d_r_h
INC_FLAGS += -I $(ASF)/sam0/drivers/system/reset/reset_sam_d_r_h
INC_FLAGS += -I $(ASF)/sam0/drivers/system/interrupt
INC_FLAGS += -I $(ASF)/sam0/drivers/system/interrupt/system_interrupt_samd21
INC_FLAGS += -I $(ASF)/sam0/drivers/sercom

#############
# API modules
#############

# port
INC_FLAGS += -I $(ASF)/sam0/drivers/port
SRCS += $(ASF)/sam0/drivers/port/port.c

# dac
INC_FLAGS += -I $(ASF)/sam0/drivers/dac
INC_FLAGS += -I $(ASF)/sam0/drivers/dac/dac_sam_d_c_h
SRCS += $(ASF)/sam0/drivers/dac/dac_sam_d_c_h/dac.c

# EXTINT module
INC_FLAGS += -I $(ASF)/sam0/drivers/extint
INC_FLAGS += -I $(ASF)/sam0/drivers/extint/module_config
INC_FLAGS += -I $(ASF)/sam0/drivers/system/interrupt
SRCS += $(ASF)/sam0/drivers/extint/extint_sam_d_r_h/extint.c
SRCS += $(ASF)/sam0/drivers/extint/extint_callback.c
SRCS += $(ASF)/sam0/drivers/system/interrupt/system_interrupt.c

# i2c
INC_FLAGS += -I $(ASF)/sam0/drivers/sercom/i2c
SRCS += $(ASF)/sam0/drivers/sercom/i2c/i2c_sam0/i2c_master.c

# NVM
INC_FLAGS += -I $(ASF)/sam0/drivers/nvm
SRCS += $(ASF)/sam0/drivers/nvm/nvm.c

####################
# samd21-synth-utils
####################

SRCS += $(SRC_DIR)/main.c
SRCS += $(SRC_DIR)/lfo.c
SRCS += $(SRC_DIR)/dacmux.c
SRCS += $(SRC_DIR)/gate.c
SRCS += $(SRC_DIR)/keyboard.c
SRCS += $(SRC_DIR)/buttons.c
SRCS += $(SRC_DIR)/state.c
SRCS += $(SRC_DIR)/portamento.c
SRCS += $(SRC_DIR)/leds.c
SRCS += $(SRC_DIR)/range.c
SRCS += $(SRC_DIR)/seq.c
SRCS += $(SRC_DIR)/arp.c
SRCS += $(SRC_DIR)/flash.c

INC_FLAGS += -I $(INC_DIR)

#########
# rules
#########

.PHONY: all flash clean

all: $(BIN)

$(BIN): $(ELF) $(LST)
	$(OBJCOPY) $< $@ -O binary

$(LST): $(ELF)
	$(OBJDUMP) -D $^ > $@

$(ELF): $(SRCS)
	mkdir -p $(BLD_DIR)
	$(CC) $(CFLAGS) $(INC_FLAGS) $^ -o $@

flash:
	openocd -f openocd.cfg -c "program $(ELF) verify reset exit"

clean:
	rm -rf $(BLD_DIR)

